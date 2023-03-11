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
/// @file OMP_Default.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Default()
{
	// 5.1.1 default 보조 지시어
	{
	/*
		: OpenMP 병렬 영역 에서는 기본적으로 루프 인덱스를 제외한 모든 변수는 스레드 간에 공유 됨
		  이는 병렬 영역에 있는 변수의 기본 속성이 처음 부터 공유(shared) 속성을 가지는 것을 의미
		  병렬 영역의 모든 변수를 threadprivate 속성으로 저정 해야 할때,
		  공유 속성으로 지정한 변수가 있다면 프로그램 오류 발생 !!!
		  OpenMP 는 자동으로 공유 속성이 되는 것을 방지 하는 기능을 제공 하고 있는 데
		  이것은 default 보조 지시어 임
		  default 보조 지시어는 변수의 데이터 유효 범위 속성을 설정
		  예를 들어 deault(none) 로 지정 하면 영역 안에서 모든 변수를 개별 스레드에서만 참조 할 수 있는
		  private 속성 or 공유 할 수 있는 공유 속성으로 모두 지정 해야 함
		  또 default(shared) 로 지정 하게 되면 영역내에서 참조 하는 모든 글로벌 변수를 공유 할 수 있음
		  C/C++ 디폴트의 데이터 속성은 default(shared) 이므로 보통은 지정 할 필요가 없음

		  #pragma omp parallel default(shared|none)

		  * 관련 지시어
		  #pragma omp parallel 지시어
		  #pragma omp task 지시어

		  [주의]
		  - default(none) 가 지정 되었을 경우, 구문 내에서 참조 하는 모든 공유 데이터는 명시적으로 데이터 속성을 정의 해야 함
		    정의 하지 않을 경우 컴파일 에러가 난다.
		  - default 보조 지시어는 #pragma omp parallel 혹은 #pragma omp task 지시어로 한번만 지정 할 수 있음
	*/
	}

	{
		int a = 0;
		printf("Main Area a : %d\n", a);

		// shared 속성 사용시
		#pragma omp parallel default(shared) 
		{
			if (omp_get_thread_num() == 0) {
				a = 1;
			}

			else {
				a = 2;
			}

			printf("%d thread Area a : %d\n", omp_get_thread_num(), a);
		}

		printf("Main Area a : %d\n", a);

		_getch();
	}

	{
		int a = 0;
		printf("Main Area a : %d\n", a);

		// none 속성 사용시 - private(a) 를 지정 해야 다른 스레드 해서 a 접근 및 갱신이 가능 !!!
		#pragma omp parallel num_threads(2), default(none), private(a)
		{
			if (omp_get_thread_num() == 0) {
				a = 1;
			}
			else {
				a = 2;
			}

			printf("%d thread Area a : %d\n", omp_get_thread_num(), a);
		}

		printf("Main Area a : %d\n", a);

		_getch();
	}
}