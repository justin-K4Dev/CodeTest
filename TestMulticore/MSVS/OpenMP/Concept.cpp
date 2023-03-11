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
	// OpenMP 병렬화 코드 이식 방법

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

		#pragma omp parallel // 병렬 처리 구간 지시 
		                     // thread 사용 갯수 2개 지정시 -> #pragma omp parallel num_thread(2) 
		{
			#pragma omp for // for loop 형태로 thread 배분 해서 병렬 처리 지시
			for ( int nCount = 0;
				  nCount < MAX;
				  ++nCount )
			{
				pData[nCount] = sqrt (pData[nCount]);

				char szBuff[128];
				sprintf_s(szBuff, 128, "Called Job - ThreadNo:%d, LoopID;%d", omp_get_thread_num(), nCount);
				std::cout << szBuff << std::endl;
			}
		} // OpenMP 내부에서 fork & join 구분 하여 { } 구간을 병렬 처리해 줌 !!!

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
			#pragma omp sections // 병렬 분배 구간 지시
			{
				#pragma omp section // 병렬 분배 1 구간 설정 지시 - 1 개의 thread 사용
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

				#pragma omp section // 병렬 분배 2 구간 설정 지시 - 1 개의 thread 사용
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