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
/// @file OMP_CopyIn.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

int a1 = 0;
int b1 = 0;

#pragma omp threadprivate(a1, b1) //a, b를 threadprivate 변수로 지정하여 스레드 내 로컬 메모리에 복사 생성
								  //하지만 값은 복사 되지 않음

void TestOMP_CopyIn()
{
	// 5.2.1 copyin 보조 지시어
	{
	/*
		: 전역 변수 또는 정적 변수를 threadprivate 보조 지시어로 지정 하면
		  병렬 영역 에서 사용할 때 프라이빗 변수로 사용 할 수 있음
		  생성된 스레드에도 로컬 메모리에 동일 이름의 프라이빗 변수가 생성 됨
		  threadprivate 보조 지시어로 지정된 변수가 병렬 영역에서 사용될 때
		  마스터 스레드에서 사용되는 변수의 값이 스레드의 로컬 변수로 전달 되지 않음
		  하지만 copyin 보조 지시어를 사용 하면 스레드의 로컬 메모리에 생성된 프라이빗 변수에 그 값을 전달 할 수 있음

		#pragma omp [parallel, parallel for, parallel sessions] copyin(변수명)

		* 관련 지시어
		#pragma opm parallel 지시어
		#pragma opm parallel for 지시어
		#pragma opm parallel sections 지시어

		[주의]
		- threadprivate 변수만 copyin 보조 지시어로 초기화 됨
		- 스레드 로컬 메모리에 선언된 변수를 copyin 의 인수로 지정 하여 사용 할 수 있음
	*/

		a1 = 1;
		b1 = 1;

		#pragma omp parallel num_threads(4)
		{
			printf("Copyin before ThreadNo:%d - a=%d, b=%d\n", omp_get_thread_num(), a1, b1);
		}

		printf("\n");

		#pragma omp parallel copyin(a1) num_threads(4) // 전역 a1 을 모든 스레드에 전달 !!!
		{
			printf("Copyin after ThreadNo:%d - a=%d, b=%d\n", omp_get_thread_num(), a1, b1);
		}

		_getch();
	}
}