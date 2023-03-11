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
#include <concurrent_unordered_map.h>
#include <ppl.h>



///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ConcurrentUnorderedMap.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-21-2012 10:55:12
///////////////////////////////////////////////////////////////////////////////

void TestPPL_ConcurrentUnorderedMap()
{
	/*
		concurrent_unordered_map Class
		
		The HYPERLINK "file:///C:\\Users\\thompet\\AppData\\Local\\Temp\\DxEditor\\DduePreview\\Default\\798d7037-df37-4310-858b-6f590bbf6ebf\\HTM\\html\\a217b4ac-af2b-4d41-94eb-09a75ee28622"
		concurrency::concurrent_unordered_map class is an associative container class that,
		just like the std::unordered_map class, controls a varying-length sequence of elements of type std::pair<const Key, Ty>.
		
		Think of an unordered map as a dictionary that you can add a key and value pair to or look up a value by key.
		This class is useful when you have multiple threads or tasks that have to concurrently access a shared container,
		insert into it, or update it.

		The following example shows the basic structure for using concurrent_unordered_map.
		This example inserts character keys in the range ['a', 'i'].
		Because the order of operations is undetermined, the final value for each key is also undetermined.
		However, it is safe to perform the insertions in parallel.

		Differences Between concurrent_unordered_map and unordered_map
		
		The concurrent_unordered_map class closely resembles the unordered_map class.
		The following points illustrate where concurrent_unordered_map differs from unordered_map:

			* The erase, bucket, bucket_count, and bucket_size methods are named unsafe_erase, unsafe_bucket, unsafe_bucket_count,
			  and unsafe_bucket_size, respectively.
		
			* The unsafe_ naming convention indicates that these methods are not concurrency-safe.
			  For more information about concurrency safety, see Concurrency-Safe Operations.

			* Insert operations do not invalidate existing pointers or iterators,
			  nor do they change the order of items that already exist in the map.
			  Insert and traverse operations can occur concurrently.

			* concurrent_unordered_map supports forward iteration only.

			* Insertion does not invalidate or update the iterators that are returned by equal_range.
			  Insertion can append unequal items to the end of the range.
			  The begin iterator points to an equal item.

		To help avoid deadlock, no method of concurrent_unordered_map holds a lock when it calls the memory allocator,
		hash functions, or other user-defined code.
		Also, you must ensure that the hash function always evaluates equal keys to the same value.
		The best hash functions distribute keys uniformly across the hash code space.


		Concurrency-Safe Operations
		
		The concurrent_unordered_map class enables concurrency-safe insert and element-access operations.
		Insert operations do not invalidate existing pointers or iterators.
		Iterator access and traversal operations are also concurrency-safe.
		The following table shows the commonly used concurrent_unordered_map methods and operators that are concurrency-safe.

			at		count			find			key_eq
			begin	empty			get_allocator	max_size
			cbegin	end				hash_function	operator[]
			cend	equal_range		insert			size

		Although the count method can be called safely from concurrently running threads,
		different threads can receive different results if a new value is simultaneously inserted into the container.

		The following table shows the commonly used methods and operators that are not concurrency-safe.

			clear		max_load_factor		rehash
			load_factor	operator=			swap
		
		In addition to these methods, any method that begins with unsafe_ is also not concurrency-safe.
	*/
	{
		Concurrency::concurrent_unordered_map<char, int> map;

		Concurrency::parallel_for(0, 1000, [&map](int i) {
			char key = 'a' + (i % 9);	// Geneate a key in the range [a,i].
			int value = i;	// Set the value to i.
			map.insert(std::make_pair(key, value)); // thread safe
		});

		// Print the elements in the map.
		std::for_each(begin(map), end(map), [](const std::pair<char, int>& pr) {
			std::wcout << L"[" << pr.first << L", " << pr.second << L"] ";
		});
	}


	/*
		concurrent_unordered_multimap Class
	
		The concurrency::concurrent_unordered_multimap class closely resembles the concurrent_unordered_map class except
		that it allows for multiple values to map to the same key.
		It also differs from concurrent_unordered_map in the following ways:

			* The concurrent_unordered_multimap::insert method returns an iterator instead of std::pair<iterator, bool>.

			* The concurrent_unordered_multimap class does not provide operator[] nor the at method.

		The following example shows the basic structure for using concurrent_unordered_multimap.
		This example inserts character keys in the range ['a', 'i'].
		concurrent_unordered_multimap enables a key to have multiple values.
	*/
	{
		Concurrency::concurrent_unordered_multimap<char, int> map;

		Concurrency::parallel_for(0, 10, [&map](int i) {
			char key = 'a' + (i % 9); // Geneate a key in the range [a,i].
			int value = i;          // Set the value to i.
			map.insert(std::make_pair(key, value));
		});

		// Print the elements in the map.
		std::for_each(begin(map), end(map), [](const std::pair<char, int>& pr) {
			std::wcout << L"[" << pr.first << L", " << pr.second << L"] ";
		});
	}

	system("pause");
}