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
/// @file OMP_Parallel.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Parallel()
{
	// 병렬 처리 지시어
	{
	/*
	    : OpenMP 병렬화 영역 지정 

		#pragma omp parallel [보조 지시어 [,보조 지시어]...]
		{ <- 병렬의 시작 지점
			to do here job !!!
		} <- 병렬의 종료 지점 - 모든 스레드 관련 리소스 소멸 !!!

		* 사용 가능한 보조 지시어
		#pragma omp parallel if(조건식)
		#pragma omp parallel num_threads(정수값)
		#pragma omp parallel default(shared 또는 none)
		#pragma omp parallel private(변수명)
		#pragma omp parallel firstprivate(변수명)
		#pragma omp parallel shared(변수명)
		#pragma omp parallel copyin(변수명)
		#pragma omp parallel reduction(오페레이터:변수명)

		[주의]
		- 병렬 영역 지정 및 스레드 생성 (명시적 스레드 수 지정 or 시스템 이용 가능한 기본 스레드 수)
		- parallel 지시어는 스레드 생성만 지원할 뿐 병렬 영역의 작업 분할은 관여 하지 않으므로
		  parallel 지시어와 함께 sections, for 지시어 를 사용 하여 작업 분할을 해주어야 효율성 향상
	*/
		#pragma omp parallel // 병렬 처리 구간 지시 
		{                    // thread 사용 갯수 2개 지정시 -> #pragma omp parallel num_threads(2) 
			printf("Welcome to OpenMP !!! - %d번 스레드 동작\n", omp_get_thread_num());
		} // OpenMP 내부에서 fork & join 구분 하여 { } 구간을 병렬 처리해 줌 !!!

		_getch();
	}
}