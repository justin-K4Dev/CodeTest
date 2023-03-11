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
/// @file OMP_If.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////


void DoJob(int nJobCount)
{
	#pragma omp parallel if (nJobCount > 1000)
	{
		if (omp_in_parallel()) // ���� �������� �˻�
		{  
			#pragma omp single
			printf("JobCount:%d, Parallel ThreadNo:%d\n", nJobCount, omp_get_thread_num());

		}
		else 
		{
			printf("JobCount:%d, Sequential ThreadNo:%d\n", nJobCount, omp_get_thread_num());
		}
	}
}


void TestOMP_If()
{
	// 5.5.1 if ���� ���þ�
	{
	/*
		: Ư�� ������ ������ ���� OpenMP ���þ �����ϴ� ����� �����ް� ���� ��쿡 �����
		  if�� ������ true�� ��쿡�� �����ϰ� false�� ��쿡�� �������� ����

		#pragma omp parallel for if(���ǽ�)

		* ���� ���þ�
		#pragma omp parallel ���þ�
		#pragma omp parallel for ���þ�
		#pragma omp parallel sections ���þ�
		#pragma omp task ���þ�

		[TIP]
		//�۾����� ������ if ���� ���þ� ���
		#pragma omp parallel sections if(omp_get_max_threads() > 3)
		{
			#pragma omp section
			...
			#pragma omp section
			...
			#pragma omp section
			...
		}

		//for �������� if ���� ���þ� ���
		#pragma omp parallel if(max_count > 1000)
		for(int n = 0; i < max_count; ++i)
		{
			...
		}
	*/

		DoJob(500);
		DoJob(20000);

		_getch();
	}
}