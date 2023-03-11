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
/// @file OMP_Ordered.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Ordered()
{
	// 3.7 ordered 지시어
	{
	/*
		: OpenMP 에서 루프 병렬 영역 내의 인덱스 변수에 순차 실행이 필요한 경우
		  #pragma omp ordered 지시어를 사용 하면 됨
		  ordered 지시어를 사용할 경우 인덱스의 카운터에 따라 0 부터 오름차순으로 차례대로 실행됨

		#pragma omp for ordered
		for ( 초기값; 조건식; 증감값 )
		{
			#pragma omp ordered
			to do here job
		}

		[주의]
		- #pragma omp ordered 지시어를 사용 하기 위해서는 
		  #pragma omp for 지시어 이후에 아래와 같이 ordered 보조 지시어를 지정 해야 함
		  #pragma omp parallel for ordered
	*/

		printf("ordered not use: ");

		#pragma omp parallel
		{
			#pragma omp for
			for (int i = 0; i < 10; i++)
			{
				printf(" %d ", i);
			}

			#pragma omp single
			{
				printf("\nordered use: ");
			}

			#pragma omp for ordered
			for (int i = 0; i < 10; i++)
			{
				#pragma omp ordered
				printf(" %d ", i);
			}

		}

		printf("\n");

		_getch();
	}

}