// TestMultiCore.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @file TestMultiCore.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 3:01:41
///////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	{
		/// @brief PPL Test function - justin 8/19/2012 3:02:29
	//	TestPPL_ConcurrentVector();

		TestPPL_ConcurrentQueue();

	//	TestPPL_ConcurrentUnorderedMap();

	//	TestPPL_ConcurrentUnorderedSet();

	//	TestPPL_ParallelFor();

	//	TestPPL_ParallelForEach();

	//	TestPPL_ParallelInvoke();

	//	TestPPL_ReaderWriterLock();

	//	TestPPL_CriticalSection();

	//	TestPPL_Combinable();

	//	TestPPL_TaskGroup();

	//	TestPPL_TaskScheduler();

	}

	{
		/// @brief AAL Test function - justin 8/19/2012 3:02:29
	//	TestAAL_AgentBasedApplication();
	}

	return 0;
}

