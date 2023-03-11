#pragma once

///////////////////////////////////////////////////////////////////////////////
/// @file Header TBB_TestFunction.h
/// @brief 
/// 
/// @author justin
/// @date 8-7-2012 13:49:17
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-10-2012 12:02:11
/// @brief TBB 주요 개념 설명
/*
    TBB Main: http://threadingbuildingblocks.org/
	TBB Doc: http://threadingbuildingblocks.org/docs/help/

	* Single Thread Based Performance 예측 정보

	  Performance = CPU Command Count * Command Processing Time

	* Multi Thread Based Performance 예측 정보

	  Single 처리 보다 향상 되는 비율  = 1 / ( 1 - 병렬 처리 비율 ) + 병렬 처리 비율 / ( 스레드 갯수 + 프로세서 종류 + 코어 갯수 )

	* Concurrent Container
	  
	  잠금 기능을 제공 하는 container !!!
	  정교한 잠금: 하나의 컨테이너에 여러 스레드들이 함께 접근 할 때 필요한 영역만 잠금
	  잠금이 없는 알고리즘: 서로 다른 스레드들이 잠금 없이 (lock-free) 작업을 통해 처리

	* DeadLock & Race Condition

	  DeadLock: 동기화 객체에 접근 하는 thread 가 2개 이상 병목 되는 현상
	  Race Condition: 동일한 변수에 2개 이상의 thread 가 접근하여 값에 변화를 주어 해당 변수와 관련된 로직에 영향을 주는 현상

	* Task Scheduler & Group
      	                   
*/
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_TestFunction.h
/// @title Multi-Core 관련 주요 테스트를 위한 Compile 설정 정의
/// @brief 
/// 
/// @author justin
/// @date 8-16-2012 22:35:09
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define TBB_USE_DEBUG 1 // TBB Debug 활성화 설정
#endif//_DEBUG

#define NOMINMAX // TBB 와 <Windows.h> ( min , max , <limits> , <algorithm> ) 간에
                 // 중복 정의된 코드를 제외 시켜 줌.

//#define DEF_TBB_MEMORY_ALLOCATOR_ON // TBB 의 scalable_malloc , scalable_free 사용
//#define DEF_TBB_MEMORY_ALLOCATOR_LOG_ON // TBB 의 scalable_malloc , scalable_free 호출시 로그 출력





///////////////////////////////////////////////////////////////////////////////
/// @file Header TBB_TestFunction.h
/// @brief TBB Test function 목록
/// 
/// @author justin
/// @date 8-17-2012 14:07:27
///////////////////////////////////////////////////////////////////////////////

/// @brief TBB 초기화 예제 - justin 8/8/2012 10:30:37
void TestTBB_Init();


/// @brief TBB alorithm 예제 - justin 8/8/2012 13:16:13
void TestTBB_ParallelFor();
void TestTBB_ParallelForEach();
void TestTBB_ParallelInvoke();
void TestTBB_ParallelReduce();
void TestTBB_ParallelWhile();
void TestTBB_ParallelSort();
void TestTBB_OverlappedParallel();


/// @brief TBB concurrent container 예제 - justin 8/14/2012 16:35:29
void TestTBB_ConcurrentQueue();
void TestTBB_ConcurrentPriorityQueue();
void TestTBB_ConcurrentVector();
void TestTBB_ConcurrentHashMap();
void TestTBB_ConcurrentUnorderedMap();


/// @brief TBB memory allocator 예제 - justin 8/16/2012 17:43:51
void TestTBB_MemmoryAllocator();


/// @brief TBB Task 예제 - justin 8/17/2012 11:32:51
void TestTBB_TaskScheduler();
void TestTBB_TaskGroup();


/// @brief TBB Sync object 예제 - justin 8/18/2012 5:15:51
void TestTBB_Mutex();
void TestTBB_Atomic();
void TestTBB_Combinable();