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
/// @file OMP_ThreadPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

int A[2] = { 1, 1 };
#pragma omp threadprivate(A)

void TestOMP_ThreadPrivate()
{
	// 4.1 threadprivate ���þ�
	{
	/*
		: �۷ι� �޸𸮿� �ִ� ������ threadprivate ���þ�� ���� �ϰ� �Ǹ�,
		  �� ������� ���� �޸𸮿� ������ �Ҵ� & ���� �Ͽ� ��� �� �� ����
		  threadprviate ���þ�� ������ ���� �ϸ�, �� ������� ������ ���� �޸� ������ �Ҵ� �ϰ�
		  �۷ι� ������ �ִ� �������� ������.
		  �ø��� ������ ���� �ϴ� �ڵ�� ������ ������� �۷ι� ������ �ִ� ���� �������� ���� �ϰ� ��

		#pragma omp threadprivate(������)

		[����]
		- threadprivate ������ ���� �� �����尡 �� ���� ���� �ϱ� ���� �ʱ�ȭ �ؾ� ��
		  ���� ������ �����尡 ���α׷��� �ø��� ���� �߿� �ʱ�ȭ �ϰ� ��
		- private ���� ó�� ������� threadprivate ������ ���� �Ͽ� ���� �� �� ����,
		  ���α׷��� �ø��� ���� �� ������ ������ ������ ������ ���� �Ͽ� ���� �ؾ� ��
		- �� ������ ���� threadprivate ������ ��ȿ �Ϸ��� ���ʿ� ������ ���� ������ ������ ���� ���� ���� �ʾƾ� ��
		- threadprivate ������ copyin, schedule, num_threads, if ���� ���þ ������ �ٸ� ���� ���þ�� ���� �� �� ����
		- C++ Ŭ������ ���� ������ ����� ���� �ϰ� �迭 �̳�, ����ü, Ŭ������ �Ϻ� ��Ҵ�
		  threadprivate ���� ���þ�� ���� �� �� ����
		- ���۷����� ������ ��� �� �� ����
		- threadprivate ������ ��巹���� �ּ� ����� �ƴ�
		
		[TIP] Ŭ������ ������ threadprivate ���þ ���� �Ϸ��� �Ʒ��� ������ ���� �ؾ� ��
		- �ʱ�ȭ �μ� ���� ����Ʈ �ʱ�ȭ�� ���, ���� ���� �ϰ� ��Ȯ�� ����Ʈ constructor �� �־�� ��
		- �������� �ʱ�ȭ�� ���, �μ��� �޾Ƶ鿩 ���� ���� �ϰ� ��Ȯ�� ����Ʈ constructor �� �־�� ��
		- ������� �ʱ�ȭ ��ü�� ������ ���� ������ ���, ���� ���� �ϰ� ��Ȯ�� constructor �� �־�� ��
	*/

		A[1] = 2;
		printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());

		#pragma omp parallel num_threads(4)
		{
			printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());
		}

		printf("\n");

		A[0] = 3;
		printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());

		#pragma omp parallel num_threads(4)
		{
			A[1] = 4;

			printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());
		}

		printf("LastCode - A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());

		_getch();
	}
}