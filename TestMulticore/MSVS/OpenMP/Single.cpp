#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-22-2012 13:04:23
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <omp.h>


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_Sections.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Single()
{
	// 2.3 single ���þ�
	{
	/*
		: ������ ���� �ϳ��� �����常 �ش� �ڵ带 ���� �� ���� ����
		  �ٸ� ������� single ���þ�� ������ �����尡 �Ϸ� �� ������
		  single ���� ���� ������ �������� �Ͻ��� ����� ���

		#pragma omp single [���� ���þ� [,���� ���þ�]...]
		{
			to do here job

			���⼭ �ٸ� ��������� �ش� �������� �ϷḦ ���
		}

		* ��� ������ ���� ���þ�
		#pragma omp single private(������)
		#pragma omp single firstprivate(������)
		#pragma omp single copyprivate(������)
		#pragma omp single nowait

		[����]
		- single ������ ���ԵǴ� ������� ������ �� ������ ��� �����尡 ���� �� �� ����
		- single ���þ�� for ���� �ȿ� �ۼ� �� �� ����
		- single ���þ�� nowait ���� ���þ�� copyprivate ���� ���þ ���ÿ� �̿� �Ұ�
		- ���� for ���� �ȿ��� throw �� ���ܴ� ���� ���� ���������� catch �ؾ� �� !!!
	*/

		printf("omp single Start !!!\n");

		#pragma omp parallel
		{
			printf("parallel - ThreadNo:%d\n", omp_get_thread_num());

			#pragma omp single  // �Ͻ��� ���� ����
			printf("omp single - ThreadNo:%d\n", omp_get_thread_num());
		}

		printf("omp single End !!!\n");

		_getch();
	}
}