#pragma once

///////////////////////////////////////////////////////////////////////////////
/// @file Header OMP_TestFunction.h
/// @brief 
/// 
/// @author justin
/// @date 8-7-2012 13:49:17
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-10-2012 12:02:11
/// @brief OpenMP 주요 개념 설명
/*
    OpenMP Main: http://openmp.org/wp/
	OpenMP 한글 설명: http://blog.naver.com/njuhb?Redirect=Log&logNo=140155938855
	                 http://himskim.egloos.com/3261980

	* Single Thread Based Performance 예측 정보

	  Performance = CPU Command Count * Command Processing Time

	* Multi Thread Based Performance 예측 정보

	  Single 처리 보다 향상 되는 비율  = 1 / ( 1 - 병렬 처리 비율 ) + 병렬 처리 비율 / ( 스레드 갯수 + 프로세서 종류 + 코어 갯수 )

	* Directive 목록

	  - 병렬 영역 지시어
	  #pragma omp parallel

	  - 작업 분할 지시어
	  #pragma omp for
	  #pragma omp sections
	  #pragma omp single
	  #pragma omp task

	  - 동기 제어 지시어
	  #pragma omp atomic
	  #pragma omp critical
	  #pragma omp master
	  #pragma omp barrier
	  #pragma omp taskwait
	  #pragma omp flush
	  #pragma omp ordered

	  - 데이터 속성 제어 지시어
	  #pragma omp threadprivate

	  - 주요 보조 지시어
	  if, num_threads, default, private, firstprivate, lastprivate, copyprivate, shared, copyin, reduction,
	  collapse, ordered, nowait, schedule, untied
      	                   
*/
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_TestFunction.h
/// @title Multi-Core 관련 주요 테스트를 위한 Compile 설정 정의
/// @brief Intel Compiler 로 빌드 하기 위한 주요 설정
///        Visual Studio Tool -> Project/Menu -> Use Intel(R) C++ 선택
///        Project Property -> Language -> OpenMP Process : General Parallel Code (/Qopenmp) 선택
/// 
/// @author justin
/// @date 8-16-2012 22:35:09
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
/// @file Header OpenMP_TestFunction.h
/// @brief OpenMP Test function 목록
/// 
/// @author justin
/// @date 8-17-2012 14:07:27
///////////////////////////////////////////////////////////////////////////////

/// @brief OpenMP 예제 - justin 8/8/2012 10:30:37

void TestOMP_Concept();

void TestOMP_MemoryScope();

// 0. 지시어
void TestOMP_Directive();

// 1. 병렬 영역 지시어
void TestOMP_Parallel();

// 2. 작업 분할 지시어
void TestOMP_For();
void TestOMP_Sections();
void TestOMP_Single();
void TestOMP_Task();

// 3. 동기 제어 지시어
void TestOMP_Atomic();
void TestOMP_Barrier();
void TestOMP_Critical();
void TestOMP_Flush();
void TestOMP_Master();
void TestOMP_Ordered();
void TestOMP_TaskWait();

// 4. 데이터 속성 제어 지시어
void TestOMP_ThreadPrivate();

// 5. 주요 보조 지시어
void TestOMP_Default();
void TestOMP_Private();
void TestOMP_NoWait();
void TestOMP_LastPrivate();
void TestOMP_If();
void TestOMP_FirstPrivate();
void TestOMP_CopyPrivate();
void TestOMP_CopyIn();
void TestOMP_Collapse();
void TestOMP_Reduction();
void TestOMP_Schedule();
void TestOMP_Shared();
void TestOMP_Untied();


// 6. Runtime Library Routines Function
void TestOMP_RLR_Function();
