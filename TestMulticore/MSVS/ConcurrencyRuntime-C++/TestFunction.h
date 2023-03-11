#pragma once

///////////////////////////////////////////////////////////////////////////////
/// @file Header TestFunction.h
/// @brief 
/// 
/// @author justin
/// @date 8-19-2012 3:06:29
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 3:28:15
/// @brief
/*
    Concurrency Runtime Doc: http://msdn.microsoft.com/en-us/library/dd492418(VS.100).aspx
	Concurrency Runtime Site ���: http://linkmemo.tistory.com/105
	Concurrency Runtime �ѱ� ����: http://lifeisforu.tistory.com/41

	* Single Thread Based Performance ���� ����

	  Performance = CPU Command Count * Command Processing Time

	* Multi Thread Based Performance ���� ����

	Single ó�� ���� ��� �Ǵ� ����  = 1 / ( 1 - ���� ó�� ���� ) + ���� ó�� ���� / ( ������ ���� + ���μ��� ���� + �ھ� ���� )

	* Concurrent Container

	  ��� ����� ���� �ϴ� container !!!
 	  ������ ���: �ϳ��� �����̳ʿ� ���� ��������� �Բ� ���� �� �� �ʿ��� ������ ���
	  ����� ���� �˰���: ���� �ٸ� ��������� ��� ���� (lock-free) �۾��� ���� ó��

	* DeadLock & Race Condition

	  DeadLock: ����ȭ ��ü�� ���� �ϴ� thread �� 2�� �̻� ���� �Ǵ� ����
	  Race Condition: ������ ������ 2�� �̻��� thread �� �����Ͽ� ���� ��ȭ�� �־� �ش� ������ ���õ� ������ ������ �ִ� ����

	* User Mode Scheduling
	  Concurrency Run-Time �� Thread �� ���� �ǰų� �� �̻� ������ �� ���� �� �����ο�
	  �ٸ� Thread ���� �纸 �ϴ� ��� ���� ( Windows 7 ( x64 ) �� Windows Server 2008 R2 ������ ���� )
	  

	* Asynchronous Agent Library

	  agent ��� ���� ���α׷��� ���ۺ��� ���༺�� �»������� ��� ������ �� ��.
	  ���α׷��� �޽��� ������ ����� ����� �� �ִ� �� ���ǵ� ���( boundary )�� ������ ���� ���� �ϰ� 
	  ���� ������ �������� �и��ϸ� ����( latency )�� �ߵ� �� ������ ȿ�������� ���� ���ҽ��� ����� �� ����.
	  �����ϸ� �޸� ������ ���ϰ� ������ ���Ӽ��� ������ �������ν�,
	  ���ļ�( parallelism )�� ���� agent �� ���� ������� �߻�ȭ�� ����� scaling performance �� ȹ���� �� ����.
*/
///
///////////////////////////////////////////////////////////////////////////////

/// @brief Concurrency Runtime PPL algorithm ���� - justin 8/20/2012 22:38:07
void TestPPL_ParallelFor();
void TestPPL_ParallelForEach();
void TestPPL_ParallelInvoke();


/// @brief Concurrency Runtime PPL Container ���� - justin 8/20/2012 23:11:22
void TestPPL_ConcurrentVector();
void TestPPL_ConcurrentQueue();
void TestPPL_ConcurrentUnorderedMap();
void TestPPL_ConcurrentUnorderedSet();


/// @brief Concurrency Runtime Synchronization Primitive ��ü ���� - justin 8/20/2012 22:38:07
void TestPPL_CriticalSection();
void TestPPL_ReaderWriterLock();
void TestPPL_Combinable();


/// @brief Concurrency Runtime Task ���� - justin 8/20/2012 23:11:22
void TestPPL_TaskGroup();
void TestPPL_TaskScheduler();


/// @brief Concurrency Runtime AAL ���� - justin 8/21/2012 0:38:31
void TestAAL_AgentBasedApplication();


