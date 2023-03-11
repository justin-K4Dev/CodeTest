using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;




namespace Profiler
{
	public class DBProfiler4Scope : ScopedProfileHelper.ScopeProfiler<DBProfileResult>
	{
		private Int32 m_db_transact_call_count = 0;

		public DBProfiler4Scope()
			: base()
		{ }

		public void incDBTransactCallCount()
		{
			m_db_transact_call_count++;
		}

		public Int32 getDBTransactCallCount() => m_db_transact_call_count;

	}//DBProfiler4Scope

	public class DBProfiler4Name : NamedProfileHelper.NamedProfiler<DBProfileResult>
	{
		private Int32 m_db_transact_call_count = 0;

		public DBProfiler4Name()
			: base()
		{ }

		public void incDBTransactCallCount()
		{
			m_db_transact_call_count++;
		}

		public Int32 getDBTransactCallCount() => m_db_transact_call_count;

	}//DBProfiler4Scope

	public class DBProfileResult : ProfileResultBase
	{
		private Int64 m_db_transact_call_count = 0;

		public DBProfileResult()
			: base()
		{ }

		public override void onCopyFromProfiler(IProfiler other)
		{
			base.onCopyFromProfiler(other);


			var transact_call_count = 0;

			if (true == other.GetType().Equals(typeof(DBProfiler4Scope)))
			{
				transact_call_count = (other as DBProfiler4Scope).getDBTransactCallCount();
			}
			else if (true == other.GetType().Equals(typeof(DBProfiler4Name)))
			{
				transact_call_count = (other as DBProfiler4Name).getDBTransactCallCount();
			}

			m_db_transact_call_count = transact_call_count;
		}

		public override void onMerge(IProfileResult other)
		{
			base.onMerge(other);

			var other_result = other as DBProfileResult;
			m_db_transact_call_count += other_result == null ? 0 : other_result.getDBTransactCallCount();
		}

		public override string toString()
		{
			return base.toString() + $", DBTransCallCount:{getDBTransactCallCount()}";
		}

		public Int64 getDBTransactCallCount() => m_db_transact_call_count;

	}//DBProfileResult
}
