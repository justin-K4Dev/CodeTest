#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file NullPtr.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 7-27-2012 2:51:03
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

namespace NullPtr
{
	int func(double *p) { return 0; }

	void nullptr_const()
	{
		{
			//변수 초기화
			char *p = nullptr;

			//함수 파라메터
			func(nullptr);

			sizeof(nullptr); // 4 byte !!!

			typeid(nullptr);

			if (NULL == nullptr) {
				std::cout << "equal NULL == nullptr" << std::endl;
			}

			//nullptr != 0 과 비교 될 수 없음 !!!
			//NULL == nullptr !!!
			//if ( nullptr ) true & false 와 비교 될 수 없음 !!!

			//throw nullptr;

			system("pause");
		}
	}

	void Test()
	{
		//nullptr_const();
	}

}// end of NullPtr