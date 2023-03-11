#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Random.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <random>
#include <chrono>
#include <functional>
#include <array>

namespace Random
{

	void get_distribution_random_info()
	{
		// get distribution random info
		{
			using TYPE = std::uniform_int_distribution<int>;

			TYPE dist;
			TYPE::result_type min = dist.min();
			TYPE::result_type max = dist.max();

			TYPE::param_type param = dist.param(); // get distribution random info

			dist.reset(); // clear cached random info !!!

			system("pause");
		}
	}


	void sample_distribution_group()
	{
		// Sample distribution group
		{
			/*
				Sample distribution groups include Discrete Distribution, Piecewise Constant Distribution, and
				Piecewise Linear Distribution. The three distributions are similar.
				The discrete distribution can specify a ratio to a specific distribution.
				To this end, there is a constructor that receives the initializer_list among the various constructors that
				the discrete_distribution template class has.
	
				Because you used the initializer_list that was recently added to the standard C ++ library,
				you can use arrays to initialize the discrete_distribution distribution class.

				If you generate a large enough number of random numbers,
				you can see that a random number reflecting the distribution of the result is generated as much as
				the ratio of the initializer_list given as the argument when generating the discrete_distribution template class.
			*/
			{
				std::default_random_engine eng;
				std::discrete_distribution<int> dist = { 2, 2, 1, 1, 2, 2, 1, 1, 2, 2 };

				std::array<int, 10> tmp = { 0, };
				for (int i = 0; i < 100000; ++i) {
					int number = dist(eng);
					++tmp[number];
				}
				for (int t : tmp) {
					std::cout << t << std::endl;
				}

				system("pause");
			}
		}
	}


	void Test()
	{
		//get_distribution_random_info();

		//sample_distribution_group();
	}

}// end of Auto