#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-18-2012 21:21:19
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tbb/tbb.h>
#include <iostream>
#include <time.h>
#include <array>
#include <queue>
#include <ppl.h>
#include <concurrent_queue.h>
#include <algorithm>
#include <tbb/task_scheduler_init.h>


int Fib(int n) 
{
	if( n < 2 ) 
	{
		return n;
	} 
	else 
	{
		int x, y;
		tbb::task_group g;

		g.run( [&] { x = Fib( n - 1); } ); // spawn a task
		g.run( [&] { y = Fib( n - 2); } ); // spawn another task
		g.wait();                          // wait for both tasks to complete

		return x + y;
	}
}


const int MAX_LOOP = 10000000;
const int THREAD_COUNT = 4;


std::deque<int> deqTest;
tbb::concurrent_queue<int> queParallelTest1;
tbb::concurrent_bounded_queue<int> queParallelTest2;
Concurrency::concurrent_queue<int> queParallelTest3;


class CSync
{
private:  
	CRITICAL_SECTION cs;

public:  
	CSync()
	{ InitializeCriticalSection(&cs); }  
	~CSync()
	{ DeleteCriticalSection(&cs); }   
	
	void Lock()
	{ EnterCriticalSection(&cs); }  
	
	void Unlock()
	{ LeaveCriticalSection(&cs); }
}; 

CSync g_Sync;

DWORD WINAPI WorkerThread( LPVOID parameter )
{  
	g_Sync.Lock();  
	static INT64 nSum = 0;
	
	while(!deqTest.empty())  
	{
		nSum += deqTest.front();
		deqTest.pop_front();  
	}  
	g_Sync.Unlock();
	
	return 1;
} 

DWORD WINAPI ParallelWorkerThread( LPVOID parameter )
{  
	int nValue = 0;  
	static INT64 nSum = 0;  
	
	if((INT_PTR)parameter == 1)  
	{
		while(!queParallelTest1.empty())
		{
			if(queParallelTest1.try_pop(nValue))
				nSum+= nValue;
		}
	}  
	else if((INT_PTR)parameter == 2)  
	{    
		while(!queParallelTest2.empty())    
		{
			if(queParallelTest2.try_pop(nValue))
				nSum+= nValue;    
		}  
	}  
	else if((INT_PTR)parameter == 3)  
	{    
		while(!queParallelTest3.empty())    
		{      
			if(queParallelTest3.try_pop(nValue))        
				nSum+= nValue;    
		}  
	}   
	
	return 1;
}


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_TaskGroup.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-18-2012 15:42:36
///////////////////////////////////////////////////////////////////////////////

void TestTBB_TaskGroup()
{
	// 기본 예제
	{
		tbb::task_scheduler_init();

		int nNo = Fib( 100 );

		std::cout << "Fibonacci No: " << nNo << std::endl;
	}

	// 응용 예제
	{
		for( int i = 0; 
			 i < MAX_LOOP; 
			 ++i )  
		{    
			deqTest.push_back(i);    
			queParallelTest1.push(i);    
			queParallelTest2.push(i);
			queParallelTest3.push(i);  
		}

		tbb::task_scheduler_init();

		tbb::tick_count t0, t1;
	
		std::tr1::array<HANDLE, THREAD_COUNT> hThread = { 0, };

		std::cout << "Win 32 Thread API Test Start" << std::endl;

		t0 = tbb::tick_count::now();
		for( int i = 0; 
			 i < THREAD_COUNT; 
			 ++i )
		{
			hThread[i] = ::CreateThread( 0, 0, WorkerThread, nullptr, 0, 0 );  
		}  
		::WaitForMultipleObjects( THREAD_COUNT, hThread.data(), true, INFINITE);
		t1 = tbb::tick_count::now();

		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();

		std::cout << "TBB Task Group + concurrent_queue Test Start" << std::endl;

		tbb::task_group tasks1;

		t0 = tbb::tick_count::now();
		tasks1.run( [] { 
						  ParallelWorkerThread( (LPVOID) 1 );
					   }
				  );
		tasks1.wait();
		t1 = tbb::tick_count::now();

		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();

		std::cout << "TBB Task Group + concurrent_bounded_queue Test Start" << std::endl;

		tbb::task_group tasks2;

		t0 = tbb::tick_count::now();
		tasks1.run( [] { 
						  ParallelWorkerThread( (LPVOID) 2 );
					   }
				  );
		tasks1.wait();
		t1 = tbb::tick_count::now();

		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();

		std::cout << "TBB Task Group + PPL concurrent_queue Test Start" << std::endl;

		tbb::task_group tasks3;

		t0 = tbb::tick_count::now();
		tasks1.run( [] { 
						  ParallelWorkerThread( (LPVOID) 3 );
					   }
				  );
		tasks1.wait();
		t1 = tbb::tick_count::now();

		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;	
		std::cout << std::endl;

		_getch();
	}

}