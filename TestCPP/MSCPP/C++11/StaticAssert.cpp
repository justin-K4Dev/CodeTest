#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file StaticAssert.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 11:45:08
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

namespace StaticAssert
{
	//use static_assert example
	const int MAX_LEVEL = 100;

	template< typename T1, int StackSize >
	class CMyStack
	{
		static_assert(StackSize >= 10, "Stack Size Error");

	public:
		T1* data;
		int nSize;

	public:
		CMyStack() : data(new T1[StackSize]), nSize(StackSize) { }
	};

	void use_static_assert()
	{
		//use static_assert()
		{
			//const value check 
			//static_assert(MAX_LEVEL <= 50, "Warning - MAX_LEVEL"); // compile error 발생

			//template const value check
			//CMyStack< int, 5 > myStack; // compile error 발생
			//std::cout << "StackSize: " << *myStack.nSize << std::endl;

			//value size check
			static_assert(sizeof(int) == 4, "not int size 4");

			system("pause");
		}
	}


	void Test()
	{
		//use_static_assert();
	}

}// end of StaticAssert