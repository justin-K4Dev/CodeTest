#include "stdafx.h"
#include "TestFunction.h"



///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelSort.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-13-2012 13:59:38
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tbb/parallel_sort.h>
#include <tbb/tick_count.h>
#include <algorithm>
#include <vector>

const int COUNT = 10000;

void TestTBB_ParallelSort()
{
	{
		// sort
		std::cout << "parallel_sort Algorithm !!!" << std::endl; 

		static const int LARGE_PRIME = 32364931;
		static const int SMALL_PRIME = 1040803;

		std::vector<int> vtDataList;
		std::vector<int> vtSTLSortList;
		std::vector<int> vtParallelSortList;

		vtDataList.resize(COUNT);

		int nValue = rand();
		for( int n = 0;
			n < COUNT;
			++n )
		{
			nValue = (nValue + LARGE_PRIME) % SMALL_PRIME;

			vtDataList[n] = nValue;
		}

		vtSTLSortList = vtDataList;
		vtParallelSortList = vtDataList;

		tbb::tick_count t0, t1;

		// STL Sort
		t0 = tbb::tick_count::now();
		std::sort(vtSTLSortList.begin(), vtSTLSortList.end());
		t1 = tbb::tick_count::now();

		std::cout << "Generic STL sort Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		// Parallel Sort
		t0 = tbb::tick_count::now();
		tbb::parallel_sort(vtParallelSortList.begin(), vtParallelSortList.end());
		t1 = tbb::tick_count::now();

		std::cout << "parallel_sort Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;
	}
}