#include "stdafx.h"

#include <vector>
#include <atomic>
#include <ctime>
#include <time.h>
#include <chrono>
#include <Windows.h>

namespace Time
{
	void waiting(int waitSec)
	{
		for (int i = 0; i < waitSec; ++i) {
			Sleep(1000);
		}
	}

	void chrono_elapsed_time()
	{
		auto start = std::chrono::system_clock::now();
		waiting(5);
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		char strTime[1024];
		ctime_s(strTime, sizeof(strTime), &end_time);
		std::cout << "finished computation at " << strTime
			      << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
		/*
		output:
			finished computation at Sun Jun 24 18:35:48 2018
			elapsed time: 5.00029s
		*/

		system("pause");
	}


	void Test()
	{
		//chrono_elapsed_time();
	}
}//end of Time