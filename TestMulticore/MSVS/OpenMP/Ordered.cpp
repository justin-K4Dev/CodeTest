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
/// @file OMP_Ordered.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Ordered()
{
	// 3.7 ordered ���þ�
	{
	/*
		: OpenMP ���� ���� ���� ���� ���� �ε��� ������ ���� ������ �ʿ��� ���
		  #pragma omp ordered ���þ ��� �ϸ� ��
		  ordered ���þ ����� ��� �ε����� ī���Ϳ� ���� 0 ���� ������������ ���ʴ�� �����

		#pragma omp for ordered
		for ( �ʱⰪ; ���ǽ�; ������ )
		{
			#pragma omp ordered
			to do here job
		}

		[����]
		- #pragma omp ordered ���þ ��� �ϱ� ���ؼ��� 
		  #pragma omp for ���þ� ���Ŀ� �Ʒ��� ���� ordered ���� ���þ ���� �ؾ� ��
		  #pragma omp parallel for ordered
	*/

		printf("ordered not use: ");

		#pragma omp parallel
		{
			#pragma omp for
			for (int i = 0; i < 10; i++)
			{
				printf(" %d ", i);
			}

			#pragma omp single
			{
				printf("\nordered use: ");
			}

			#pragma omp for ordered
			for (int i = 0; i < 10; i++)
			{
				#pragma omp ordered
				printf(" %d ", i);
			}

		}

		printf("\n");

		_getch();
	}

}