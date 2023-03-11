#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-22-2012 14:43:42
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <omp.h>

int Fibonacci( int n )
{
	int x, y;

	if( n < 2 )
	{
		return n;
	}
	
	x = Fibonacci( n - 1 );
	y = Fibonacci( n - 2 );

	return ( x + y );
}


int FibonacciByTack( int n )
{
	int x, y;

	if( n < 2 )
	{
		return n;
	}

	printf("omp task shared(x) Start !!! - (n:%d), ThreadNo:%d\n", n, omp_get_thread_num());
	
	#pragma omp task shared( x ) // task 지정 및  shared 설정으로 x 값을 taskwait 이후에도 공유 됨
	x = Fibonacci( n - 1 );

	printf("omp task shared(y) Start !!! - (n:%d), ThreadNo:%d\n", n, omp_get_thread_num());

	#pragma omp task shared( y ) // task 지정 및 shared 설정으로 y 값을 taskwait 이후에도 공유 됨
	y = Fibonacci( n - 2 );

	#pragma omp taskwait // 모든 task 완료 대기 지시
	printf("Fibonacci = %d(x:%d, y:%d), ThreadNo:%d\n", (x + y), x, y, omp_get_thread_num());

	return ( x + y );
}


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_Task.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 14:43:45
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Task()
{
	// 2.4 task 지시어
	{
	/*
		: task 지시어를 통해서 수행 해야 할 코드를 작업큐에 등록 하고,
		  스레드 팀과 연결 하여 작업큐에 등록된 코드를 스레드 팀이 실행 하며,
		  스레드는 작업을 완료한 후 반환, 단 동기화를 지원 하지 않기 때문에
		  taskwait 를 통해서 명시적으로 처리 해야 함
		  테스크를 작업큐에 등록 할때 동기화 문제가 발생 될 수 있기 때문에
		  보통은 #pragma omp single 지시어를 사용하여 하나의 스레드로 동작하게 함

		#pragma omp task
		{
			to do here job
		}

		* 사용 가능한 보조 지시어
		#pragma omp task if(스칼라식)
		#pragma omp task untied
		#pragma omp task default(shared 또는 none)
		#pragma omp task private(변수명)
		#pragma omp task firstprivate(변수명)
		#pragma omp task shared(변수명)
	*/
	}

	// 기본 예제
	{
		const int MAX = 10000;

		printf("Basic Example: omp single -> omp task Start !!!\n");

		_getch();

		#pragma omp parallel
		{
			#pragma omp single // 단일 thread 처리 지시
			{
				for( int n = 0;
					 n < MAX;
					 ++n )
				{
					#pragma omp task // task 지시
					{
						// to do here task !!!
						printf("LoopNo:%d, ThreadNo:%d\n", n, omp_get_thread_num());
					}
				}
			}
		}

		printf("Basic Example: omp single -> omp task End !!!\n\n");

		_getch();
	}

	// 응용 예제
	{
		const int MAX = 41;
		int nFibNoList[MAX] = { 0, };

		clock_t start, end;

		printf("omp for Start !!!\n");

		_getch();

		start = clock();
		#pragma omp parallel
		{
			#pragma omp for
			for( int n = 0;
				 n < MAX;
				 ++n )
			{
				nFibNoList[ n ] = Fibonacci( n );
				printf("LoopNo:%d, ThreadNo:%d\n", n, omp_get_thread_num());
			}

		}
		end = clock();

		printf("omp for End !!!\n");

		std::cout << "Parallel for" << std::endl; 
		std::cout << "Elapsed Time: " << (end - start) << " msec" << std::endl;
		std::cout << std::endl;

		int n = 0;

		printf("omp single -> omp task Start !!!\n");

		_getch();

		start = clock();
		#pragma omp parallel
		{
			#pragma omp single private( n ) // private( n ) - 병렬화 구역내 local 변수 지시
			for( n = 0;
				 n < MAX;
				 ++n )
			{
				#pragma omp task
				{
					nFibNoList[ n ] = Fibonacci( n );
					printf("LoopNo:%d, ThreadNo:%d\n", n, omp_get_thread_num());
				}
			}

		}
		end = clock();

		printf("omp single -> omp task End !!!\n");

		std::cout << "Task 1" << std::endl; 
		std::cout << "Elapsed Time: " << (end - start) << " msec" << std::endl;
		std::cout << std::endl;

		printf("omp single Start !!!\n");

		_getch();

		start = clock();
		#pragma omp parallel
		{
			#pragma omp single private( n ) // private( n ) - 병렬화 구역내 local 변수 지시
			for( n = 0;
				 n < MAX;
				 ++n )
			{
				nFibNoList[ n ] = FibonacciByTack( n );
				printf("LoopNo:%d, ThreadNo:%d\n", n, omp_get_thread_num());
			}

		}
		end = clock();

		printf("omp single End !!!\n");

		std::cout << "Task 2" << std::endl; 
		std::cout << "Elapsed Time: " << (end - start) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();
	}
}