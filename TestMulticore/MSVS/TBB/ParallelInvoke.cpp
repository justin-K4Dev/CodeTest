#include "stdafx.h"
#include "TestFunction.h"



///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelInvoke.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-13-2012 13:59:38
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tbb/parallel_invoke.h>
#include <tbb/tick_count.h>
#include <algorithm>
#include <vector>


void bar(int n) 
{ 
	std::cout << "Called bar() - param: " << n << std::endl; 
}

class MyFunctor 
{
public:
	int arg;

public:
	MyFunctor(int a) : arg(a) { return; }

	void operator()() const { bar(arg); }
};

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelInvoke.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 5:13:14
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ParallelInvoke()
{

	// 기본 예제
	{
		// class use
		MyFunctor f(1);
		MyFunctor g(2);
		MyFunctor h(3);

		tbb::parallel_invoke( f, g, h );

		// lambda use
		tbb::parallel_invoke( [] { bar( 1 ); }, 
			                  [] { bar( 2 ); }, 
							  [] { bar( 3 ); }
						    );
	}
}