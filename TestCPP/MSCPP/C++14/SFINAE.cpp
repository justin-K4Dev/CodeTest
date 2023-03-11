#include "stdafx.h"


#include <type_traits>
#include <array>

#include <map>


namespace SFINAE
{
	//Substitution Failure Is Not An Error

	template<typename T>
	class zero_init
	{
	protected:
		T val;
	public:
		zero_init() : val(static_cast<T>(0)) { }
		zero_init(T val) : val(val) { }
		operator T&() { return val; }
		operator T() const { return val; }
	};

	void implicit_conversions()
	{
		zero_init<int> i; assert(i == 0);
		i = 7; assert(i == 7);
		//switch (i) {}     //error until C++14 (more than one conversion function)
		//OK since C++14 (both functions convert to the same type int)
		//switch (i + 0) {} //always okay (implicit conversion)
	}


	template <typename T, typename U>
	struct decay_equiv : std::is_same<typename std::decay<T>::type, U>::type
	{ };

	void decay_use()
	{
		//기본적으로 std::decay<T>는 T 타입 본연의 형식으로 strip-down 시키는 역할
		//std::decay는 Implicit conversions 중 Value transformations 역할을 수행

		std::cout	<< std::boolalpha
					<< decay_equiv<int, int>::value << '\n'
					<< decay_equiv<int&, int>::value << '\n'
					<< decay_equiv<int&&, int>::value << '\n'
					<< decay_equiv<const int&, int>::value << '\n'
					<< decay_equiv<int[2], int*>::value << '\n'
					<< decay_equiv<int(int), int(*)(int)>::value << '\n';

		system("pause");

		/*
		output:
			true
			true
			true
			true
			true
			true
		*/
	}


	class car;
	class bar;

	template<class T>
	struct check
	{
		template<class Q = T>
		typename std::enable_if<std::is_same<Q, bar>::value, bool>::type test()
		{
			return true;
		}

		template<class Q = T>
		typename std::enable_if<!std::is_same<Q, bar>::value, bool>::type test()
		{
			return false;
		}
	};

	void enable_if_use_1()
	{
		check<car> check_car;
		check<bar> check_bar;

		if (!check_car.test() && check_bar.test()) {
			std::cout << "It works!" << std::endl;
		}

		system("pause");

		/*
		output:
			It works!
		*/
	}



	template < typename... > struct are_derived_from;

	template < typename BASE, typename T >
	struct are_derived_from< BASE, T > : std::is_base_of< BASE, typename std::decay<T>::type >
	{};

	template < typename BASE, typename FIRST, typename... REST >
	struct are_derived_from< BASE, FIRST, REST... > : std::conditional< std::is_base_of< BASE, typename std::decay<FIRST>::type >::value
										                             && are_derived_from<BASE, REST... >::value
													                  , std::true_type
		                                                              , std::false_type >::type
	{};

	struct base { /* ... */ };

	template < typename FIRST, typename... REST >
	typename std::enable_if< are_derived_from<base, FIRST, REST... >::value >::type foo(FIRST*, REST*...)
	{
		std::cout << "all are pointers to types derived from base\n";
	}

	template < typename FIRST, typename... REST >
	typename std::enable_if< are_derived_from<base, FIRST, REST... >::value >::type foo(FIRST&&, REST&&...)
	{
		std::cout << "all are references to types derived from base\n";
	}

	void enable_if_use_2()
	{
		struct A : base
		{} a;
		struct B : base
		{} b;
		struct C : base
		{} c;
		struct D : base
		{} d;

		foo(&a, &b, &c, &d);
		foo(a, b, B(), c, d, D());


		system("pause");
		/*
		output:
			all are pointers to types derived from base
			all are references to types derived from base
		*/
	}


	template <typename Ref, typename T1, typename... TN>
	struct all_match;

	template <typename Ref, typename T>
	struct all_match<Ref, T>
	{
		static constexpr bool value = std::is_same<T, Ref>::value;
	};

	template <typename Ref, typename T1, typename... TN>
	struct all_match
	{
		static constexpr bool value = std::is_same<T1, Ref>::value && all_match<Ref, TN...>::value;
	};

	template <typename T, typename... U>
	typename std::enable_if<all_match<int, U...>::value, void>::type
	testFunction(T a, U... bs)
	{
		std::cout << "bs are integers\n";
	}

	template <typename T, typename... U>
	typename std::enable_if<all_match<char, U...>::value, void>::type
	testFunction(T a, U... bs)
	{
		std::cout << "bs are chars\n";
	}

	void enable_if_use_3()
	{
		testFunction(1.0, 3);				//ok
		testFunction(1.0, 'c', 'r', 'p');	//ok
		//testFunction(1.0, 3, 4.0f, 5);	//fail

		system("pause");

		/*
		output:
			bs are integers
			bs are chars
		*/
	}


	template <typename T, typename = int>
	struct HasX : std::false_type
	{
		bool GetValue() { return this->value; }
	};

	template <typename T>
	struct HasX <T, decltype((void)T::x, 0)> : std::true_type
	{
		bool GetValue() { return this->value; }
	};

	struct A { int x; };
	struct B { int y; };

	void true_type_use()
	{
		HasX<A> a;
		std::cout << a.GetValue() << std::endl;
		HasX<B> b;
		std::cout << b.GetValue() << std::endl;

		system("pause");
		/*
		output:
			1
			0
		*/
	}


	#define IS_MEMBER(T1, M, funcName)																																			\
	struct {																																									\
		struct isMember { bool M; };																																			\
		template<typename T>																																					\
		struct checkMember : isMember, public T																																	\
		{ };																																									\
																																												\
		enum return_t { not_member = 0, is_object = 1, is_function = 3 };																										\
																																												\
		template<typename T, typename = decltype(checkMember<T>::M)> constexpr return_t what_member() { return not_member;  }													\
		template<typename T> typename std::enable_if<std::is_member_object_pointer<decltype(&T::M)>::value, return_t>::type constexpr what_member() { return is_object; }		\
		template<typename T> typename std::enable_if<std::is_member_function_pointer<decltype(&T::M)>::value, return_t>::type constexpr what_member() { return is_function; }   \
		constexpr operator return_t() { return what_member<T1>(); }																												\
	} funcName

	struct Object
	{
		int id;
		std::string name;

		int GetID() { return id; }
	};

	//can't be in function
	IS_MEMBER(Object, id,		isIDofObject);
	IS_MEMBER(Object, name,		isNameofObject);
	IS_MEMBER(Object, GetID,	isGetIDofObject);

	//known at compile time
	enum { const_isIDofObject = (int)isIDofObject };
	static constexpr int const_isGetIDofObject = isGetIDofObject;

	void check_type()
	{
		std::cout << std::boolalpha <<	"0 - not_member, 1 - is_object, 2 - is_function \n\n" <<
										"is id member of Object = " << isIDofObject << std::endl <<
										"is name member of Object = " << isNameofObject << std::endl <<
										"is GetID() member of Object = " << isGetIDofObject << std::endl <<
		std::endl;

		system("pause");
		/*
		output:
			0 - not_member, 1 - is_object, 2 - is_function

			is id member of Object = 1
			is name member of Object = 1
			is GetID() member of Object = 2
		*/
	}


	template<int...>
	struct seq
	{ };

	template<int max, int... s>
	struct make_seq : make_seq <max - 1, max - 1, s...>
	{ };

	template<int... s>
	struct make_seq < 0, s... >
	{
		typedef seq<s...> type;
	};

	template<int max>
	using MakeSeq = typename make_seq<max>::type;

	template<int x, typename Arg>
	struct my_storage
	{
		my_storage()
		{
			std::cout << "my_storage" << std::endl;
		}
		Arg data;
	};

	template<typename Seq, typename... Args>
	struct my_helper
	{
		my_helper()
		{
			std::cout << "my_helper1" << std::endl;
		}
	};

	template<int s0, int... s, typename A0, typename... Args>
	struct my_helper<seq<s0, s...>, A0, Args...> : my_storage<s0, A0>, my_helper < seq<s...>, Args... >
	{
		my_helper()
		{
			std::cout << "my_helper2" << std::endl;
		}
	};

	template<typename... Args>
	struct my : my_helper<MakeSeq<sizeof...(Args)>, Args...>
	{
		my()
		{
			std::cout << "my" << std::endl;
		}
	};

	template<int N, typename T>
	T& get(my_storage<N, T>& f)
	{
		return f.data;
	}

	template<int N, typename T>
	T const& get(my_storage<N, T> const& f)
	{
		return f.data;
	}

	void variadic_like_tuple_1()
	{
		my<int, float, int> f;

		get<0>(f) = 7;
		get<1>(f) = 3.14f;
		get<2>(f) = 6;
		std::cout << get<0>(f) << ", " << get<1>(f) << ", " << sizeof(f) << "\n";

		system("pause");
	}


	template <typename T>
	void xtuple_size(const T& a)
	{
		std::cout << T::N << std::endl;
	}

	//tuple (primary template)
	template <typename ...Types> class xtuple;

	//empty tuple (specialization)
	template <> class xtuple<> {};

	//recursive tuple definition (partial specialization)
	template <typename T, typename ... Types>
	class xtuple<T, Types...> : private xtuple<Types ...>
	{
	public:
		xtuple() {}
		xtuple(const T& a, Types ... args) : first_(a), xtuple<Types...>(args...)
		{}

		enum { N = 1 + sizeof...(Types) };

	public:
		T first_;
	};

	//tuple_element
	template <size_t N, typename xtuple>
	struct xtuple_element;

	//type of the first element
	template <typename T, typename ... Types>
	struct xtuple_element<0, xtuple<T, Types...>>
	{
		using Type = T;
		using TupleType = xtuple<T, Types...>;
	};

	//recursive tuple_element definition
	template <size_t N, typename T, typename ... Types>
	struct xtuple_element<N, xtuple<T, Types...>> : public xtuple_element<N - 1, xtuple<Types...>>
	{};

	template <size_t N, typename ... Types>
	inline typename xtuple_element<N, xtuple<Types...>>::Type& Get(xtuple<Types...>& t)
	{
		using TupleType = xtuple_element<N, xtuple<Types...>>::TupleType;
		return ((TupleType&)t).first_;
	}

	//sequence template -> C++ 14에서는 std::index_sequence로 대체가능
	template <int... Remains>
	struct sq {};

	template <int N, int... Remains>
	struct gen_seq : gen_seq<N - 1, N - 1, Remains...> {};

	template <int... Remains>
	struct gen_seq<0, Remains...> : sq<Remains...> {};


	//pretty-print a tuple (from http://stackoverflow.com/a/6245777/273767)
	template <typename Tuple, int... Is>
	void print_tuple_impl(std::ostream& os, const Tuple& t, sq<Is...>)
	{
		using swallow = int[]; // guaranties left to right order
		(void)swallow {
			0, (void(os << (Is == 0 ? "" : ", ") << Get<Is>(t)), 0)...
		};
	}

	template <typename ... Types>
	std::ostream& operator<< (std::ostream& out, const xtuple<Types...>& t)
	{
		out << " [ ";
		print_tuple_impl(out, t, gen_seq<sizeof...(Types)>{});
		out << " ] ";

		return out;
	}

	void variadic_like_tuple_2()
	{
		{
			xtuple<int, char, double> t(1, 'a', 3.4);
			xtuple_size(t); //3
		}

		{
			xtuple<int, char, double> t(1, 'a', 3.4);

			auto c = Get<1>(t);
			std::cout << c << std::endl; //a
		}

		system("pause");
	}

	void Test()
	{
		//variadic_like_tuple_2();

		//variadic_like_tuple_1();

		//check_type();

		//true_type_use();

		//enable_if_use_3();

		//enable_if_use_2();

		//enable_if_use_1();

		//decay_use();

		//implicit_conversions();
	}

}//SFISNAE