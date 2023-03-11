#pragma once

#include "MemoryCounter.h"

void* operator new(size_t sz, const char* file, int line)
{
	void* ptr = malloc(sz);
	Memory::GetMemoryCounter().NotifyAllocatedMemoryInfo(ptr, sz, "", file, line);
	return ptr;
}

void* operator new[](size_t sz, const char* file, int line)
{
	void* ptr = malloc(sz);
	Memory::GetMemoryCounter().NotifyAllocatedMemoryInfo(ptr, sz, "", file, line);
	return ptr;
}

void operator delete(void* ptr, size_t size)
{
	Memory::GetMemoryCounter().NotifyDeallocatedMemoryInfo(ptr, size);
	free(ptr);
}

void operator delete(void* ptr, const char* file, size_t size)
{
	Memory::GetMemoryCounter().NotifyDeallocatedMemoryInfo(ptr, size);
	free(ptr);
}

void operator delete[](void* ptr, size_t size)
{
	Memory::GetMemoryCounter().NotifyDeallocatedMemoryInfo(ptr, size);
	free(ptr);
}

namespace Memory
{
	template <class TAllocator>
	class MemoryAllocator
	{
	public:
		explicit MemoryAllocator() {}
		virtual~MemoryAllocator() {}

		void* operator new(size_t sz)
		{
			return TAllocator::Allocate(sz, "", 0);
		}

		void* operator new(size_t sz, const char* file, int line)
		{
			return TAllocator::Allocate(sz, file, line);
		}

		void* operator new[](size_t sz)
		{
			return TAllocator::Allocate(sz);
		}

		void* operator new[](size_t sz, const char* file, int line)
		{
			return TAllocator::Allocate(sz, file, line);
		}

		void operator delete(void* ptr)
		{
			TAllocator::Deallocate(ptr, 0);
		}

		void operator delete(void* ptr, size_t size)
		{
			TAllocator::Deallocate(ptr, size);
		}

		void operator delete(void* ptr, const char* file, int line)
		{
			TAllocator::Deallocate(ptr, 0);
		}

		void operator delete[](void* ptr)
		{
			TAllocator::Deallocate(ptr, 0);
		}

		void operator delete[](void* ptr, size_t size)
		{
			TAllocator::Deallocate(ptr, size);
		}
	};

	#define new new(__FILE__, __LINE__)
}