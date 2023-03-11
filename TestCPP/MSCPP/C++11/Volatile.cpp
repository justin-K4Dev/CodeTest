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
		//- ����ȭ ���� compile option �� ������ ��� �����Ϸ��� ȿ�� ���� ����� optimize �������� �ڵ带 ���Ƿ� ���� �ϴµ�
		//	volatile ������ ������ compile ����ȭ option �� ���� ���� �ʰ� �Ѵ�.
		//- �Ʒ��� ������ ������ volatile ��� �Ѵ�.
		//
		//1. ������ �Ϲ� ��ƾ�� ���ͷ�Ʈ ��ƾ�� ���� read/write �� �Բ� �߻��ϴ� ���
		//2. ������ ��������� Ư�� ��ƾ���� cpu �������� ������ �� ���
		//3. ������ �ܺ� �ý��۰� ���� �Ǿ� �־�� �� ���
		//4. �ڵ��� ������ ��Ű�� ���� ���
		//5. AVR ȯ�濡�� IO Constroller �޸� ���� �ϴ� ������ read/write �� �Բ� �߻��ϴ� ���
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
		//case 1. ������ �Ϲ� ��ƾ�� ���ͷ�Ʈ ��ƾ�� ���� read/write �� �Բ� �߻��ϴ� ���
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
		//case 2. ������ ��������� Ư�� ��ƾ���� cpu �������� ������ �� ���
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
		//case 4. �ڵ��� ������ ��Ű�� ���� ���
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