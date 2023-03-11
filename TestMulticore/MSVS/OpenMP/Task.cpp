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
	
	#pragma omp task shared( x ) // task ���� ��  shared �������� x ���� taskwait ���Ŀ��� ���� ��
	x = Fibonacci( n - 1 );

	printf("omp task shared(y) Start !!! - (n:%d), ThreadNo:%d\n", n, omp_get_thread_num());

	#pragma omp task shared( y ) // task ���� �� shared �������� y ���� taskwait ���Ŀ��� ���� ��
	y = Fibonacci( n - 2 );

	#pragma omp taskwait // ��� task �Ϸ� ��� ����
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
	// 2.4 task ���þ�
	{
	/*
		: task ���þ ���ؼ� ���� �ؾ� �� �ڵ带 �۾�ť�� ��� �ϰ�,
		  ������ ���� ���� �Ͽ� �۾�ť�� ��ϵ� �ڵ带 ������ ���� ���� �ϸ�,
		  ������� �۾��� �Ϸ��� �� ��ȯ, �� ����ȭ�� ���� ���� �ʱ� ������
		  taskwait �� ���ؼ� ��������� ó�� �ؾ� ��
		  �׽�ũ�� �۾�ť�� ��� �Ҷ� ����ȭ ������ �߻� �� �� �ֱ� ������
		  ������ #pragma omp single ���þ ����Ͽ� �ϳ��� ������� �����ϰ� ��

		#pragma omp task
		{
			to do here job
		}

		* ��� ������ ���� ���þ�
		#pragma omp task if(��Į���)
		#pragma omp task untied
		#pragma omp task default(shared �Ǵ� none)
		#pragma omp task private(������)
		#pragma omp task firstprivate(������)
		#pragma omp task shared(������)
	*/
	}

	// �⺻ ����
	{
		const int MAX = 10000;

		printf("Basic Example: omp single -> omp task Start !!!\n");

		_getch();

		#pragma omp parallel
		{
			#pragma omp single // ���� thread ó�� ����
			{
				for( int n = 0;
					 n < MAX;
					 ++n )
				{
					#pragma omp task // task ����
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

	// ���� ����
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
			#pragma omp single private( n ) // private( n ) - ����ȭ ������ local ���� ����
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
			#pragma omp single private( n ) // private( n ) - ����ȭ ������ local ���� ����
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