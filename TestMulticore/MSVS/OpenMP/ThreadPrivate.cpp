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
/// @file OMP_ThreadPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

int A[2] = { 1, 1 };
#pragma omp threadprivate(A)

void TestOMP_ThreadPrivate()
{
	// 4.1 threadprivate 지시어
	{
	/*
		: 글로벌 메모리에 있는 변수를 threadprivate 지시어로 지정 하게 되면,
		  각 스레드는 로컬 메모리에 영역에 할당 & 복사 하여 사용 할 수 있음
		  threadprviate 지시어로 변수를 지정 하면, 각 스레드는 스레드 로컬 메모리 영역에 할당 하고
		  글로벌 영역에 있는 변수값을 복사함.
		  시리얼 영역을 실행 하는 코드와 마스터 스레드는 글로벌 영역에 있는 원본 변수값을 접근 하게 됨

		#pragma omp threadprivate(변수명)

		[주의]
		- threadprivate 변수의 값은 각 스레드가 그 값을 복사 하기 전에 초기화 해야 함
		  보통 마스터 스레드가 프로그램의 시리얼 실행 중에 초기화 하게 됨
		- private 변수 처럼 스레드는 threadprivate 변수를 복사 하여 참조 할 수 없고,
		  프로그램의 시리얼 영역 및 마스터 스레드 영역의 변수를 복사 하여 참조 해야 함
		- 각 스레드 내의 threadprivate 변수가 유효 하려면 최초에 생성한 병렬 영역의 스레드 수가 변경 되지 않아야 함
		- threadprivate 변수는 copyin, schedule, num_threads, if 보조 지시어를 제외한 다른 보조 지시어는 지정 할 수 없음
		- C++ 클래스의 정적 데이터 멤버를 제외 하고 배열 이나, 구조체, 클래스의 일부 요소는
		  threadprivate 보조 지시어로 지정 할 수 없음
		- 레퍼런스형 변수는 사용 할 수 없음
		- threadprivate 변수의 어드레스는 주소 상수가 아님
		
		[TIP] 클래스형 변수에 threadprivate 지시어를 지정 하려면 아래의 조건을 충족 해야 함
		- 초기화 인수 없는 디폴트 초기화인 경우, 접근 가능 하고 정확한 디폴트 constructor 가 있어야 함
		- 직접적인 초기화의 경우, 인수를 받아들여 접근 가능 하고 정확한 디폴트 constructor 가 있어야 함
		- 명시적인 초기화 객체를 동반한 복사 생성의 경우, 접근 가능 하고 정확한 constructor 가 있어야 함
	*/

		A[1] = 2;
		printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());

		#pragma omp parallel num_threads(4)
		{
			printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());
		}

		printf("\n");

		A[0] = 3;
		printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());

		#pragma omp parallel num_threads(4)
		{
			A[1] = 4;

			printf("A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());
		}

		printf("LastCode - A[0]:%d, A[1]:%d - ThreadNo:%d\n", A[0], A[1], omp_get_thread_num());

		_getch();
	}
}