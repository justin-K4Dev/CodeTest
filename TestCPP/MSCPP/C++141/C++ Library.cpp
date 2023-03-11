#include "stdafx.h"




namespace CPP_Library
{
	void standard_library_improvements()
	{
		/*
			Standard Library improvements:

			• Minor basic_string _ITERATOR_DEBUG_LEVEL != 0 diagnostics improvements.
				Tripping an IDL check in string machinery will now report the specific behavior that caused the trip.
				For example, instead of "string iterator not dereferencable" you'll get "cannot dereference string iterator
				because it is out of range (e.g. an end iterator)".

			• Performance improvement:
				made basic_string::find(char) overloads only call traits::find once.
				Previously this was implemented as a general string search for a string of length 1.

			• Performance improvement:
				basic_string::operator== now checks the string's size before comparing the strings' contents.

			• Performance improvement:
				removed control coupling in basic_string which was difficult for the compiler optimizer to analyze.
				Resolves VSO# 262848 ": reserve() does too much work".
				Note that for all short strings, calling reserve still has nonzero cost to do nothing.

			• We added <any>, <string_view>, apply(), make_from_tuple().

			• std::vector has been overhauled for correctness and performance:
				aliasing during insertion/emplacement is now correctly handled as required by the Standard,
				the strong exception guarantee is now provided when required by the Standard via move_if_noexcept() and other logic,
				and insertion/emplacement perform fewer element operations.

			• The C++ Standard Library now avoids dereferencing null fancy pointers.

			• Added <optional>, <variant>, shared_ptr::weak_type, and <cstdalign>.

			• Enabled C++14 constexpr in min/max/minmax(initializer_list) and min_element/max_element/minmax_element().

			• Improved weak_ptr::lock() performance.

			• Fixed std::promise's move assignment operator, which previously could cause code to block forever.

			• Fixed compiler errors with atomic<T *>'s implicit conversion to T *.

			• pointer_traits<Ptr> now correctly detects Ptr::rebind<U>.

			• Fixed a missing const qualifier in move_iterator's subtraction operator.

			• Fixed silent bad codegen for stateful user-defined allocators requesting propagate_on_container_copy_assignment
				and propagate_on_container_move_assignment.

			• atomic<T> now tolerates overloaded operator&().

			• To increase compiler throughput, C++ Standard Library headers now avoid including declarations
				for unnecessary compiler intrinsics.

			• Slightly improved compiler diagnostics for incorrect bind() calls.

			• Improved the performance of std::string/std::wstring's move constructors by more than 3x

			• For a complete list of STL improvment see the STL Fixes In VS 2017 RTM.
		*/
		{
		}
	}

	void open_source_library_support()
	{
		/*
			Open source library support

			Vcpkg is an open-source command line tool that greatly simplifies the process of acquiring
			and building open source C++ static libs and DLLS in Visual Studio.
			For more information, see Vcpkg updates: Static linking is now available.
		*/
		{
		}
	}

	void cpp_rest_sdk_290()
	{
		/*
			CPPRest SDK 2.9.0

			The CPPRestSDK, a cross-platform web API for C++,
			has been updated to version 2.9.0.
			For more information, see CppRestSDK 2.9.0 is available on GitHub.
		*/
	}

	void visual_cpp_runtime()
	{
		/*
			Visual C++ Runtime
			
			• New header "cfguard.h" for Control Flow Guard symbols.
		*/
		{
		}
	}


	void Test()
	{

	}

}// end of CodeManagement