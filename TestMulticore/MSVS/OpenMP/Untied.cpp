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
/// @file OMP_Untied.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Untied()
{
	// 5.5.2 untied 보조 지시어
	{
	/*
		: #pragma omp task 지시어를 사용 하여 태스크 병렬 처리를 진행 하는 동안
		  OpenMP는 때때로 다시 스케줄링 하여 스레드의 작업을 분배함
		  다시 스케줄링 하는 경우는 실행해야 할 태스크의 개수가 상당히 많을 수록
		  가능성이 커짐

		  스케줄링 하는 시점은 새로 태스크를 시작할 경우, taskwait 지시어를 만났을 경우와
		  마지막 위치에 도달 했을 때임
		  태스크를 진행 중인 스레드도 작업을 일시 중지하고 이후 진행할 작업을 분배 받게 됨
		  스케줄링이 끝나면 일시 중지 되었던 태스크를 다시 진행 하게 되는데,
		  디폴트 설정을 중지되기 전에 작업을 진행 하던 스레드가 이어 받아 작업함

		  프로그래머가 판단 하여 만일 태스크 작업의 세부 내용이 스레드 작업과 독립적으로 수행 할 수 있어서
		  일시 중지한 태스크를 다른 스레드가 이어서 작업해도 무방하다면, untied 보조 지시어로 설정 할 수 있음
		  untied 보조 지시어로 설정되면, 태스크를 일시 중지하고 스케줄링 작업이 끝난 뒤에
		  가장 빠르게 할당 받은 스레드가 중지된 작업을 이어서 진행 하게 됨
		  이렇게 설정된 작업을 언타이드 태스크 라고 함

		  다시 설명하면 태스크의 갯수가 많을 수록 시스템은 때때로 다시 스케줄링을 진행함
		  작업중인 스레드도 중지하고 스케줄링에 동참하게 되며 스케줄링이 끝나면
		  중지전에 작업을 진행했던 스레드가 이어 받아 작업함
		  하지만 untied 보조 지시어가 설정되면 스케줄링 작업이 끝난뒤
		  가장 빠르게 할당 받은 스레드가 중지된 작업을 이어 받음

		#pragma omp task untied
	*/

		#pragma omp single
		{
			#pragma omp task untied
			for(int i = 0; i < 1000; i++) 
			{
				printf("Called task 1 job - LoopID:%d, ThreadNo:%d\n", i, omp_get_thread_num());
			}

			#pragma omp task
			for(int i = 0; i < 1000; i++) 
			{
				printf("Called task 2 job - LoopID:%d, ThreadNo:%d\n", i, omp_get_thread_num());
			}

			#pragma omp task
			{
				printf("Called task 3 job - ThreadNo:%d\n", omp_get_thread_num());
			}
		}



		_getch();
	}

}