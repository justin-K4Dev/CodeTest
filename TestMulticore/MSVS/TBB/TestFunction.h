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
/// @brief TBB �ֿ� ���� ����
/*
    TBB Main: http://threadingbuildingblocks.org/
	TBB Doc: http://threadingbuildingblocks.org/docs/help/

	* Single Thread Based Performance ���� ����

	  Performance = CPU Command Count * Command Processing Time

	* Multi Thread Based Performance ���� ����

	  Single ó�� ���� ��� �Ǵ� ����  = 1 / ( 1 - ���� ó�� ���� ) + ���� ó�� ���� / ( ������ ���� + ���μ��� ���� + �ھ� ���� )

	* Concurrent Container
	  
	  ��� ����� ���� �ϴ� container !!!
	  ������ ���: �ϳ��� �����̳ʿ� ���� ��������� �Բ� ���� �� �� �ʿ��� ������ ���
	  ����� ���� �˰���: ���� �ٸ� ��������� ��� ���� (lock-free) �۾��� ���� ó��

	* DeadLock & Race Condition

	  DeadLock: ����ȭ ��ü�� ���� �ϴ� thread �� 2�� �̻� ���� �Ǵ� ����
	  Race Condition: ������ ������ 2�� �̻��� thread �� �����Ͽ� ���� ��ȭ�� �־� �ش� ������ ���õ� ������ ������ �ִ� ����

	* Task Scheduler & Group
      	                   
*/
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_TestFunction.h
/// @title Multi-Core ���� �ֿ� �׽�Ʈ�� ���� Compile ���� ����
/// @brief 
/// 
/// @author justin
/// @date 8-16-2012 22:35:09
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define TBB_USE_DEBUG 1 // TBB Debug Ȱ��ȭ ����
#endif//_DEBUG

#define NOMINMAX // TBB �� <Windows.h> ( min , max , <limits> , <algorithm> ) ����
                 // �ߺ� ���ǵ� �ڵ带 ���� ���� ��.

//#define DEF_TBB_MEMORY_ALLOCATOR_ON // TBB �� scalable_malloc , scalable_free ���
//#define DEF_TBB_MEMORY_ALLOCATOR_LOG_ON // TBB �� scalable_malloc , scalable_free ȣ��� �α� ���





///////////////////////////////////////////////////////////////////////////////
/// @file Header TBB_TestFunction.h
/// @brief TBB Test function ���
/// 
/// @author justin
/// @date 8-17-2012 14:07:27
///////////////////////////////////////////////////////////////////////////////

/// @brief TBB �ʱ�ȭ ���� - justin 8/8/2012 10:30:37
void TestTBB_Init();


/// @brief TBB alorithm ���� - justin 8/8/2012 13:16:13
void TestTBB_ParallelFor();
void TestTBB_ParallelForEach();
void TestTBB_ParallelInvoke();
void TestTBB_ParallelReduce();
void TestTBB_ParallelWhile();
void TestTBB_ParallelSort();
void TestTBB_OverlappedParallel();


/// @brief TBB concurrent container ���� - justin 8/14/2012 16:35:29
void TestTBB_ConcurrentQueue();
void TestTBB_ConcurrentPriorityQueue();
void TestTBB_ConcurrentVector();
void TestTBB_ConcurrentHashMap();
void TestTBB_ConcurrentUnorderedMap();


/// @brief TBB memory allocator ���� - justin 8/16/2012 17:43:51
void TestTBB_MemmoryAllocator();


/// @brief TBB Task ���� - justin 8/17/2012 11:32:51
void TestTBB_TaskScheduler();
void TestTBB_TaskGroup();


/// @brief TBB Sync object ���� - justin 8/18/2012 5:15:51
void TestTBB_Mutex();
void TestTBB_Atomic();
void TestTBB_Combinable();