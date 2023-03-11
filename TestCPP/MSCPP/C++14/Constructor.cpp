#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Initialize.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace Constructor
{
	// constructor example
	class TEST
	{
	public:
		// default: Explicitly specifying that the compiler should generate the function automatically
		TEST() = default;
		TEST(const TEST&) = default;
		~TEST() = default;

		TEST& operator=(const TEST&) = default;

		void func(int i) { std::cout << i << std::endl; }

		// delete: Explicitly specifying that the compiler does not automatically generate functions
		void func(double d) = delete; 

		void* operator new(size_t) = delete; // Do not assign it to new.
	};

	struct TEST2
	{
		void func(int i) { std::cout << i << std::endl; }
		void func(double d) = delete;
	};

	void consturctor()
	{
		// constructor
		{
			int i = 11;

			TEST test;
			test.func(i);

			//double d = 11.0;
			//test.func(d); // compile error
		}

		system("pause");
		
		/*
		output:
			11
		*/
	}


	// use std::is_copy_constructible() example
	template <class T>
	void swap(T& a, T& b)
	{
		static_assert(std::is_copy_constructible<T>::value,
			"Swap requires copying");
		static_assert(std::is_nothrow_copy_constructible<T>::value
			&& std::is_nothrow_copy_assignable<T>::value,
			"Swap may throw");
		auto c = b;
		b = a;
		a = c;
	}

	template <class T>
	struct data_structure
	{
		static_assert(std::is_default_constructible<T>::value,
			"Data Structure requires default-constructible elements");
	};

	struct no_copy
	{
		no_copy(const no_copy&) = default;
		no_copy() = default;
	};

	struct no_default
	{
		no_default() = default;
	};

	void use_std_is_copy_constructible()
	{
		// use std::is_copy_constructible()
		{
			int a, b;
			swap(a, b);

			no_copy nc_a, nc_b;
			swap(nc_a, nc_b); // 1

			data_structure<int> ds_ok;
			data_structure<no_default> ds_error; // 2

			system("pause");
		}
	}


	void Test()
	{
		//consturctor();

		//use_std_is_copy_constructible();
	}

}// end of Constructor