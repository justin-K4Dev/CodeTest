#include "stdafx.h"


#include <memory>
#include <unordered_map>

namespace Alias
{
	// Type alias example
	// type alias, identical to
	// typedef std::ios_base::fmtflags flags;
	using flags = std::ios_base::fmtflags;
	// the name 'flags' now denotes a type:
	flags fl = std::ios_base::dec;

	// type alias, identical to
	// typedef void (*func)(int, int);
	using func = void(*) (int, int);
	// the name 'func' now denotes a pointer to function:
	void example(int, int) {}
	func f = example;

	// alias template
	template<class T>
	using ptr = T*;
	// the name 'ptr<T>' is now an alias for pointer to T
	ptr<int> x;

	// type alias used to hide a template parameter 
	template<class CharT>
	using mystring = std::basic_string<CharT, std::char_traits<CharT>>;
	mystring<char> str;

	// type alias can introduce a member typedef name
	template<typename T>
	struct Container { using value_type = T; };
	// which can be used in generic programming
	template<typename Container>
	void g(const Container& c) { typename Container::value_type n; }

	// type alias used to simplify the syntax of std::enable_if
	template<typename T>
	using Invoke = typename T::type;
	template<typename Condition>
	using EnableIf = Invoke<std::enable_if<Condition::value>>;
	template<typename T, typename = EnableIf<std::is_polymorphic<T>>>
	int fpoly_only(T t) { return 1; }

	struct S { virtual ~S() {} };

	void type_alias()
	{
		/*
			Type alias, alias template 

			Type alias is a name that refers to a previously defined type (similar to typedef).
			Alias template is a name that refers to a family of types.

				Syntax
				Alias declarations are declarations with the following syntax:
					using identifier attr(optional) = type-id ;
					template < template-parameter-list >
					using identifier attr(optional) = type-id ;

			template<class T>
			struct Alloc { };
			template<class T>
			using Vec = vector<T, Alloc<T>>; // type-id is vector<T, Alloc<T>>
			Vec<int> v; // Vec<int> is the same as vector<int, Alloc<int>>

			template<typename...>
			using void_t = void;
			template<typename T>
			void_t<typename T::foo> f();
			f<int>(); // error, int does not have a nested type foo

			template<class T>
			struct A;
			template<class T>
			using B = typename A<T>::U; // type-id is A<T>::U
			template<class T>
			struct A { typedef B<T> U; };
			B<short> b; // error: B<short> uses its own type via A<short>::U
		*/
		{
			// alias - object pointer
			using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;

			// alias - function pointer
			using funcPtr = void(*)(int, const std::string&);


			Container<int> c;
			g(c); // Container::value_type will be int in this function
				  // fpoly_only(c); // error: enable_if prohibits this
			S s;
			fpoly_only(s); // okay: enable_if allows this

			system("pause");
		}
	}


	void Test()
	{
		//type_alias();
	}

}// end of Using