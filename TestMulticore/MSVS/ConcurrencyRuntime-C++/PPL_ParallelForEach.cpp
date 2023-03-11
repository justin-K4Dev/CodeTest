#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:48:35
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <ppl.h>
#include <array>
#include <sstream>
#include <iostream>



///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ParallelForEach.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 4:28:09
///////////////////////////////////////////////////////////////////////////////

void TestPPL_ParallelForEach()
{
	{
		// Create an array of integer values.
		std::tr1::array<int, 5> values = { 1, 2, 3, 4, 5 };

		// Print each value in the array in parallel.
		Concurrency::parallel_for_each( values.begin(), values.end(), [] (int value) {
			                                                                             std::wstringstream ss;
			                                                                             ss << value << L' ';
			                                                                             std::wcout << ss.str();
		                                                                             }
		                              );

	}
}