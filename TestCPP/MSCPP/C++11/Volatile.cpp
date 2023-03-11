#include "stdafx.h"


#include <thread>
#include <chrono>

namespace Volatile
{
	void volatile_keyword()
	{
		//compile with: /EHsc /O2

		//volatile ?
		//
		//- 최적화 관련 compile option 을 설정한 경우 컴파일러가 효율 등을 고려해 optimize 관점에서 코드를 임의로 변경 하는데
		//	volatile 설정한 변수는 compile 최적화 option 에 적용 받지 않게 한다.
		//- 아래의 경우들은 변수에 volatile 사용 한다.
		//
		//1. 변수가 일반 루틴과 인터럽트 루틴에 의해 read/write 가 함께 발생하는 경우
		//2. 변수가 명시적으로 특정 루틴에서 cpu 점유률을 유지해 줄 경우
		//3. 변수가 외부 시스템과 연동 되어 있어야 할 경우
		//4. 코드의 순서를 지키고 싶은 경우
		//5. AVR 환경에서 IO Constroller 메모리 접근 하는 변수에 read/write 가 함께 발생하는 경우
	}


	// case_1 example
	volatile bool g_sentinel = true;
	int g_criticalData = 0;

	void funcThread1(void* pArg)
	{
		while (g_sentinel) {
			std::this_thread::sleep_for(std::chrono::seconds(0));   //volatile spin lock
		}

		//criticalData load guaranteed after every load of g_sentinel
		std::cout << "Critical Data = " << g_criticalData << std::endl;
	}

	void funcThread2(void* pArg)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(2));   //volatile spin lock

		g_criticalData++; //guaranteed to occur before write to g_sentinelData
		g_sentinel = false; //exit critical section
	}


	void case_1()
	{
		//case 1. 변수가 일반 루틴과 인터럽트 루틴에 의해 read/write 가 함께 발생하는 경우
		{
			std::thread th1(funcThread1, (void*)NULL);
			std::thread th2(funcThread2, (void*)NULL);

			th1.join();
			th2.join();

			if (true == g_sentinel) {
				std::cout << "success." << std::endl;
			}
			else {
				std::cout << "failure !!!" << std::endl;
			}
		}
	}


	void case_2()
	{
		//case 2. 변수가 명시적으로 특정 루틴에서 cpu 점유률을 유지해 줄 경우
		{
			int i;
			double j;

			for (i = 0; i < 10; ++i) {

				j = sqrt(2.8) + log(3.5) + 56; // called only once
			}

			std::cout << " value: " << j << std::endl;
		}
		{
			int i;
			volatile double j;

			for (i = 0; i < 10; ++i) {

				j = sqrt(2.8) + log(3.5) + 56; // called as for loop
			}

			std::cout << " volatile value: " << j << std::endl;
		}

		system("pause");
	}


	void case_4()
	{
		//case 4. 코드의 순서를 지키고 싶은 경우
		{
			int first = 10;
			double second = 100;

			std::cout << "first: " << first << " second: " << second << std::endl;
		}
		{
			int first = 10;
			volatile double second = 100;

			std::cout << "first: " << first << "volatile second: " << second << std::endl;
		}

		system("pause");
	}


	void Test()
	{
		//volatile_keyword();

		//case_1();

		//case_2();

		//case_4();
	}
}// end of Volatile