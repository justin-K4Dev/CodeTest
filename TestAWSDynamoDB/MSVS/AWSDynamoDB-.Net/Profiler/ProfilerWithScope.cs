using System;
using System.Runtime;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Text;
using System.Linq;
using System.Xml.Linq;
using System.Reflection.Metadata;


using Helper;


namespace Profiler
{
	//============================================================================
	// 함수 스코프내에서만 성능을 체크해 주는 모듈
	//
	// author : kangms
	//============================================================================

	public static class ScopedProfileHelper
	{
		private static readonly object m_lock = new object();

		private static readonly ConcurrentDictionary<Int32/*thread_id*/, ThreadInfo> m_thread_infos = new ConcurrentDictionary<Int32, ThreadInfo>();
		private static bool m_is_enable = false;
		private static Helper.Timer m_stopwatch = new Helper.Timer(0.0f);

		public static void init(bool isEnable)
		{
			m_is_enable = isEnable;
		}

		public static bool isEnabled()
		{
			return m_is_enable == true;
		}

		public static void fillupMonitor(ref ProfileInfo monitor)
		{
			if (false == isEnabled())
			{
				return;
			}

			monitor.collect(out var named, out var scoped);
			{
				// 평균 내림차순으로
				{
					var results = new Dictionary<string, IProfileResult>();
					foreach (var each in m_thread_infos)
					{
						foreach(var top_profiler in each.Value.getTopProfiles())
						{
							var profiler_base = top_profiler as IProfiler;
							var to_check_key = profiler_base.getProfileKey();

							top_profiler.getResultAsElapsed(to_check_key, ref results);
						}
					}

					var sorted_results = results.Values.ToList();
					sorted_results.Sort(
						delegate (IProfileResult x, IProfileResult y)
						{
							if (x.getAvgTickPerFunc() == y.getAvgTickPerFunc())
							{
								return 0;
							}
							else if (x.getAvgTickPerFunc() > y.getAvgTickPerFunc())
							{
								return -1;
							}
							else
							{
								return 1;
							}
						}
					);

					foreach (var each in sorted_results)
					{
						scoped.AppendLine(each.toString());
					}
				}
			}
		}

		private static TProfiler begin<TProfiler>(string profileName, string profileKey)
			where TProfiler : class, IProfiler4Scope, new()
		{
            var thread = System.Threading.Thread.CurrentThread;
            var found_thread = findOrCreateThread<TProfiler>(thread, profileName, profileKey);
            if (found_thread == null)
            {
                return null;
            }

			return found_thread.begin<TProfiler>(profileName, profileKey) as TProfiler;
		}

		private static void end(IProfiler4Scope ender)
		{
            if (ender == null)
            {
                return;
            }

            var found_owner_thread = ender.getOwnerThreadInfo();
			found_owner_thread?.end(ender);
		}

		public static ThreadInfo findOrCreateThread<TProfiler>( System.Threading.Thread thread
			                                                  , string profileName, string profileKey)
			where TProfiler : class, IProfiler4Scope, new()
		{
			if (false == isEnabled())
			{
				return null;
			}

			lock (m_lock)
			{
				var thread_id = thread.ManagedThreadId;
				if (false == m_thread_infos.TryGetValue(thread_id, out var found))
				{
					found = new ThreadInfo();
					if(false == found.initThreadInfo<TProfiler>( thread_id, thread.Name
						                                       , profileName, profileKey))
					{
						return null;
					}

					if(false == m_thread_infos.TryAdd(thread_id, found))
					{
						return null;
					}
				}

				return found;
			}
		}

		public static Helper.Timer getStopwatchTimer()
		{
			return m_stopwatch;
		}

		public class Scoped<TProfiler> : IDisposable
			where TProfiler : class, IProfiler4Scope, new()
		{
			private bool m_disposed = false;
			private readonly TProfiler m_profiler = default(TProfiler);

			public Scoped(StackFrame stackFrame, string callName, bool isOn)
			{
				if (false == isEnabled() || isOn == false)
				{
					return;
				}

				var object_name = stackFrame.GetMethod().DeclaringType.FullName;
				var func_name = stackFrame.GetMethod().Name;

				var method_full_name = object_name + "." + func_name;
				var profile_key = method_full_name + "." + callName;

				var profile_name = $"CN:{callName}, MN:{method_full_name}, {System.IO.Path.GetFileName(stackFrame.GetFileName())}:{stackFrame.GetFileLineNumber()}";
				m_profiler = ScopedProfileHelper.begin<TProfiler>(profile_name, profile_key);
			}

			~Scoped()
			{
				Dispose(false);
			}

			public void Dispose()
			{
				Dispose(true);
				GC.SuppressFinalize(this);
			}

			public virtual void Dispose(bool disposing)
			{
				if (m_disposed == true)
				{
					return;
				}

				m_disposed = true;

				if (disposing)
				{
					if (m_profiler != null)
					{
						var thread_id = System.Threading.Thread.CurrentThread.ManagedThreadId;
						end(m_profiler);
					}
				}
			}

			public TProfiler getProfiler()
			{
				return m_profiler;
			}

		}//Scoped

		public class ThreadInfo
		{
			private readonly Stack<IProfiler4Scope> m_stack = new Stack<IProfiler4Scope>();
			private readonly List<IProfiler4Scope> m_top_profiles = new List<IProfiler4Scope>();

			private Int32 m_thread_id = 0;
			private string m_thread_name = string.Empty;

			private bool m_is_creating = true;

			public ThreadInfo() { }

			public bool initThreadInfo<TProfiler>( Int32 threadId, string threadName
											     , string profileName, string profileKey )
				where TProfiler : class, IProfiler4Scope, new()
			{
				m_thread_id = threadId;
				m_thread_name = threadName;

				var root = new TProfiler();
				if (false == root.onInitProfiler( profileName, profileKey
												, this, null ))
				{
					return false;
				}

				m_top_profiles.Add(root);
				m_stack.Push(root);

				return true;
			}

			public TProfiler begin<TProfiler>(string profileName, string profileKey)
				where TProfiler : class, IProfiler4Scope, new()
			{
				var current = getCurrentProfiler();
				if(null == current)
				{
					current = new TProfiler();
					if (false == current.onInitProfiler( profileName, profileKey
													   , this, null ))
					{
						return null;
					}

					m_top_profiles.Add(current);
					m_stack.Push(current);
				}
				else
				{
					if (false == isCreating())
					{
						current = current.findOrCreateChildProfiler(profileName, profileKey);
						if (null == current)
						{
							return null;
						}
					}
				}

				m_is_creating = false;

				current.onBegin();

				return current as TProfiler;
			}

			public void end(IProfiler4Scope profiler)
			{
				profiler.onEnd();
				m_stack.Pop();
			}

			public List<IProfiler4Scope> getTopProfiles()
			{
				return m_top_profiles;
			}

			private IProfiler4Scope getCurrentProfiler()
			{
				return m_stack.Count == 0 ? null : m_stack.Peek();
			}

			public bool isCreating() => m_is_creating;

			public Int32 getThreadId() => m_thread_id;

			public string getThreadName() => m_thread_name;
		}//ThreadInfo


		public abstract class ScopeProfiler<TProfileResult> : ProfilerBase<TProfileResult>, IProfiler4Scope
			where TProfileResult : IProfileResult, new()
		{
			private ScopedProfileHelper.ThreadInfo m_thread_info = null;
			private IProfiler4Scope m_parent = null;

			private readonly ConcurrentDictionary<string, IProfiler4Scope> m_child_profilers = new ConcurrentDictionary<string, IProfiler4Scope>();

			public ScopeProfiler() { }

			public virtual bool onInitProfiler( string profileName, string profileKey
											  , ScopedProfileHelper.ThreadInfo threadInfo
											  , IProfiler4Scope parent )
			{
				base.initProfiler( profileName, profileKey
					             , threadInfo.getThreadId(), threadInfo.getThreadName() );

				m_thread_info = threadInfo;
				m_parent = parent;

				return true;
			}

			public IProfiler4Scope findOrCreateChildProfiler(string profileName, string profileKey)
			{
				if (false == m_child_profilers.TryGetValue(profileKey, out var found))
				{
					found = newProfiler();
					if(false == found.onInitProfiler( profileName, profileKey
									  				, getOwnerThreadInfo(), this ))
					{
						return null;
					}

					if(false == m_child_profilers.TryAdd(profileKey, found))
					{
						return null;
					}
				}

				return found;
			}

			public virtual void onBegin()
			{
				incFuncCallCount();

				setTickBegin(ScopedProfileHelper.getStopwatchTimer().Elapsed.TotalMilliseconds);
			}

			public virtual void onEnd()
			{
				var elapsed = ScopedProfileHelper.getStopwatchTimer().Elapsed.TotalMilliseconds;

				addTickTotal(elapsed);

				updateTickMIn(elapsed);
				updateTickMax(elapsed);
			}

			private IProfiler4Scope newProfiler()
			{
				return Activator.CreateInstance(GetType()) as IProfiler4Scope;
			}

			public override void getResultAsElapsed(string toCheckKey, ref Dictionary<string, IProfileResult> profileResults)
			{
				base.getResultAsElapsed(toCheckKey, ref profileResults);

				foreach (var each in m_child_profilers)
				{
					each.Value.getResultAsElapsed(toCheckKey, ref profileResults);
				}
			}

			private string getDepthString()
			{
				var sb = new StringBuilder();

				IProfiler4Scope parent = m_parent;
				while (parent != null)
				{
					sb.Append('\t');
					parent = parent.getParentProfiler();
				}

				return sb.ToString();
			}

			public IProfiler4Scope getParentProfiler() => m_parent;

			public ScopedProfileHelper.ThreadInfo getOwnerThreadInfo() => m_thread_info;

		}//ScopeProfiler

	}//ScopedProfileHelper

}
