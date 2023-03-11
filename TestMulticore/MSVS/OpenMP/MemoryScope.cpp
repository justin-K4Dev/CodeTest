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
	// thread global scope 변수
	{
		int x = 0; // Master thread 가 생성한 변수는 모든 스레드에서 접근 가능 !!!

		#pragma omp parallel
		{
			if ( omp_get_thread_num() == 0 )
			{
				x = 1;
			}
			else
			{
				x = 2; // 1 번 thread 가 값을 2 로 변경
			}
		}

		_getch();
	}

	// thread local scope 변수
	{
		int x = 0;

		#pragma omp parallel private( x ) // 보조 지시어 private( x ) : thread local 변수 x 생성
		{
			if ( omp_get_thread_num() == 0 )
			{
				x = 1;
			}
			else
			{
				x = 2; // 1 번 thread 가 값을 2 로 변경
			}

			char szBuff[128];
			sprintf_s(szBuff, 128, "Thread Local Variable - ThreadNo:%d, x:%d", omp_get_thread_num(), x);
			std::cout << szBuff << std::endl; 
		}

		std::cout << "Master Thread Variable - x:" << x << std::endl;

		_getch();
	}
}