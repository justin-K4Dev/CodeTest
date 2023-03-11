#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Auto.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace Auto
{
	// return value example
	auto func1(int i)
	{
		return i + 100;
	}

	void return_value()
	{
		// return value
		{
			auto v = func1(10);
			std::cout << v << std::endl;

			system("pause");

			/*
			output:
				110
			*/
		}
	}


	// return referece example
	int x = 100;

	auto& func2()
	{
		return x;
	}

	void return_reference()
	{
		// return reference
		{
			auto &v = func2();
			std::cout << v << std::endl;

			system("pause");

			/*
			output:
				100
			*/
		}
	}


	void range_based_for()
	{
		// range based for
		{
			std::vector<int> vtValueList;
			vtValueList.push_back(1);
			vtValueList.push_back(2);
			vtValueList.push_back(3);

			for (auto v : vtValueList)
			{ 
				std::cout << v << std::endl;
			}

			// reference
			for (auto &v : vtValueList)
			{ }

			// const
			for (auto const v : vtValueList)
			{ }

			// const + reference
			for (auto const &v : vtValueList)
			{ }
		}

		system("pause");


		/*
		output:
			1
			2
			3
		*/
	}


	void Test()
	{
		//return_value();

		//return_reference();

		//range_based_for();
	}

}// end of Auto