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
/// @file OMP_LastPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_LastPrivate()
{
	// 5.1.5 lastprivate 보조 지시어
	{
	/*
		: lastprivate 보조 지시어는 프라이빗 보조 지시어와 기본적인 기능은 동일하게 동작하고
		  메인 영역에 있는 변수에 결과값을 전달 하는 기능이 추가 되었음
		  모든 스레드의 값이 메인 영역에 있는 변수로 중복 되어 전달 되는 것이 아니라
		  마지막으로 종료 되는 스레드의 변수값이 메인 영역에 변수로 전달 됨
		  private & lastprivate 보조 지시어로 지정된 변수는 스레드가 생성 되면서
		  메모리가 할당될 때 메인 영역에 있는 값이 전달 되지 않고 0 또는 쓰레기 값으로 초기화 되므로
		  스레드 영역 에서 별도로 초기화 해줘야 함

		#pragma omp for lastprivate(변수명)
		#pragma omp for sections lastprivate(변수명)

		[주의]
		- nowait 보조 지시어와 함께 사용된 lastprivate 보조 지시어는 데이터 저장시에 경합이 발생 함
		  그 외는 private 와 동일
	*/

		int a = 1;

		#pragma omp parallel
		{

			#pragma omp sections firstprivate(a), lastprivate(a)
			{
				#pragma omp section
				{
					printf("Section 1 - a Init:%d\n", a); // 메인 a 변수의 초기값이 로컬 a 에 전달됨

					a = 2;

					printf("Section 1 - a Change:%d\n", a); // 메인 a 변수에 변경된 값이 전달됨
				}

				#pragma omp section
				{
					printf("Section 2 : a Init:%d\n", a); // 메인 a 변수의 초기값이 로컬 a 에 전달됨

					a = 3;

					printf("Section 2 : a Change:%d\n", a); // 메인 a 변수에 변경된 값이 전달됨
				}
			}
		}

		printf("a Last:%d\n", a);

		_getch();
	}
}