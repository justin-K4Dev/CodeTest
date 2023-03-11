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
/// @brief OpenMP �ֿ� ���� ����
/*
    OpenMP Main: http://openmp.org/wp/
	OpenMP �ѱ� ����: http://blog.naver.com/njuhb?Redirect=Log&logNo=140155938855
	                 http://himskim.egloos.com/3261980

	* Single Thread Based Performance ���� ����

	  Performance = CPU Command Count * Command Processing Time

	* Multi Thread Based Performance ���� ����

	  Single ó�� ���� ��� �Ǵ� ����  = 1 / ( 1 - ���� ó�� ���� ) + ���� ó�� ���� / ( ������ ���� + ���μ��� ���� + �ھ� ���� )

	* Directive ���

	  - ���� ���� ���þ�
	  #pragma omp parallel

	  - �۾� ���� ���þ�
	  #pragma omp for
	  #pragma omp sections
	  #pragma omp single
	  #pragma omp task

	  - ���� ���� ���þ�
	  #pragma omp atomic
	  #pragma omp critical
	  #pragma omp master
	  #pragma omp barrier
	  #pragma omp taskwait
	  #pragma omp flush
	  #pragma omp ordered

	  - ������ �Ӽ� ���� ���þ�
	  #pragma omp threadprivate

	  - �ֿ� ���� ���þ�
	  if, num_threads, default, private, firstprivate, lastprivate, copyprivate, shared, copyin, reduction,
	  collapse, ordered, nowait, schedule, untied
      	                   
*/
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_TestFunction.h
/// @title Multi-Core ���� �ֿ� �׽�Ʈ�� ���� Compile ���� ����
/// @brief Intel Compiler �� ���� �ϱ� ���� �ֿ� ����
///        Visual Studio Tool -> Project/Menu -> Use Intel(R) C++ ����
///        Project Property -> Language -> OpenMP Process : General Parallel Code (/Qopenmp) ����
/// 
/// @author justin
/// @date 8-16-2012 22:35:09
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
/// @file Header OpenMP_TestFunction.h
/// @brief OpenMP Test function ���
/// 
/// @author justin
/// @date 8-17-2012 14:07:27
///////////////////////////////////////////////////////////////////////////////

/// @brief OpenMP ���� - justin 8/8/2012 10:30:37

void TestOMP_Concept();

void TestOMP_MemoryScope();

// 0. ���þ�
void TestOMP_Directive();

// 1. ���� ���� ���þ�
void TestOMP_Parallel();

// 2. �۾� ���� ���þ�
void TestOMP_For();
void TestOMP_Sections();
void TestOMP_Single();
void TestOMP_Task();

// 3. ���� ���� ���þ�
void TestOMP_Atomic();
void TestOMP_Barrier();
void TestOMP_Critical();
void TestOMP_Flush();
void TestOMP_Master();
void TestOMP_Ordered();
void TestOMP_TaskWait();

// 4. ������ �Ӽ� ���� ���þ�
void TestOMP_ThreadPrivate();

// 5. �ֿ� ���� ���þ�
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
