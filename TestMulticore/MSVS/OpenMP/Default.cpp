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
/// @file OMP_Default.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Default()
{
	// 5.1.1 default ���� ���þ�
	{
	/*
		: OpenMP ���� ���� ������ �⺻������ ���� �ε����� ������ ��� ������ ������ ���� ���� ��
		  �̴� ���� ������ �ִ� ������ �⺻ �Ӽ��� ó�� ���� ����(shared) �Ӽ��� ������ ���� �ǹ�
		  ���� ������ ��� ������ threadprivate �Ӽ����� ���� �ؾ� �Ҷ�,
		  ���� �Ӽ����� ������ ������ �ִٸ� ���α׷� ���� �߻� !!!
		  OpenMP �� �ڵ����� ���� �Ӽ��� �Ǵ� ���� ���� �ϴ� ����� ���� �ϰ� �ִ� ��
		  �̰��� default ���� ���þ� ��
		  default ���� ���þ�� ������ ������ ��ȿ ���� �Ӽ��� ����
		  ���� ��� deault(none) �� ���� �ϸ� ���� �ȿ��� ��� ������ ���� �����忡���� ���� �� �� �ִ�
		  private �Ӽ� or ���� �� �� �ִ� ���� �Ӽ����� ��� ���� �ؾ� ��
		  �� default(shared) �� ���� �ϰ� �Ǹ� ���������� ���� �ϴ� ��� �۷ι� ������ ���� �� �� ����
		  C/C++ ����Ʈ�� ������ �Ӽ��� default(shared) �̹Ƿ� ������ ���� �� �ʿ䰡 ����

		  #pragma omp parallel default(shared|none)

		  * ���� ���þ�
		  #pragma omp parallel ���þ�
		  #pragma omp task ���þ�

		  [����]
		  - default(none) �� ���� �Ǿ��� ���, ���� ������ ���� �ϴ� ��� ���� �����ʹ� ��������� ������ �Ӽ��� ���� �ؾ� ��
		    ���� ���� ���� ��� ������ ������ ����.
		  - default ���� ���þ�� #pragma omp parallel Ȥ�� #pragma omp task ���þ�� �ѹ��� ���� �� �� ����
	*/
	}

	{
		int a = 0;
		printf("Main Area a : %d\n", a);

		// shared �Ӽ� ����
		#pragma omp parallel default(shared) 
		{
			if (omp_get_thread_num() == 0) {
				a = 1;
			}

			else {
				a = 2;
			}

			printf("%d thread Area a : %d\n", omp_get_thread_num(), a);
		}

		printf("Main Area a : %d\n", a);

		_getch();
	}

	{
		int a = 0;
		printf("Main Area a : %d\n", a);

		// none �Ӽ� ���� - private(a) �� ���� �ؾ� �ٸ� ������ �ؼ� a ���� �� ������ ���� !!!
		#pragma omp parallel num_threads(2), default(none), private(a)
		{
			if (omp_get_thread_num() == 0) {
				a = 1;
			}
			else {
				a = 2;
			}

			printf("%d thread Area a : %d\n", omp_get_thread_num(), a);
		}

		printf("Main Area a : %d\n", a);

		_getch();
	}
}