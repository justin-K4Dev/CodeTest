#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-21-2012 10:54:41
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <concurrent_queue.h>
#include <concurrent_vector.h>
#include <ppl.h>


///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ConcurrentVector.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-21-2012 10:54:44
///////////////////////////////////////////////////////////////////////////////
void TestPPL_ConcurrentVector()
{
	/*
		concurrent_vector Class

		The concurrency::concurrent_vector class is a sequence container class that,
		just like the std::vector class, lets you randomly access its elements.
		
		The concurrent_vector class enables concurrency-safe append and element access operations.
		Append operations do not invalidate existing pointers or iterators.
		
		Iterator access and traversal operations are also concurrency-safe.

		Differences Between concurrent_vector and vector
		
		The concurrent_vector class closely resembles the vector class.
		The complexity of append, element access,
		and iterator access operations on a concurrent_vector object are the same as for a vector object.
		
		The following points illustrate where concurrent_vector differs from vector:

			* Append, element access, iterator access,
			  and iterator traversal operations on a concurrent_vector object are concurrency-safe.

			* You can add elements only to the end of a concurrent_vector object.
			  The concurrent_vector class does not provide the insert method.

			* A concurrent_vector object does not use move semantics when you append to it.

			* The concurrent_vector class does not provide the erase or pop_back methods.
			  As with vector, use the clear method to remove all elements from a concurrent_vector object.

			* The concurrent_vector class does not store its elements contiguously in memory.
			  Therefore, you cannot use the concurrent_vector class in all the ways that you can use an array.
			  For example, for a variable named v of type concurrent_vector,
			  the expression &v[0]+2 produces undefined behavior.

			* The concurrent_vector class defines the grow_by and grow_to_at_least methods.
			  These methods resemble the resize method, except that they are concurrency-safe.

			* A concurrent_vector object does not relocate its elements when you append to it or resize it.
			  This enables existing pointers and iterators to remain valid during concurrent operations.

			* The runtime does not define a specialized version of concurrent_vector for type bool.

		Concurrency-Safe Operations
	
		All methods that append to or increase the size of a concurrent_vector object,
		or access an element in a concurrent_vector object, are concurrency-safe.
		
		The exception to this rule is the resize method.

		The following table shows the common concurrent_vector methods
		and operators that are concurrency-safe.

			at			end					operator[]
			begin		front				push_back
			back		grow_by				rbegin
			capacity	grow_to_at_least	rend
			empty		max_size			size

		Operations that the runtime provides for compatibility with the STL,
		for example, reserve, are not concurrency-safe.
		The following table shows the common methods and operators that are not concurrency-safe.

			assign		reserve
			clear		resize
			operator=	shrink_to_fit

	*/
	{
		// Create a concurrent_vector object that contains a few
	    // initial elements.

	    Concurrency::concurrent_vector<int> v;
	    v.push_back(2);
	    v.push_back(3);
	    v.push_back(4);

	    // Perform two tasks in parallel.
	    // The first task appends additional elements to the concurrent_vector object.
	    // The second task computes the sum of all elements in the same object.

		Concurrency::parallel_invoke( [&v] {
									           for(int i = 0; i < 10000; ++i)
											   {
												   v.push_back(i);
											   }
                                           },
									  [&v] {
											   Concurrency::combinable<int> sums;
											   for(auto i = v.begin(); i != v.end(); ++i) 
											   {
							 					   sums.local() += *i;
											   }     
								 
											   std::wcout << L"sum = " << sums.combine(std::plus<int>()) << std::endl;
										  }
	                                );

		_getch();
	}
}