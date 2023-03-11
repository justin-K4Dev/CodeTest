#include "stdafx.h"



namespace BugFixes
{

	void copy_list_initialization()
	{
		/*
			Copy-list-initialization

			The following two examples compile in Visual Studio 2015 but not in Visual Studio 2017.
		*/
		{
			struct A
			{
				explicit A(int) {}
				A(double) {}
			};

			// A a1 = { 1 }; // error C3445: copy-list-initialization of 'A' cannot use an explicit constructor
			// const A& a2 = { 1 }; // error C2440: 'initializing': cannot convert from 'int' to 'const A &'

			// To correct the error, use direct initialization:
			A a1{ 1 };
			const A& a2{ 1 };

			system("pause");
		}
		/*
			In Visual Studio 2015, the compiler erroneously treated copy-list-initialization in the same way as regular copy-initialization;
			it considered only converting constructors for overload resolution.
			In the following example,
			Visual Studio 2015 chooses MyInt(23) but Visual Studio 2017 correctly raises the error.
		*/
		{
			// From http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_closed.html#1228
			struct MyStore {
				explicit MyStore(int initialCapacity);
			};

			struct MyInt {
				MyInt(int i);
			};

			struct Printer {
				void operator()(MyStore const& s);
				void operator()(MyInt const& i);
			};

			// Printer p;
			// p({ 23 }); // C3066: there are multiple ways that an object of this type can be called with these arguments

			system("pause");
		}
		/*
			This example is similar to the previous one but raises a different error.
			It succeeds in Visual Studio 2015 and fails in Visual Studio 2017 with C2668.
		*/
		{
			struct A {
				explicit A(int) {}
			};

			struct B {
				B(int) {}
			};

			// void f(const A&) {}
			// void f(const B&) {}

			// f({ 1 }); // error C2668: 'f': ambiguous call to overloaded function

			system("pause");
		}
	}


	void deprecated_typedefs()
	{
		/*
			Deprecated typedefs

			Visual Studio 2017 now issues the correct warning for deprecated typedefs that are declared in a class or struct.
			The following example compiles without warnings in Visual Studio 2015 but produces C4996 in Visual Studio 2017.
		*/
		{
			struct A
			{
				// also for __declspec(deprecated) 
				[[deprecated]] typedef int inttype;
			};

			//A::inttype a = 0; // C4996 'A::inttype': was declared deprecated

			system("pause");
		}
	}


	// constexpr keyword example
	template<int N>
	struct array
	{
		constexpr int size() const { return N; }
	};

	void constexpr_keyword()
	{
		/*
			constexpr keyword

			Visual Studio 2017 correctly raises an error
			when the left-hand operand of a conditionally evaluating operation is not valid in a constexpr context.
			he following code compiles in Visual Studio 2015 but not in Visual Studio 2017
			(C3615 constexpr function 'f' cannot result in a constant expression):
		*/
		{
			struct Object
			{
				constexpr bool f(const array<1> &arr)
				{
					return arr.size() == 10 || arr.size() == 11; // C3615

					// To correct the error, either declare the array::size() function as constexpr
					// or remove the constexpr qualifier from f.
				}
			};

			system("pause");
		}
	}


	void class_types_passed_to_variadic_functions()
	{
		/*
			Class types passed to variadic functions

			In Visual Studio 2017, classes or structs that are passed to a variadic function such as printf must be trivially copyable.
			When passing such objects, the compiler simply makes a bitwise copy and does not call the constructor or destructor.
		*/
		{
			struct S
			{
				S(int i) : i(i) {}
				S(const S& other) : i(other.i) {}

				operator int() { return i; }

			private:
				int i;
			} s(0);

			// printf("%i\n", s); // warning C4840 : non-portable use of class 'main::S'
									// as an argument to a variadic function


			// std::atomic<int> i(0);
			// printf("%i\n", i); // error C4839: non-standard use of class 'std::atomic<int>'
									// as an argument to a variadic function
									// note: the constructor and destructor will not be called; 
									// a bitwise copy of the class will be passed as the argument
									// error C2280: 'std::atomic<int>::atomic(const std::atomic<int> &)':
									// attempting to reference a deleted function

			// To correct the error, you can call a member function that returns a trivially copyable type				
			std::atomic<int> i(0);
			printf("%i\n", i.load());

			// or else perform a static cast to convert the object before passing it:
			printf("%i\n", static_cast<int>(s));

			// For strings built and managed using CStringW,
			// the provided operator LPCWSTR() should be used to cast a CStringW object to
			// the C pointer expected by the format string.
			// CStringW str1;
			// CStringW str2;
			// str1.Format(L"%s", static_cast<LPCWSTR>(str2));

			system("pause");
		}
	}


	void cv_qualifiers_in_class_construction()
	{
		/*
			cv-qualifiers in class construction

			In Visual Studio 2015, the compiler sometimes incorrectly ignores the cv-qualifier
			when generating a class object via a constructor call.
			This can potentially cause a crash or unexpected runtime behavior.

			The following example compiles in Visual Studio 2015 but raises a compiler error in Visual Studio 2017:
		*/
		{
			struct B
			{
				int v;
				B(int i)
				{
					v = i;
				}
				operator int() const // declare operator int() as const.
				{
					return v;
				}
			};

			int i = (const B)0; // error C2440
			// To correct the error, declare operator int() as const.

			system("pause");
		}
	}


	// for Access checking on qualified names in templates example
	template <class T> class S
	{
		typedef typename T type;
	};

	template <class T, std::enable_if<std::is_integral<typename S<T>::type>::value, T>* = 0>
	bool f(T x) { return true; }

	void access_checking_on_qualified_names_in_templates()
	{
		/*
			Access checking on qualified names in templates

			Previous versions of the compiler did not perform access checking on qualified names in some template contexts.
			This can interfere with expected SFINAE behavior where the substitution is expected to fail due to the inaccessibility of a name.
			This could have potentially caused a crash
			or unexpected behavior at runtime due to the compiler incorrectly calling the wrong overload of the operator.
			In Visual Studio 2017, a compiler error is raised.
			The specific error might vary but typically it is "C2672 no matching overloaded function found".

			The following code compiles in Visual Studio 2015 but raises an error in Visual Studio 2017:
		*/
		{
			// f(10); // C2672: No matching overloaded function found.

			system("pause");
		}
	}


	// Missing template argument lists example
	template <class T> class ListNode;
	template <class T> using ListNodeMember = ListNode<T> T::*;
	// template <class T, ListNodeMember M> class ListHead; // C2955: 'ListNodeMember': use of alias 
	// template requires template argument list
	template <class T, ListNodeMember<T> M> class ListHead;

	void missing_template_argument_lists()
	{
		/*
			Missing template argument lists

			In Visual Studio 2015 and earlier, the compiler did not diagnose missing template argument lists
			when the template appeared in a template parameter list
			(for example as part of a default template argument or a non-type template parameter).
			This can result in unpredictable behavior, including compiler crashes or unexpected runtime behavior.

			The following code compiles in Visual Studio 2015 but produces an error in Visual Studio 2017.
		*/
		{
			system("pause");
		}
	}


	// Expression-SFINAE example
	template <class T, class ReturnT, class... ArgsT>
	class IsCallable
	{
	public:
		struct BadType {};

		template <class U>
		// static decltype(std::declval<T>()(std::declval<ArgsT>()...)) Test(int) // C2064. Should be declval<U>
		static decltype(std::declval<U>()(std::declval<ArgsT>()...)) Test(int)
		{
			return value;
		}

		template <class U>
		static BadType Test(...)
		{
			return badType;
		}

		BadType badType;
		static constexpr bool value = std::is_convertible<decltype(Test<T>(0)), ReturnT>::value;
	};

	void expression_sfinae()
	{
		/*
			Expression-SFINAE

			To support expression-SFINAE, the compiler now parses decltype arguments
			when the templates are declared rather than instantiated.
			Consequently, if a non-dependent specialization is found in the decltype argument,
			it will not be deferred to instantiation-time and will be processed immediately
			and any resulting errors will be diagnosed at that time.
				
			The following example shows such a compiler error that is raised at the point of declaration:
		*/
		{
			constexpr bool test1 = IsCallable<int(), int>::value;
			static_assert(test1, "PASS1");
			constexpr bool test2 = !IsCallable<int*, int>::value;
			static_assert(test2, "PASS2");

			system("pause");
		}
	}


	// Classes declared in anonymous namespaces example
	/*
		namespace
		{
			struct __declspec(dllexport) S1
			{
				virtual void f() {} // C2201 "error C2201: 'const anonymous namespace'::S1::vftable'': must have external linkage in order to be exported/imported."
			};
		}
	*/

	void classes_declared_in_anonymous_namespaces()
	{
		/*
			Classes declared in anonymous namespaces

			According to the C++ standard, a class declared inside an anonymous namespace has internal linkage,
			and therefore cannot be exported.
			In Visual Studio 2015 and earlier, this rule was not enforced.
			In Visual Studio 2017 the rule is partially enforced.

			The following example raises this error in Visual Studio 2017:
				"error C2201: 'const anonymous namespace'::S1::vftable'': must have external linkage in order to be exported/imported."
		*/
		{
			system("pause");
		}
	}


	void Test()
	{
		copy_list_initialization();

		deprecated_typedefs();

		constexpr_keyword();

		class_types_passed_to_variadic_functions();

		cv_qualifiers_in_class_construction();

		access_checking_on_qualified_names_in_templates();

		missing_template_argument_lists();

		expression_sfinae();

		classes_declared_in_anonymous_namespaces();
	}
}