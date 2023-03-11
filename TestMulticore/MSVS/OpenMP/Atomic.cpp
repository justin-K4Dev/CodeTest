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
/// @file OMP_Atomic.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Atomic()
{
	// 3.4 atomic 지시어
	{
	/*
		: OpenMP 병렬 영역 에서 여러 개의 스레드가 하나의 공유 변수를 동시에 변경 할때 
		  발생 할 수 있는 오류 (race condition) 를 방지
		  공유 변수에 대해서 읽기, 쓰기가 한번에 이루어지는 연산자 에서만 사용

		#pragma omp atomic

		[주의]
		- x = x + 1 과 같은 식은 atomic 조작이 아니기 때문에 atomic 지시어를 사용 해도 정합성 보장을 받을 수 없음
		- x += func(x) 에서 x 값을 param 으로 사용 하고 있어서 atomic 지시어를 사용 할 수 없음
		- atomic 구문 에서는 { } 를 사용 할 수 없음
	*/

		int nThreadCount = 0;

		#pragma omp parallel num_threads(10) //스레드 10개 생성
		{
			#pragma omp atomic
			nThreadCount++;
		}

		printf("Created Thread Count: %d\n", nThreadCount);

		_getch();
	}


}