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
/// @file OMP_Sections.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Sections()
{
	// 2.2 sections 지시어
	{
	/*
		: 루프의 반복 작업 없이 여러 스레드에게 작업 단위로 배분 하여 병렬로 처리 하는 기능

		#pragma omp sections [보조 지시어 [,보조 지시어]...]
		{
			#pragma omp section
			{
				to do here job 1
			}

			#pragma omp section
			{
				to do here job 2
			}
		}

		* 사용 가능한 보조 지시어
		#pragma omp parallel private(변수명)
		#pragma omp parallel firstprivate(변수명)
		#pragma omp parallel lastprivate(변수명)
		#pragma omp parallel reduction(오페레이터:변수명)
		#pragma omp parallel schedule(종별 [,체크사이즈])
		#pragma omp parallel collapse(정수)
		#pragma omp parallel ordered
		#pragma omp parallel nowait

		[주의]
		- #pragma omp section 지시어는 단독으로 사용 될 수 없고, #pragma omp sections 지시어 영역 안에 있어야 함
		- #pragma omp section 지시어 안에 각 section 의 코드는 진입과 종료가 1개인 구조 블럭 이어야 함
		  하나의 section 안에서 다른 section 영역으로 분기 할 수 없음
		- #pragma omp section 지시어는 1개의 nowait 보조 지시어만 사용 할 수 있고,
		  #pragma omp parallel sections 처럼 통합 지시어 에서는 nowait 보조 지시어를 사용 할 수 없음
		- 병렬 for 루프 안에서 throw 한 예외는 같은 병렬 루프내에서 catch 해야 함 !!!
	*/

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

		printf("omp sections Start !!!\n");

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

						printf("section 1 - LoopID:%d, ThreadNo:%d\n", nCount, omp_get_thread_num());
					}
				}

				#pragma omp section // 병렬 분배 2 구간 설정 지시 - 1 개의 thread 사용
				{
					for ( int nCount = 0;
						  nCount < MAX;
						  ++nCount )
					{
						pData2[nCount] = sqrt (pData2[nCount]);

						printf("section 2 - LoopID:%d, ThreadNo:%d\n", nCount, omp_get_thread_num());
					}
				}
			}
		}

		printf("omp sections End !!!\n");

		delete [] pData1;
		delete [] pData2;

		_getch();
	}
}