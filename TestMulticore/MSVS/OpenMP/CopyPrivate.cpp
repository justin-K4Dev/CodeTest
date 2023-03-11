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
/// @file OMP_CopyPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

int a = 0;
#pragma omp threadprivate(a)

void TestOMP_CopyPrivate()
{
	// 5.2.2 copyprivate ���� ���þ�
	{
	/*
		: copyin ���� ���þ�� ���� �������� ó�� �ʱ�ȭ �� ���� 
		  ������ �����忡 �ִ� threadprivate ������ ���� �� ������� ���� �Ͽ� ���� �� �� ����
		  copyprivate ���� ���þ�� threadprivate ������ ���� ���� �ȿ��� ���ϴ� ������ ���ϴ� ������
		  �� �����忡 ���� �� �� ����
		  ��� ó���� ���� ���� ���� ���� ������ �� ������ ����� �� �����ϰ� ��� �� �� ����
		  ������ copyprivate ���� ���þ�� #pragma single ���þ� ������ ��� �� �� ����

		#pragma omp single copyprivate(������)

		* ���� ���þ�
		#pragma omp single ���þ�
		#pragma omp threadprivate ���þ�

		[����]
		- #pragma omp single ���þ� �ȿ��� copyprivate ���� ���þ�� ������ ������
		  �ٽ� pirvate ���� ���þ� �Ǵ� firstprivate ���� ���þ��� ������ ���� �� �� ����
	*/
		#pragma omp parallel num_threads(4)
		{
			a = omp_get_thread_num();

			printf("Copyprivate before ThreadNo:%d, a=%d\n", omp_get_thread_num(), a);

			#pragma omp single copyprivate(a) // �� ������ a ���� ���� �ϰ� �� �����忡 ���� !!!
			{
				a = 7;
				printf("\n");
			}

			printf("Copyprivate after Thread:%d, a=%d\n", omp_get_thread_num(), a);

			#pragma omp barrier
			#pragma omp single
			printf("\n");

			a = omp_get_thread_num();
			printf("ThreadNo:%d, a=%d\n", omp_get_thread_num(), a);
		}

		_getch();
	}
}