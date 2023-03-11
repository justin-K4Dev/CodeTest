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
	Concurrency Runtime Site 목록: http://linkmemo.tistory.com/105
	Concurrency Runtime 한글 설명: http://lifeisforu.tistory.com/41

	* Single Thread Based Performance 예측 정보

	  Performance = CPU Command Count * Command Processing Time

	* Multi Thread Based Performance 예측 정보

	Single 처리 보다 향상 되는 비율  = 1 / ( 1 - 병렬 처리 비율 ) + 병렬 처리 비율 / ( 스레드 갯수 + 프로세서 종류 + 코어 갯수 )

	* Concurrent Container

	  잠금 기능을 제공 하는 container !!!
 	  정교한 잠금: 하나의 컨테이너에 여러 스레드들이 함께 접근 할 때 필요한 영역만 잠금
	  잠금이 없는 알고리즘: 서로 다른 스레드들이 잠금 없이 (lock-free) 작업을 통해 처리

	* DeadLock & Race Condition

	  DeadLock: 동기화 객체에 접근 하는 thread 가 2개 이상 병목 되는 현상
	  Race Condition: 동일한 변수에 2개 이상의 thread 가 접근하여 값에 변화를 주어 해당 변수와 관련된 로직에 영향을 주는 현상

	* User Mode Scheduling
	  Concurrency Run-Time 은 Thread 가 병목 되거나 더 이상 진행할 수 없을 때 여유로운
	  다른 Thread 에게 양보 하는 기능 제공 ( Windows 7 ( x64 ) 와 Windows Server 2008 R2 에서만 제공 )
	  

	* Asynchronous Agent Library

	  agent 기반 모델은 프로그램의 시작부터 병행성이 태생적으로 녹아 들어가도록 해 줌.
	  프로그램을 메시지 전달을 사용해 통신할 수 있는 잘 정의된 경계( boundary )를 따르는 조합 가능 하고 
	  재사용 가능한 조각으로 분리하면 지연( latency )을 견딜 수 있으며 효율적으로 병렬 리소스를 사용할 수 있음.
	  가능하면 메모리 공유를 피하고 데이터 종속성에 초점을 맞춤으로써,
	  병렬성( parallelism )을 위해 agent 와 같은 고수준의 추상화를 사용해 scaling performance 를 획득할 수 있음.
*/
///
///////////////////////////////////////////////////////////////////////////////

/// @brief Concurrency Runtime PPL algorithm 예제 - justin 8/20/2012 22:38:07
void TestPPL_ParallelFor();
void TestPPL_ParallelForEach();
void TestPPL_ParallelInvoke();


/// @brief Concurrency Runtime PPL Container 예제 - justin 8/20/2012 23:11:22
void TestPPL_ConcurrentVector();
void TestPPL_ConcurrentQueue();
void TestPPL_ConcurrentUnorderedMap();
void TestPPL_ConcurrentUnorderedSet();


/// @brief Concurrency Runtime Synchronization Primitive 객체 예제 - justin 8/20/2012 22:38:07
void TestPPL_CriticalSection();
void TestPPL_ReaderWriterLock();
void TestPPL_Combinable();


/// @brief Concurrency Runtime Task 예제 - justin 8/20/2012 23:11:22
void TestPPL_TaskGroup();
void TestPPL_TaskScheduler();


/// @brief Concurrency Runtime AAL 예제 - justin 8/21/2012 0:38:31
void TestAAL_AgentBasedApplication();


