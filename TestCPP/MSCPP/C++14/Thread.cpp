#include "stdafx.h"

#include <thread>
#include <mutex>

namespace Thread
{
	thread_local unsigned int thl_i = 0;
	std::mutex mtx;

	void ThreadFunc(int nID)
	{
		++thl_i;

		std::unique_lock<std::mutex> lock(mtx);
		std::cout << nID << "ThreadLocal value : " << thl_i << std::endl;
	}

	void thread_local_tls()
	{
		std::thread th1(ThreadFunc, 0), th2(ThreadFunc, 1);

		std::unique_lock<std::mutex> lock(mtx);
		std::cout << "Main thread : " << thl_i << std::endl;
		lock.unlock();

		th1.join();
		th2.join();

		system("pause");
	}

	void Test()
	{
		//thread_local_tls();
	}

}// end of Thread