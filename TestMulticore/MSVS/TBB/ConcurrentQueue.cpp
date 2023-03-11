#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:42:56
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <deque>
#include <tbb/concurrent_queue.h>
#include <array>
#include <tbb/task_scheduler_init.h>
#include <process.h>
#include <tbb/tick_count.h>


volatile LONG g_lPushCount(0);
volatile LONG g_lPopCount(0);

// max element count in queue
#define MAX_ELEMENT_COUNT    100000

// generic STL double-ended queue - non-blocking support
static std::deque<int> g_stlDeq;
static CRITICAL_SECTION g_csLock;
static double g_dTotalSec;

// TBB concurrent queue - thread safe & non-blocking support
static tbb::concurrent_queue<int> g_tbbQue;

// TBB concurrent bounded queue - thread safe & blocking support
static tbb::concurrent_bounded_queue<int> g_tbbBndQue;


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-15-2012 1:43:30
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerBySTLDeque( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start Generic STL Deque Push - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		  ++n )
	{
		::EnterCriticalSection(&g_csLock);
		g_stlDeq.push_back( n );
		::LeaveCriticalSection(&g_csLock);

		::InterlockedIncrement(&g_lPushCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerBySTLDeque( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start Generic STL Deque Pop - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		)
	{
		::EnterCriticalSection(&g_csLock);
		if( true == g_stlDeq.empty() )
		{
			::LeaveCriticalSection(&g_csLock);
			continue;
		}

		nValue = g_stlDeq.front();
		g_stlDeq.pop_front();
		::LeaveCriticalSection(&g_csLock);

		++n;

		::InterlockedIncrement(&g_lPopCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-15-2012 1:43:30
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerByTBBBndQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Bounded Queue Push - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		n < 100000;
		++n )
	{
		g_tbbBndQue.push(n);

		::InterlockedIncrement(&g_lPushCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerByTBBBndQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Bounded Queue Pop - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		  ++n )
	{
		g_tbbBndQue.pop( nValue );

		::InterlockedIncrement(&g_lPopCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-15-2012 1:43:30
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerByTBBQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Queue Push - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		n < 100000;
		++n )
	{
		g_tbbQue.push(n);

		::InterlockedIncrement(&g_lPushCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerByTBBQueue( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Queue Pop - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		)
	{
		if( false == g_tbbQue.try_pop( nValue ) )
		{
			continue;
		}

		++n;

		::InterlockedIncrement(&g_lPopCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file ConcurrentQueue.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-16-2012 12:59:48
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ConcurrentQueue()
{
	///////////////////////////////////////////////////////////////////////////////
	/// @author justin
	/// @date 8-16-2012 0:06:57
	/// @brief 	unsafe 함수 형태는 2개 이상의 thread 로 접근시 안전하지 못한다 라는 의미.
	///			try_pop: 요소가 존재할 경우 요소와 true 를 반환, 빈 상태일 경우도 false 를 반환. ( non-blocking )
	///         
	///         성능 비교 결과: concurrent_bounded_queue > concurrent_queue > deque
	///////////////////////////////////////////////////////////////////////////////

	// 기본 예제
	{
		tbb::concurrent_queue<int> queue;

		for( int n = 0;
			 n < 10;
			 ++n )
		{
			queue.push(n);
		}

		for( auto itPos = queue.unsafe_begin();
			 itPos != queue.unsafe_end();
			 ++itPos )
		{
			std::cout << *itPos << "";
		}		
		std::cout << std::endl;
		
		int nTemp = 0;
		while(true)
		{
			if( true != queue.try_pop(nTemp) )
			{
				break;
			}

			std::cout << "Pop: " << nTemp << std::endl;
		}
		std::cout << std::endl;

		_getch();
	}

	// STL deque & concurrent_bounded_queue & concurrent_queue 성능 비교
	{
		{
			// generic deque 

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPushCount = 0;
			g_lPopCount = 0;

			g_dTotalSec = 0.0;

			::InitializeCriticalSection(&g_csLock);

			std::cout << "Generic STL Deque push & pop !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				 i < (int) aHandleArray.size(); 
				 ++i )
			{	
				unsigned aThreadID;
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerBySTLDeque, NULL, CREATE_SUSPENDED, &aThreadID);
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
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerBySTLDeque, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			::DeleteCriticalSection(&g_csLock);

			std::cout << "STLDeque Count: " << g_stlDeq.size() << std::endl;
			std::cout << "Total Push Count: " << g_lPushCount << std::endl;
			std::cout << "Total Pop Count: " << g_lPopCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}

		{
			// concurrent_bounded_queue

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPushCount = 0;
			g_lPopCount = 0;

			g_dTotalSec = 0;

			std::cout << "TBB Bounded Queue push & pop !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				 i < (int) aHandleArray.size(); 
				 ++i )
			{	
				unsigned aThreadID;
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerByTBBBndQueue, NULL, CREATE_SUSPENDED, &aThreadID);
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
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerByTBBBndQueue, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			std::cout << "TBBBoundedQueue Count: " << g_tbbBndQue.size() << std::endl;
			std::cout << "Total Push Count: " << g_lPushCount << std::endl;
			std::cout << "Total Pop Count: " << g_lPopCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}

		{
			// concurrent_queue

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPushCount = 0;
			g_lPopCount = 0;

			g_dTotalSec = 0;

			std::cout << "TBB Queue push & pop !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				 i < (int) aHandleArray.size(); 
				 ++i )
			{	
				unsigned aThreadID;
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerByTBBQueue, NULL, CREATE_SUSPENDED, &aThreadID);
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
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerByTBBQueue, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			std::cout << "TBBQueue Count: " << g_tbbQue.unsafe_size() << std::endl;
			std::cout << "Total Push Count: " << g_lPushCount << std::endl;
			std::cout << "Total Pop Count: " << g_lPopCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}
	}
}