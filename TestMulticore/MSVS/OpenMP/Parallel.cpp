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
/// @file OMP_Parallel.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Parallel()
{
	// ���� ó�� ���þ�
	{
	/*
	    : OpenMP ����ȭ ���� ���� 

		#pragma omp parallel [���� ���þ� [,���� ���þ�]...]
		{ <- ������ ���� ����
			to do here job !!!
		} <- ������ ���� ���� - ��� ������ ���� ���ҽ� �Ҹ� !!!

		* ��� ������ ���� ���þ�
		#pragma omp parallel if(���ǽ�)
		#pragma omp parallel num_threads(������)
		#pragma omp parallel default(shared �Ǵ� none)
		#pragma omp parallel private(������)
		#pragma omp parallel firstprivate(������)
		#pragma omp parallel shared(������)
		#pragma omp parallel copyin(������)
		#pragma omp parallel reduction(���䷹����:������)

		[����]
		- ���� ���� ���� �� ������ ���� (����� ������ �� ���� or �ý��� �̿� ������ �⺻ ������ ��)
		- parallel ���þ�� ������ ������ ������ �� ���� ������ �۾� ������ ���� ���� �����Ƿ�
		  parallel ���þ�� �Բ� sections, for ���þ� �� ��� �Ͽ� �۾� ������ ���־�� ȿ���� ���
	*/
		#pragma omp parallel // ���� ó�� ���� ���� 
		{                    // thread ��� ���� 2�� ������ -> #pragma omp parallel num_threads(2) 
			printf("Welcome to OpenMP !!! - %d�� ������ ����\n", omp_get_thread_num());
		} // OpenMP ���ο��� fork & join ���� �Ͽ� { } ������ ���� ó���� �� !!!

		_getch();
	}
}