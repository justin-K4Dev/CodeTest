#pragma once

#include "ObjectAllocator.h"

namespace Memory
{
	template <class T>
	class STLMemoryCountingAllocator : public ObjectAllocator<STLMemoryCountingAllocator<T>>
	{
	public:
		// type definitions
		typedef T value_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T &reference;
		typedef const T &const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;


		// rebind allocator to type U
		template <class U> struct rebind
		{
			typedef STLMemoryCountingAllocator<U> other;
		};

		pointer address(reference value) const
		{
			return &value;
		}
		const_pointer address(const_reference value) const
		{
			return &value;
		}

		STLMemoryCountingAllocator() : base() {}
		STLMemoryCountingAllocator(const STLMemoryCountingAllocator&) : base() {}
		template <typename U>
		STLMemoryCountingAllocator(const STLMemoryCountingAllocator<U>&) : base() {}
		~STLMemoryCountingAllocator() {}

		// return maximum number of elements that can be allocated
		size_type max_size() const throw()
		{
			return base.max_size();
		}

		pointer allocate(size_type num, const void * p = 0)
		{
			pointer ptr = base.allocate(num, p);

			GetMemoryCounter().NotifyAllocatedMemoryInfo(ptr, num * sizeof(T), typeid(T).name(), __FILE__, __LINE__);

			return ptr;
		}

		void construct(pointer p, const T &value)
		{
			return base.construct(p, value);
		}

		// destroy elements of initialized storage p
		void destroy(pointer p)
		{
			base.destroy(p);
		}

		// deallocate storage p of deleted elements
		void deallocate(pointer p, size_type num)
		{
			GetMemoryCounter().NotifyDeallocatedMemoryInfo(p, num * sizeof(T));
			base.deallocate(p, num);
		}

		std::allocator<T> base;
	};

	// for our purposes, we don't want to distinguish between allocators.
	template <class T1, class T2>
	bool operator==(const STLMemoryCountingAllocator<T1> &, const T2 &) throw()
	{
		return true;
	}

	template <class T1, class T2>
	bool operator!=(const STLMemoryCountingAllocator<T1> &, const T2 &) throw()
	{
		return false;
	}
}