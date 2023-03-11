#include "stdafx.h"



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>


namespace Lambda
{

	//lambda function example
	std::function< void() > f()
	{
		std::string str("Lambda f()");
		return [=]() { std::cout << "Called function " << str << std::endl; };
	}

	void lambda_function()
	{
		//lambda function
		{
			[] //Lambda Capture 
			() //Argument
			{ //body
				std::cout << "Hello, World !!!" << std::endl;
			}
			(); //call lambda function
		}
		//call Lambda
		{
			[] { std::cout << "Hello, Justin !!!" << std::endl; } ();
		}
		//with parameter
		{
			auto func = [](int n) { std::cout << "My back number: " << n << std::endl; };

			func(1);
			func(10);
		}
		//with return
		{
			auto func1 = [] { return 3.14f; };
			auto func2 = [](float f) { return f; };
			auto func3 = []() -> float { return 3.14f; }; //-> 기호로 명시적 반환 타입 지정

			float f1 = func1();
			float f2 = func2(9.99f);
			float f3 = func3();
		}
		//with lambda return 
		{
			auto func = f();

			func(); //called f() Lambda
			f()(); //called f() Lambda
		}
	}
	

	void with_auto()
	{
		//with auto
		{
			auto func = [] { std::cout << "Hello, NCSoft !!!" << std::endl; };

			func();
		}
	}


	void with_class()
	{
		//with class
		{
			class CNetwork
			{
			private:
				std::vector<int> m_vtSendPacketList;

			private:
				void Send(int nPacketNo)
				{
					std::cout << "Send Packet No: " << nPacketNo << std::endl;
				}

			public:
				CNetwork() { return; }

				void PushPacket(int nNo) { m_vtSendPacketList.push_back(nNo); }

				void SendAll()
				{
					std::for_each(m_vtSendPacketList.begin(),
						m_vtSendPacketList.end(),
						[this](int nNo)
					{
						Send(nNo);
					});
				}
			};

			CNetwork network;
			network.PushPacket(1);
			network.PushPacket(2);
			network.PushPacket(3);
			network.PushPacket(4);
			network.PushPacket(4);

			network.SendAll();

			system("pause");
		}
	}


	//with Template example
	template<typename T>
	void Test(T func)
	{
		func();
	}

	void with_template()
	{
		//with Template
		{
			auto func = [] { std::cout << "Wonderful Days !!!" << std::endl; };

			Test(func); //call Template function
		}
	}


	void capture()
	{
		//default capture
		{
			int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0;

			[&, n1, n2] {}; //n3, n4, n5 참조, n1, n2 복사

			//with reference variable capture
			std::vector<int> vtDataList;
			vtDataList.push_back(100);
			[=, &n1, &n2] {}; //n3, n4, n5 복사, n1, n2 참조

							  //[ n1, n1 ] { }; // 동일 변수 사용에 대한 compile error

							  //[ &, &n1 ] { }; // n1 은 이미 참조 default capture 됨 !!!

							  //[ =, n1 ] { }; // n1 은 이미 복사 default capture 됨 !!!
		
			vtDataList.push_back(1000);
			vtDataList.push_back(10);

			int nTotal(0);

			std::for_each(vtDataList.begin(),
				vtDataList.end(),
				[&nTotal](int nData)
			{
				nTotal += nData;
			});

			std::cout << "Total: " << nTotal << std::endl;
		}
		//with pointer variable capture
		{
			std::vector<int> vtDataList;
			vtDataList.push_back(100);
			vtDataList.push_back(1000);
			vtDataList.push_back(10);

			int nTotal = 0;
			int *pnTotal = &nTotal;

			std::for_each(vtDataList.begin(),
				vtDataList.end(),
				[pnTotal](int nData)
			{
				*pnTotal += nData;
			});

			std::cout << "Total: " << nTotal << std::endl;
		}
		//with copy capture
		{
			std::vector<int> vtDataList;
			vtDataList.push_back(100);
			vtDataList.push_back(1000);
			vtDataList.push_back(10);

			int nTotal = 1000;

			std::for_each(vtDataList.begin(),
				vtDataList.end(),
				[nTotal](int nData) mutable //값 복사 전달시 mutable 키워드 사용
			{                              //모든 변수 값 복사 전달시 [=] !!!
				nTotal += nData;

				std::cout << "Lambda Total: " << nTotal << std::endl;
			});

			std::cout << "Total: " << nTotal << std::endl;
		}
		//with multi copy capture
		{
			std::vector<int> vtDataList;
			vtDataList.push_back(100);
			vtDataList.push_back(1000);
			vtDataList.push_back(10);

			int nTotal = 0;
			int nBigTotal = 0;

			std::for_each(vtDataList.begin(),
				vtDataList.end(),
				[&nTotal, &nBigTotal](int nData) //모든 변수 참조 전달시 [&] !!!
			{
				nTotal += nData;

				if (500 < nData)
				{
					nBigTotal = nData;
				}
			});

			std::cout << "Total: " << nTotal << std::endl;
			std::cout << "BigTotal: " << nBigTotal << std::endl;
		}
	}

	std::string GetValue(std::function<std::string(int)> funcData)
	{
		return funcData(10);
	}

	void with_stl()
	{
		//with STL
		{
			class CPC
			{
			protected:
				int m_nNo;
				bool m_bDie;

			public:
				CPC(int nNo) { m_nNo = nNo; m_bDie = false; }

				int GetNo() { return m_nNo; }

				void SetDie(bool bTrue) { m_bDie = bTrue; }
				bool IsDie() { return m_bDie; }
			};

			std::vector<CPC> vtPCList;

			CPC pc1(1);
			pc1.SetDie(false);
			vtPCList.push_back(pc1);

			CPC pc2(2);
			pc2.SetDie(false);
			vtPCList.push_back(pc2);

			CPC pc3(3);
			pc3.SetDie(true);
			vtPCList.push_back(pc3);

			auto itPos = std::find_if(vtPCList.begin(),
				vtPCList.end(),
				[](CPC &pc) -> bool //return type
			{
				return pc.IsDie();
			});

			if (vtPCList.end() != itPos)
			{
				std::cout << "Death PC No: " << (*itPos).GetNo() << std::endl;
			}
		}
		//with STL function
		{
			std::vector< std::function< int() > > vtFunctionList;

			vtFunctionList.push_back([] { return 100; });
			vtFunctionList.push_back([] { return 200; });

			std::cout << "Called STL function return: " << vtFunctionList[0]() << std::endl;
			std::cout << "Called STL function return: " << vtFunctionList[1]() << std::endl;
		}
		//with declared function 
		{
			std::function<int(std::string const &)> f;

			f = [](std::string const & s)->int { // return type
				return s.size();
			};
		}
		//with recurcive
		{
			std::function< int(int) > fact = [&fact](int x) {
				return x == 0 ? 1 : x * fact(x - 1);
			};

			std::cout << fact(3) << std::endl;
		}
		//lambda function parameter
		{
			std::string strValue("Object");

			auto func_GetValue = [&](int i) {
				return strValue;
			};

			std::string strData = GetValue(func_GetValue);

			std::cout << strData << std::endl;
		}
	}


	void lambda_recursive_with_std_function()
	{
		{
			auto term = [](int a)->int {
				return a * a;
			};

			auto next = [](int a)->int {
				return ++a;
			};

			std::function<int(int, int)> sum;
			sum = [term, next, &sum](int a, int b)->int {
				if (a > b)
					return 0;
				else
					return term(a) + sum(next(a), b);
			};

			std::cout << sum(1, 10) << std::endl;
		}

		{
			int N = 0;

			// Signature declaration via std::function -> std::function<int(int)>
			// Function signature int (int)
			// [&fact] - Capture the lambda itself
			std::function<int(int)> fact = [&fact](int N)
			{
				if (N < 0) // if the user entered a negative number
				{
					return 0; // return zero
				}
				else if (N == 0) // if the user entered zero,
				{
					return 1; // return the factorial from zero, which is 1
				}
				else // in all other cases
				{
					return N * fact(N - 1); // we perform recursive function calls
				}
			};

			std::cout << "Input number for factorial" << std::endl;
			std::cin >> N;
			std::cout << "Factorial for number " << N << " = " << fact(N) << std::endl; // fact(N) - function for calculating the factorial.
		}
	}


	void Test()
	{
		//lambda_recursive_with_std_function();

		//lambda_function();

		//with_auto();

		//with_class();

		//with_template();

		//capture();

		//with_stl();
	}

}//end of Lambda