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
/// @file OMP_Directive.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Directive()
{
	// 1. 병렬 영역 지시어
//	TestOMP_Parallel();

	// 2. 작업 분할 지시어
//	TestOMP_For();
//	TestOMP_Sections();
//	TestOMP_Single();
//	TestOMP_Task();

	// 3. 동기 제어 지시어
//	TestOMP_Atomic();
//	TestOMP_Barrier();
//	TestOMP_Critical();
//	TestOMP_Flush();
//	TestOMP_Master();
//	TestOMP_Ordered();
//	TestOMP_TaskWait();

	// 4. 데이터 속성 제어 지시어
//	TestOMP_ThreadPrivate();

	// 5. 주요 보조 지시어
	/*
		* 데이터 공유 속성 지정

		: OpenMP 에 희한 병렬 영역 에서 사용 하는 변수에 대하여 각 스레드가 공유 할 수 있는 속성을 지정
		
		- 관련 보조 지시어
		  default 보조 지시어
		  shared 보조 지시어
		  private 보조 지시어
		  firstprivate 보조 지시어
		  lastprivate 보조 지시어
		  reduction 보조 지시어

		* 데이터 복사 속성 지정

		: OpenMP 병렬 영역에서 하나의 스레드가 가지는 private 변수의 값을 다른 스레드로 데이터를 복사 하는 기능 지원

		- 관련 보조 지시어
		  copyin 보조 지시어
		  copyprivate 보조 지시어

		* 스케줄 속성 지정

		: 루프 병렬 영역 에서 스레드 팀이 해야 할 작업에 대해 분할 방법을 지정 할 수 있음

		- 관련 보조 지시어
		  schedule 보조 지시어

		* 암시적 barrier 제거

		: OpenMP 병렬 프로그램은 모든 스레드 팀의 동작이 완료 되어야 다음 코드를 진행 하는 암시적 barrier 가 존재
		  프로그램의 효율을 위해서 프로그래머가 암시적 barrier 를 제거 하고 
		  스레드 동작을 제어 할 수 있는 기능을 제공

		- 관련 보조 지시어
		  nowait 보조 지시어

		* 기타 보조 지시어

		: OpenMP 병렬 영역 에서 특정 조건을 지정 할 수 있는 기능을 제공

		- 관련 보조 지시어
		  if 보조 지시어
		  collapse 보조 지시어
		  untied 보조 지시어
	*/

	// 5.1 데이터 공유 속성 지정
	/*
		: OpenMP 는 작업 분할 또는 루프 병렬화를 지원 하면서 스레드에 필요한 변수의 속성과 사용 가능한 영역을
		  자동으로 지정 해주는 기능을 지원 하는데 이러한 것을 OpenMP 에 의한 암시적 속성지정 이라고 하는데
		  경우에 따라 프로그래머가 변수의 속성을 명시적으로 지정 하여 사용할 필요가 있음
	*/
//	TestOMP_Default();
//	TestOMP_Shared();
//	TestOMP_Private();
//	TestOMP_Reduction();
//	TestOMP_FirstPrivate();
//	TestOMP_LastPrivate();

	// 5.2 데이터 복사 속성 지정
	/*
		: 1개의 스레드에 있는 private 변수로 부터 팀 내의 다른 스레드에 있는 변수로 데이터를 복사 하는 기능을 지원 함
	*/
//	TestOMP_CopyIn();
//	TestOMP_CopyPrivate();

	// 5.3 스케줄 속성 지정
	/*
		: #pragma omp for 지시어 에서 스레드 간에 작업을 어떻게 분배 할지를 지정 함
	*/
//	TestOMP_Schedule();

	// 5.4 암시적 barrier 제거
	/*
		: OpenMP 는 병렬 영역의 마지막 위치에서 스레드 팀 내의 모든 스레드가 완료 되기를
		  기다리는 기능을 자동으로 제공함
		  이것을 암시적 베리어 라고 하는데 작업이 먼저 종료된 스레드는 대기 상태로 기다리게 됨
		  이것은 자동으로 스레드 동기화를 시켜주는 것과 같아서 OpenMP 사용자에게 편리성을 제공 하지만
		  어떤 경우에는 대기 하는 시간 만큼 효율성이 떨어질때도 있음
	*/
//	TestOMP_NoWait();

	// 5.5 기타 보조 지시어
//	TestOMP_If();
//	TestOMP_Collapse();
	TestOMP_Untied();
}