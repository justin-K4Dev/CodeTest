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
/// @file OMP_Critical.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Critical()
{
	// 3.5 critical ���þ�
	{
	/*
		: #pragma omp critical ���þ� ���Ŀ� ũ��Ƽ�� ��ü �̸��� ���� �Ͽ� ���
		  ���� ũ��Ƽ�� ��ü������ ������ ������ �ѹ��� �ϳ��� �����常 ���� ��
		  �ٸ� �����尡 ���� �̸��� ũ��Ƽ�� ��ü�� ���� ��� �ϰ� ���� ��,
		  ���� ������ �����尡 ũ��Ƽ�� ������ ������ �Ϸ� �ɶ� ���� ���� �������� ���
		  ���� ũ��Ƽ�� ������ ��� �� ������ ����ȭ �Ҷ� ���

		#pragma omp critical[(ũ��Ƽ�� ��ü��)]
		{ <- ���� ����
			to do here job
		} <- �Ϸ� ����

		[����]
		- critical ���þ�� #pragma omp parallel ������ ������ ������ �� �Ӹ� �ƴ϶�,
		  ���α׷� ���� ��� ������ ���� ���࿡ ��� �� �� ����
		- #pragma omp critical ���þ� ���� �������� for ���þ� or single ���þ ��� �� �� ����
		- C++ ������ critical ���þ� ���� ������ throw �� ���ܴ� ���� critical �������� ������ �簳 �ؾ� �� !!!
		  �׸��� throw �� ���ܴ� ������ �����尡 catch �ؾ� �� !!!
	*/

		const int MAX = 1000;
		float *Data;
		Data = new float[MAX];

		int i = 0;
		for (i = 0; i < MAX; i++) {
			Data[i] = (float)i;
		}

		float max = 0;

		#pragma omp parallel for
		for (i = 0; i < MAX; i++) 
		{
			#pragma omp critical(MAXVALUE)
			{
				// �������� �����尡 ������ �޸𸮿� ���� & ������ ��
				// critical �� �̿��Ͽ� ����ȭ�� �����ؾ� ��.
				if (max < Data[i]) {
					max = Data[i];
				}

			}
		}

		printf("MaxValue:%.3f\n", max);
		delete Data;

		_getch();
	}
}