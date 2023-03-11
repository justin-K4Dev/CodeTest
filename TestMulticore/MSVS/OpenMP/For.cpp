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
/// @file OMP_For.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_For()
{
	// 2.1 for ���þ�
	{
	/*
		: for ���� ���� ����ȭ
		  for ���� ���� ������ �� �۾��� ����� �ִ� ���̳� ����� ���ϴ� ��Ģ�� ������ �̶� ��

		#pragma omp parallel
		{
			#pragma omp for [���� ���þ� [,���� ���þ�]...]
			for ( �ʱⰪ, ���ǽ�, ������ ) <- private ���� �ڵ� ����
			{
				to do here job !!!
			}
		}

		#pragma omp parallel for
		for ( �ʱⰪ, ���ǽ�, ������ ) <- private ���� �ڵ� ����
		{
			to do here job !!!
		}

		* ��� ������ ���� ���þ�
		#pragma omp parallel private(������)
		#pragma omp parallel firstprivate(������)
		#pragma omp parallel lastprivate(������)
		#pragma omp parallel reduction(���䷹����:������)
		#pragma omp parallel collapse(����)
		#pragma omp parallel ordered
		#pragma omp parallel nowait

		[����]
		- ��ø for �� ��� ù��° for �� ���� ó�� !!!
		- schedule ���� ���þ�, collapse ���� ���þ�, ordered ���� ���þ��
		  �ϳ��� #pragma omp for ���þ �ѹ��� ��� ����
		- ��ø for �� ���� ó�� �ؾ� �� ��� 
		  collapse ���� ���þ� or omp_set_nested() �Լ� ���� ����
		- ���� for ���� �ȿ��� throw �� ���ܴ� ���� ���� ���������� catch �ؾ� �� !!!
		- #pragma omp parallel for ���� ���þ� ������ nowait ���� ���þ ���� ����
		  nowait ���� ���þ ��� �ؾ� �ϴ� ��� 
		  #pragma omp parallel & #pragma omp for ���þ ���������� ��� �ؾ� ��
	*/

		const int MAX = 10000;
		float *pData = NULL;

		pData = new float[MAX];

		for ( int nCount = 0;
			  nCount < MAX;
			  ++nCount )
		{
			pData[nCount] = (float)nCount;
		}

		printf("omp for Start !!!");

		#pragma omp parallel // ���� ó�� ���� ���� 
		                     // thread ��� ���� 2�� ������ -> #pragma omp parallel num_thread(2) 
		{
			#pragma omp for // for loop ���·� thread ��� �ؼ� ���� ó�� ����
			for ( int nCount = 0;
				  nCount < MAX;
				  ++nCount )
			{
				pData[nCount] = sqrt (pData[nCount]);

				printf("LoopID:%d - ThreadNo:%d\n", nCount, omp_get_thread_num());
			}
		} // OpenMP ���ο��� fork & join ���� �Ͽ� { } ������ ���� ó���� �� !!!

		printf("omp for End !!!");

		delete [] pData;
	
		_getch();
	}

}