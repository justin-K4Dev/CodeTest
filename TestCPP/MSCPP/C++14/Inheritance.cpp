#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Inheritance.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace Inheritance
{
	struct Base
	{
		virtual void foo(int i);

		// final: use to prevent child classes from being overridden
		virtual void zoo(int v) final;
	};

	struct Driven : Base
	{
		// override: tells the compiler to override the member function of the parent class
		virtual void foo(int i) override
		{ return; }
		//virtual void foo(float i) override; //compile error !!!

		//virtual void zoo(int v); //compile error !!!
	};

	void Test()
	{

	}

}// end of Inheritance