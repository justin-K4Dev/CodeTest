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
/// @file OMP_Barrier.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Barrier()
{
	// 3.2 barrier 지시어
	{
	/*
		: 스레드 팀의 모든 스레드를 동기화 하고, 각 스레드는 스레드 팀의 모든 스레드가 
		  #pragma omp barrier 위치에 도달 할때 까지 대기 함

		#pragma omp barrier

		[주의]
		- C++ 언어의 문법 규칙에 허용 되는 곳에서만 사용 가능 하고, if, while do, switch 문 등의 직후에 사용 할 수 없음
		- barrier 지시어는 OpenMP for, sections, single, critical 지시어 영역 내에서 사용 할 수 없음
		- barrier 지시어를 사용한 경우 단 하나의 스레드 라도 도달 하지 못하면 barrier 지점 이후의 코드를 실행 하지 못함 !!!
		- if 문 이후에 #pragma omp barrier 사용시 { } 로 감싸줘야 함 !!!
	*/

		#pragma omp parallel num_threads(4)
		{
			#pragma omp master    
			{        
				printf("Called master job - ThreadNo:%d\n", omp_get_thread_num());
			}
			
			#pragma omp barrier    
			printf("Called job end - ThreadNo:%d\n\n", omp_get_thread_num());
		}

		_getch();
	}

}