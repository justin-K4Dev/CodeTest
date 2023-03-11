#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-21-2012 10:55:09
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <concurrent_unordered_set.h>
#include <ppl.h>



///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ConcurrentUnorderedSet.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-21-2012 10:55:12
///////////////////////////////////////////////////////////////////////////////

void TestPPL_ConcurrentUnorderedSet()
{
	/*
		concurrent_unordered_set Class

		The concurrency::concurrent_unordered_set class closely resembles the concurrent_unordered_map class except
		that it manages values instead of key and value pairs.
		The concurrent_unordered_set class does not provide operator[] nor the at method.

		The following example shows the basic structure for using concurrent_unordered_set.
		This example inserts character values in the range ['a', 'i'].
		It is safe to perform the insertions in parallel.
	*/

	{
		//
		// Insert a number of items into the set in parallel.

		Concurrency::concurrent_unordered_set<char> set;

		Concurrency::parallel_for(0, 10000, [&set](int i) {
			set.insert('a' + (i % 9)); // Geneate a value in the range [a,i].
		});

		// Print the elements in the set.
		std::for_each(begin(set), end(set), [](char c) {
			std::wcout << L"[" << c << L"] ";
		});
	}

	/*
		concurrent_unordered_multiset Class

		The concurrency::concurrent_unordered_multiset class closely resembles the concurrent_unordered_set class except
		that it allows for duplicate values.
		It also differs from concurrent_unordered_set in the following ways:

			* The concurrent_unordered_multiset::insert method returns an iterator instead of std::pair<iterator, bool>.

			* The concurrent_unordered_multiset class does not provide operator[] nor the at method.

		The following example shows the basic structure for using concurrent_unordered_multiset.
		This example inserts character values in the range ['a', 'i'].
		concurrent_unordered_multiset enables a value to occur multiple times.
	*/
	{
		//
		// Insert a number of items into the set in parallel.

		Concurrency::concurrent_unordered_multiset<char> set;

		Concurrency::parallel_for(0, 40, [&set](int i) {
			set.insert('a' + (i % 9)); // Geneate a value in the range [a,i].
		});

		// Print the elements in the set.
		std::for_each(begin(set), end(set), [](char c) {
			std::wcout << L"[" << c << L"] ";
		});
	}

	system("pause");
}