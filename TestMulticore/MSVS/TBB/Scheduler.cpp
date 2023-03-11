#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-17-2012 15:23:44
/// @brief 
///        Task Scheduler 사용 설명 ( Tree 구조 )
///        1. Task 를 위한 메모리 할당 ( (overloaded) new() , tbb::task::allocate_root() )
///        2. Task 생성 및 초기화
///        3. Task Root 실행 ( tbb::task::spawn_root_and_wait() )
///        4. Task Business Logic 처리 ( tbb::task::execute() 재정의 )
///        
///        Task 는 Thread 를 비선점적으로 대응해 준다.
///
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <tbb/tbb.h>
#include <tbb/task.h>
#include <iostream>
#include <time.h>
#include <array>
#include <queue>
#include <ppl.h>
#include <concurrent_queue.h>
#include <algorithm>
#include <tbb/task_scheduler_init.h>

const int g_nCutOff = 16;

long SerialFib(long n)
{
	if (n < 2)
		return n;
	else
		return SerialFib(n - 1) + SerialFib(n - 2);
}

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-17-2012 17:30:01
/// @brief Task normal 사용 구조 ( Blocking 형태 )
///
///
///////////////////////////////////////////////////////////////////////////////

class CFibTask1 : public tbb::task
{
public:
	const long m_n;
	long *const m_pnSum;


public:
	CFibTask1( long n, long *sum ) : m_n(n), m_pnSum(sum) { return; }

	// Task 주 행위를 재정의
	tbb::task* execute ()
	{
		if ( m_n < g_nCutOff )
		{
			*m_pnSum = SerialFib( m_n );
		}
		else
		{
			long x, y;
			CFibTask1 &a = *new ( this->allocate_child() ) CFibTask1 (m_n - 1, &x);
			CFibTask1 &b = *new ( this->allocate_child() ) CFibTask1 (m_n - 2, &y);

			this->set_ref_count( 3 ); // ref count 3 설정 ( child task 2개 + 대기 1개 )

			this->spawn( b ); // b task 실행 시작 !!!

			this->spawn_and_wait_for_all( a ); // a 의 실행을 시작하고 모든 child task 들에 대해 대기 설정

			*m_pnSum = x + y; // 합 계산
		}

		return NULL;
	}
};

long ParallelFib(long n)
{
	long sum;
	CFibTask1& a = *new ( tbb::task::allocate_root() ) CFibTask1(n, &sum);
	tbb::task::spawn_root_and_wait( a );
	return sum;
}

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-17-2012 17:30:01
/// @brief Task Continuation 사용 구조 ( Non-Blocking 형태 )
///
///
///////////////////////////////////////////////////////////////////////////////

class CFibContinuation : public tbb::task
{
public:
	long *const m_pnSum;
	long m_nX, m_nY;

	CFibContinuation(long *pnSum) : m_pnSum(pnSum), m_nX(0), m_nY(0) { return; }

	tbb::task* execute()
	{
		*m_pnSum = m_nX + m_nY;
		return NULL;
	}
};


class CFibTask2 : public tbb::task
{
public:
	const long m_n;
	long *const m_pnSum;


public:
	CFibTask2( long n, long *sum ) : m_n(n), m_pnSum(sum) { return; }

	// Task 주 행위를 재정의
	tbb::task* execute ()
	{
		if ( m_n < g_nCutOff )
		{
			*m_pnSum = SerialFib( m_n );
		}
		else
		{
			CFibContinuation &c = *new ( this->allocate_continuation() ) CFibContinuation (m_pnSum);

			CFibTask2 &a = *new ( c.allocate_child() ) CFibTask2 (m_n - 1, &c.m_nX);
			CFibTask2 &b = *new ( c.allocate_child() ) CFibTask2 (m_n - 2, &c.m_nY);

			c.set_ref_count( 2 ); // ref count 2 설정 ( child task 2개 )

			c.spawn( b ); // b task 실행 시작 !!!
			c.spawn( a ); // a task 실행 시작 !!!

			return NULL;
		}

		return NULL;
	}
};

long ParallelFibContinuation(long n)
{
	long sum;
	CFibTask2& a = *new ( tbb::task::allocate_root() ) CFibTask2(n, &sum);
	tbb::task::spawn_root_and_wait( a );
	return sum;
}


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_TaskScheduler.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-17-2012 15:32:49
///////////////////////////////////////////////////////////////////////////////

void TestTBB_TaskScheduler()
{
	{
		tbb::task_scheduler_init();

		// Task normal 구조 처리
		ParallelFib ( 20 );

		_getch();
	}

	{
		tbb::task_scheduler_init();

		// Task Continuation 구조 처리
		ParallelFibContinuation ( 20 );

		_getch();
	}
}