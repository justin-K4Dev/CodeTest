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
/// @file OMP_NoWait.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_NoWait()
{
	// 5.4.1 nowiat ���� ���þ�
	{
	/*
		: ���α׷��Ӱ� ���⿡ �Ͻ��� ����� �ʿ� ���ٰ� �ǴܵǸ� �������� ������ �� �� ����
		  OpenMP �� nowait ���� ���þ �̿��Ͽ� �Ͻ��� ����� ���� �ϵ��� ����
		  nowait �� �����Ǹ� ���� �۾��� ������ ������� ���� ���� ������ ��ġ����
		  ������� ��� ���� �ʰ� ���� �۾��� ������
		  parallel �������� ������ ������ ���� �۾��� �ִ� ���
		  nowait ���� ���þ ����Ͽ� ������ ���� ��ų �� ����		

		#pragma omp wait
		#pragma omp sections nowait

		* ���� ���þ�
		#pragma omp for ���þ�
		#pragma omp sections ���þ�
		#pragma omp singls ���þ�

		[����]
		- reduction ���� ���þ�� nowait ���� ���þ ���ÿ� ��� ���� ��,
		  �� �������� ������� �ջ� �ϴ� �����߿� ������ ������ �߻� �� �� ����
		- #pragma omp parallel ���þ� ���� nowait �� ���� �� �� ����
		- #pragma omp parallel sections ���þ� ���� nowait �� ���� �� �� ����
		- #pragma omp parallel for ���þ nowait ���� ���þ ��� �� �� ����
	*/

		const unsigned int MAX = 5;

		float *Data1 = new float[MAX];
		float *Data2 = new float[MAX];

		int i = 0;

		for (i = 0; i < MAX; i++) 
		{
			Data1[i] = (float) ( i + 1 );
			Data2[i] = (float) ( i + 1 );
		}

		#pragma omp parallel
		{
			printf("omp for nowait Start !!! - ThreadNo:%d\n", omp_get_thread_num());
		
			#pragma omp for nowait // for ���� �۾� 1
			for (i = 0; i < MAX; i++) 
			{
				Data1[i] = sqrt(Data1[i]);

				printf("Called job - LoopID:%d, ThreadNo:%d\n", i, omp_get_thread_num());
			} // nowait ���� ���þ�� �۾��� �Ϸ��� ������� �ٸ� �����尡 �Ϸ� �Ǳ⸦ ��ٸ��� �ʰ� �ٷ� ���� ���� 

			printf("omp for Start !!! - ThreadNo:%d\n", omp_get_thread_num());

			#pragma omp for // for ���� �۾� 2
			for (i = 0; i < MAX; i++) 
			{
				Data2[i] = log(Data2[i]);

				printf("Called job - LoopID:%d, ThreadNo:%d\n", i, omp_get_thread_num());
			}
		}

		_getch();
	}

}