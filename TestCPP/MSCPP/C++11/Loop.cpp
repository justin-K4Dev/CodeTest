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

namespace Loop
{

	void for_range_base()
	{
		/*
			Range-based for loop

			The for-loop has another syntax, which is used exclusively with ranges:

			for ( declaration : range ) statement;

			This kind of for loop iterates over all the elements in range,
			where declaration declares some variable able to take the value of an element in this range.
			Ranges are sequences of elements, including arrays, containers,
			and any other type supporting the functions begin and end;
			Most of these types have not yet been introduced in this tutorial,
			but we are already acquainted with at least one kind of range: strings,
			which are sequences of characters.

			An example of range-based for loop using strings:
		*/
		{
			std::string str( "Hello!" );
			for (char c : str)
			{
				std::cout << "[" << c << "]";
			}
			std::cout << '\n';

			system("pause");
			/*
				output:
					[H][e][l][l][o][!]
			*/
		}
		/*
			Note how what precedes the colon (:) in the for loop is the declaration of a char variable
			(the elements in a string are of type char).
			We then use this variable, c, in the statement block to represent the value of each of the elements in the range.

			This loop is automatic and does not require the explicit declaration of any counter variable.

			Range based loops usually also make use of type deduction for the type of the elements with auto.
			Typically, the range-based loop above can also be written as:
		*/
		{
			std::string str( "Hello C++ !!!" );
			for (auto c : str)
			{
				std::cout << "[" << c << "]";
			}
			std::cout << '\n';

			system("pause");
			/*
				output:
					[H][e][l][l][o][ ][C][+][+][ ][!][!][!]
			*/
		}
	}


	void for_each_in()
	{
		/*
			for each, in

			Syntax
  
				for each (type identifier in expression) {  
					statements  
				}
		*/

		std::vector<int> dataList;
		dataList.push_back(1);
		dataList.push_back(2);
		dataList.push_back(3);

		for each(auto v in dataList) {
			std::cout << v << std::endl;
		}

		system("pause");
		/*
			output:
				1
				2
				3
		*/
	}


	void Print(int n)
	{
		std::cout << n << " ";
	}

	struct OutFunctor
	{
		void operator() (int n)
		{
			std::cout << n << " ";
		}
	};

	void for_each_use()
	{
		//for_each + function
		{
			std::vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			//call predicate - function
			std::for_each(v.begin(), v.end(), Print);
			std::cout << std::endl;

			system("pause");
			/*
				output:
					1 2 3
			*/
		}

		//for_each + functor
		{
			std::vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
		
			//call predicate - functor
			std::for_each(v.begin(), v.end(), OutFunctor());
			std::cout << std::endl;

			system("pause");
			/*
				output:
					1 2 3
			*/
		}
	}


	void Test()
	{
		//for_range_base();

		//for_each_in();

		//for_each_use();
	}

}// end of Loop