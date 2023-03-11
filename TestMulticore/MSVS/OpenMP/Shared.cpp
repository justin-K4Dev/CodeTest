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
/// @file OMP_Shared.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Shared()
{
	// 5.1.2 shared 보조 지시어
	{
	/*
		: 변수명에 지정된 변수를 스레드 팀 내의 모든 스레드가 공유
		  task 지시어를 사용할 경우, 재귀적인 테스트 안에서 참조되는 변수를 shared 보조 지시어에
		  부모 영역(task 영역을 소유 하는 병렬 영역)의 값을 참조

		#pragma omp shared(변수명)

		* 관련 지시어
		#pragma omp parallel 지시어
		#pragma omp task 지시어

		[주의]
		- #pragma omp task 지시어 에서 변수가 shared 로 사용 되는 경우, task 영역의 처리가 종료 되기 전에 변수가 소멸 되서는 안됨

	*/
		#pragma omp parallel
		{
			int a = 0, b = 0;

			#pragma omp single
			{
				for (int iCount = 0; iCount < 10; ++iCount) 
				{
					// a 는 스레드간에 공유 , b 는 스레드간에 공유 안됨 !!!
					#pragma omp task shared(a), private(b)
					{
						#pragma omp atomic
						a++;

						#pragma omp atomic
						b++;
					}
				}
			}

			#pragma omp single
			printf("shared a: %d, private b: %d\n", a, b);
		}

		_getch();
	}


}