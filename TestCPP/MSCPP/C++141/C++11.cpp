#include "stdafx.h"


#include <type_traits>

namespace CPP11
{
	// this overload is always in the set of overloads
	// ellipsis parameter has the lowest ranking for overload resolution
	void Func(...)
	{
		std::cout << "Catch-all overload called\n";
	}

	// this overload is added to the set of overloads if
	// C is a reference-to-class type and F is a member function pointer
	template<class C, class F>
	auto Func(C c, F f) -> decltype((void)(c.*f)(), void())
	{
		std::cout << "Reference overload called\n";
	}

	// this overload is added to the set of overloads if
	// C is a pointer-to-class type and F is a member function pointer
	template<class C, class F>
	auto Func(C c, F f) -> decltype((void)((c->*f)()), void())
	{
		std::cout << "Pointer overload called\n";
	}

	struct X { void f() {} };


	// for check function
	template<typename T>
	class Checker
	{ 
	public:
		typedef short yes;
		typedef char no;
		
		template <typename C>
		static yes Func(decltype(&C::Call)) {
			return 1;
		}
		
		template <typename C>
		static no Func(...) { 
			return '0';
		}
		
		enum { IsFunc = sizeof(Func<T>(0)) == sizeof(yes) };
	};
	
	class A
	{ 
	public:
		virtual void Call() { return; }
	};
	
	class B
	{ 
	public: 
	};

	void expression_SFINAE()
	{
		/*
			Expression SFINAE

			Expression SFINAE support in more libraries The Visual C++ compiler continues to improve its support for expression SFINAE,
			which is required for template argument deduction and substitution where decltype
			and constexpr expressions may appear as template parameters.
				
			For more information, see Expression SFINAE improvements in Visual Studio 2017 RC.

			What is expression SFINAE?
				
			SFINAE is an acronym for ¡°substitution failure is not an error.¡±
			It is derived from an arcane process used by C++ compilers during overload resolution.
			At its core, the idea is quite simple:
			if a candidate function template¡¯s specialization would lead to an ill-formed (compiler-internal)
			declaration of that specialization,
			just silently ignore that template as is if the compiler has never seen it.
			In another words, the compiler will pretend that wasn¡¯t the template it was looking for.
			It is an old notion that has been part of C++ since it¡¯s the C++98 release.
			In that version of C++, the condition for 
			¡°ill-formed compiler-internal declaration of a function template specialization¡±
			was specified for types only.

			With the advent of type query features such as decltype and auto,
			the validity of a function type now entails the validity of expressions,
			since whether decltype(expr) is a valid type depends on whether the operand expr is well-formed.
			Hence the term ¡°Expression SFINAE¡±.
			It is a little bit more involved because now the compiler has to perform overload resolution including potentially
			unbounded evaluation of constant expressions while it is checking whether a type makes sense.

			URL : http://en.cppreference.com/w/cpp/language/sfinae
		*/
		{
			X x;

			Func(x, &X::f);
			Func(&x, &X::f);
			Func(42, 1337);

			system("pause");

			/*
			output:
				Reference overload called
				Pointer overload called
				Catch-all overload called
			*/
		}

		/*
			Use decltype and SFINAE to check whether compile time exists
		*/
		{
			std::cout << Checker<A>::IsFunc << ", " << Checker<B>::IsFunc << std::endl;

			system("pause");
			/*
			output:
				1, 0
			*/
		}
	}


	void Test()
	{
		//expression_SFINAE();
	}
}