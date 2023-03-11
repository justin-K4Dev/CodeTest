#include "stdafx.h"



#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <list>

namespace Mutex
{

	void std_mutex()
	{
		//std::mutex
		{
			std::mutex mtx_lock;

			std::thread threadObj([&]()
			{
				for (int i = 0; i < 3; ++i) {
					mtx_lock.lock();
					std::cout << "Thread No:" << i << std::endl;
					mtx_lock.unlock();
				}
			});

			system("pause");
		}
	}


	void std_mutex_try_lock()
	{
		//use std_mutex_try_lock
		{
			std::chrono::milliseconds interval(100);

			std::mutex mtxLock;
			int updateCount(0);

			std::thread thReceiver;
			thReceiver = std::thread([&]()
			{
				std::this_thread::sleep_for(interval); //let thread take a lock

				while (true) {
					//try to lock mutex to modify 'mutex obj'
					if (mtxLock.try_lock()) {
						std::cout << "success get lock obj !!! - UpdateCount:" << updateCount << "\n";
						mtxLock.unlock();
						return;
					}
					else {
						//can't get lock to modify 'mutex obj'
						//but there is some other work to do
						++updateCount;
						std::cout << "can't get lock obj !!! - UpdateCount:" << updateCount << "\n";
						std::this_thread::sleep_for(interval);
					}
				}
			});

			std::thread thSender;
			thSender = std::thread([&]()
			{
				mtxLock.lock();
				std::this_thread::sleep_for(5 * interval);
				++updateCount;
				mtxLock.unlock();
			});

			thReceiver.join();
			thSender.join();

			system("pause");
		}
	}


	void std_lock_guard()
	{
		//use lock_guard 
		{
			std::mutex mtxLock;

			std::thread threadObj([&]()
			{
				for (int i = 0; i < 5; ++i) {
					//Automatically call unlock when leaving the scope
					std::lock_guard<std::mutex> guard(mtxLock);
					std::cout << "Thread No:" << i << std::endl;
				}
			});

			system("pause");
		}
	}


	void std_recursive_mutex()
	{
		/*
			Recursive_mutex can be locked on the same thread and locked again.
			Unlock must be called as many times as the number of locks.
		*/
		{
			class Buffer
			{
				std::list<int> queue;
				std::recursive_mutex rm_lock;
			public:
				bool empty() {
					std::lock_guard<std::recursive_mutex> lock(rm_lock);
					return queue.empty();
				}

				void push(int nValue)
				{
					std::lock_guard <std::recursive_mutex> lock(rm_lock);
					queue.push_back(nValue);
				}

				int pop() throw (std::out_of_range) // (deprecated in C++11)(until C++17)
				{
					std::lock_guard <std::recursive_mutex> lock(rm_lock);
					while (empty())
					{
						//...
					}

					int tmp = queue.front();
					queue.pop_front();

					return tmp;
				}
			};

			std::chrono::milliseconds interval(100);

			std::mutex mtxLock;
			int updateCount(0);

			Buffer buffer;

			std::thread thReceiver;
			thReceiver = std::thread([&]()
			{
				std::this_thread::sleep_for(interval); //let thread take a lock

				while (true) {
					if (buffer.empty())
						break;
						
					int value = buffer.pop();
					std::cout << "Pop - Value:" << value << std::endl;
				}
			});

			std::thread thSender;
			thSender = std::thread([&]()
			{
				for (int i = 0; i < 3; ++i) {
					buffer.push(i + 100);
				}
			});


			thSender.join();
			thReceiver.join();

			system("pause");
		}
	}


	void Test()
	{
		std_mutex();

		//std_mutex_try_lock();

		//std_lock_guard();

		//std_recursive_mutex();
	}

}// end of Mutex