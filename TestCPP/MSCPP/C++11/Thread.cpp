#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Thread.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <chrono>
#include <mutex>

namespace Thread
{

	void use_std_thread()
	{
		//Function, function object, and lambda function to the function to be called from the thread.
		{
			std::thread threadObj([]()
			{
				for (int i = 0; i < 5; i++)
				{
					std::cout << "Hello thread" << std::endl;
				}
			});

			system("pause");
		}
	}

	
	void create_n_operates_thread()
	{
		//Creates and operates a thread at a specific time after class creation.		
		{
			std::thread threadObj;
			threadObj = std::thread([]()
			{
				for (int i = 0; i < 5; i++)
				{
					std::cout << "Hello thread" << std::endl;
				}
			});

			system("pause");
		}
	}


	void use_parameters_in_thread_function()
	{
		//Using parameters in a thread function
		{
			std::thread threadObj = std::thread([](int nParam)
			{
				for (int i = 0; i < 3; i++)
				{
					std::cout << "Hello thread - Param:" << nParam << std::endl;
				}
			}, 4);

			system("pause");
		}
	}


	//Using a member function of a class in a thread example
	class Updater
	{
	public:
		void doUpdate()
		{
			for (int i = 0; i < 5; ++i) {
				std::cout << "Update count:" << i << std::endl;
			}
		}
	};

	void using_a_member_function_of_class_in_thread()
	{
		//Using a member function of a class in a thread
		{
			Updater updater;
			std::thread threadObj(&Updater::doUpdate, &updater);

			system("pause");
		}
	}


	void use_std_thread_join()
	{
		//use std::thread::join
		{
			std::thread threadObj([]()
			{
				for (int i = 0; i < 5; i++)
				{
				}
			});

			threadObj.join(); //wait for the thread to terminate

			system("pause");
		}

	}


	void use_std_call_once()
	{
		//use std::call_once
		{
			std::once_flag onceFlag;

			for (int i = 0; i < 3; ++i) {
				std::call_once(onceFlag, []()
				{
					std::cout << "Called once !!!" << std::endl;
				});
			}

			system("pause");
		}
	}


	void use_std_thread_get_id()
	{
		/*
			use std::thread::get_id()

			- get an identifier for this thread
			- identify each thread in a multi-thread
			- Know the thread that accesses a public resource from a multithreaded thread,
			  so that only a specific thread can access it.		
		*/
		{
			std::thread threadObj([]()
			{
				for (int i = 0; i < 5; i++)
				{
				}
			});

			std::thread::id testID = threadObj.get_id();

			system("pause");
		}
	}

	
	void use_std_thread_detach()
	{
		/*
			use std::thread::detach()

			- break thread object and thread linkage
			- thread objects can not control threads
			- whether detach and termination of thread		
		*/
		{
			std::thread threadObj([]()
			{
				for (int i = 0; i < 5; i++)
				{
				}
			});

			threadObj.detach();

			system("pause");
		}
	}


	void use_std_this_thread_sleep()
	{
		//use std::this_thread::sleep_for(), std::this_thread::sleep_until()
		{
			std::thread threadObj([]()
			{
				std::chrono::seconds waitTime(5);

				for (int i = 0; i < 5; i++)
				{
					std::this_thread::sleep_for(waitTime); //sleep_for - stops for the specified time
				}

				std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

				std::this_thread::sleep_until(startTime + waitTime); //sleep_until - stops until the specified time

				std::this_thread::yield(); //give up the activity of yourself (thread) and give it to another thread
			});

			threadObj.join(); //wait for the thread to terminate

			system("pause");
		}
	}

	void Test()
	{
		//use_std_thread();

		//create_n_operates_thread();

		//use_parameters_in_thread_function();

		//using_a_member_function_of_class_in_thread();

		//use_std_thread_join();

		//use_std_call_once();

		//use_std_thread_get_id();

		//use_std_thread_detach();

		//use_std_this_thread_sleep();
	}

}// end of Auto