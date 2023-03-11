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
#include <map>

namespace Random
{
	void cpp_std_random()
	{
		/*
			C++ standard Random Lib

			To use the standard random number library, include #include <random> in the source code.
			The library provides a more versatile and precise random number generator than
			the random number library we have provided in the C format library.
			The standard library's random number generator is basically a uniform random number generator and
			is divided into two concepts, engine and distribution.
			The engine generates a random number between the minimum and maximum values that are uniformly distributed.
			For example, if you set the minimum and maximum values for a particular engine to 1 and 10,
			respectively, you can use this engine to get a random number between 1 and 10.
			As with generic random number generators, you can set the seed value in the engine,
			and the seed value can be any random number from another engine.
		*/
		{
			auto seed = time(NULL);

			std::default_random_engine engine;
			engine.seed(seed);
			std::default_random_engine::result_type v = engine();
			std::default_random_engine::result_type min = engine.min();
			std::default_random_engine::result_type max = engine.max();
			std::default_random_engine::result_type defaultSeed = std::default_random_engine::default_seed;
			std::cout << "min : " << min << std::endl << "max : " << max << std::endl;
			std::cout << "value : " << v << std::endl;
			engine.seed();
			std::cout << "Default seed : " << defaultSeed << std::endl;
			std::cout << "value : " << engine() << std::endl;
			std::cout << "value : " << engine() << std::endl;
			engine.seed();
			std::cout << "value : " << engine() << std::endl;

			system("pause");
		}
	}


	void random_generator()
	{
		//random generator
		{
			//Mersenne twister - for 32bit
			//std::mt19937_64 - for 64bit
			std::mt19937 mtRand;

			for (int i = 0; i < 7; i++)
			{
				unsigned int temp = mtRand();
			}

			system("pause");
		}
		//random generator + seed value
		{
			auto currTime = std::chrono::system_clock::now();
			auto duration = currTime.time_since_epoch();
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

			std::mt19937 mtRand(millis); //use seed by time

			for (int i = 0; i < 7; ++i) {
				std::cout << mtRand() << std::endl;
			}

			system("pause");
		}
	}


	void non_deterministic_random_number_generation()
	{
		/*
			non-deterministic random number generation

			Generates non-deterministic random numbers,
			which can be used for seed initialization or
			encryption purposes in other pseudorandom number generation engines

			Because we need to generate unpredictable random numbers,
			we use hardware resources instead of software.

			Ex) Use hardware noise or mouse movement.
			- On Windows, wrapped CryptGenRandom() function
			- On Unix, use /dev/random or /dex/urandom
		*/
		{
			std::random_device rng;
			for (int i = 0; i < 7; i++)
			{
				auto result = rng();
				std::cout << result << std::endl;
			}

			system("pause");
		}
	}


	void generate_random_numbers_in_range()
	{
		/*
			generate random numbers in range
		*/
		{
			std::mt19937_64 rng1(3244);

			//int type 
			std::uniform_int_distribution<__int64> dist1(-3, 3); //-3 ~ 3
			for (int i = 0; i < 7; i++)
			{
				auto result = dist1(rng1);
				std::cout << result << std::endl;
			}

			//real type
			std::uniform_real_distribution<double> dist2(0.0, 1.0); //0.0 ~ 1.0 less than
			for (int i = 0; i < 7; i++)
			{
				auto result = dist2(rng1);
				std::cout << result << std::endl;
			}

			system("pause");
		}
	}


	void an_example_of_a_random_number_generator_that_combines_an_engine_with_a_distribution()
	{
		/*
			An example of a random number generator that combines an engine with a distribution
		*/
		{
			std::default_random_engine engine;
			std::uniform_int_distribution<int> dist(1, 100);

			auto result = dist(engine);

			std::cout << result << std::endl;

			system("pause");
		}
	}


	void an_example_of_using_a_random_number_generator_with_bind()
	{
		/*
			An example of using a random number generator with bind
		*/
		{
			std::default_random_engine engine;
			std::uniform_int_distribution<int> distribution(1, 10);
			auto generator = std::bind(distribution, engine);
			auto result = generator();

			std::cout << result << std::endl;

			system("pause");
		}
	}


	void an_example_of_getting_distribution_random_info()
	{
		/*
			An example of getting distribution random info
		*/
		{
			std::uniform_int_distribution<int> dist;
			std::uniform_int_distribution<int>::result_type min = dist.min();
			std::uniform_int_distribution<int>::result_type max = dist.max();

			std::uniform_int_distribution<int>::param_type param = dist.param(); //get distribution random info

			dist.reset(); //clear cached random info !!!

			system("pause");
		}
	}

	
	void engine_template_class()
	{
		/*
			Engine Template class

			The standard library provides a number of uniform random number generator engines.
			First, the most basic engine is the linear_congruential_engine template class,
			which implements a linear congruential algorithm.
			The rand function is an example of a typical implementation of a linear joint engine and
			the ignition formula of a linear joint engine is as follows.

				X^n + 1 = (aX^n + c) Modm

			Since the linear joint engine generates recursive values ​​successively,
			the memory required for random number generation is small and
			can generate a random number sequence very quickly,
			but the next value is affected by the present value and
			the quality of the random number sequence is poor.
			Therefore, we do not recommend using random random numbers for specific functions and
			using the results for statistical Monte Carlo simulation or for cryptographic and security purposes.
			Among the predefined engines,
			minstd_rand and minstd_rand0 are template specialization classes for the linear Joint Engine.

			A commonly used engine template is the mersenne_twister_engine template class,
			which implements the mersenne twister algorithm.
			Mersenne Twister is named after the idea that the number of repetitions of random numbers is a Mersenne prime number.
			It is possible to implement the algorithm by bit operation only, and
			the sequence generation speed is very fast and the quality of the sequence is good.
			Was released in 2002.
			In 2006, code was created to speed up random number generation using the processor's SSE instructions with 128-bit SIMD.
			The Mersenne Twister algorithm maker's homepage has released algorithms optimized for use in various environments such as CUDA.
			MT19937, which has 2^19937 cycles among the various kinds of algorithms, is the most used, and
			it has a good quality of random number, so it is not too difficult to use it when a general random number is needed.
			It is suitable for use in simulations, etc. However, by collecting about 624 random numbers,
			it can track the state of the random number generator and
			deduce the next random number of the sequence so that
			it can be used for password and security purposes. Is not recommended.

			There are a number of template arguments for the mersenne_twister_engine class.
			In order to implement the exact algorithm, you have to satisfy some of the parameter conditions.
			Among the template parameters, _Wx is the word size, _Nx is the state size, and _Rx is the mask bit,
			value of _Wx * (_Nx - 1) + _Rx must be Mersenne prime.
			The mersenne_twister_engine class typically uses predefined engines rather than
			creating custom engines because of the many template parameters.

			The Mersenne Twister algorithm uses a lot of cycles with 2 ^ 19937-1, and
			the standard C ++ random library provides the predefined Mersenne twister algorithm class mt19937 for that period and
			provides its 64-bit version, mt19937_64.

			The sequence generated by the linear joint algorithm is general but simple, categorized, and short in duration.
			There are several random number generation algorithms to overcome these drawbacks, and
			one of them is to use delayed Fibonacci sequences.
			Delayed Fibonacci sequences have a very long cycle, good water repellency, and
			fast production times, and are easy to vectorize and parallel.

			The subtract_with_carry_engine template class generates random numbers without multiplication,
			so it is very fast and the quality of the random number sequence is good, and
			the quality of the random number sequence can be greatly improved by using the engine adapter template which
			discards some of the generated values of the random number sequence.

				x(i) = (x(i - S) - x(i - R) - cy(i - 1)) mod M

			The S and R of the ignition formula of the delayed Fibonacci sequence correspond to the S and
			R of the template parameters of subtract_with_carry_engine, and
			M is equal to the value of the template class argument W multiplied by 2.

			In the case of a delayed Fibonacci sequence,
			incorrect assignment of the template parameter results in poor quality of the random number sequence.
			Therefore, we recommend using the predefined classes ranlux24_base and ranlux48_base.

			The key to engine selection is to find out what is right for you in terms of the trade-off relationship between time and performance.
			Linear_congruential_engine can be implemented directly through a fast and simple algorithm, and
			does not require much memory space to perform the algorithm.
			However, the quality of the random number is low and
			a sequence of random numbers corresponding to a certain range is generated according to the random number.
			Since subtract_with_carry_engine is processed by bit operation etc., special operation is not necessary and
			it can be expected to improve speed through vectorization or parallelization.
			However, if the initial value is wrong, it generates a very low number of random numbers.
			The subtract_with_carry_engine or mersenne_twister_engine has a disadvantage of using memory more than linear_congruential_engine.
			Mersenne_twister_engine can make the random number sequence very long by properly assigning template parameters.
		*/
		{
		}
	}
	

	void engine_adaptor_template()
	{
		/*
			Engine Adaptor template

			The engine adapter template class accepts the engine as one of the template arguments, which
			improves the quality of the random number sequence by editing the sequence generated by the base engine.

			discard_block_engine template class is a representative engine adapter template class that
			discards some of the random number sequences generated by the base engine and
			repeats cycles as needed to significantly improve the quality of the engine sequence.

			Ranlux24, ranlux48, etc. are the predefined engine classes that apply discard_block_engine.
			Independent_bits_engine improves the quality of the random number sequence by rearranging
			the bit values of the random number sequence of the underlying engine and
			shuffle_order_engine rearranges the order of the random number sequence.
			Knuth_b is a predefined engine class that has a linear_congruential_engine base class and
			shuffle_order_engine as an adapter class to supplement the quality of the sequence.
		*/
		{
		}
	}


	void non_deterministic_random_generator()
	{
		/*
			Non-deterministic Random Generator

			Generally, a random number generator generates a random number sequence based on a seed value.
			The seed value is a value that must be input decisively.
			This is because we pass the value as an argument to the seed member.
			The standard random number library provides random_device,
			a nondeterministic random number generator template class.
			A random number generated by random_device uses a system value or an operating system or
			a hardware resource since the seed value must be a random number that does not need the seed value.
		*/
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, 99);

			std::cout << dist(mt) << std::endl;
				
			system("pause");
		}

		/*
			To accomplish this, we wrap the CryptGenRandom() function for Windows, and
			/dev/random or /dex/urandom for Unix or Linux.
			By creating an instance of the engine with the seed value of a random random number generator and
			instantiating an engine adapter template class based on the engine,
			it is used as a random number generator to improve the security and
			improve the quality of the random number sequence.
			The random_device value can be used as a random value.
			However, it is common to use very expensive operating system resources or
			hardware devices to generate random_device values on all platforms,
			including the Windows operating system.

			The basic random number engine in Visual C++, mt19937,
			generates random numbers of 500 megabytes per second,
			while random_device generates random numbers of 1.9 megabits per second.
			Therefore, you should avoid using random_device continuously when developing applications that
			require continuous random numbers for application performance.
		*/
		{
			// random_device value has an even distribution
			std::random_device randomDevice;
			std::array<int, 10> test = { 0, };
			std::uniform_int_distribution<int> dist(0, 9);
			for (int n = 0; n < 1000000; ++n) {
				++test[dist(randomDevice)];
			}

			system("pause");
		}
	}


	void using_the_distribution_class()
	{
		/*
			using the distribution class

			The engine class sets the minimum and
			maximum values according to the type of the template argument when defining the instance,
			generates a sequence according to the algorithm of the engine, and returns an arbitrary value.
			The engine typically sets the minimum and maximum values that can be returned depending on the return type.
			For example, mt19937, defined as the default random number engine in Visual C++,
			generates a random number between 0 and 2^32-1
				
				Predefined minimum and maximum values per engine category
				clas				min		max
				minsted_rand0		1		2,147,483,646
				minsted_rand		0		2,147,483,646
				mt9937				0		4,294,967,295
				mt9937_64			0		18,446,744,073,709,551,615
				ranlux24_base		0		16,777,215
				ranlux48_base		0		281,474,976,710,655

			Any value obtained from the engine now needs to be transformed to use a range of values ​​that
			is appropriate for the business logic, which is handled by the distribution class.
			In general, it is important to use the proper distribution for the random number rather than the engine,
			unless random quality is a very important field, such as random number sequence or random number sequence,
			such as testing, simulation, or cryptographic logic.
			The distribution class is responsible for transforming an arbitrary number obtained from the engine to a specific range or
			frequency and converting it to a random number according to the business logic of the program.
			The distribution classes are classified into uniform distribution groups, Bernoulli distribution groups,
			Poisson distribution groups, Normal distribution groups, and Sampling distributions according to the range or
			frequency of conversion. Can be grouped.
			The distribution can be roughly classified into a discrete distribution with a finite probability value and
			a continuous distribution with a probability density function.
		*/
	}


	// use std::uniform_int_distribution example
	class CustomEngine
	{
	public:
		typedef unsigned int result_type;
		static result_type min() { return 0; }
		static result_type max() { return 100000000; }
		explicit CustomEngine() : cache_(0) { }
		result_type operator()() { return ++cache_; }

	private:
		unsigned int cache_;
	};

	void use_std_uniform_int_distribution()
	{
		/*
			use std::uniform_int_distribution

			uniform distribution rearranges any value obtained from the engine into a uniform distribution.
			In general, you can use uniform distribution for the portion of the rand() function where
			you specify the category by using %.
			Specify the maximum and minimum values required
			for the template parameter of uniform_int_distribution class so that 
			the random number value through the random number generator is a value between the categories.
			If the type is a real type, you can use the uniform_real_distribution class.

			CustomEngine class returns values in order from the internally set minimum to the maximum.
			In the end, CustomEngine returns a perfectly uniform distribution,
			so you can easily see the result of the distribution class.
			If you set the category of uniform_int_distribution template class from 0 to 9,
			connect CustomEngine, and generate a random number that is large enough,
			you can see that the results are uniform.
			uniform distribution is evenly distributed over the whole range of random numbers.
		*/
		{
			std::array<int, 10> tmp = { 0, };
			CustomEngine ce;
			std::uniform_int_distribution<> dis(0, 9);
			for (int i = 0; i < 100000; ++i) {
				++tmp[dis(ce)];
			}
			for (int i : tmp) {
				std::cout << i << " ";
			}
			std::cout << std::endl;

			system("pause");
		}

		/*
			generate_canonical class generates randomly distributed random numbers between 0.0 and
			1.0 in real numbers.
			Note that the generate_canonical class in Visual Studio 2013 uses uniform_real_distribution class,
			which sets the argument to produce the same result,
			because the implementation is incorrect and the result is not as standard.
			This issue will be addressed in the Visual Studio 2014 release.
		*/
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			for (int i = 0; i < 5; ++i) {
				std::cout << std::generate_canonical<double, std::numeric_limits<double>::digits>(mt) << " ";
			}
			std::cout << std::endl;

			system("pause");
		}

	}


	void use_std_bernoulli_distribution()
	{
		/*
			use std::bernoulli_distribution

			Bernoulli distribution uses the bernoulli_distribution class and
			is used to determine true or false with a fixed fixed probability.
			You can get random numbers like front/back, success/failure, and on/off like a coin throw.
			For example, if you call another virtual character from within a game,
			you can use the Bernoulli distribution with a factor of 0.5 as the argument for whether
			the virtual character is a man, or
			you can use the distribution creator You can use the Bernoulli distribution with a probability of 1/6.
		*/
		{
			// A random value of true or false can be obtained with a probability of 30%.
			std::array<int, 2> tmp = { 0, };
			std::random_device seed;
			std::default_random_engine eng(seed());
			std::bernoulli_distribution dist(0.3);
				
			bool result = dist(eng);

			for (int i = 0; i < 100000; ++i) {
				if (dist(eng)) {
					++tmp[1]; 
				}
				else { 
					++tmp[0]; 
				}
			}
			for (int i : tmp) { 
				std::cout << i << " ";
			}

			std::cout << std::endl;

			system("pause");
		}
	}


	void use_std_binomial_distribution()
	{
		/*
			use std::binomial_distribution

			Suppose that in a farm game, pig farms consistently raise 13 pigs.
			But one day when the application was set to kill a couple of pigs when they set up a 20% chance that
			they had a strong food poisoning bacteria on their pigs' food.
			If you use a Bernoulli-distributed random number to find the number of dead pigs,
			a probability of 0.2 will result in the death of a certain number of pigs.
			But this is a problem.
			Because each pig consumes food with its own food-borne bacteria,
			the probability of each pig's death is 20%, not 20% of the entire community.
			Because pigs die every 20% of the time, if they are lucky as a whole, only one can die, and
			if they are not lucky, they can die.
			And for real gamers, it would be even more fun to have a bit more fluid than to die 20% at a glance.
			Binomial distributions can be used if a certain probability is given and
			a problem of the kind in the population is chosen.

			The number of cases that can be combined if the number of pigs can not die due to 13 pigs can be set to 14.
			The binomial_distribution template class receives two arguments, the population N and the probability p.
			In the pig problem, the number of possible outbreaks and the probability of death are set to 14 and 0.2, respectively.
			If you get a random number, you can get various values such as lucky birds do not die and 7 birds die in groups.
		*/
		{
			// An example of a code that finds a random number with a 20% probability in a population of 14 using a binomial distribution.
			std::array<int, 14> tmp = { 0, };
			std::random_device seed;
			std::default_random_engine eng(seed());
			std::binomial_distribution<> dist(14, 0.2);

			for (int i = 0; i < 100000; ++i) {
				++tmp[dist(eng)];
			}
			for (int i : tmp) { 
				std::cout << i << " ";
			}
				
			system("pause");
		}
	}


	void use_std_geometric_distribution()
	{
		/*
			use std::geometric_distribution

			Suppose that the areas 0 to 9 are divided into zones and laid out in a row.
			At this time, assume that there is a green grass that grows well at a probability of 70% in area 0, and
			that the contaminated soil becomes red when it goes to area 9 and grass does not grow well.
			If you want to set the ratio of green to green in each zone from 0 to 9, how can you implement it ?

			Geometric distribution is given as a factor, which is the probability of success on the first attempt.
			The higher the probability, the higher the probability of success in the first attempt, and the lower the probability,
			the higher the rank in the order of the next rank.
			In the area 0, it is possible to express the green grass area with the approximate probability of 70%, and
			the less the random number value to take the green point,
			the more the green grass area can be represented by the pollution.
		*/
		{
			std::array<int, 14> tmp = { 0, };
			std::random_device seed;
				
			std::default_random_engine eng(seed());
			std::geometric_distribution<int> dist(0.7);

			for (int i = 0; i < 100000; ++i) {
				++tmp[dist(eng)];
			}
			for (int i : tmp) { 
				std::cout << i << " "; 
			}
			
			system("pause");
		}
	}


	void use_std_negative_binomial_distribution()
	{
		/*
			use std_negative_binomial_distribution

			Negative Binomial Distribution is a kind of discrete distribution.
			Assuming that it succeeds with p probability,
			we can give the number of times that failed until k successes as a random number.

			The first argument of the template class constructor corresponds to the success k and
			the second argument to the success probability p.
			The random number through the negative binomial distribution eventually becomes the number of failures.

			For example, you might be able to simulate the number of batters that
			will not hit you until you hit 4 hits and hit 2 hits.
		*/
		{
			std::array<int, 20> tmp = { 0, };
			std::random_device seed;
			std::default_random_engine eng(seed());

			std::negative_binomial_distribution<> dist(2, 0.4);
				
			for (int i = 0; i < 100000; ++i) {
				int t = dist(eng);
				if (t > 19)
					continue;
				++tmp[t];
			}
			for (int i : tmp) { 
				std::cout << i << " ";
			}

			system("pause");
		}
	}

	
	void discrete_distribution()
	{
		/*
			Discrete distribution

			The discrete distribution can select a random number from the additive set, which is a collection of possible values.
			For example, assuming a fair coin throw, the probability of the front face is 0.5.
			For example, you can choose a random number for a die when you roll a die within the additive set of 1, 2, 3, 4, 5, 6.
			The discrete distributions provided by the standard C ++ random number library,
			such as the Bernoulli distribution, binomial distribution, geometry distribution, Poisson distribution, and
			uniform distribution, provide integer values ​​as the result.
			The continuous distribution represents a selected random number among the possible values ​​in a continuous range
			other than the additive set form.
			For example, the time it takes for a certain frequency band that can not be predicted to vibrate.
			A particular additive set can not be selected for the result values.
			The standard C ++ random number library provides floating-point values ​​as the result of this continuous distribution, and
			is an example of a typical continuous distribution such as exponential distribution, gamma distribution,
			normal distribution, and uniform real number distribution.
		*/
		{
		}
	}


	void poisson_distribution_group()
	{
		/*
			Poisson distribution group

			Poisson distribution groups include Poisson distribution, Exponential distribution, 
			Gamma distribution, Weibull distribution, Extreme Value distribution, and
			the standard C ++ random number library Supports their distributions with the poisson_distribution,
			exponential_distribution, gamma_distribution, weibull_distribution, and
			extreme_value_distribution template classes, respectively.
			Poisson distribution is a typical discrete probability distribution with Bernoulli distribution and
			is one of the most frequently used distributions.
			Poisson distribution means the number of times a particular event issues in a certain space or period.
			For example, the number of people who visit a fast food store,
			the number of defective insole that is attached to a factory that attaches a shoe insole, and
			the number of commits committed to a large project registered on a configuration management system, GitHub.
			Or when estimating the number of people born in Seoul on a specific time basis or
			estimating the number of cars passing through the highpass gate for one hour at Pangyo Tollgate, And the like.
			The place or time must be a unit or unit time, and
			the probability of an event being issued must be constant over the whole unit time, and
			it must be a single event that does not interfere with other events, 
			uch as cars passing through defective products, do.
			Because it is not affected by other factors,
			the total number of occurrences is proportional to the size due to the probability of occurrence
			in a certain unit interval. For other discrete probabilities, the total number of trials,
			the number of successes, and the number of failures must be known, and
			the value between the probabilities associated with them can be obtained.
			However, the Poisson distribution has no relation to success or failure since it is meaningful only for
			the number of occurrences without the number of trials.
			Therefore, if the number of occurrences and the average are known,
			random numbers in the distribution range reflecting the probability values ​​can be obtained.
			The ignition formula of Poisson distribution is as follows.
			The lambda value in the recursion formula must be greater than or equal to zero.

				f(k; λ) = Pr(X=k) = λ^ke-^-λ/k!

			The lambda value of the recursion is the average.
			If an event occurs in an interval with an average length of lambda,
			the probability of each value k of the random number sequences is equal to the probability that
			the event occurs k times in a lambda length interval.
			Since e is a constant and irrational number,
			it can be expressed as an approximate value of 2.7182818284590452353602874 ... as a decimal number because it is irrational.
			The e value is an important constant used below the natural logarithm and can be expressed as an ignition formula below.

				e = lim (1 + 1/n)^n
					n→∞

			The lambda value corresponds to the mean of the poisson_distribution template class member.
			Generates a sequence of zero or more values corresponding to IntType and uses it as a random number.

			The return value of member function mean() in poisson_distribution is the value of the constructor argument when
			creating an instance of the poisson_distribution template class,
			which corresponds to the lambda value in the recursive expression.
			As you can see in the general distribution, it has min(), max() members, input_type, result_type, and so on.

			If you put an average value in an instance of poisson_distribution,
			you can get a random number that follows the Poisson distribution based on the average value.
			If you generate a random number of random numbers continuously through a random engine,
			you can see that the frequency of the result follows the Poisson distribution.
		*/
		{
			//An example of code that obtains a random number following a Poisson distribution with a probability of 3.5
			std::array<int, 20> tmp = { 0, };
			std::random_device seed_gen;
			std::default_random_engine eng(seed_gen());
				
			std::poisson_distribution<int, double> dist(3.5);

			for (int i = 0; i < 100000; ++i) {
				int t = dist(eng);
				++tmp[t];
				if (t > 19) continue;
			}

			system("pause");
		}
	}


	void use_std_exponential_distribution()
	{
		/*
			use std::exponential_distribution

			The exponential distribution is a representative continuous distribution library of standard C ++ random number libraries.
			It is used when the probability decreases with time.
			For example, assuming that you have created a physical strength value for a simulated element in a game such as Diablo,
			moving the long distance between the map and the village with equipment, weapons, and
			items you have acquired, Will decrease.
			If a unique boss monster is in the field and has a life element on it to make it exist for a certain amount of time,
			the more time the monster appears, the more likely it is that the monster will disappear.
			At this time, as the probability of being alive decreases over time,
			the use of random numbers can reflect the exponential distribution.
			In a game like Quake, when you carry a powerful electromagnetic gun,
			you can apply an exponential distribution that reduces the probability that
			you will not be able to use it unless you eventually discharge it without recharging it without using it.

			In a game like Dungeons and Dragons, let's say you've given away a large number of weapons as dragons.
			This weapon is more durable as time goes by, and eventually it breaks down so that it can not be used.
			Instead of breaking all the swords of a dragon,
			you can change the timing of the cracks by reflecting the random number It will be more interesting.
			The ignition formula of the exponential distribution can be expressed as:

				p(x|λ) = λe^-λx , x > 0

			The value passed to the constructor in the template class and the value stored in the instance is the lambda value,
			which is the lambda value of the probability density function p.
			If the number of strikes of a character who has the ability to hit 5 times per second in an online game
			is determined by the Poisson distribution random number,
			the time taken from the first shot to the next shot can be obtained by the random number of the exponential distribution.
			The lambda value passed to the constructor of the exponential_distribution template class is 5.

			You can create an instance by passing a lambda value to the exponential_distribution constructor, and
			the lambda value assigned to the instance can be retrieved through the lambda () member.

			Notice that the result is inverted to floating point.
			If you use exponential_distribution to find enough random numbers and graph it,
			you can see that it is an exponential distribution.
		*/
		{
			std::array<int, 10> tmp = { 0, };
			std::random_device seed_gen;
			std::default_random_engine eng(seed_gen());

			std::exponential_distribution<> dist(1);
				
			for (int i = 0; i < 100000; ++i) {
				double number = dist(eng);
				if (number < 1.0)
					++tmp[int(10 * number)];
			}
		}
	}


	void use_std_gamma_distribution()
	{
		/*
			use std::gamma_distribution

			The gamma distribution is a continuous probability distribution and the recursion formula is as follows.
			It takes two values of alpha and beta as arguments, and in the following ignition formula, when x is 1,
			lambda has the same distribution as exponential values of 1.

				p(x|a,b) = (1 / r(a) * b^a) * x^(a-1) * e^(-x/b) , x >= 0

			Assuming that you have 5 characters per second to strike and give 100 damage per hit, and
			the number of strikes follows the Poisson distribution,
			the value of the time taken to kill a monster with a Stamina of 1000 is the gamma distribution.
			Once you hit it, it will take 100 damage, so your character must hit 10 times to kill the monster.
			Therefore, the parameters of the gamma distribution are given as 5 and 10.

			Gamma_distribution provides the alpha() and beta() member functions to
			retrieve the parameters alpha and beta as constructors.
			Gamma_distribution generates a random number greater than 0 and
			receives a type for the result value as a template argument.

		*/
		{
			//An example of a random number when the alpha and beta values of gamma_distribution are 2.0, respectively.
			double a(2.0), b(2.0);

			std::mt19937 gen(1701);
			std::gamma_distribution<> distr(a, b);
			std::cout << std::endl;
				
			std::cout << "min() == " << distr.min() << std::endl;
			std::cout << "max() == " << distr.max() << std::endl;
			std::cout << "alpha() == " << distr.alpha() << std::endl;
			std::cout << "beta() == " << distr.beta() << std::endl;

			std::map<double, int> histogram;
			for (int i = 0; i < 10; ++i) {
				++histogram[distr(gen)];
			}
				
			int counter = 0;
			for (const auto& elem : histogram) {
				std::cout << ++counter << ": " << elem.first << std::endl;
			}
			std::cout << std::endl;

			system("pause");
		}

		/*
			We can see that gamma_distribution shows a gamma distribution when the graph is obtained by
			generating enough random numbers to obtain the frequency in each interval where
			the alpha value and the beta value are 2.0 respectively.

			Note that the gamma distribution along with the exponential distribution is the number of occurrences of
			the random number in the interval, such as a value between 0 and 1, and a value between 1 and 2,
			rather than a specific number of times,
		*/
		{
			//Example of code that gets the frequency of gamma_distribution
			std::default_random_engine eng;
			std::gamma_distribution<double> dist(2.0, 2.0);

			std::array<int, 10> tmp = { 0, };
			for (int i = 0; i < 10000; ++i) {
				double number = dist(eng);
				if (number < 10) ++tmp[int(number)];
			}
			for (int t : tmp) {
				std::cout << t << std::endl;
			}

			system("pause");
		}

	}


	void use_std_weibull_distribution()
	{
		/*
			use std::weibull_distribution

			Weibull distribution is generally defined as the ability to simulate the survival of a living bacterium when
			subjected to a particular stimulus in a microbiological laboratory environment, or to cause degradation, destruction,
			or death by certain factors, such as when modeling the life span of a specific component in a device environment.
			Used in situations.
			The difference from the exponential distribution is that if we consider only the case where
			the probability of failure of a specific part is constant,
			we can obtain the random number considering both the case where the probability of failure of the part
			increases over time

				p(x|a,b) = a/b * (x/b)^(a-1) * e^-(x/b)^a , x >= 0

			In the recursion formula, a and b are received, where a is the waviness coefficient or shape parameter, and
			b is the scale parameter.
			The weibull_distribution template class provides member functions a() and b() that can query a and b values.
		*/
		{
			system("pause");
		}
	}


	void normal_distribution_group()
	{
		/*
			Normal distribution group

			If you want to find a random number in the front and back of a coin, a scissors rock, a dice, a play, etc.,
			the binomial distribution is used because it makes a specific selection in the situation where
			the number of occurrences is determined.
			However, when the number of such songs increases,
			it becomes difficult to predict which pattern will be most frequently released,
			for example, when the music is thousands or tens of thousands of songs.
			However, the distribution of random numbers should reflect this frequency.
			When the number of items that can come out of a natural phenomenon is increased,
			the appearance of a normal distribution is obtained.
			For example, if there is an average height in Korea,
			there are many people who do not deviate much from the average height.
			The normal distribution is one of the most famous distributions, and is also called the Gaussian distribution,
			as it is most frequently used as the continuous probability distribution included
			in the regular high school courses in Korea.
			Statistics are the most important and widely used distribution.
			Many natural values ​​are normally distributed.

			The normal distribution groups supported by the standard C ++ random number library include Normal Distribution,
			Lognormal Distribution, Chisquared Distribution, cauchy_distribution, F distribution (Fisher_F_distribution),
			Student t distribution ( Student's t Distribution).
			It provides the template classes for normal_distribution, lognormal_distribution, chi_squared_distribution,
			cauchy_distribution, fisher_f_distribution, and student_t_distribution, which support each distribution.
			The ignition formula of the normal distribution is as follows.
			The factor requires an average value of μ and a standard deviation of σ.

				p(x|u,q) = 1 / q√2π * e^-(x-u)^2/2a^2

			The normal_distribution template class that supports the normal distribution receives average and
			standard deviation values through the constructor and can be queried through mean() and stddev() members.
			Note that you must enter a value greater than or equal to 0 when
			assigning a standard deviation value through the constructor.

			The normal_distribution template class generates a random number of a type of RealType.
			The average probability of occurrence of the values is the mean given to mean and
			follows the normal distribution with variance S * S.

			The normal_distribution distribution template class,
			which has an average of 5 and a standard deviation of 2, generates random numbers.
		*/
		{
			std::default_random_engine eng;
			std::normal_distribution<double> dist(5.0, 2.0);

			std::array<int, 10> tmp = { 0, };
			for (int i = 0; i < 10000; ++i) {
				double number = dist(eng);
				if ((number >= 0.0) && (number < 10.0))
					++tmp[int(number)];
			}

			system("pause");
		}
	}


	void use_std_lognormal_distribution()
	{
		/*
			use std::lognormal_distribution

			The log-normal distribution takes an exponential value in the normal distribution and
			the frequency of the most frequent occurrences is shifted to the left.
			For example, in a stock simulation, you might be able to get a random value that
			follows the log-normal distribution in order to increase the revenue to the normal distribution form, and
			include a random number in the determination of the salary increase to be paid to
			employees in the management simulation game You can use the lognormal distribution.
		*/
		{
			system("pause");
		}
	}


	void Test()
	{
		//cpp_std_random();

		//random_generator();

		//non_deterministic_random_number_generation();

		//generate_random_numbers_in_range();

		//an_example_of_a_random_number_generator_that_combines_an_engine_with_a_distribution();

		//an_example_of_using_a_random_number_generator_with_bind();

		//an_example_of_getting_distribution_random_info();

		//engine_template_class();

		//engine_adaptor_template();

		//non_deterministic_random_generator();

		//using_the_distribution_class();

		//use_std_uniform_int_distribution();

		//use_std_bernoulli_distribution();

		//use_std_binomial_distribution();

		//use_std_geometric_distribution();

		//use_std_negative_binomial_distribution();

		//discrete_distribution();

		//poisson_distribution_group();

		//use_std_exponential_distribution();

		//use_std_gamma_distribution();

		//use_std_weibull_distribution();

		//normal_distribution_group();
		
		//use_std_lognormal_distribution();
	}

}// end of Auto