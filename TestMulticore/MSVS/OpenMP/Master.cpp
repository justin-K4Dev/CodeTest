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
/// @file OMP_Master.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Master()
{
	// 3.1 master ���þ�
	{
	/*
		: ������ ������ ������ �����尡 �ش� �ڵ带 ���� �ϵ��� ��
		  #pragma omp master ���þ�� ����ȭ�� ���� ���� �ʱ� ������
		  �ٸ� ��������� ���Ŀ� ������ �ڵ带 ���� �ϰ� �ǹǷ�
		  ������ �����尡 �Ϸ� �� �� ���� ��� �Ϸ��� barrier ���þ ��� �ؾ� ��

		#pragma omp master
		{
			to do here job
		}

		[����]
		- #pragma omp master ���þ� ���� ���� ����� throw �� 
		  #pragma omp master ���þ��� ���� ���� ������ ������ �簳 �ؾ� ��
		  �׸��� throw �� ���ܴ� ������ �����忡 ���ؼ� catch �ؾ� ��
	*/

		const int MAX = 1000000;
		float *Data;
		Data = new float[MAX];

		int iCount = 0;
		for (iCount = 0; iCount < MAX; iCount++) {
			Data[iCount] = (float)iCount;
		}

		#pragma omp parallel
		{
			#pragma omp for

			for (iCount = 0; iCount < MAX; iCount++) {
				Data[iCount] = sqrt(Data[iCount]);
			}

			//��� ���

			#pragma omp master
			for (iCount = 0; iCount < MAX; iCount++) {
				printf("Data[%d] = %.4f\n", iCount, Data[iCount]);
			}

			//������� �踮��
			#pragma omp barrier
			#pragma omp for
			for (iCount = 0; iCount < MAX; iCount++) {
				Data[iCount] = log(Data[iCount]);
			}

		}

		delete Data;

		_getch();
	}

}