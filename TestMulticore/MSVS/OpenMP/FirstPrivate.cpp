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
/// @file OMP_FirstPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_FirstPrivate()
{
	// 5.1.4 firstprivate ���� ���þ�
	{
	/*
		: firstprivate ���� ���þ�� �����̺� ���� ���þ�� �⺻���� ����� �����ϰ� �����ϳ�
		  ������ ���� �ʱ�ȭ �ϴ� ����� �߰� �Ǿ� ����
		  �����̺� ������ ���� ������ �������� ���� ���� ���� ������ ���� ���� �ʰ�
		  �� �����尡 ���������� �������� �ʱ�ȭ �Ͽ� ��� �ؾ� ��

		#pragma omp parallel firstprivate(������)

		* ���� ���þ�
		#pragma omp parallel ���þ�
		#pragma omp sections ���þ�
		#pragma omp task ���þ�

		[����]
		- private ���� ���þ�� ����
	*/

		float A[5] = { 1, 2, 3, 4, 5 };

		printf("ThreadNo:%d - A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		#pragma omp parallel num_threads(3), firstprivate(A) // ���� A �� ������ �ʱ�ȭ ��
		{
			A[3] = 7;

			printf("ThreadNo:%d - A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);
		}

		printf("ThreadNo:%d - A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		_getch();
	}
}