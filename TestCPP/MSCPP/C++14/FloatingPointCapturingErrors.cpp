#include "stdafx.h"

#include <cmath>
#include <cfloat>

namespace FloatingPointCapturingErrors
{
	//There are a couple of ways to trap NANs, and some requires a debugger attached to get the best results.

	void numberic_compare()
	{
		/*
			Comparison

			When comparing the variable against itself, it will produce opposite results than with normal numbers.
		*/
		{
			double inf = std::numeric_limits<double>::infinity();
			double nan = std::numeric_limits<double>::quiet_NaN();
			double ind = sqrt(-1);

			if (nan != nan) {
				std::cout << "nan != nan" << std::endl;
			}

			if (ind != ind) {
				std::cout << "ind != ind" << std::endl;
			}

			if (inf != inf) {
				std::cout << "inf != inf" << std::endl;
			}

			//Note, infinity is a number!

			/*
			output:
				nan != nan
				ind != ind
				std::isnan(nan) is true
				std::isnan(ind) is true
			*/

			system("pause");
		}
	}

	void numeric_compare_std()
	{
		/*
			Use the standard C++11

			C++11 introduced a couple of methods to determine if a value is a NaN or not,
			which are residing the the std::namespace.
		*/
		{
			if (std::isnan(NAN))
				std::cout << "std::isnan(NAN) is true" << std::endl;

			if (std::isnan(sqrt(-1.0)))
				std::cout << "std::isnan(sqrt(-1.0)) is true" << std::endl;

			if (std::isnan(INFINITY))
				std::cout << "std::isnan(INFINITY) is true" << std::endl;

			//Note that inf is still missing, which is correct behavior.

			/*
			output:
				std::isnan(nan) is true
				std::isnan(ind) is true
			*/

			system("pause");
		}
	}


	void numeric_compare_msvc()
	{
		/*
			Control floating-point control word - MSVC

			The use of _controlfp and _control87 family will alter the floating-point control word,
			essentially making the computer issue a hardware exception when a floating point exception occurs.
			The default with MSVC is to silence floating point exceptions,
			with the possibility to silently destroy simulations.

			I personally recommend turning on all floating point exceptions,
			so all (or most) cases can be reviewed and the code made more robust.

			The usage is a bit counter-intuitive, but after a while you¡¯ll get used to it.
			Here is what works for me.
		*/
		{
			//According to the docs, always clear fp control word
			auto state = _clearfp();
			state = _control87(0, 0);
		}

		/*
			This will reset, and get current floating point control word state.
			With this, we can modify the floating point control word to our liking.
		*/
		{
			auto state = _clearfp();

			//This will turn ON FPE for zerodiv
			state = _control87(state & ~_EM_ZERODIVIDE, _MCW_EM);

			//This WILL NOT fail
			const double sqrtneg = sqrt(-1);

			//This WILL fail due to zerodiv
			const double zero = 0.0;
			//const double zerodivresult = 1.0 / zero; //error C2124
		}
		/*
			Otherwise, we can break on indeterminate (#IND) with _EM_INVALID.
		*/
		{
			auto state = _clearfp();

			// This will turn on FPE for #IND
			state = _control87(state & ~_EM_INVALID, _MCW_EM);

			// This WILL fail
			const double sqrtneg = sqrt(-1);

			// This WILL NOT fail and it'll produce #inf
			const double zero = 0.0;
			//const double zerodivresult = 1.0 / zero; //error C2124
		}
		/*
			If you want to turn on two or more FPEs, you must do some bit arithmetic to set the right switches.
		*/
		{
			auto state = _clearfp();

			// This will turn on FPE for #IND and zerodiv
			state = _control87(state & ~(_EM_ZERODIVIDE | _EM_INVALID), _MCW_EM);
		}
		/*
			If you want to turn all FPEs, this will do it.
		*/
		{
			auto state = _clearfp();
			
			// All FPEs
			state = _control87( state & ~(  _EM_INEXACT | _EM_UNDERFLOW
                                         | _EM_OVERFLOW | _EM_ZERODIVIDE 
				                         | _EM_INVALID  | _EM_DENORMAL )
				              , _MCW_EM );

			//To find out what floating point exception which are active, this snippet will help.
			bool inexact = 0 == (state & _EM_INEXACT);
			bool underflow = 0 == (state & _EM_UNDERFLOW);
			bool overflow = 0 == (state & _EM_OVERFLOW);
			bool zerodiv = 0 == (state & _EM_ZERODIVIDE);
			bool invalid = 0 == (state & _EM_INVALID);
			bool denorm = 0 == (state & _EM_DENORMAL);

			std::cout << std::boolalpha << "Will break on: n"
										<< "Inexact: " << inexact << "n"
										<< "Underflow: " << underflow << "n"
										<< "Overflow: " << overflow << "n"
										<< "Zerodiv: " << zerodiv << "n"
										<< "Invalid: " << invalid << "n"
										<< "Denormal: " << denorm << "n";
			/*
			output:
				Will break on:
				Inexact: false
				Underflow: false
				Overflow: false
				Zerodiv: true
				Invalid: true
				Denormal: false
			*/
		}

		system("pause");
	}


	void Test()
	{
		//numberic_compare();

		//numeric_compare_std();

		//numeric_compare_msvc();
	}
}