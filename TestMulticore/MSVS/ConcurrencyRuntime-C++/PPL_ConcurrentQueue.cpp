#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-21-2012 10:55:09
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

//Yield macro from Windows.h conflicting with concurrency::Context::Yield
#ifdef Yield
#undef Yield
#endif//Yield

#include <assert.h>
#include <iostream>
#include <math.h>
#include <concurrent_queue.h>
#include <concurrent_vector.h>
#include <ppl.h>


// Determines whether the input value is prime.
bool is_prime(int n)
{
	if (n < 2)
		return false;

    for ( int i = 2; i < n; ++i )
    {
        if ((n % i) == 0)
			return false;
    }

    return true;
}

// Determines whether the input value is a Carmichael number.
bool is_carmichael(const int n) 
{
    if (n < 2) 
		return false;

	int k = n;
	for (int i = 2; i <= k / i; ++i) 
	{
		if (k % i == 0) 
		{
			if ((k / i) % i == 0) 
				return false;
			if ((n - 1) % (i - 1) != 0)
				return false;
			
			k /= i;
			i = 1;
		}
	 }

	return k != n && (n - 1) % (k - 1) == 0;
}

void parallel_concurrent_queue_1()
{
	// The maximum number to test.
	const int max = 10000000;

	// Holds the Carmichael numbers that are in the range [0, max).
	Concurrency::concurrent_queue<int> carmichaels;

	// Holds the prime numbers that are in the range  [0, sqrt(max)).
	Concurrency::concurrent_vector<int> primes;

	// Generate the set of Carmichael numbers and the set of prime numbers
	// in parallel.
	Concurrency::parallel_invoke( [&] {
			                                Concurrency::parallel_for(0, max, [&](int i) {
				                                                                            if (is_carmichael(i)) {
					                                                                                                    carmichaels.push(i);
				                                                                                                    }
			                                                                            }
											                        );
		                                },
		                            [&] {
			                                Concurrency::parallel_for(0, int(sqrt(static_cast<double>(max))), [&] (int i) {
																															if (is_prime(i)) {
																																                    primes.push_back(i);
																															                    }
			                                                                                                            } 
											                        );
		                                }
							    );

	system("pause");
}

void parallel_concurrent_queue_2()
{
	// The maximum number to test.
	const int max = 10000;

	// Holds the message numbers that are in the range [0, max).
	Concurrency::concurrent_queue<int> messageQueue;

	// Generate the set of message numbers and the set of prime numbers
	// in parallel.
	Concurrency::parallel_invoke( [&] {
			                                Concurrency::parallel_for(0, max, [&](int i) {
																							messageQueue.push(i);
																							std::cout << "CallNo:" << i << " Pushed value:" << i << std::endl;
			                                                                            }
											                        );
		                                },
		                            [&] {
			                                Concurrency::parallel_for(0, max, [&](int i) {
														
													int poped_value;
													while (messageQueue.empty() == false) {
														if (messageQueue.try_pop(OUT poped_value)) {
															std::cout << "CallNo:" << i << " Poped value: " << poped_value << std::endl;
														}
														else {
															std::cout << "CallNo:" << i << " empty !!!" << std::endl;
														}
													}
												}
											);
		                                }
							    );

	std::cout << "RemainCount:" << messageQueue.unsafe_size() << std::endl;

	system("pause");
}

void ProducerTask(void* p)
{
	Concurrency::concurrent_queue<int>* pq = (Concurrency::concurrent_queue<int>*)p;

	for (int i = 0; i < 10000; ++i) {
		pq->push(i);

		std::cout << "Pushed value:" << i << std::endl;
	}
}

void Producer_Consumer() 
{
	Concurrency::concurrent_queue<int> q;

	// Schedule a task to produce 1000 items 
	Concurrency::CurrentScheduler::ScheduleTask(ProducerTask, &q);

	// Consume 10000 items 
	for (int i = 0; i < 10000; ++i) {
		int result = -1;

		while (!q.try_pop(result)) {

			std::cout << "Poped value:" << result << std::endl;

			concurrency::Context::Yield();
		}

		assert(result == i);
	}

	std::cout << "RemainCount:" << q.unsafe_size() << std::endl;

	system("pause");
}


void TestPPL_ConcurrentQueue()
{
	/*
		concurrent_queue Class

		The concurrency::concurrent_queue class, just like the std::queue class,
		lets you access its front and back elements.
		
		The concurrent_queue class enables concurrency-safe enqueue and dequeue operations.
		The concurrent_queue class also provides iterator support that is not concurrency-safe.

		Differences Between concurrent_queue and queue
		
		The concurrent_queue class closely resembles the queue class.
		The following points illustrate where concurrent_queue differs from queue:

			* Enqueue and dequeue operations on a concurrent_queue object are concurrency-safe.

			* The concurrent_queue class provides iterator support that is not concurrency-safe.

			* The concurrent_queue class does not provide the front or pop methods.
			  The concurrent_queue class replaces these methods by defining the try_pop method.

			* The concurrent_queue class does not provide the back method.
			  Therefore, you cannot reference the end of the queue.

			* The concurrent_queue class provides the unsafe_size method instead of the size method.
			  The unsafe_size method is not concurrency-safe.

		Concurrency-Safe Operations
	
		All methods that enqueue to or dequeue from a concurrent_queue object are concurrency-safe.
		The following table shows the common concurrent_queue methods and operators that are concurrency-safe.

			empty			push
			get_allocator	try_pop

		Although the empty method is concurrency-safe,
		a concurrent operation may cause the queue to grow or shrink before the empty method returns.
		The following table shows the common methods and operators that are not concurrency-safe.

			clear			unsafe_end
			unsafe_begin	unsafe_size
	*/
	{
		//parallel_concurrent_queue_1();

		//parallel_concurrent_queue_2();

		Producer_Consumer();
	}
}