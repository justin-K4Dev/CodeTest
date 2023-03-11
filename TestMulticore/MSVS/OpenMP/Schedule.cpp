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
/// @file OMP_Schedule.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Schedule()
{
	// 5.3.1 스케줄 속성 지정
	{
	/*
		: OpenMP 의 디폴트 설정은 static 으로 되어 있음
	      for 루프 전체 횟수를 스레드 수로 나누어 각 스레드에 분배 처리 함

		  디폴트 루프 분할 방법 (static)
		  작업 분할 크기 = 총 루프 카운트 / 스레드 개수

		  만일 연산 횟수가 스레드 수로 나누어 떨어지지 않으면, 처리를 먼저 끝낸 스레드가 추가로 실행
		  OpenMP 에서는 이러한 스케줄 방식을 schedule 보조 지시어를 사용 하여
		  스레드 팀의 반복 분배 방법을 변경 할 수 있음

		#pragma omp for schedule(스케줄 방식 덩어리 사이즈(chunk_size))
		chunk_size: 하나의 스레드가 한번의 스케줄 에서 처리할 연속된 작업의 덩어리 크기

		* schedule 보조 지시어 종류

		static
		: #pragma omp for schedule(static, chunk_size) 를 지정할 경우,
		  각 스레드에 덩어리로 지정한 크기의 작업량으로 할당 됨
		  분할된 작업은 라운드 로빈 방식으로 스레드 번호의 순서에 따라
		  팀 내의 스레드에 할당 됨
		  덩어리 크기가 지정되지 않은 경우 총 작업량을 스레드로 나누어 분할 함

		dynamic
		: #pragma omp for schedule(dynamic, chunk_size) 를 지정할 경우,
		  작업을 수행할 준비가 완료된 대기 상태의 스레드로 부터 작업 할당 요청을 함
		  dynamic의 의미 처럼 스케줄을 분배한 상태로 작업을 진행 하는 것이 아니라
		  작업을 할 수 있는 스레드가 있으면 그때 그때 배분 하는 방식 임
          각각의 스레드는 할당된 작업을 완료할 때까지 작업을 수행하고, 더는 진행할 작업이 없을 경우
		  다시 대기 상태로 들어가 작업 할당 요청을 함
		  분배하는 모든 작업량은 덩어리 크기로 지정한 만큼 반복적으로 분배 되고,
		  마지막에는 나머지 크기만큼 할당 함
		  덩어리 크기를 지정 하지 않았을 경우에는 디폴트로 1 임

		guided
		: #pragma omp for schedule(guided, chunk_size) 를 지정할 경우,
		  작업을 배분 하는 스케줄 방식은 dynamic 으로 지정 할 때와 같이 유휴 스레드가 있으면 작업을 할당 함
		  차이점은 배분하는 덩어리의 크기가 점차 줄어든다는 것
		  최초 할당 되는 덩어리 크기는 지정한 값이지만 각 스레드에 처음 할당된 작업이 완료 되면
		  크기에서 일정한 비율로 줄어든 크기만큼 재할당 함
		  반복해서 작업을 할당 받을 수록 덩어리 크기는 줄어들어 1과 같아짐
		  덩어리 크기를 지정하지 않았을 경우에는 디폴트 1 임

		auto
		: #pragma omp for schedule(auto, chunk_size)를 지정할 경우, 컴파일러 또는 실시간 시스템이 가장 적합하다고
		  판단 하는 스케줄링으로 설정 됨
		  단 OpenMP 3.0 이상에서 사용 가능

		runtime
		: #pragma omp for schedule(runtime)를 지정할 경우,
		  스케줄에 대한 결정은 프로그램이 실행 될 때까지 연기 되면,
		  스케줄과 덩어리 크기는 run-sched-var 내부 제어 변수값으로 설정됨
		  run-sched-var 내부 제어 변수는 OMP_SCHEDULE 환경 변수로 설정함
		  만일 설정된 값이 없으면 static와 동일 하게 적용됨

		[주의]
		- schedule 보조 지시어는 #pragma omp for 루프 지시어에 한 번만 지정 할 수 있음
		- 덩어리 크기는 반드시 양수 이어야 함
		- 덩어리 크기의 값은 팀내의 모든 스레드에 동일 하게 적용됨 (guided 설정 제외)
		- run-sched-var 내부 제어 변수는 팀내의 모든 스레드가 동일한 값이어야 함
		- schedule(runtime) 또는 schedule(auto)가 지정 됐을 경우 덩어리 크기를 설정 할 수 없음
	*/

		const int MAX = 100;

		int i = 0;

		// 스레드 별로 배분받을 작업을 저장할 2중 배열
		int Data[4][MAX] = { 0, };

		for (i = 0; i < MAX; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				Data[j][i] = 0;
			}
		}

		omp_set_num_threads(4); // 생성될 스레드 갯수 설정

		#pragma omp parallel
		{
			#pragma omp for schedule(static, 4)

			for (i = 0; i < MAX; i++)
			{
				// 할당받은 작업을 스레드 별로 배열에 저장
				Data[omp_get_thread_num()][i] = i;
			}

		}

		FILE *stream;

		char buf[20];

		if ((stream = fopen("./ScheduleStatic.txt", "w+")) == NULL)
		{
			fprintf(stderr, "File open error !!!\n");

			return;
		}

		memset(buf, 0x00, 20);

		sprintf(buf, "\t0번\t1번\t2번\t3번\n");

		fwrite(buf, strlen(buf)+1, 1, stream);

		// 저장된 스레드별 배분 데이터를 파일로 출력

		for (i = 0; i < MAX; i++) 
		{
			memset(buf, 0x00, 20);

			sprintf(buf, "\t%d\t%d\t%d\t%d\n", Data[0][i], Data[1][i], Data[2][i], Data[3][i]);

			fwrite(buf, strlen(buf)+1, 1, stream);
		}

		printf("Schedule Write complate\n");

		fclose(stream);

		_getch();
	}
}