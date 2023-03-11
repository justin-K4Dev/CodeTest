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
	// 3.2 barrier ���þ�
	{
	/*
		: ������ ���� ��� �����带 ����ȭ �ϰ�, �� ������� ������ ���� ��� �����尡 
		  #pragma omp barrier ��ġ�� ���� �Ҷ� ���� ��� ��

		#pragma omp barrier

		[����]
		- C++ ����� ���� ��Ģ�� ��� �Ǵ� �������� ��� ���� �ϰ�, if, while do, switch �� ���� ���Ŀ� ��� �� �� ����
		- barrier ���þ�� OpenMP for, sections, single, critical ���þ� ���� ������ ��� �� �� ����
		- barrier ���þ ����� ��� �� �ϳ��� ������ �� ���� ���� ���ϸ� barrier ���� ������ �ڵ带 ���� ���� ���� !!!
		- if �� ���Ŀ� #pragma omp barrier ���� { } �� ������� �� !!!
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