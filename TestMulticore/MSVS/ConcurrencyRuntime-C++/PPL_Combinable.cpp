#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-21-2012 10:54:02
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <ppl.h>
#include <array>
#include <numeric>
#include <bitset>
#include <iostream>


// Calls the provided work function and returns the number of milliseconds 
// that it takes to call that function.
template <class Function>
__int64 time_call(Function&& f)
{
	__int64 begin = GetTickCount();
	f();
	return GetTickCount() - begin;
}

// Determines whether the input value is prime.
bool is_Prime(int n)
{
	if (n < 2)
		return false;

	for (int i = 2; i < n; ++i)
	{
		if ((n % i) == 0)
			return false;
	}

	return true;
}

const int limit = 40000;

///////////////////////////////////////////////////////////////////////////////
/// @file PPL_Combinable.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-21-2012 10:54:06
///////////////////////////////////////////////////////////////////////////////

void TestPPL_Combinable()
{
	{
		// Create an array object that contains 200000 integers.
		std::tr1::array<int, 200000> a;

		// Initialize the array such that a[i] == i.
		int n = 0;
		std::generate( a.begin(), a.end(), [&] {
			                                       return n++;
	    	                                   }
		             );

		int prime_sum;
		__int64 elapsed;

		// Compute the sum of the numbers in the array that are prime.
		elapsed = time_call( [&] {
			                         prime_sum = std::accumulate(a.begin(), a.end(), 0, [&] (int acc, int i) {
				                                                                                                 return acc + (is_Prime(i) ? i : 0);
			                                                                                                 }
									                            );
		                         }
		                   );

		std::wcout << prime_sum << std::endl;   
		std::wcout << L"serial time: " << elapsed << L" ms" << std::endl << std::endl;

		// Now perform the same task in parallel.
		elapsed = time_call([&] {
			                        Concurrency::combinable<int> sum;
			                        Concurrency::parallel_for_each(a.begin(), a.end(), [&](int i) {
				                                                                                      sum.local() += (is_Prime(i) ? i : 0);
			                                                                                      }
									                              );

			                        prime_sum = sum.combine(std::plus<int>());
		                        }
		                   );
		std::wcout << prime_sum << std::endl;
		std::wcout << L"parallel time: " << elapsed << L" ms" << std::endl << std::endl;

		_getch();
	}

	{
		// A set of prime numbers that is computed serially.
		std::bitset<limit> primes1;

		// A set of prime numbers that is computed in parallel.
		std::bitset<limit> primes2;

		__int64 elapsed;

		// Compute the set of prime numbers in a serial loop.
		elapsed = time_call([&] {
			                        for(int i = 0; i < limit; ++i) 
									{
				                        if (is_Prime(i))
					                        primes1.set(i);
			                        }
		                        }
		                   );
		std::wcout << L"serial time: " << elapsed << L" ms" << std::endl << std::endl;

		// Compute the same set of numbers in parallel.
		elapsed = time_call([&] 
							{
								// Use a parallel_for loop and a combinable object to compute 
								// the set in parallel. 
								// You do not need to synchronize access to the set because the 
								// combinable object provides a separate bitset object to each thread.
								Concurrency::combinable<std::bitset<limit>> working;

								Concurrency::parallel_for(0, limit, [&](int i) 
																	{
																		if (is_Prime(i))
																			working.local().set(i);
																	}
														 );

								// Merge each thread-local computation into the final result.
								working.combine_each( [&](std::bitset<limit>& local) 
													  {
														  primes2 |= local;
													  } );
							} );

		std::wcout << L"parallel time: " << elapsed << L" ms" << std::endl << std::endl;
	}
}