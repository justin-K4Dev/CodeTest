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
/// @file OMP_Critical.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Critical()
{
	// 3.5 critical 지시어
	{
	/*
		: #pragma omp critical 지시어 이후에 크리티컬 객체 이름을 지정 하여 사용
		  같은 크리티컬 객체명으로 지정된 영역은 한번에 하나의 스레드만 실행 됨
		  다른 스레드가 같은 이름의 크리티컬 객체를 먼저 사용 하고 있을 때,
		  먼저 실행한 스레드가 크리티컬 영역의 동작이 완료 될때 까지 진입 지점에서 대기
		  보통 크리티컬 섹션은 어느 한 구문을 동기화 할때 사용

		#pragma omp critical[(크리티컬 객체명)]
		{ <- 진입 지점
			to do here job
		} <- 완료 지점

		[주의]
		- critical 지시어는 #pragma omp parallel 지정된 영역의 스레드 팀 뿐만 아니라,
		  프로그램 안의 모든 스레드 동기 실행에 사용 할 수 있음
		- #pragma omp critical 지시어 영역 내에서는 for 지시어 or single 지시어를 사용 할 수 없음
		- C++ 에서는 critical 지시어 영역 내에서 throw 된 예외는 같은 critical 영역에서 실행을 재개 해야 함 !!!
		  그리고 throw 된 예외는 동일한 스레드가 catch 해야 함 !!!
	*/

		const int MAX = 1000;
		float *Data;
		Data = new float[MAX];

		int i = 0;
		for (i = 0; i < MAX; i++) {
			Data[i] = (float)i;
		}

		float max = 0;

		#pragma omp parallel for
		for (i = 0; i < MAX; i++) 
		{
			#pragma omp critical(MAXVALUE)
			{
				// 여러개의 스레드가 동일한 메모리에 접근 & 갱신할 때
				// critical 을 이용하여 동기화를 보장해야 함.
				if (max < Data[i]) {
					max = Data[i];
				}

			}
		}

		printf("MaxValue:%.3f\n", max);
		delete Data;

		_getch();
	}
}