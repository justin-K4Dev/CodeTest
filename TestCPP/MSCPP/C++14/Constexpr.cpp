#include "stdafx.h"



namespace Constexpr
{
	// use constexpr example

	// when constexpr is attached to a function, it implies inline.
	// that is, it evaluates at compile time and is compiled with inline functions.
	constexpr double pow(double x, size_t y)
	{
		return y != 1 ? x * pow(x, y - 1) : x;
	}

	constexpr int factorial(int n)
	{
		return n <= 1 ? 1 : (n * factorial(n - 1));
	}

	template<int v>
	struct Print
	{
		Print() { std::cout << v << '\n'; }
	};

	/*
		constexpr int RandShort()
		{
			// Context that can never be constants
			// error C3615: The result of the constexpr function 'RandShort' must not be a constant expression.
			return rand() % 65535;
		}
	*/

	// use to constructor
	class ConstString
	{
	private:
		const char* p = nullptr;
		std::size_t sz = 0;

	public:
		template<std::size_t N>
		constexpr ConstString(const char(&a)[N]) // constructor
			: p(a), sz(N - 1)
		{
		}

	public:
		constexpr char operator[](std::size_t n) const
		{
			return n < sz ? p[n] : throw std::out_of_range("");
		}

	public:
		constexpr std::size_t size() const { return sz; }
	};

	constexpr std::size_t CountLowercase(ConstString s, std::size_t n = 0, std::size_t c = 0)
	{
		return n == s.size() ? c : s[n] >= 'a' && s[n] <= 'z' ? CountLowercase(s, n + 1, c + 1) : CountLowercase(s, n + 1, c);
	}

	void use_constexpr_keyword()
	{
		// constexpr (Generalized constant expression)
		{
			/*
				- Variables, functions, and classes can be used as integers at compile time.
				  In other words, the work that can be treated as a constant is processed at compile time.
				- You can replace #define or template.
			*/
			{
				constexpr float x = 42.f;	// OK
				constexpr float y{ 108.f }; // OK
				//constexpr int i;			// error C2737: 'i': 'constexpr' 개체를 초기화해야 합니다.
				int j = 0;
				//constexpr int k = j + 1;	// error C2131 : 식이 상수로 계산되지 않았습니다.

				system("pause");
			}
			{
				double a = pow(2.0, 2);
				double b = pow(3.0, 6);

				system("pause");
			}
			{
				// 4 is a literal type, so compilation succeeds in constant time
				Print<factorial(4)> out1;

				// Ab has a value of 4, but it is not a literal type
				// error C2975: 'v': Invalid template argument for 'Print'. A compile-time constant expression is required.
				int ab = 4;
				//Print<factorial(ab)> out2;

				// Since this is not a literal type, this function is executed at runtime.
				// But it works normally.
				int cd = factorial(ab);

				system("pause");

				/*
				output:
					24
				*/
			}
			{
				std::cout << "Number of lowercase letters in \"Hello, world!\" is ";

				// "Hello, world!" is implicitly returned as a ConstString and passed to the argument of the CountLowercase function..
				// CountLowercase was evaluated at compile time, and with the result, Print is also determined at compile time.
				Print<CountLowercase("Hello, world!")> out;

				system("pause");

				/*
				output:
					Number of lowercase letters in "Hello, World !" is 9
				*/
			}
		}
	}


	void Test()
	{
		//use_constexpr_keyword();
	}
}// end of Constexpr

