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
/// @file OMP_Private.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Private()
{
	// 5.1.3 private 보조 지시어
	{
	/*
		: 스레드 팀 내의 각 스레드에서 private 보조 지시어로 지정된 변수를 스레드 로컬 메모리 영역에서 생성 하여 사용 하도록 함
		  프라이빗 변수는 단순히 스레드 로컬 메모리 영역이 할당 되는 것이기 때문에
		  순차 영역 오리지널 변수가 가지는 데이터 값은 전달 되지 않음
		  프라이빗 변수는 개별 스레드에서 초기화 해야 함

		#pragma omp parallel private(변수명)

		* 관련 지시어
		#pragma omp parallel 지시어
		#pragma omp task 지시어

		* 관련 보조 지시어
		firstprivate(변수명)
		lastprivate(변수명)

		[주의]
		- 프라이빗으로 선언된 변수는 병렬 영역 내에서 같은 이름으로 또 다시 선언 해서 사용하면 안됨
		- const형 & 레퍼런스형 변수는 프라이빗 으로 사용 못함
	*/

		float A[5] = { 1, 2, 3, 4, 5 };

		printf("ThreadNo:%d, Memory A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		#pragma omp parallel num_threads(3), private(A)
		{
			A[3] = 7;
			printf("ThreadNo:%d, Memory A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);
		}

		printf("ThreadNo:%d, Memory A[1]=%.2f, A[3]=%.2f\n", omp_get_thread_num(), A[1], A[3]);

		_getch();
	}
}