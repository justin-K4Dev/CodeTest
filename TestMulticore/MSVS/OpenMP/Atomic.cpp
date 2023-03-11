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
/// @file OMP_Atomic.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Atomic()
{
	// 3.4 atomic ���þ�
	{
	/*
		: OpenMP ���� ���� ���� ���� ���� �����尡 �ϳ��� ���� ������ ���ÿ� ���� �Ҷ� 
		  �߻� �� �� �ִ� ���� (race condition) �� ����
		  ���� ������ ���ؼ� �б�, ���Ⱑ �ѹ��� �̷������ ������ ������ ���

		#pragma omp atomic

		[����]
		- x = x + 1 �� ���� ���� atomic ������ �ƴϱ� ������ atomic ���þ ��� �ص� ���ռ� ������ ���� �� ����
		- x += func(x) ���� x ���� param ���� ��� �ϰ� �־ atomic ���þ ��� �� �� ����
		- atomic ���� ������ { } �� ��� �� �� ����
	*/

		int nThreadCount = 0;

		#pragma omp parallel num_threads(10) //������ 10�� ����
		{
			#pragma omp atomic
			nThreadCount++;
		}

		printf("Created Thread Count: %d\n", nThreadCount);

		_getch();
	}


}