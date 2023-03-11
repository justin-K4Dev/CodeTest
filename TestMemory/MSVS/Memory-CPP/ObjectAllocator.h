#pragma once

#include "MemoryAllocator.h"
#include "MemoryCounter.h"
#include "Singleton.hpp"

namespace Memory
{
	template <class T>
	class ObjectAllocator : public MemoryAllocator<ObjectAllocator<T>>
	{
	public:
		static void* Allocate(size_t count, const char* file = "", int line = 0);
		static void Deallocate(void* ptr);
		static void Deallocate(void* ptr, size_t size);
	};

	template<class T>
	void* ObjectAllocator<T>::Allocate(size_t count, const char* file, int line) throw(std::bad_alloc)
	{
		void* ptr = malloc(count);
		if (nullptr == ptr) {
			return nullptr;
		}

		GetMemoryCounter().NotifyAllocatedMemoryInfo(ptr, count, typeid(T).name(), file, line);
		return ptr;
	}

	template<class T>
	void ObjectAllocator<T>::Deallocate(void* ptr) throw(std::bad_alloc)
	{
		GetMemoryCounter().NotifyDeallocatedMemoryInfo(ptr, 0);
		free(ptr);
	}

	template<class T>
	void ObjectAllocator<T>::Deallocate(void* ptr, size_t size) throw(std::bad_alloc)
	{
		GetMemoryCounter().NotifyDeallocatedMemoryInfo(ptr, size);
		free(ptr);
	}

}