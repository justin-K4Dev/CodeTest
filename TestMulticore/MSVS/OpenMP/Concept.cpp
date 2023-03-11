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
/// @file OMP_Concept.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Concept()
{
	// OpenMP ����ȭ �ڵ� �̽� ���

	{
		const int MAX = 10000;
		float *pData = NULL;

		pData = new float[MAX];

		for ( int nCount = 0;
			  nCount < MAX;
			  ++nCount )
		{
			pData[nCount] = (float)nCount;
		}

		#pragma omp parallel // ���� ó�� ���� ���� 
		                     // thread ��� ���� 2�� ������ -> #pragma omp parallel num_thread(2) 
		{
			#pragma omp for // for loop ���·� thread ��� �ؼ� ���� ó�� ����
			for ( int nCount = 0;
				  nCount < MAX;
				  ++nCount )
			{
				pData[nCount] = sqrt (pData[nCount]);

				char szBuff[128];
				sprintf_s(szBuff, 128, "Called Job - ThreadNo:%d, LoopID;%d", omp_get_thread_num(), nCount);
				std::cout << szBuff << std::endl;
			}
		} // OpenMP ���ο��� fork & join ���� �Ͽ� { } ������ ���� ó���� �� !!!

		delete [] pData;

		_getch();
	}

	{
		const int MAX = 10000;
		int nCount = 0;

		float *pData1 = new float[MAX];
		float *pData2 = new float[MAX];

		for ( int nCount = 0;
			  nCount < MAX;
			  ++nCount )
		{
			pData1[nCount] = (float)nCount;
		}

		for ( int nCount = 0;
			  nCount < MAX;
			  ++nCount )
		{
			pData2[nCount] = (float)nCount;
		}

		#pragma omp parallel
		{
			#pragma omp sections // ���� �й� ���� ����
			{
				#pragma omp section // ���� �й� 1 ���� ���� ���� - 1 ���� thread ���
				{
					for ( int nCount = 0;
						nCount < MAX;
						++nCount )
					{
						pData1[nCount] = sqrt (pData1[nCount]);

						char szBuff[128];
						sprintf_s(szBuff, 128, "Called Job - ThreadNo:%d, LoopID;%d", omp_get_thread_num(), nCount);
						std::cout << szBuff << std::endl;
					}
				}

				#pragma omp section // ���� �й� 2 ���� ���� ���� - 1 ���� thread ���
				{
					for ( int nCount = 0;
						  nCount < MAX;
						  ++nCount )
					{
						pData2[nCount] = sqrt (pData2[nCount]);

						char szBuff[128];
						sprintf_s(szBuff, 128, "Called Job - ThreadNo:%d, LoopID;%d", omp_get_thread_num(), nCount);
						std::cout << szBuff << std::endl;
					}
				}
			}
		}

		delete [] pData1;
		delete [] pData2;

		_getch();
	}

}