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
/// @file OMP_CopyPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

int a = 0;
#pragma omp threadprivate(a)

void TestOMP_CopyPrivate()
{
	// 5.2.2 copyprivate 보조 지시어
	{
	/*
		: copyin 보조 지시어는 병렬 영역에서 처음 초기화 할 때만 
		  마스터 스레드에 있는 threadprivate 변수의 값을 각 스레드로 전달 하여 복사 할 수 있음
		  copyprivate 보조 지시어는 threadprivate 변수를 병렬 영역 안에서 원하는 지점에 원하는 값으로
		  각 스레드에 복사 할 수 있음
		  재귀 처리나 내포 병렬 같이 공유 변수의 값 전달이 어려울 때 유용하게 사용 할 수 있음
		  하지만 copyprivate 보조 지시어는 #pragma single 지시어 에서만 사용 할 수 있음

		#pragma omp single copyprivate(변수명)

		* 관련 지시어
		#pragma omp single 지시어
		#pragma omp threadprivate 지시어

		[주의]
		- #pragma omp single 지시어 안에서 copyprivate 보조 지시어로 지정한 변수를
		  다시 pirvate 보조 지시어 또는 firstprivate 보조 지시어의 변수로 지정 할 수 없음
	*/
		#pragma omp parallel num_threads(4)
		{
			a = omp_get_thread_num();

			printf("Copyprivate before ThreadNo:%d, a=%d\n", omp_get_thread_num(), a);

			#pragma omp single copyprivate(a) // 이 시점에 a 값을 변경 하고 각 스레드에 전달 !!!
			{
				a = 7;
				printf("\n");
			}

			printf("Copyprivate after Thread:%d, a=%d\n", omp_get_thread_num(), a);

			#pragma omp barrier
			#pragma omp single
			printf("\n");

			a = omp_get_thread_num();
			printf("ThreadNo:%d, a=%d\n", omp_get_thread_num(), a);
		}

		_getch();
	}
}