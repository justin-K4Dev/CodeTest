#include "stdafx.h"



namespace CPP17
{
	template<typename... Args>
	auto RightFold(Args... args)
	{
		return (args - ...);
	}

	template<typename... Args>
	auto LeftFold(Args... args)
	{
		return (... - args);
	}

	template<typename... Args>
	auto RightFoldWithInit(Args... args)
	{
		return (args - ... - 1);
	}

	template<typename... Args>
	auto LeftFoldWithInit(Args... args)
	{
		return (1 - ... - args);
	}

	void fold_expression()
	{
		std::cout << RightFold(1, 2, 3, 4) << std::endl;            // (1-(2-(3-4)))    // Unary Right simple examples
		std::cout << LeftFold(1, 2, 3, 4) << std::endl;             // (((1-2)-3)-4)    // Unary Left simple examples
		std::cout << RightFoldWithInit(2, 3, 4) << std::endl;       // (2-(3-(4-"1")))  // Binary Right simple examples
		std::cout << LeftFoldWithInit(2, 3, 4) << std::endl;        // ((("1"-2)-3)-4)  // Binary Left simple examples

		std::cout << std::endl;
	}


	void terse_static_assert()
	{
		/*
			Terse static_assert

			Terse static_assert (available with /std:c++latest) In C++17 the message parameter for static_assert is optional.
			For more information, see Extending static_assert, v2.

				Syntax
				• static_assert ( bool_constexpr )					(since C++17)

			URL : http://en.cppreference.com/w/cpp/language/static_assert
		*/
		{
		}
	}


	void fallthrough_attribute()
	{
		/*
			[[fallthrough]] attribute (available with /std:c++latest)

			[[fallthrough]] attribute (available with /std:c++latest) The [[fallthrough]] attribute can be used in the context of switch statements
			as a hint to the compiler that the fall-through behavior is intended.
			This prevents the compiler from issuing warnings in such cases.
			For more information, see Wording for [[fallthrough]] attribute.

				- A null statement marked with the attribute­token fallthrough​, is a fallthrough statement.
					The fallthrough attribute­token shall appear at most once in each attribute­list, with no
					attribute­argument­clause.
				- A fallthrough statement may appear within an enclosing switch statement,
					on some path of execution immediately between a preceding statement and a succeeding case­labeled statement.
				- [Note: If an implementation would have otherwise issued a warning about implicit fall through on a
					path of execution immediately after a fallthrough statement, it is encouraged not to. ­­ end note]

			URL : http://en.cppreference.com/w/cpp/language/attributes
		*/
		{
		}
	}

	void generalized_range_based_for_loops()
	{
		/*
			Generalized range-based for loops (no compiler switch required)

			Generalized range-based for loops (no compiler switch required) Range-based for loops no longer require
			that begin() and end() return objects of the same type.
			This enables end() to return a sentinel object such as used by ranges as defined in the Ranges-V3 proposal.
			For more information, see Generalizing the Range-Based For Loop and the range-v3 library on GitHub.

			URL : https://github.com/ericniebler/range-v3
			      https://github.com/Microsoft/Range-V3-VS2015
		*/
		{
		}

		// Usable std::any Type
		{
			std::any v;
			v = 10;
		}
	}


	template <class T, class ... Candidates>
	constexpr bool is_total_same()
	{
		bool pairs[] = { std::is_same<T, Candidates>::value... };
		for (bool p : pairs) {
			if (!p) {
				return false;
			}
		}
		return true;
	}

	template <class T, class ... Candidates>
	constexpr bool is_any_same()
	{
		bool pairs[] = { std::is_same<T, Candidates>::value... };
		for (bool p : pairs) {
			if (p) { 
				return true;
			}
		}
		return false;
	}

	void is_same_variadic()
	{
		std::cout << is_total_same<int, int>()
			      << ", " << is_total_same<double, double, int>()
				  << ", " << is_any_same<int, short, float, double, int>()
		<< std::endl;

		system("pause");

		/*
		output:
			1, 0, 1
		*/
	}


	namespace details
	{
		template <typename Tuple, typename Mapping>
		struct return_type;

		template <template <typename ...> typename Tuple, typename ... Types, typename Mapping>
		struct return_type<Tuple<Types...>, Mapping>
		{
			using type = Tuple<std::invoke_result_t<Mapping, Types>...>;
		};
		template <template <typename, std::size_t> typename Array, 
				  typename T, std::size_t Size, typename Mapping>
		struct return_type<Array<T, Size>, Mapping>
		{
			using type = Array<std::invoke_result_t<Mapping, T>, Size>;
		};

		template <typename Tuple, typename Mapping>
		using return_type_t = typename return_type<Tuple, Mapping>::type;

		template <typename Tuple, typename Mapping, std::size_t ... Indices>
		return_type_t<std::decay_t<Tuple>, 
					  std::decay_t<Mapping>> perform_mapping(Tuple&& tup, 
															 Mapping&& mapping, 
															 std::index_sequence<Indices...>)
		{
			return {mapping(std::get<Indices>(std::forward<Tuple>(tup)))...};
		}
	}

	template <typename Tuple, typename Mapping, 
			  std::size_t Size = std::tuple_size<std::decay_t<Tuple>>::value>
	auto perform_mapping(Tuple&& tup, Mapping&& mapping)
	{
		return details::perform_mapping(std::forward<Tuple>(tup), 
										std::forward<Mapping>(mapping), std::make_index_sequence<Size>{});
	}


	void tuple_to_function()
	{
		auto mapper = [](int x) {return x * 2; };
		std::array<int, 3> a{ 1, 2, 3 };
		auto b = perform_mapping(a, mapper);

		std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';


		auto tuple = std::make_tuple(1, std::string{ "a" });
		auto self_adder = [](const auto& x) {return x + x; };
		auto another_tuple = perform_mapping(tuple, self_adder);
		std::cout << std::get<0>(another_tuple) << ' ' << std::get<1>(another_tuple) << '\n';


		system("pause");

		/*
		output:
			2 4 6
			2 aa
		*/
	}


	template < std::size_t... Ns, typename... Ts >
	auto tail_impl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
	{
		return  std::make_tuple(std::get<Ns + 1u>(t)...);
	}

	template <class F, class... R >
	std::tuple<R...> tail(std::tuple<F, R...> t)
	{
		return  tail_impl(std::make_index_sequence<sizeof...(R)>(), t);
	}

	template<class X>
	constexpr bool check_for_type(std::tuple<> t)
	{
		return false;
	}

	template<class X, class F, class... R>
	constexpr bool check_for_type(std::tuple<F, R...> t)
	{
		if constexpr(std::is_same<F, X>::value) {
			return true;
		}
		return check_for_type<X>(tail(t));
	}

	void tuple_type_check()
	{
		auto t2 = std::make_tuple(4, "qw", 6.5);

		std::cout << check_for_type<float>(t2) << std::endl;

		system("pause");

		/*
		output:
		*/
	}


	void Test()
	{
		//fold_expression();

		//tuple_type_check();

		//tuple_to_function();

		//is_same_variadic();

		//terse_static_assert();

		//fallthrough_attribute();

		//generalized_range_based_for_loops();
	}
}