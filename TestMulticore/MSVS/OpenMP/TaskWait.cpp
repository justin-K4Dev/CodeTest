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
/// @file OMP_TaskWait.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_TaskWait()
{
	// 3.3 taskwait 지시어
	{
	/*
		: #pragma omp task 지시어로 작업큐에 등록한 모든 코드가 완료 될때 까지
		  #pragma omp taskwait 지시어가 있는 위치에서 대기

		#pragma omp taskwait

		[주의]
		- taskwait 지시어는 C/C++ 문법의 규칙이 허용 되는 곳에서만 사용 가능 하고
		  if, while, do, switch 문 등의 직후 에는 사용 할 수 없음
	*/

		int a = 0;
		int b = 0;
		int c = 0;

		#pragma omp parallel
		{
			#pragma omp task
			{
				a = 1;
				printf("Called task 1 job - ThreadNo:%d\n", omp_get_thread_num());
			}

			#pragma omp task
			{
				b = 2;
				printf("Called task 2 job - ThreadNo:%d\n", omp_get_thread_num());
			}

			#pragma omp taskwait
			{
				c = a + b;

				printf("Called end (c:%d) - ThreadNo:%d\n", c, omp_get_thread_num());
			}
		}

		_getch();
	}
}