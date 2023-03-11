#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:41:42
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <deque>
#include <queue>
#include <tbb/concurrent_priority_queue.h>
#include <array>
#include <tbb/task_scheduler_init.h>
#include <process.h>
#include <tbb/tick_count.h>


volatile LONG g_lPriPushCount(0);
volatile LONG g_lPriPopCount(0);

// max element count in queue
#define MAX_ELEMENT_COUNT    100000

// 우선 순위 비교 사용자 정의 객체
class CPriorityCompare
{
public:
	bool operator() (const int& n1, const int& n2) const 
	{
		return n1 > n2;
	}
};

// generic STL priority queue - non-blocking support
static std::priority_queue<int, std::deque<int>, CPriorityCompare> g_stlPriQue;
static CRITICAL_SECTION g_csLock;
static double g_dTotalSec;

// TBB concurrent prioriity queue - thread safe & non-blocking support
static tbb::concurrent_priority_queue<int, CPriorityCompare> g_tbbPriQue;


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentPriorityQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-15-2012 1:43:30
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerBySTLPriQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start Generic STL Priority Queue Push - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		  ++n )
	{
		::EnterCriticalSection(&g_csLock);
		g_stlPriQue.push( n );
		::LeaveCriticalSection(&g_csLock);

		::InterlockedIncrement(&g_lPriPushCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerBySTLPriQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start Generic STL Priority Queue Pop - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		)
	{
		::EnterCriticalSection(&g_csLock);
		if( true == g_stlPriQue.empty() )
		{
			::LeaveCriticalSection(&g_csLock);
			continue;
		}

		nValue = g_stlPriQue.top();
		::LeaveCriticalSection(&g_csLock);

		++n;

		::InterlockedIncrement(&g_lPriPopCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentPriorityQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-15-2012 1:43:30
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerByTBBPriQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Priority Queue Push - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		n < 100000;
		++n )
	{
		g_tbbPriQue.push(n);

		::InterlockedIncrement(&g_lPriPushCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerByTBBPriQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Priority Queue Pop - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		  ++n )
	{
		if( false == g_tbbPriQue.try_pop( nValue ) )
		{
			continue;
		}

		++n;

		::InterlockedIncrement(&g_lPriPopCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentPriorityQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-16-2012 12:59:48
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ConcurrentPriorityQueue()
{
	///////////////////////////////////////////////////////////////////////////////
	/// @author justin
	/// @date 8-16-2012 0:06:57
	/// @brief 	try_pop: 요소가 존재할 경우 요소와 true 를 반환, 빈 상태일 경우도 false 를 반환. ( non-blocking )
	///         
	///         성능 비교 결과: concurrent_priority_queue > priority_queue
	///////////////////////////////////////////////////////////////////////////////

	// 기본 예제
	{
		tbb::concurrent_priority_queue<int, CPriorityCompare> priQueue;

		for( int n = 0;
			n < 10;
			++n )
		{
			priQueue.push(n);
		}

		int nTemp = 0;
		while(true)
		{
			if( true != priQueue.try_pop(nTemp) )
			{
				break;
			}

			std::cout << "Pop: " << nTemp << std::endl;
		}
		std::cout << std::endl;

		_getch();
	}

	// STL priority_queue & concurrent_priority_queue 성능 비교
	{
		{
			// generic priority_queue 

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPriPushCount = 0;
			g_lPriPopCount = 0;

			g_dTotalSec = 0.0;

			::InitializeCriticalSection(&g_csLock);

			std::cout << "Generic STL Priority Queue push & pop !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				i < (int) aHandleArray.size(); 
				++i )
			{	
				unsigned aThreadID;

				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerBySTLPriQueue, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			aHndleCnt = 0;

			for( int i = 0; 
				i < (int) aHandleArray.size();
				++i )
			{
				unsigned aThreadID;   

				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerBySTLPriQueue, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			::DeleteCriticalSection(&g_csLock);

			std::cout << "STLPriorityQueue Count: " << g_stlPriQue.size() << std::endl;
			std::cout << "Total Push Count: " << g_lPriPushCount << std::endl;
			std::cout << "Total Pop Count: " << g_lPriPopCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}

		{
			// concurrent_priority_queue

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPriPushCount = 0;
			g_lPriPopCount = 0;

			g_dTotalSec = 0;

			std::cout << "TBB Priority Queue push & pop !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				i < (int) aHandleArray.size(); 
				++i )
			{	
				unsigned aThreadID;

				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerByTBBPriQueue, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			aHndleCnt = 0;

			for( int i = 0; 
				i < (int) aHandleArray.size();
				++i )
			{
				unsigned aThreadID;   

				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerByTBBPriQueue, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			std::cout << "TBBPriorityQueue Count: " << g_tbbPriQue.size() << std::endl;
			std::cout << "Total Push Count: " << g_lPriPushCount << std::endl;
			std::cout << "Total Pop Count: " << g_lPriPopCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}
	}
}