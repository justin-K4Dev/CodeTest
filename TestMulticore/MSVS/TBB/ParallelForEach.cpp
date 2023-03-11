#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:34:42
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <xfunctional>
#include <iterator>
#include <algorithm>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for_each.h>
#include <tbb/tick_count.h>


class SingleWork
{
private:
	int m_var;

public:
	SingleWork() { return; }
	SingleWork(int var) : m_var(var) { return; }

	void Process() 
	{
		// time killing
		for ( int i = 0; 
			  i < 10000; 
			  ++i)
		{
			m_var += i;
		}
	}

	void Release() 
	{
		delete this;
	}
};

SingleWork* AllocateInit()
{
	return new SingleWork( rand() );
}


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelForEach.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 18:18:03
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ParallelForEach()
{
	{
		tbb::task_scheduler_init();

 		tbb::tick_count t0, t1;

		// pointer type container
		std::vector<SingleWork*> vtJobList;
 
		// Generic STL algorithm
		std::generate_n(std::back_inserter(vtJobList), 50000, AllocateInit);   

		t0 = tbb::tick_count::now();
		std::for_each(vtJobList.begin(), vtJobList.end(), std::mem_fun(&SingleWork::Process));
		std::for_each(vtJobList.begin(), vtJobList.end(), std::mem_fun(&SingleWork::Release));
		t1 = tbb::tick_count::now();
		vtJobList.clear();

		std::cout << "Generic STL Use" << std::endl; 
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;   

		// parallel_for_each TBB algorithm
		std::generate_n(std::back_inserter(vtJobList), 50000, AllocateInit);    

		// Except for the function name and namespace are completely identical.
		t0 = tbb::tick_count::now();  
		tbb::parallel_for_each(vtJobList.begin(), vtJobList.end(), std::mem_fun(&SingleWork::Process));
		tbb::parallel_for_each(vtJobList.begin(), vtJobList.end(), std::mem_fun(&SingleWork::Release));
		t1 = tbb::tick_count::now();
		vtJobList.clear();

		std::cout << "TBB parallel_for_each Use" << std::endl; 
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;   
	}
}


