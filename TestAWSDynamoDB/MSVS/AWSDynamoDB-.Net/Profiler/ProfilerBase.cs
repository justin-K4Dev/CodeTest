using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;




namespace Profiler
{
	//============================================================================
	// 성능 체크 모듈의 공통적인 것들을 모아 두었다.
	//
	// author : kangms
	//============================================================================

	public abstract class IInfo
	{
		public abstract string toString();
		public abstract bool hasInfo();
	}

	public interface IProfiler
	{
		double getTickMax();

		double getTickMin();

		Int32 getFuncCallCount();

		double getTickTotal();

		string getThreadName();

		Int32 getThreadId();

		string getProfileKey();

		string getProfileName();
	}

	public interface IProfiler4Scope
	{
		bool onInitProfiler( string profileName, string profileKey
						   , ScopedProfileHelper.ThreadInfo threadInfo
						   , IProfiler4Scope parent);

		void onBegin();

		void onEnd();

		IProfiler4Scope findOrCreateChildProfiler(string profileName, string profileKey);

		void getResultAsElapsed(string toCheckKey, ref Dictionary<string, IProfileResult> profileResults);

		IProfiler4Scope getParentProfiler();

		ScopedProfileHelper.ThreadInfo getOwnerThreadInfo();
	}

	public interface IProfiler4Name
	{
		bool onInitProfiler( string profileName, Thread currThread );

		void onBegin(string profileKey);

		void onEnd(string profileKey);

		void getResultAsElapsed(string toCheckKey, ref Dictionary<string, IProfileResult> profileResults);

	}//IProfiler

	public interface IProfileResult
	{
		void onCopyFromProfiler(IProfiler other);

		void onMerge(IProfileResult other);

		double getAvgTickPerFunc();

		string toString();
	}//IProfileResult

	public class ProfileInfo : IInfo
	{
		private StringBuilder m_named_profile = new StringBuilder();
		private StringBuilder m_scoped_profile = new StringBuilder();

		public ProfileInfo() { }

		public void collect(out StringBuilder namedProfile, out StringBuilder scopedProfile)
		{
			namedProfile = m_named_profile;
			scopedProfile = m_scoped_profile;
		}

		public override bool hasInfo()
		{
			return m_named_profile.Length != 0 || m_scoped_profile.Length != 0;
		}

		public override string toString()
		{
			return string.Format("{0}\n{1}"
								, m_named_profile.ToString(), m_scoped_profile.ToString());
		}
	}//ProfileInfo

	public abstract class ProfilerBase<TProfileResult> : IProfiler
		where TProfileResult : IProfileResult, new()
	{
		private string m_profile_name = string.Empty;
		private string m_profile_key = string.Empty;

		private Int32 m_thread_id = 0;
		private string m_thread_name = string.Empty;

		private double m_ticks_total = 0;

		private Int32 m_function_call_count = 0;

		private double m_ticks_begin = 0;
		private double m_ticks_min = 999999;
		private double m_ticks_max = 0;

		public ProfilerBase() { }

		public void initProfiler( string profileName, string profileKey
			                    , Int32 threadId, string threadName)
		{
			m_profile_name = profileName;
			m_profile_key = profileKey;

			m_thread_id = threadId;
			m_thread_name = threadName;
		}

		public virtual void getResultAsElapsed(string toCheckKey, ref Dictionary<string, IProfileResult> profileResults)
		{
			var created_result = new TProfileResult();

			if (false == profileResults.TryGetValue(toCheckKey, out var found))
			{
				created_result.onCopyFromProfiler(this);
				profileResults.Add(toCheckKey, created_result);
			}
			else
			{
				found.onMerge(created_result);
			}
		}

		public double getTickMax() => m_ticks_max;

		protected void updateTickMax(double toTryTickMax) { m_ticks_max = Math.Max(m_ticks_max, toTryTickMax); }

		public double getTickMin() => m_ticks_min;

		protected void updateTickMIn(double toTryTickMin) { m_ticks_min = Math.Min(m_ticks_min, toTryTickMin); }

		public double getTickBegin() => m_ticks_begin;

		protected void setTickBegin(double tickBegin) { m_ticks_begin = tickBegin; }

		public Int32 getFuncCallCount() => m_function_call_count;

		protected void incFuncCallCount() => m_function_call_count++;

		public double getTickTotal() => m_ticks_total;

		protected void addTickTotal(double toAddTick) { m_ticks_total += toAddTick; }

		public string getThreadName() => m_thread_name;

		public Int32 getThreadId() => m_thread_id;

		public string getProfileKey() => m_profile_key;

		public string getProfileName() => m_profile_name;
	}//ProfilerBase

	public abstract class ProfileResultBase : IProfileResult
	{
		private string m_profile_name = string.Empty;
		private string m_profile_key = string.Empty;

		private Int32 m_thread_id = 0;
		private string m_thread_name = string.Empty;

		private double m_ticks_total = 0;

		private Int64 m_function_call_count = 0;

		private double m_ticks_min = 999999;
		private double m_ticks_max = 0;

		public ProfileResultBase()
		{ }

		public virtual void onCopyFromProfiler(IProfiler other)
		{
			m_profile_name = other.getProfileName();
			m_profile_key = other.getProfileKey();

			m_thread_id = other.getThreadId();
			m_thread_name = other.getThreadName();

			m_ticks_total = other.getTickTotal();

			m_function_call_count = other.getFuncCallCount();

			m_ticks_min = other.getTickMin();
			m_ticks_max = other.getTickMax();
		}

		public virtual void onMerge(IProfileResult other)
		{
			var other_result_base = other as ProfileResultBase;

			m_ticks_total += other_result_base.m_ticks_total;
			m_function_call_count += other_result_base.m_function_call_count;

			m_ticks_min = Math.Min(m_ticks_min, other_result_base.m_ticks_min);
			m_ticks_max = Math.Max(m_ticks_max, other_result_base.m_ticks_max);
		}

		public double getAvgTickPerFunc()
		{
			return m_function_call_count == 0 ? 0 : m_ticks_total / m_function_call_count;
		}

		public virtual string toString()
		{
			return string.Format( "ProfileName:{0}, TID:{6}, FuncCallCount:{1:#,0}, avgTickPerFunc:{2}, tickMin:{3}, tickMax:{4}, tickTotal:{5}"
								, m_profile_name
								, m_function_call_count
								, getAvgTickPerFunc().ToString("F3")
								, m_ticks_min.ToString("F3")
								, m_ticks_max.ToString("F3")
								, m_ticks_total.ToString("F3")
								, m_thread_id );
		}
	}//ProfileResultBase

	//============================================================================
	// 성능 모니터링을 위한 주요 정보들을 수집 하고 출력 하는 함수를 연결 한다.
	//
	// author : kangms
	//============================================================================

	public static class PerformanceMonitor
	{
		private static Helper.LogicPeriodicTimer m_monitor_timer;

		public static void start(Int32 monitorIntervalSec, Helper.LogicPeriodicTimer.FnFunction monitorUpdate)
		{
			m_monitor_timer = new Helper.LogicPeriodicTimer(monitorIntervalSec, monitorUpdate);
		}

		public static void stop()
		{
			m_monitor_timer.cancelTimer();
		}
	}//PerformanceMonitor
}
