#include "stdafx.h"



///////////////////////////////////////////////////////////////////////////////
/// @file Lambda.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 7-26-2012 23:30:21
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>

namespace Lambda
{

	void generic_lambdas()
	{
		// generic lambdas
		{
			// use auto
			{
				auto Sum = [](auto a, auto b) {
					return a + b;
				};

				int i = Sum(3, 4);
				float f = (float)Sum(3.14, 4.64);
			}

			// capture variable initialize
			{
				auto nums = { 10, 100, 1000 };
				auto pNums = std::make_unique<std::vector<int>>(nums);

				auto a = [ptr = std::move(pNums)]() {
					// use ptr
				};
			}

			// use Variadic argument
			{
				auto Sum = [](auto&&... args) {
					std::cout << sizeof...(args) << std::endl;
				};
			}

			// uncaptured lambda can be cast to function pointer
			{
				auto L = [](auto a, auto b) { return a + b; };
				int (*fp)(int, int) = L;

				L(10, 100);
			}

			// lambda throw
			{
				/*
					You can use the throw () exception specification to indicate
					that a lambda expression does not throw any exceptions.
					As you can see, the Visual C ++ compiler generates a throw () warning
					if the lambda expression declares the C4297 exception specification and
					the lambda body throws an exception, just like a regular function.
				*/

				// compile with: /W4 /EHsc

				// C4297 expected
				[]() throw() // <- You can use the throw () exception specification to indicate
					         //    that a lambda expression does not throw any exceptions.
				{
					//throw 1; 
				}();
			}
		}

		system("pause");
	}


	void lambda_recursive()
	{
		auto fib = [](int64_t x, const auto& lambda)->int64_t
		{
			if (x == 0 || x == 1)
				return 1;
			else return lambda(x - 1, lambda) + lambda(x - 2, lambda);
		};

		fib(35, fib);

		system("pause");
	}


	void Test()
	{
		lambda_recursive();

		//generic_lambdas();
	}

}// end of Lambda