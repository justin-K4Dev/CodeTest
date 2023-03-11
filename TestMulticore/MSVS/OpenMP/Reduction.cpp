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
/// @file OMP_Reduction.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Reduction()
{
	// 5.1.6 reduction 보조 지시어
	{
	/*
		: 각 스레드별로 연산된 결과값을 다시 취합하여 메인 영역으로 전달 할때 사용
		  reduction 보조 지시어는 지정되는 오퍼레이터를 이용하여 스레드 별로 연산할 결과를 취합 함
		  병렬 영역 내에서의 스레드 변수의 값을 취합할 때 동기화를 지원
		  변수명에 지정된 변수는 각 스레드 별로 프라이빗 속성을 가지고
		  오퍼레이터 별로 지정된 값으로 초기화 함
		  변수명에 복수의 변수를 지정 할 수 있음 예) (+:a, b)

		* 오퍼레이터별 초기값
		  +  :  0
		  *  :  1
		  -  :  0
		  &  :  ~0
		  |  :  0
		  ^  :  0
		  && :  1
		  || :  0

		#pragma omp parallel recdunction(오퍼레이터:변수명)
		#pragma omp for reduction(오퍼레이터:변수명)
		#pragma omp parallel for reduction(오퍼레이터:변수명)

		[주의]
	    - 디폴트로 사용된 reduction 보조 지시어는 모든 스레드의 종료를 기다리고 데이터 동기화를 지원 함
		  nowait 보조 지시어와 함께 reduction 보조 지시어를 사용할 경우,
	 	  각 스레드는 모든 스레드의 종료를 기다리지 않기 때문에 순차 영역의 변수에 결과값을 취합 할때 경합을 벌이게 됨

          #pragma omp parallel
	      {
              #pragma omp for reduction(+:sum) nowait
	      }

	    - 배열, 포인터, 레퍼런스형 변수는 reduction 보조 지시어의 변수로 사용할 수 없음
		- const 수식된 변수는 reduction 보조 지시어의 변수로 사용할 수 없음
		- reduction 보조 지시어로 지정하는 변수는 오퍼레이터가 조작 할 수 있는 있는 데이터형 이어야 함
	*/

		int sum = 0, i = 0;

		int Data[100];

		for (i = 0; i < 100; ++i) 
		{
			Data[i] = 1;
		}

		// sum 변수가 각 스레드별로 생성되어 메인 스레드의 sum 변수에 동기화 하면서 자동으로 누적 !!! 
		#pragma omp parallel for reduction(+:sum)
		for (i = 0; i < 100; ++i) 
		{
			sum += Data[i];
		}

		printf("Total:%d\n", sum);

		_getch();
	}
}