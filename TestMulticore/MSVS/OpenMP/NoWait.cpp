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
/// @file OMP_NoWait.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_NoWait()
{
	// 5.4.1 nowiat 보조 지시어
	{
	/*
		: 프로그래머가 보기에 암시적 베리어가 필요 없다고 판단되면 수동으로 제거해 줄 수 있음
		  OpenMP 는 nowait 보조 지시어를 이용하여 암시적 베리어를 제거 하도록 해줌
		  nowait 가 지정되면 먼저 작업을 종료한 스레드는 병렬 영역 마지막 위치에서
		  베리어로 대기 하지 않고 다음 작업을 시작함
		  parallel 영역내에 독립된 복수의 분할 작업이 있는 경우
		  nowait 보조 지시어를 사용하여 성능을 개선 시킬 수 있음		

		#pragma omp wait
		#pragma omp sections nowait

		* 관련 지시어
		#pragma omp for 지시어
		#pragma omp sections 지시어
		#pragma omp singls 지시어

		[주의]
		- reduction 보조 지시어와 nowait 보조 지시어를 동시에 사용 했을 때,
		  각 스레드의 결과값을 합산 하는 과정중에 데이터 경합이 발생 될 수 있음
		- #pragma omp parallel 지시어 에는 nowait 는 지정 할 수 없음
		- #pragma omp parallel sections 지시어 에는 nowait 는 지정 할 수 없음
		- #pragma omp parallel for 지시어에 nowait 보조 지시어를 사용 할 수 없음
	*/

		const unsigned int MAX = 5;

		float *Data1 = new float[MAX];
		float *Data2 = new float[MAX];

		int i = 0;

		for (i = 0; i < MAX; i++) 
		{
			Data1[i] = (float) ( i + 1 );
			Data2[i] = (float) ( i + 1 );
		}

		#pragma omp parallel
		{
			printf("omp for nowait Start !!! - ThreadNo:%d\n", omp_get_thread_num());
		
			#pragma omp for nowait // for 루프 작업 1
			for (i = 0; i < MAX; i++) 
			{
				Data1[i] = sqrt(Data1[i]);

				printf("Called job - LoopID:%d, ThreadNo:%d\n", i, omp_get_thread_num());
			} // nowait 보조 지시어로 작업을 완료한 스레드는 다른 스레드가 완료 되기를 기다리지 않고 바로 다음 진행 

			printf("omp for Start !!! - ThreadNo:%d\n", omp_get_thread_num());

			#pragma omp for // for 루프 작업 2
			for (i = 0; i < MAX; i++) 
			{
				Data2[i] = log(Data2[i]);

				printf("Called job - LoopID:%d, ThreadNo:%d\n", i, omp_get_thread_num());
			}
		}

		_getch();
	}

}