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
	// 2.1 for 지시어
	{
	/*
		: for 루프 문을 병렬화
		  for 루프 문을 수행할 때 작업을 배분해 주는 양이나 방법을 정하는 규칙을 스케줄 이라 함

		#pragma omp parallel
		{
			#pragma omp for [보조 지시어 [,보조 지시어]...]
			for ( 초기값, 조건식, 증감값 ) <- private 변수 자동 지정
			{
				to do here job !!!
			}
		}

		#pragma omp parallel for
		for ( 초기값, 조건식, 증감값 ) <- private 변수 자동 지정
		{
			to do here job !!!
		}

		* 사용 가능한 보조 지시어
		#pragma omp parallel private(변수명)
		#pragma omp parallel firstprivate(변수명)
		#pragma omp parallel lastprivate(변수명)
		#pragma omp parallel reduction(오페레이터:변수명)
		#pragma omp parallel collapse(정수)
		#pragma omp parallel ordered
		#pragma omp parallel nowait

		[주의]
		- 중첩 for 인 경우 첫번째 for 만 병렬 처리 !!!
		- schedule 보조 지시어, collapse 보조 지시어, ordered 보조 지시어는
		  하나의 #pragma omp for 지시어에 한번만 사용 가능
		- 중첩 for 를 병렬 처리 해야 할 경우 
		  collapse 보조 지시어 or omp_set_nested() 함수 사용시 가능
		- 병렬 for 루프 안에서 throw 한 예외는 같은 병렬 루프내에서 catch 해야 함 !!!
		- #pragma omp parallel for 통합 지시어 에서는 nowait 보조 지시어를 설정 못함
		  nowait 보조 지시어를 사용 해야 하는 경우 
		  #pragma omp parallel & #pragma omp for 지시어를 개별적으로 사용 해야 함
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

		#pragma omp parallel // 병렬 처리 구간 지시 
		                     // thread 사용 갯수 2개 지정시 -> #pragma omp parallel num_thread(2) 
		{
			#pragma omp for // for loop 형태로 thread 배분 해서 병렬 처리 지시
			for ( int nCount = 0;
				  nCount < MAX;
				  ++nCount )
			{
				pData[nCount] = sqrt (pData[nCount]);

				printf("LoopID:%d - ThreadNo:%d\n", nCount, omp_get_thread_num());
			}
		} // OpenMP 내부에서 fork & join 구분 하여 { } 구간을 병렬 처리해 줌 !!!

		printf("omp for End !!!");

		delete [] pData;
	
		_getch();
	}

}