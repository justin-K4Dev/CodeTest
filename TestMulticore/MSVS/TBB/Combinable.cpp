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
#include <algorithm>
#include <bitset>
#include <vector>
#include <tbb/combinable.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for_each.h>



///////////////////////////////////////////////////////////////////////////////
/// @file TBB_Combinable.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-17-2012 19:21:31
///////////////////////////////////////////////////////////////////////////////

void TestTBB_Combinable()
{
	// 기본 예제
	{
		tbb::combinable<int> g_nTotal;

		tbb::concurrent_vector<int> vtDataList;

		std::generate( vtDataList.begin(), vtDataList.end(), [] () -> int
		                                                     {
																 static int nValue = 0;
															     return ++nValue;
															 } );

		tbb::parallel_for_each( vtDataList.begin(), vtDataList.end(), [&] (int n)
		                                                              {
																		  g_nTotal.local() += vtDataList[n];
		                                                              } );

		int nTotalValue = g_nTotal.combine(std::plus<int>());

		std::cout << "TBB combinable - Total:" << nTotalValue << std::endl;

		system("pause");
	}
}