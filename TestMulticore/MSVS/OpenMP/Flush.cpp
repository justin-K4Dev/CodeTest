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
/// @file OMP_Flush.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Flush()
{
	// 3.6 flush 지시어
	{
	/*
		: 하나의 메모리 변수에 여러 개의 스레드가 경합 (race condition) 을 벌이게 될 때
		  그 정합성을 유지 시켜줌
		  먼저 읽어간 스레드는 이전의 값을 가지고 연산을 수행 하게 되며,
		  이때 값을 변경을 한 스레드 에서 flush 지시어를 사용 하면,
		  다른 스레드 에서 읽어간 뷰가 갱신 되면서 데이터의 정합성을 유지 하게 됨
		  flush 지시어 사용시 변수명으로 지정한 메모리의 값을 스레드 팀 전체에 전달 하여
		  그 데이터 정합성을 유지 하고, 변수를 여러개 지정 할 수 있음
		  변수명을 지정하지 않은 flush 지시어는 코드에 있는 글로벌 변수를 모든 스레드에 변수값으로 전달
		  
		#pragma omp flush(변수명)

		[주의]
		- 변수명에 포인터가 지정 되었을 경우, 포인터 주소값이 flush 됨
		- OpenMP 병렬 영역 에는 다음과 같은 암시적인 flush 지점이 있음
		  parallel, critical, ordered 의 입구와 출구
		  nowait 가 지정 되지 않은 워크 셰어링 직전과 직후
		  테스크 스케줄 포인트의 직전과 직후
		  barrier 영역 안, omp_set_lock(), omp_unset_lock() 로 지시 되는 영역,
		  omp_test_lock, omp_set_nest_lock(), omp_test_nest_lock() 로 지시 되는 영역
		  flush 변수명이 지정 되었을 경우의, atomic 구분의 입구와 출구
	*/

		int a = 0, b = 0;

		#pragma omp parallel sections
		{
			#pragma omp section // 0번 쓰레드
			{
				b = 1;

				#pragma omp flush(a, b)
				if (a == 0) {
					printf("ThreadNo:0 - a:%d, b:%d\n", a, b);
				}
			}

			#pragma omp section // 1번 쓰레드
			{
				a = 1;

				#pragma omp flush(a, b)
				if (b == 0 ) {
					printf("ThreadNo:1 - a:%d, b:%d\n", a, b);
				}

			}
		}

		_getch();
	}


}