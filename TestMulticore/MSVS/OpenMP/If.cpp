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
		if (omp_in_parallel()) // 병렬 영역인지 검사
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
	// 5.5.1 if 보조 지시어
	{
	/*
		: 특정 조건을 만족할 때만 OpenMP 지시어가 지정하는 기능을 제공받고 싶을 경우에 사용함
		  if의 구문이 true인 경우에만 동작하고 false인 경우에는 동작하지 않음

		#pragma omp parallel for if(조건식)

		* 관련 지시어
		#pragma omp parallel 지시어
		#pragma omp parallel for 지시어
		#pragma omp parallel sections 지시어
		#pragma omp task 지시어

		[TIP]
		//작업분할 구문의 if 보조 지시어 사용
		#pragma omp parallel sections if(omp_get_max_threads() > 3)
		{
			#pragma omp section
			...
			#pragma omp section
			...
			#pragma omp section
			...
		}

		//for 루프문에 if 보조 지시어 사용
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