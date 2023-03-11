#include "stdafx.h"



namespace CPP14
{
	void nsdmi()
	{
		/*
			NSDMI(non-static data member initializers) for Aggregates

			NSDMI for Aggregates An aggregate is an array or a class with no user-provided constructor,
			no private or protected non-static data members, no base classes,
			and no virtual functions. Beginning in C++14 aggregates may contain member initializers.
			For more information, see Member initializers and aggregates.
		*/
		{
			struct Univ
			{
				std::string name;
				int rank;
				std::string city = "unknown";
			};

			Univ u = { "Columbia",10 };
			std::cout << u.name << ' ' << u.rank << ' ' << u.city << '\n';

			system("pause");

			/*
			output:
				Columbia 10 unknown
			*/
		}
		{
			struct X { int i, j, k = 42; };

			X a[] = { 1, 2, 3, 4, 5, 6 };

			for each (X &v in a) {
				std::cout << v.i << ',' << v.j << ',' << v.k << std::endl;
			}

			system("pause");

			/*
			output:
				1,2,3
				4,5,6
			*/
		}
		{
			struct A
			{
				struct X { int a, b; };
				X x = { 1, 2 };
				int n;
			};

			A a = { { 10 }, 5 };
			std::cout << a.x.b << std::endl;

			system("pause");

			/*
			output:
				0
			*/
		}
	}


	// Extended constexpr example
	constexpr int factorial(int n)
	{
		// local variable
		int result = 0;

		// multiple return statements
		if (n <= 1)
			result = 1;
		else
			result = n * factorial(n - 1);

		return result;
	}

	template <int N>
	struct Factorial
	{
		enum { value = N * Factorial<N - 1>::value };
	};

	template <>
	struct Factorial<0>
	{
		enum { value = 1 };
	};

	// constexpr type return
	constexpr int Factorial2Const(int n)
	{
		return n <= 0 ? 1 : n  * Factorial2Const(n - 1);
	}

	void extended_constexpr()
	{
		/*
			Extended constexpr

			Extended constexpr Expressions declared as constexpr are now allowed to contain certain kinds of declarations,
			if and switch statements, loop statements,
			and mutation of objects whose lifetime began within the constexpr expression evaluation.
			Also, there is no longer a requirement that a constexpr non-static member function be implicitly const.
			For more information, see Relaxing constraints on constexpr functions.

				Accepted Changes

				The changes selected by the Evolution Working Group were:

				• Allow declarations within constexpr functions, other than:
					- static or thread_local variables
					- uninitialized variables
				• Allow if and switch statements (but not goto)
				• Allow all looping statements:
					- for (including range-based for), while, and do-while
				• Allow mutation of objects whose lifetime began within the constant expression evaluation.
				
			In addition, in discussion of N3598, Option 2 was selected,
			which removes the rule that a constexpr non-static member function is implicitly const.
		*/
		{
			// The result of constexpr function can be used as the value of enum
			enum FACTORIAL
			{
				first = Factorial2Const(1),
				second = Factorial2Const(2),
				third = Factorial2Const(3),
			};
		}
	}


	void Test()
	{
		//nsdmi();

		//extended_constexpr();
	}
}