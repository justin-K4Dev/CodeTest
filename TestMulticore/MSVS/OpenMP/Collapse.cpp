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
/// @file OMP_Collapse.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Collapse()
{
	// 5.5.3 collapse 보조 지시어
	{
	/*
		: OpenMP 의 기본적인 기능 #pragma omp for 지시어 영역 안에 for 루프가 2개 이상 중첩 되면
		  가장 외각에 있는 for 루프 하나에 대해서만 병렬화를 지원함
		  #pragma omp for 지시어 영역 안에 #pragma omp for 지시어를 사용하려면
		  내포(nested) 병렬화를 지정 해야함
		  
		  또 다른 방법으로는 collapse 보조 지시어를 사용하여 내측의 루프에 대해서도
		  OpenMP 병렬 처리를 할 수 있음
		  2개 이상의 for 문에 대해서 하나의 #pragma omp for 지시어를 사용하고
		  collapse 보조 지시어를 이용하여 중첩할 루프 개수를 지정함

		  collapse 보조 지시어를 사용하면 내측에 있는 for 루프 구문을 전개하여
		  2개 이상의 for 문이 1개의 커다란 루프처럼 이루어짐
		  이것은 중첩된 for 루프만큼 스레드 수가 증가 하는 것이 아님
		  스레드 팀은 1개의 커다란 루프처럼 전개된 작업을 분할 하는 스케줄링을 하게 됨
		  collapse 보조 지시어는 병렬화의 효율을 향상 시킴
		  2개 이상의 for 문으로 전개 되는 것은 2차원 배열이 pc 메모리상에는 1차원으로 할당 되는 것과 유사함

		#pragma omp for collapse(루프갯수)

		[주의]
		- collapse 보조 지시어는 #pragma omp for 지시어에 한 번만 지정 할 수 있음
	*/

		int i = 0;
		int j = 0;
		int count = 0;

		#pragma omp parallel shared(count), private(i, j)
		{
			#pragma omp for collapse(2)  //중첩 갯수 지정
			for (i = 0; i < 10; i++) 
			{
				for (j = 0; j < 10; j++) 
				{
					#pragma omp atomic  //shared 변수에 대한 동기화
					count++;
				}

			}
		}

		printf("LoopCount:%d\n", count);

		_getch();
	}



}