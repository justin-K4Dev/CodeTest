#include "stdafx.h"


#include <exception>

namespace Exception
{
	//set_unexpected example
	class X {};
	class Y {};
	class Z : public X {};
	class W {};

	void f() throw(X, Y)
	{
		int n = 0;
		if (n) throw X(); // OK
		if (n) throw Z(); // also OK
		throw W(); // will call std::unexpected()
	}

	void std_set_unexpected()
	{
		//use set_unexpected
		{
			std::set_unexpected([] {
				std::cout << "That was unexpected" << std::endl; //flush needed
				std::abort();
			});

			f();

			system("pause");
		}
	}

	void Test()
	{
		//std_set_unexpected();
	}

}