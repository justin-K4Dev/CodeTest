#include "stdafx.h"


namespace UpdateV153
{
	// for Calls to deleted member templates example
	template<typename T>
	struct S
	{
		template<typename U>
		static int f() = delete;
	};

	void calls_to_deleted_member_templates()
	{
		/*
			Calls to deleted member templates

			In previous versions of Visual Studio,
			the compiler in some cases would fail to emit an error for ill-formed calls to a deleted member template
			which would¡¯ve potentially caused crashes at runtime.

			The following code now produces C2280,
			"'int S::f(void)': attempting to reference a deleted function":
		*/
		{
			// decltype(S<int>::f<int>()) i; // this should fail "'int S::f(void)': attempting to reference a deleted function"
			int i;

			// To fix the error, declare i as int.
			i = 10;

			system("pause");
		}
	}


	void pre_condition_checks_for_type_traits()
	{
		/*
			Pre-condition checks for type traits

			Visual Studio 2017 Update Version 15.3 improves pre-condition checks for type-traits to more strictly follow the standard.
			One such check is for assignable.

			The following code produces C2139 in Update Version 15.3:
		*/
		{
			struct D;
			enum E;

			// static_assert(!__is_assignable(D, D), "fail"); // C2139 in 15.3
			// static_assert(__is_convertible_to(E, E), "fail"); // C2139 in 15.3

			system("pause");
		}
	}


	// for New compiler warning and runtime checks on native-to-managed marshaling example
	class Q
	{
	public:
		Q() : p_(new int) {}
		~Q() { delete p_; }

		Q(Q const &) = delete;
		Q(Q &&rhs)
		{
			p_ = rhs.p_;
		}

	private:
		int *p_;
	};

	// #pragma unmanaged 

	void func(Q a) { return; }

	// #pragma managed

	void new_compiler_warning_and_runtime_checks_on_native_to_managed_marshaling()
	{
		/*
			New compiler warning and runtime checks on native-to-managed marshaling

			Calling from managed functions to native functions requires marshalling.
			The CLR performs the marshaling but it doesn't understand C++ semantics.
			If you pass a native object by value,
			CLR will either call the object's copy-constructor or use BitBlt,
			which may cause undefined behavior at runtime.
			Now the compiler will emit a warning if it can know at compile time
			that a native object with deleted copy ctor is passed between native and managed boundary by value.
			For those cases in which the compiler doesn't know at compile time,
			it will inject a runtime check so that the program will call std::terminate immediately
			when an ill-formed marshalling occurs.
				
			In Update Version 15.3, the following code produces
			C4606 " 'A': passing argument by value across native and managed boundary requires valid copy constructor.
			Otherwise the runtime behavior is undefined".		
		*/
		{
			func(Q()); // This call from managed to native requires marshalling.
				        // The CLR doesn't understand C++ and uses BitBlt, which will result in a double-free later.

			// To fix the error, remove the #pragma managed directive to mark the caller as native and avoid marshalling.

			system("pause");
		}
	}


	// for Out-of-line definition of a template member function example
	struct K1 {};

	// template <typename T>
	// void K1::func(T t) {} // C2039: 'func': is not a member of 'K1'

	// To fix the error, add a declaration to the class :
	struct K2 {
		template <typename T>
		void func(T t);
	};
	template <typename T>
	void K2::func(T t) {}

	void out_of_line_definition_of_a_template_member_function()
	{
		/*
			Out-of-line definition of a template member function

			Update Version 15.3 produces an error when it encounters an out-of-line definition of a template member function
			that was not declared in the class.

			The following code now produces error C2039: 'func': is not a member of 'K1':
		*/
		{
			system("pause");
		}
	}


	void attempting_to_take_the_address_of_this_pointer()
	{
		/*
			Attempting to take the address of "this" pointer

			In C++ 'this' is an prvalue of type pointer to X. You cannot take the address of 'this' or bind it to an lvalue reference.
			In previous versions of Visual Studio, the compiler would allow you to circumvent this restriction by performing a cast.
			In Update Version 15.3, the compiler produces error C2664.
		*/
		{
			system("pause");
		}
	}


	void conversion_to_an_inaccessible_base_class()
	{
		/*
			Conversion to an inaccessible base class

			Update Version 15.3 produces an error when you attempt to convert a type to a base class which is inaccessible.
			The compiler now raises
			"error C2243: 'type cast': conversion from 'D *' to 'B *' exists, but is inaccessible".

			The following code is ill-formed and can potentially cause a crash at runtime.
			The compiler now produces C2243 when it encounters code like this:
		*/
		{
			class B { };
			class J : public B { }; // C2243. should be public B { }; 

			std::unique_ptr<B>(new J());

			system("pause");
		}
	}


	// for Default arguments are not allowed on out of line definitions of member functions example
	// template <typename T>
	// struct A
	// {
	//     T f(T t, bool b = false);
	// };

	// template <typename T>
	// T A<T>::f(T t, bool b = false) // C5034
	// { }
	// To fix the error, remove the "= false" default argument.

	void default_arguments_are_not_allowed_on_out_of_line_definitions_of_member_functions()
	{
		/*
			Default arguments are not allowed on out of line definitions of member functions

			Default arguments are not allowed on out-of-line definitions of member functions in template classes.
			The compiler will issue a warning under /permissive,
			and a hard error under /permissive- In previous versions of Visual Studio,

			the following ill-formed code could potentially cause a runtime crash.

			Update Version 15.3 produces warning C5034: 'A::f': an out-of-line definition of a member of a class template cannot have default arguments:
		*/
		{
			system("pause");
		}
	}


	void use_of_offsetof_with_compound_member_designator()
	{
		/*
			Use of offsetof with compound member designator

			In Update Version 15.3, using offsetof(T, m) where m is a "compound member designator" will result in a warning
			when you compile with the /Wall option.

			The following code is ill-formed and could potentially cause crash at runtime.
			Update Version 15.3 produces
				"warning C4841: non-standard extension used: compound member designator in offseto":
		*/
		{
			struct A {
				int arr[10];
			};

			// warning C4841: non-standard extension used: compound member designator in offsetof 
			// constexpr auto off = offsetof(A, arr[2]);

			// To fix the code, either disable the warning with a pragma or change the code to not use offsetof:
			#pragma warning(push) 
			#pragma warning(disable: 4841) 
			// constexpr auto off = offsetof(A, arr[2]);
			#pragma warning(pop) 

			system("pause");
		}
	}


	// for Using offsetof with static data member or member function example
	struct L
	{
		int foo() { return 10; }
		static constexpr int bar = 0;
	};

	void using_offsetof_with_static_data_member_or_member_function()
	{
		/*
			Using offsetof with static data member or member function

			In Update Version 15.3, using offsetof(T, m) where m refers to a static data member or a member function will result in an error.

			The following code produces
			"error C4597: undefined behavior: offsetof applied to member function 'foo'"
			and "error C4597: undefined behavior: offsetof applied to static data member 'bar'":
		*/
		{
			// constexpr auto off = offsetof(L, foo);
			// constexpr auto off2 = offsetof(L, bar);

			// This code is ill - formed and could potentially cause crash at runtime.
			// To fix the error, change the code to no longer invoke undefined behavior.
			// This is non - portable code that is disallowed by the C++ standard.

			system("pause");
		}
	}


	void new_warning_on_declspec_attributes()
	{
		/*
			New warning on declspec attributes

			In Update Version 15.3, the compiler no longer ignores attributes if __declspec(¡¦) is applied before extern "C" linkage specification.
			Previously, the compiler would ignore the attritbute, which could have runtime implications.
			When the /Wall /WX option is set, the following code produces
				"warning C4768: __declspec attributes before linkage specification are ignored":
		*/
		{
			// for New warning on declspec attributes example
			// __declspec(noinline) extern "C" HRESULT __stdcall // C4768

			// To fix the warning, put extern "C" first:
			// extern "C" __declspec(noinline) HRESULT __stdcall

			// This warning is off - by - default and only impacts code compiled with / Wall / WX.

			system("pause");
		}
	}


	// for decltype and calls to deleted destructors example
	template<typename T>
	struct W
	{
		~W() = delete;
	};

	template<typename T>
	auto f()->W<T>;

	template<typename T>
	auto g(T) -> decltype((f<T>()));

	void decltype_and_calls_to_deleted_destructors()
	{
		/*
			decltype and calls to deleted destructors

			In previous versions of Visual Studio,
			the compiler did not detect when a call to a deleted destructor occurred in the context of the expression associated with 'decltype'.
			In Update Version 15.3, the following code produces
				"error C2280: 'A::~A(void)': attempting to reference a deleted function":
		*/
		{
			// g(42); // "error C2280: 'A::~A(void)': attempting to reference a deleted function"

			system("pause");
		}
	}


	void uninitialized_const_variables()
	{
		/*
			Uninitialized const variables
			
			Visual Studio 2017 RTW release had a regression in which the C++ compiler would not issue a diagnostic
			if a 'const' variable was not initialized.
			This regression has been fixed in Visual Studio 2017 Update 1.

			The following code now produces
				"warning C4132: 'Value': const object should be initialized":
		*/
		{
			// const int Value; // C4132

			// To fix the error, assign a value to Value.
			const int Value = 100;

			system("pause");
		}
	}

	// for Empty declarations example
	struct G {};
	
	template <typename>
	struct B {};
	
	enum C { c1, c2, c3 };

	void empty_declarations()
	{
		/*
			Empty declarations

			Visual Studio 2017 Update Version 15.3 now warns on empty declarions for all types, not just built-in types.
			The following code now produces a level 2 C4091 warning for all four declarations:
		*/
		{
			// int;    // warning C4091 : '' : ignored on left of 'int' when no variable is declared
			// G;      // warning C4091 : '' : ignored on left of 'main::A' when no variable is declared
			// B<int>; // warning C4091 : '' : ignored on left of 'B<int>' when no variable is declared
			// C;      // warning C4091 : '' : ignored on left of 'C' when no variable is declared

			// To remove the warnings, simply comment - out or remove the empty declarations.
			// In cases where the un - named object is intended to have a side effect(such as RAII) it should be given a name.
			// The warning is excluded under / Wv:18 and is on by default under warning level W2.

			system("pause");
		}
	}


	void std_is_convertible_for_array_types()
	{
		/*
			std::is_convertible for array types

			Previous versions of the compiler gave incorrect results for std::is_convertible for array types.
			This required library writers to special-case the Visual C++ compiler
			when using the std::is_convertable<¡¦> type trait.
			In the following example,
			the static asserts pass in earlier versions of Visual Studio
			but fail in Visual Studio 2017 Update Version 15.3:
		*/
		{
			// compiler switch : /std:c++latest

			using Array = char[1];

			// static_assert(std::is_convertible<Array, Array>::value);
			// static_assert((std::is_convertible<const Array, const Array>::value), "");
			// static_assert((std::is_convertible<Array&, Array>::value), "");
			// static_assert((std::is_convertible<Array, Array&>::value), "");

			// std::is_convertible is calculated by checking to see if an imaginary function definition is well formed :
			// To test() { return std::declval<From>(); }

			system("pause");
		}
	}


	void private_destructors_and_std_is_constructible()
	{
		/*
			Private destructors and std::is_constructible
			
			Previous versions of the compiler ignore whether a destructor was private when decided the result of std::is_constructible.
			It now considers them. In the following example, the static asserts pass in earlier versions of Visual Studio
			but fail in Visual Studio 2017 Update Version 15.3:
		*/
		{
			class PrivateDtor
			{
				PrivateDtor(int) { return; }
			private:
				~PrivateDtor() { return; }
			};

			// This assertion used to succeed. It now correctly fails.
			// static_assert(std::is_constructible<PrivateDtor, int>::value); // C2607

			// Private destructors cause a type to non-constructible.std::is_constructible is calculated as if the following declaration were written :

			// template<typename T, typename Args>
			// T Object(std::declval<Args>());

			// This call implies a destructor call.

			system("pause");
		}
	}


	// for Ambiguous overload resolution example
	namespace N {
		template<class T>
		void fn(T&, T&) { return; }

		template<class T>
		void fn() { return; }
	}

	template<class T>
	void fn(T&, T&) { return; }

	struct Y {};


	void ambiguous_overload_resolution()
	{
		/*
			Ambiguous overload resolution

			Previous versions of the compiler sometimes failed to detect ambiguity
			when it found multiple candidates via both using declarations and argument dependent lookups.
			This can lead to wrong overload being chosen and unexpected runtime behavior.
			In the following example,
			Visual Studio 2017 Update Version 15.3 correctly raises C2668 'fn': ambiguous call to overloaded function:
		*/
		{
			using N::fn;

			Y s1, s2;
			// fn(s1, s2); // C2668

			// To fix the code, remove the using N::f statement if you intended to call ::f().
			N::fn(s1, s2);

			system("pause");
		}
	}

	// for local function declarations and argument dependent lookup example
	struct H {};
	void lf(H, int) { return; }

	void local_function_declarations_and_argument_dependent_lookup()
	{
		/*
			local function declarations and argument dependent lookup
			
			Local function declarations hide the function declaration in the enclosing scope
			and disable argument dependent lookup.
			However, previous versions of the Visual C++ compiler performed argument dependent lookup in this case,
			potentially leading to the wrong overload being chosen and unexpected runtime behavior.
			Typically, the error is due to an incorrect signature of the local function declaration.
			In the following example,
			Visual Studio 2017 Update Version 15.3 correctly raises C2660 'lf': function does not take 2 arguments:
		*/
		{
			void lf(H); // C2660 'lf': function does not take 2 arguments:
					    // or void f(S, int);
			H h;
			// lf(h, 0);

			// To fix the problem, either change the lf(H) signature or remove it.

			system("pause");
		}
	}


	void order_of_initialization_in_initializer_lists()
	{
		/*
			order of initialization in initializer lists
		
			Class members are initialized in the order they are declared, not the order they appear in initializer lists.
			Previous versions of the compiler did not warn when the order of the initializer list differed from the order of declaration.
			This could lead to undefined runtime behavior if the intialization of one member depended on another member in the list already being initialized.
			In the following example,
			Visual Studio 2017 Update Version 15.3 (with /Wall or /WX) raises
				warning C5038: data member 'A::y' will be initialized after data member 'A::x':
		*/
		{
			struct A
			{
				A(int a) : y(a), x(y) {} // Initialized in reverse, y reused
				int x;
				int y;
			};

			// To fix the problem arrange the intializer list to have the same order as the declarations.
			// A similar warning is raised when one or both initializers refer to base class members.

			// Note that the warning is off - by - default and only affects code compiled with /Wall or /WX.

			system("pause");
		}
	}


	void Test()
	{
		calls_to_deleted_member_templates();

		pre_condition_checks_for_type_traits();

		new_compiler_warning_and_runtime_checks_on_native_to_managed_marshaling();

		out_of_line_definition_of_a_template_member_function();

		attempting_to_take_the_address_of_this_pointer();

		conversion_to_an_inaccessible_base_class();

		default_arguments_are_not_allowed_on_out_of_line_definitions_of_member_functions();

		use_of_offsetof_with_compound_member_designator();

		using_offsetof_with_static_data_member_or_member_function();

		new_warning_on_declspec_attributes();

		decltype_and_calls_to_deleted_destructors();

		uninitialized_const_variables();

		empty_declarations();

		std_is_convertible_for_array_types();

		private_destructors_and_std_is_constructible();

		ambiguous_overload_resolution();

		local_function_declarations_and_argument_dependent_lookup();

		order_of_initialization_in_initializer_lists();
	}
}