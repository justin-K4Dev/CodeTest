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
/// @file OMP_Shared.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Shared()
{
	// 5.1.2 shared ���� ���þ�
	{
	/*
		: ������ ������ ������ ������ �� ���� ��� �����尡 ����
		  task ���þ ����� ���, ������� �׽�Ʈ �ȿ��� �����Ǵ� ������ shared ���� ���þ
		  �θ� ����(task ������ ���� �ϴ� ���� ����)�� ���� ����

		#pragma omp shared(������)

		* ���� ���þ�
		#pragma omp parallel ���þ�
		#pragma omp task ���þ�

		[����]
		- #pragma omp task ���þ� ���� ������ shared �� ��� �Ǵ� ���, task ������ ó���� ���� �Ǳ� ���� ������ �Ҹ� �Ǽ��� �ȵ�

	*/
		#pragma omp parallel
		{
			int a = 0, b = 0;

			#pragma omp single
			{
				for (int iCount = 0; iCount < 10; ++iCount) 
				{
					// a �� �����尣�� ���� , b �� �����尣�� ���� �ȵ� !!!
					#pragma omp task shared(a), private(b)
					{
						#pragma omp atomic
						a++;

						#pragma omp atomic
						b++;
					}
				}
			}

			#pragma omp single
			printf("shared a: %d, private b: %d\n", a, b);
		}

		_getch();
	}


}