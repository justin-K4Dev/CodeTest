#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-22-2012 13:04:23
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <omp.h>


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_Sections.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Single()
{
	// 2.3 single 지시어
	{
	/*
		: 스레드 팀중 하나의 스레드만 해당 코드를 실행 할 것을 지정
		  다른 스레드는 single 지시어로 지정된 스레드가 완료 될 때까지
		  single 구조 블럭의 마지막 지점에서 암시적 동기로 대기

		#pragma omp single [보조 지시어 [,보조 지시어]...]
		{
			to do here job

			여기서 다른 스레드들은 해당 스레드의 완료를 대기
		}

		* 사용 가능한 보조 지시어
		#pragma omp single private(변수명)
		#pragma omp single firstprivate(변수명)
		#pragma omp single copyprivate(변수명)
		#pragma omp single nowait

		[주의]
		- single 영역에 진입되는 스레드는 스레드 팀 내부의 어느 스레드가 될지 알 수 없음
		- single 지시어는 for 구문 안에 작성 할 수 없음
		- single 지시어는 nowait 보조 지시어와 copyprivate 보조 지시어를 동시에 이용 불가
		- 병렬 for 루프 안에서 throw 한 예외는 같은 병렬 루프내에서 catch 해야 함 !!!
	*/

		printf("omp single Start !!!\n");

		#pragma omp parallel
		{
			printf("parallel - ThreadNo:%d\n", omp_get_thread_num());

			#pragma omp single  // 암시적 동기 설정
			printf("omp single - ThreadNo:%d\n", omp_get_thread_num());
		}

		printf("omp single End !!!\n");

		_getch();
	}
}