#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 15:30:35
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <ppl.h>
#include <string>
#include <iostream>

// Returns the result of adding a value to itself.
template <typename T>
T twice ( const T& t )
{
	return t + t;
}

///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ParallelInvoke.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 15:31:14
///////////////////////////////////////////////////////////////////////////////

void TestPPL_ParallelInvoke()
{
	{
		// Define several values.
		int n = 54;
		double d = 5.6;
		std::wstring s = L"Hello";

		// Call the twice function on each value concurrently.
		Concurrency::parallel_invoke(
			                            [&n] { n = twice(n); },
			                            [&d] { d = twice(d); },
			                            [&s] { s = twice(s); }
		                            );

		// Print the values to the console.
		std::wcout << n << L' ' << d << L' ' << s << std::endl;
	}

}