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
			//���� �ʱ�ȭ
			char *p = nullptr;

			//�Լ� �Ķ����
			func(nullptr);

			sizeof(nullptr); // 4 byte !!!

			typeid(nullptr);

			if (NULL == nullptr) {
				std::cout << "equal NULL == nullptr" << std::endl;
			}

			//nullptr != 0 �� �� �� �� ���� !!!
			//NULL == nullptr !!!
			//if ( nullptr ) true & false �� �� �� �� ���� !!!

			//throw nullptr;

			system("pause");
		}
	}

	void Test()
	{
		//nullptr_const();
	}

}// end of NullPtr