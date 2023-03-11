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
/// @file OMP_Private.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Private()
{
	// 5.1.3 private ���� ���þ�
	{
	/*
		: ������ �� ���� �� �����忡�� private ���� ���þ�� ������ ������ ������ ���� �޸� �������� ���� �Ͽ� ��� �ϵ��� ��
		  �����̺� ������ �ܼ��� ������ ���� �޸� ������ �Ҵ� �Ǵ� ���̱� ������
		  ���� ���� �������� ������ ������ ������ ���� ���� ���� ����
		  �����̺� ������ ���� �����忡�� �ʱ�ȭ �ؾ� ��

		#pragma omp parallel private(������)

		* ���� ���þ�
		#pragma omp parallel ���þ�
		#pragma omp task ���þ�

		* ���� ���� ���þ�
		firstprivate(������)
		lastprivate(������)

		[����]
		- �����̺����� ����� ������ ���� ���� ������ ���� �̸����� �� �ٽ� ���� �ؼ� ����ϸ� �ȵ�
		- const�� & ���۷����� ������ �����̺� ���� ��� ����
	*/

		float A[5] = { 1, 2, 3, 4, 5 };

		printf("ThreadNo:%d, Memory A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		#pragma omp parallel num_threads(3), private(A)
		{
			A[3] = 7;
			printf("ThreadNo:%d, Memory A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);
		}

		printf("ThreadNo:%d, Memory A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		_getch();
	}
}