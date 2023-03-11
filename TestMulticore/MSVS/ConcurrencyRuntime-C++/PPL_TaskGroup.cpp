#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-20-2012 22:58:35
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <windows.h>
#include <concrt.h>
#include <concrtrm.h>
#include <ppl.h>

class CWindowsEvent
{
public:
	HANDLE m_event;

public:
	CWindowsEvent()
	: m_event( ::CreateEvent(NULL, TRUE, FALSE, TEXT("WindowsEvent")) )
	{
	}

	~CWindowsEvent()
	{
		::CloseHandle(m_event);
	}

	void set()
	{
		::SetEvent(m_event);
	}

	void wait(int count = INFINITE)
	{
		::WaitForSingleObject(m_event, count);
	}
};

template < typename T >
void DoTaskGroup(T &e)
{
	//Create a Lambda Waiting for the Event
	auto task = [ &e ]  
	{  
		std::cout << "Waiting in a task for the event !!!" << std::endl;
		e.wait();
	}; 

	//Create a taskgroup and schedule multiple copies of the task
	Concurrency::task_group tg;  
	for( int i = 0; 
		i < 10; 
		++i )  
	{  
		tg.run( task );  
	}  

	//Sleep
	Sleep( 1000 );

	//Wait for the events
	std::cout << "Set the Event !!!" << std::endl;
	e.set();  

	//Wait for the tasks
	tg.wait();

	_getch();
}


///////////////////////////////////////////////////////////////////////////////
/// @file ConRT_TaskGroup.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-20-2012 22:58:41
///////////////////////////////////////////////////////////////////////////////

void TestPPL_TaskGroup()
{
	// 기본 예제
	{
		//Create a scheduler that uses two threads.
		Concurrency::CurrentScheduler::Create( Concurrency::SchedulerPolicy( 1, Concurrency::MaxConcurrency, 2 ) );  

		//Declare an Event
		CWindowsEvent e; // 2 Thread 대기후 빠져 나옴 !!!

		DoTaskGroup<CWindowsEvent>( e );
	}

	{
		//Create a scheduler that uses two threads.
		Concurrency::CurrentScheduler::Create( Concurrency::SchedulerPolicy( 1, Concurrency::MaxConcurrency, 2 ) );  

		//Declare an Event
		Concurrency::event e; // 다른 Task 를 모두 실행 시키고 처리

		DoTaskGroup<Concurrency::event>( e );
	}
}