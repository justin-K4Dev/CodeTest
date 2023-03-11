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
	// 3.3 taskwait ���þ�
	{
	/*
		: #pragma omp task ���þ�� �۾�ť�� ����� ��� �ڵ尡 �Ϸ� �ɶ� ����
		  #pragma omp taskwait ���þ �ִ� ��ġ���� ���

		#pragma omp taskwait

		[����]
		- taskwait ���þ�� C/C++ ������ ��Ģ�� ��� �Ǵ� �������� ��� ���� �ϰ�
		  if, while, do, switch �� ���� ���� ���� ��� �� �� ����
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