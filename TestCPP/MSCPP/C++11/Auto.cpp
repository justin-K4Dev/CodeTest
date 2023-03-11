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
	// auto keyword example
	class CObj { };

	void auto_keyword()
	{
		// auto keyword
		{
			// char*
			auto strName = "BugKing";
			std::cout << strName << std::endl;

			// int
			auto nNumber = 100;
			std::cout << nNumber << std::endl;

			// pointer
			int nUserMode = 1;
			auto *pUserMode = &nUserMode;
			std::cout << "pUserMode: Value - " << *pUserMode << ", address: " << pUserMode << std::endl;

			// reference
			int nAccountMode = 100;
			auto &refAccountMode = nAccountMode;
			std::cout << "pUserMode: Value - " << nAccountMode << ", refValue: " << refAccountMode << std::endl;

			// class
			auto *pObj = new CObj;

			// STL
			std::vector<int> vtValueList;
			vtValueList.push_back(1);
			vtValueList.push_back(2);
			vtValueList.push_back(3);

			// for
			for (auto itPos = vtValueList.begin();
				itPos != vtValueList.end();
				++itPos) {
				auto nValue = *itPos;

				std::cout << "vector element: " << nValue << std::endl;
			}

			// range for
			for (auto &v : vtValueList) {
			}

			// for each in
			for each(auto itPos in vtValueList) {
			}

			// lambda
			auto func1 = [] {
				int a = 10;

				return a;
			};

			int b = func1();

			auto func2 = [](int n) {
				return n;
			};

			int c = func2(10);
			int d = func2(100);

			system("pause");
		}
	}


	void Test()
	{
		//auto_keyword();
	}

}// end of Auto