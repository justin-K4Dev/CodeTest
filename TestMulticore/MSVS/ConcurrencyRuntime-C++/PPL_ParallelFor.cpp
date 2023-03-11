#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 15:29:40
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <ppl.h>
#include <array>
#include <sstream>
#include <iostream>


///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ParallelFor.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 15:29:44
///////////////////////////////////////////////////////////////////////////////
void TestPPL_ParallelFor()
{
	{
		// Print each value from 1 to 5 in parallel.
		Concurrency::parallel_for( 1, 6, [] (int value) {
				                                            std::wstringstream ss;
				                                            ss << value << L' '; 
															std::wcout << ss.str();
			                                            }
			                     );

		_getch();
	}
}