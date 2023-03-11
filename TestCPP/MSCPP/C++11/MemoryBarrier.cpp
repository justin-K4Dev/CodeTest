#include "stdafx.h"


#include <thread>
#include <chrono>
#include <atomic>

namespace MemoryBarrier
{
	/*	
		Memory Barrier or Memory Fence
		: CPU or Compiler 는 특정 연산의 순서를 강제 하도록 하는 기능.
	
		- CPU 는 비순차적 명령어 (Out of Order) 처리 기법을 통해 연산 결과에 영향이 가지 않도록
		  순서를 변경 할 수 있으며, Compiler 에서도 역시 비슷한 최적화를 수행 한다.
		  하지만, 이러한 기능은 여러 스레드가 동시에 처리 되는 경우,
	      코드의 실행 순서가 바뀌어 실행 되는 동안 다른 스레드 에서 그 부분에 대한 메모리를
	      접근 하여 잘못된 결과가 나올 수 있다.
	      따라서 특정 부분에 대하여 실행 순서를 강제하는 Memory Barrier 를
	      로직에 작성해 줘야 한다.

		std::memory_order

		std::memory_order specifies how regular, non-atomic memory accesses are to be ordered around an atomic operation.
		Absent any constraints on a multi-core system, when multiple threads simultaneously read and write to several variables,
		one thread can observe the values change in an order different from the order another thread wrote them.
		Indeed, the apparent order of changes can even differ among multiple reader threads.
		Some similar effects can occur even on uniprocessor systems due to compiler transformations allowed by the memory model.
		The default behavior of all atomic operations in the library provides for sequentially consistent ordering (see discussion below).
		That default can hurt performance,
		but the library's atomic operations can be given an additional std::memory_order argument to specify the exact constraints,
		beyond atomicity, that the compiler and processor must enforce for that operation.


		typedef enum memory_order {
			memory_order_relaxed,   // relaxed
			memory_order_consume,   // consume
			memory_order_acquire,   // acquire
			memory_order_release,   // release
			memory_order_acq_rel,   // acquire/release
			memory_order_seq_cst    // sequential consistency, block memory re-ordering !!!
		} memory_order;


		memory_order_relaxed :
			The operation is ordered to happen atomically at some point.
			This is the loosest memory order, providing no guarantees on how memory accesses in different threads are ordered
			with respect to the atomic operation.
		memory_order_consume :
			[Applies to loading operations]
			The operation is ordered to happen once all accesses to memory in the releasing thread
			that carry a dependency on the releasing operation (and that have visible side effects on the loading thread) have happened.
		memory_order_acquire :
			[Applies to loading operations]
			The operation is ordered to happen once all accesses to memory in the releasing thread
			(that have visible side effects on the loading thread) have happened.
		memory_order_release :
			[Applies to storing operations]
			The operation is ordered to happen before a consume or acquire operation,
			serving as a synchronization point for other accesses to memory that may have visible side effects on the loading thread.
		memory_order_acq_rel :
			[Applies to loading/storing operations]
			The operation loads acquiring and stores releasing (as defined above for memory_order_acquire and memory_order_release).
		memory_order_seq_cst :
			The operation is ordered in a sequentially consistent manner:
			All operations using this memory order are ordered to happen once all accesses to memory
			that may have visible side effects on the other threads involved have already happened.
			This is the strictest memory order,
			guaranteeing the least unexpected side effects between thread interactions though the non-atomic memory accesses.
			For consume and acquire loads, sequentially consistent store operations are considered releasing operations.
	*/

	//common info
	struct Payload
	{
		int tick;
		std::string str;
		int param;
	};

	Payload g_payload;

	//Memory order 가드용 atomic 변수
	std::atomic<int> g_guard;


	//memory_fence_by_atomic example

	//thread 1 producer
	void TrySendMessage()
	{
		//...

		g_payload.tick = clock();
		g_payload.str = "TestMessage";
		g_payload.param = 10;

		//지금까지 쓴 내용들이 Acquire를 수행한 쓰레드에서 보여져야 한다.
		std::atomic_thread_fence(std::memory_order_release);

		g_guard.store(1, std::memory_order_relaxed);
	}

	//thread 2 waiting consumer
	void TryReceiveMessage()
	{
		// ...

		Payload result;

		// Load 수행
		int ready = g_guard.load(std::memory_order_relaxed);
		if (ready != 0)
		{
			std::atomic_thread_fence(std::memory_order_acquire);
			//이후부터는 Release 이전에 쓰여진 메모리 값들이 모두 제대로 보여야 한다


			result.tick = g_payload.tick;
			result.str = g_payload.str;
			result.param = g_payload.param;
		}
	}

	void memory_fence_by_atomic()
	{
		//std::atomic_thread_fence : using std::memory_order : memory_order_release -> memory_order_acquire
		{
			std::thread th1(TrySendMessage);
			std::thread th2(TryReceiveMessage);

			th1.join();
			th2.join();
		}

		//std::atomic_signal_fence
		{
			//메모리 재배치 금지 !!!
		}
	}
		

	//momory order example

	//thread 1 producer
	void DoSendMessage()
	{
		//...

		//전역 변수에 값 쓰기
		g_payload.tick = clock();
		g_payload.str = "TestMessage";
		g_payload.param = 50;

		//여기에서 Write-Release 수행
		//지금까지 쓴 내용들이 Acquire 이후에 보여진다.
		g_guard.store(1, std::memory_order_release);
	}

	//쓰레드 2에서 대기중인 consumer
	void DoReceiveMessage()
	{
		// ...

		Payload result;

		//Load-Acquire 수행
		int ready = g_guard.load(std::memory_order_acquire);
		//이후부터는 Release 이전에 쓰여진 메모리 값들이 모두 제대로 보인다

		if (ready != 0)
		{
			result.tick = g_payload.tick;
			result.str = g_payload.str;
			result.param = g_payload.param;
		}
	}

	void memory_order()
	{
		//memory order
		{
			std::thread th1(DoSendMessage);
			std::thread th2(DoReceiveMessage);

			th1.join();
			th2.join();
		}
	}

	//memory barrier or memory fence example
	int x = 0;
	int y = 0;

	void funcThread1(void* pArg)
	{
		while (x == 0) {}
		std::cout << y << std::endl;
	}

	void funcThread2(void* pArg)
	{
		y = 10;
		x = 1;
	}

	void funcThread3(void* pArg)
	{
		while (x == 0) {}
		std::cout << y << std::endl;
	}

	void funcThread4(void* pArg)
	{
		y = 10;

		_mm_mfence(); //코드 순서가 변경 되지 않도록 Memory Barrier 를 설정.

		x = 1;

		_mm_mfence(); //코드 순서가 변경 되지 않도록 Memory Barrier 를 설정.
	}
		
	void memory_barrier_or_memory_fence()
	{
		//memory barrier or memory fence
		{
			std::thread th1(funcThread1, (void*)NULL);
			std::thread th2(funcThread2, (void*)NULL);

			th1.join();
			th2.join();
		}

		{
			std::thread th3(funcThread3, (void*)NULL);
			std::thread th4(funcThread4, (void*)NULL);

			th3.join();
			th4.join();
		}

		system("pause");
	}


	void Test()
	{
		//memory_fence_by_atomic();

		//memory_order();

		//memory_barrier_or_memory_fence();
	}

}// end of MemoryBarrier