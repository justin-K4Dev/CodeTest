using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Helper;


namespace Profiler
{
	//============================================================================
	// 함수 스코프를 벋어나서도 성능을 체크해 주는 모듈
	//
	// author : kangms
	//============================================================================

	public static class NamedProfileHelper
	{
		private static bool m_is_enable = false;
		private static Helper.Timer m_stopwatch = new Helper.Timer(0.0f);

		private static ConcurrentDictionary<string, IProfiler4Name> m_profilers = new ConcurrentDictionary<string, IProfiler4Name>();

		public static void init(bool isEnable)
		{
			m_is_enable = isEnable;
		}

		//=======================================================================================================
		// 프로파일을 시작한다. 시작 시각을 저장한다.
		//=======================================================================================================
		public static TProfiler begin<TProfiler>(string profileName, string profileKey)
			where TProfiler : class, IProfiler4Name, new()
		{
			var thread = System.Threading.Thread.CurrentThread;
			var found_profiler = findOrCreateProfiler<TProfiler>(profileName, thread) as TProfiler;
			if (found_profiler == null)
			{
				return null;
			}

			found_profiler.onBegin(profileKey);
			return found_profiler;
		}

		//=======================================================================================================
		// 프로파일을 종료한다. 시작시각에서 종료시각까지의 경과시간을 계산후 기록한다.
		// 호출횟수증가, 경과시간의 누적, 최소/최대값 갱신
		//=======================================================================================================
		public static void end(string profileName, string profileKey)
		{
            m_profilers.TryGetValue(profileName, out var found);
            found?.onEnd(profileKey);
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
					foreach (var each in m_profilers)
					{
						var profiler_base = each.Value as IProfiler;
						var to_check_key = profiler_base.getProfileName();

						each.Value.getResultAsElapsed(to_check_key, ref results);
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

		private static bool isEnabled()
		{
			return m_is_enable == true;
		}


		private static TProfiler findOrCreateProfiler<TProfiler>( string profileName, Thread currThread )
			where TProfiler : class, IProfiler4Name, new()
		{
			if (false == m_profilers.TryGetValue(profileName, out var found))
			{
				found = new TProfiler();

				found.onInitProfiler(profileName, currThread);

				m_profilers.TryAdd(profileName, found);
			}

			return found as TProfiler;
		}


		public abstract class NamedProfiler<TProfileResult> : ProfilerBase<TProfileResult>, IProfiler4Name
			where TProfileResult : IProfileResult, new()
		{
			private readonly ConcurrentDictionary<string, double> m_keys = new ConcurrentDictionary<string, double>();

			public NamedProfiler() { }

			public virtual bool onInitProfiler( string profileName, Thread currThread )
			{
				base.initProfiler( profileName, string.Empty
					             , currThread.ManagedThreadId, currThread.Name );

				return true;
			}

			public virtual void onBegin(string profileKey)
			{
				var begin_time = m_stopwatch.Elapsed.TotalMilliseconds;
				m_keys.TryAdd(profileKey, begin_time);
			}

			public virtual void onEnd(string profileKey)
			{
				if (false == m_keys.TryRemove(profileKey, out var ticks_begin))
				{
					return;
				}

				incFuncCallCount();

				var elapsed = (m_stopwatch.Elapsed.TotalMilliseconds - ticks_begin);

				addTickTotal(elapsed);

				updateTickMIn(elapsed);
				updateTickMax(elapsed);
			}

		}//ScopeProfiler


	}//NamedProfileHelper
}
