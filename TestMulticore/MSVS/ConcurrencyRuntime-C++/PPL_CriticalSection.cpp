#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-18-2012 5:09:21
/// @brief 
///       
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ppl.h>

//number of iterations each thread performs
static const int NUM_ITERATIONS = 150000;
int number = 0;

//Demonstrates use of critical section
template<typename Mutex>
void FunctionA(Mutex &mtx)
{
	for( int i = 0; i < NUM_ITERATIONS; ++i)
	{
		Mutex::scoped_lock lock(mtx);
		++number;
	}
}

//Demonstrates use of critical section
template<typename Mutex>
void FunctionB(Mutex &mtx)
{
	for( int i = 0; i < NUM_ITERATIONS; ++i)
	{
		Mutex::scoped_lock lock(mtx);
		++number;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @file PPL_CriticalSection.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-17-2012 19:21:31
///////////////////////////////////////////////////////////////////////////////

void TestPPL_CriticalSection()
{
	// 기본 예제
	{
		Concurrency::critical_section mtx; // spin count 지정 할 수 없음 !!!

		Concurrency::parallel_invoke(
			                         [&] { FunctionA<Concurrency::critical_section>(mtx); },
			                         [&] { FunctionB<Concurrency::critical_section>(mtx); }
		                            );

		std::cout << "Final value of number:" << number << std::endl;

		_getch();
	}
}