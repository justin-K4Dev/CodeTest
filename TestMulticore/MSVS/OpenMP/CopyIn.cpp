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
/// @file OMP_CopyIn.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

int a1 = 0;
int b1 = 0;

#pragma omp threadprivate(a1, b1) //a, b�� threadprivate ������ �����Ͽ� ������ �� ���� �޸𸮿� ���� ����
								  //������ ���� ���� ���� ����

void TestOMP_CopyIn()
{
	// 5.2.1 copyin ���� ���þ�
	{
	/*
		: ���� ���� �Ǵ� ���� ������ threadprivate ���� ���þ�� ���� �ϸ�
		  ���� ���� ���� ����� �� �����̺� ������ ��� �� �� ����
		  ������ �����忡�� ���� �޸𸮿� ���� �̸��� �����̺� ������ ���� ��
		  threadprivate ���� ���þ�� ������ ������ ���� �������� ���� ��
		  ������ �����忡�� ���Ǵ� ������ ���� �������� ���� ������ ���� ���� ����
		  ������ copyin ���� ���þ ��� �ϸ� �������� ���� �޸𸮿� ������ �����̺� ������ �� ���� ���� �� �� ����

		#pragma omp [parallel, parallel for, parallel sessions] copyin(������)

		* ���� ���þ�
		#pragma opm parallel ���þ�
		#pragma opm parallel for ���þ�
		#pragma opm parallel sections ���þ�

		[����]
		- threadprivate ������ copyin ���� ���þ�� �ʱ�ȭ ��
		- ������ ���� �޸𸮿� ����� ������ copyin �� �μ��� ���� �Ͽ� ��� �� �� ����
	*/

		a1 = 1;
		b1 = 1;

		#pragma omp parallel num_threads(4)
		{
			printf("Copyin before ThreadNo:%d - a=%d, b=%d\n", omp_get_thread_num(), a1, b1);
		}

		printf("\n");

		#pragma omp parallel copyin(a1) num_threads(4) // ���� a1 �� ��� �����忡 ���� !!!
		{
			printf("Copyin after ThreadNo:%d - a=%d, b=%d\n", omp_get_thread_num(), a1, b1);
		}

		_getch();
	}
}