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
/// @file OMP_FirstPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_FirstPrivate()
{
	// 5.1.4 firstprivate 보조 지시어
	{
	/*
		: firstprivate 보조 지시어는 프라이빗 보조 지시어와 기본적인 기능은 동일하게 동작하나
		  변수의 값을 초기화 하는 기능이 추가 되어 있음
		  프라이빗 변수는 메인 영역의 변수값이 병렬 영역 안의 변수로 전달 되지 않고
		  각 스레드가 개별적으로 변수값을 초기화 하여 사용 해야 함

		#pragma omp parallel firstprivate(변수명)

		* 관련 지시어
		#pragma omp parallel 지시어
		#pragma omp sections 지시어
		#pragma omp task 지시어

		[주의]
		- private 보조 지시어와 동일
	*/

		float A[5] = { 1, 2, 3, 4, 5 };

		printf("ThreadNo:%d - A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		#pragma omp parallel num_threads(3), firstprivate(A) // 현재 A 의 값으로 초기화 됨
		{
			A[3] = 7;

			printf("ThreadNo:%d - A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);
		}

		printf("ThreadNo:%d - A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		_getch();
	}
}