#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-22-2012 13:04:23
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <omp.h>


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-22-2012 16:52:24
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <omp.h>


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_MemoryScope.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_MemoryScope()
{
	// thread global scope ����
	{
		int x = 0; // Master thread �� ������ ������ ��� �����忡�� ���� ���� !!!

		#pragma omp parallel
		{
			if ( omp_get_thread_num() == 0 )
			{
				x = 1;
			}
			else
			{
				x = 2; // 1 �� thread �� ���� 2 �� ����
			}
		}

		_getch();
	}

	// thread local scope ����
	{
		int x = 0;

		#pragma omp parallel private( x ) // ���� ���þ� private( x ) : thread local ���� x ����
		{
			if ( omp_get_thread_num() == 0 )
			{
				x = 1;
			}
			else
			{
				x = 2; // 1 �� thread �� ���� 2 �� ����
			}

			char szBuff[128];
			sprintf_s(szBuff, 128, "Thread Local Variable - ThreadNo:%d, x:%d", omp_get_thread_num(), x);
			std::cout << szBuff << std::endl; 
		}

		std::cout << "Master Thread Variable - x:" << x << std::endl;

		_getch();
	}
}