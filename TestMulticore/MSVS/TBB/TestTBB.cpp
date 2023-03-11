// TestMultiCore.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TestFunction.h"

#define DEF_TBB_MEMORY_ALLOCATOR_ON

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
		/// @brief TBB Test function - justin 8/19/2012 3:02:29

	//	TestTBB_Init();

	//	TestTBB_ParallelFor();

	//  TestTBB_ParallelForEach();

    //  TestTBB_ParallelInvoke();

	//	TestTBB_ParallelReduce();

	//	TestTBB_ParallelWhile();

	//	TestTBB_ParallelSort();

	//	TestTBB_OverlappedParallel();

	//	TestTBB_ConcurrentQueue();

	//	TestTBB_ConcurrentVector();

	//	TestTBB_ConcurrentHashMap();

	//	TestTBB_ConcurrentUnorderedMap();

		TestTBB_MemmoryAllocator();

	//	TestTBB_Atomic();

	//	TestTBB_Mutex();

	//	TestTBB_TaskScheduler();

	//	TestTBB_TaskGroup();
	}

	return 0;
}

