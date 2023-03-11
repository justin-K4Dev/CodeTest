#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:44:12
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <tbb/concurrent_vector.h>
#include <array>
#include <tbb/task_scheduler_init.h>
#include <process.h>
#include <tbb/tick_count.h>

volatile LONG g_lPushBackCount(0);
volatile LONG g_lPopBackCount(0);

// max element count in queue
#define MAX_ELEMENT_COUNT    100000

// generic STL queue - non-blocking support
static std::vector<int> g_stlVec;
static CRITICAL_SECTION g_csLock;
static double g_dTotalSec;

// TBB concurrent vector - thread safe & non-blocking support
static tbb::concurrent_vector<int> g_tbbVec;


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentVector.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-15-2012 1:43:30
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerBySTLVector( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start Generic STL Vector PushBack - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		  ++n )
	{
		::EnterCriticalSection(&g_csLock);
		g_stlVec.push_back( n );
		::LeaveCriticalSection(&g_csLock);

		::InterlockedIncrement(&g_lPushBackCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerBySTLVector( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start Generic STL Vector PopBack - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		)
	{
		::EnterCriticalSection(&g_csLock);
		if( true == g_stlVec.empty() )
		{
			::LeaveCriticalSection(&g_csLock);
			continue;
		}

		nValue = g_stlVec.back();
		g_stlVec.pop_back();
		::LeaveCriticalSection(&g_csLock);

		++n;

		::InterlockedIncrement(&g_lPopBackCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentVector.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-16-2012 10:31:51
///////////////////////////////////////////////////////////////////////////////

unsigned int DoProducerByTBBVector( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Vector PushBack - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	for ( int n = 0;
		  n < 100000;
		  ++n )
	{
		::EnterCriticalSection(&g_csLock);
		g_tbbVec.push_back(n);
		::LeaveCriticalSection(&g_csLock);

		::InterlockedIncrement(&g_lPushBackCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

unsigned int DoConsumerByTBBVector( void *pvoid )
{
	tbb::tick_count t0, t1;

	::Sleep(1 * 1000);

	std::cout << "Start TBB Vector PopBack - Current Thread ID: " << ::GetCurrentThreadId() << std::endl;

	t0 = tbb::tick_count::now();
	int nValue = 0;
	for ( int n = 0;
		  n < MAX_ELEMENT_COUNT;
		)
	{
		::EnterCriticalSection(&g_csLock);
		if( true == g_tbbVec.empty() )
		{
			::LeaveCriticalSection(&g_csLock);
			continue;
		}

		nValue = g_tbbVec.back();
		g_tbbVec.resize(g_tbbVec.size() - 1);
		::LeaveCriticalSection(&g_csLock);
		++n;

		::InterlockedIncrement(&g_lPopBackCount);
	}
	t1 = tbb::tick_count::now();

	std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec - CurrentThreadID: " << ::GetCurrentThreadId() << std::endl;
	std::cout << std::endl;

	g_dTotalSec += ((t1 - t0).seconds() * 1000);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentVector.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-16-2012 11:22:07
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ConcurrentVector()
{
	///////////////////////////////////////////////////////////////////////////////
	/// @author justin
	/// @date 8-16-2012 0:09:41
	/// @brief concurrent_vector �� ��ҵ鿡 ���� ������ �϶����� ������ ��ü ũ�� ������ ���� �ϰ�
	///        ����� �ݺ��ڵ� ���� ���� ����. ������ �̷� ������ ������� ���ؼ� ������ ��ü ũ�� �����
	///        ���� ���� ����� �����Ƿ� ���� ������ �䱸 ���� �ʴ� �ٸ� ��� ���ϴ� �� ���� !!! 
	///
	///        ���� �� ���: concurrent_vector > vector
	///////////////////////////////////////////////////////////////////////////////

	// �⺻ ����
	{
		tbb::concurrent_vector<int> vtDataList;

		// ��� �߰�
		for ( int n = 0;
			  n < MAX_ELEMENT_COUNT;
			  ++n )
		{
			vtDataList.push_back( n );
		}

		std::cout << "Element count: " << vtDataList.size() << std::endl;

		// ������ ��� �߰�
		int nAddValue[5] = { MAX_ELEMENT_COUNT + 1, 
			                 MAX_ELEMENT_COUNT + 2, 
							 MAX_ELEMENT_COUNT + 3, 
							 MAX_ELEMENT_COUNT + 4, 
							 MAX_ELEMENT_COUNT + 5 };

		::memcpy( &vtDataList.grow_by( 5 ) , // grow_by() ���� 5 ���� ��Ұ� ������ ��ġ�� �߰� �� !!!
			      nAddValue,                 // ��ҳ��� �ʱⰪ�� 0
				  sizeof(int) * 5 );

		std::cout << "Called grow_by() -> Element count: " << vtDataList.size() << std::endl;
		std::cout << "Init value: " << vtDataList[vtDataList.size() - 1] << std::endl;

		// ������ ��� �߰�
		vtDataList.grow_to_at_least(MAX_ELEMENT_COUNT + 10); // ����� ũ�Ⱑ argument �� �� ���� ���� ��� 
			                                                 // argument �� ����ŭ ��Ҹ� �߰� �� !!!
		                                                     // ��ҳ��� �ʱⰪ�� 0

		std::cout << "Called grow_to_at_least() -> Element count: " << vtDataList.size() << std::endl;
		std::cout << "Init value: " << vtDataList[vtDataList.size() - 1] << std::endl;

		// ��� ��� & ����
		int nValue = vtDataList.back();
		vtDataList.resize(vtDataList.size() - 1); // ũ�⸦ ���� �Ͽ� ������ ��Ҹ� ���� !!!

		_getch();
	}

	// STL vector & concurrent_vector ���� ��
	{
		{
			// generic vector

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPushBackCount = 0;
			g_lPopBackCount = 0;

			g_dTotalSec = 0.0;

			::InitializeCriticalSection(&g_csLock);

			std::cout << "Generic STL Vector PushBack & PopBack !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				 i < (int) aHandleArray.size(); 
				 ++i )
			{	
				unsigned aThreadID;
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerBySTLVector, NULL, CREATE_SUSPENDED, &aThreadID);
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
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerBySTLVector, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			::DeleteCriticalSection(&g_csLock);

			std::cout << "STLVector Count: " << g_stlVec.size() << std::endl;
			std::cout << "Total PushBack Count: " << g_lPushBackCount << std::endl;
			std::cout << "Total PopBack Count: " << g_lPopBackCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}

		{
			// concurrent_vector

			tbb::task_scheduler_init aInit(10); 
			size_t aHndleCnt(0);
			std::tr1::array<HANDLE, 10> aHandleArray;

			g_lPushBackCount = 0;
			g_lPopBackCount = 0;

			g_dTotalSec = 0;

			::InitializeCriticalSection(&g_csLock);

			std::cout << "TBB Vector PushBack & PopBack !!!" << std::endl;
			std::cout << std::endl;

			for( int i = 0; 
				 i < (int) aHandleArray.size(); 
				 ++i )
			{	
				unsigned aThreadID;
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoProducerByTBBVector, NULL, CREATE_SUSPENDED, &aThreadID);
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
			
				aHandleArray[ aHndleCnt++ ] = (HANDLE) ::_beginthreadex(NULL, 0, DoConsumerByTBBVector, NULL, CREATE_SUSPENDED, &aThreadID);
			}

			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::ResumeThread);
			WaitForMultipleObjects((DWORD)aHandleArray.size(), aHandleArray.data(), TRUE, INFINITE);
			std::for_each(aHandleArray.begin(), aHandleArray.end(), ::CloseHandle);

			::DeleteCriticalSection(&g_csLock);

			std::cout << "TBBVector Count: " << g_tbbVec.size() << std::endl;
			std::cout << "Total PushBack Count: " << g_lPushBackCount << std::endl;
			std::cout << "Total PopBack Count: " << g_lPopBackCount << std::endl;
			std::cout << "Total Elapsed Time: " << g_dTotalSec << " msec" << std::endl;
			std::cout << std::endl;

			_getch();
		}
	}
}

