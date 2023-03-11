#include "stdafx.h"
#include "Function.h"

#include <tbb/task_scheduler_init.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/scalable_allocator.h>
#include <tbb/cache_aligned_allocator.h>
#include <tbb/tick_count.h>


#ifdef DEF_TBB_MEMORY_ALLOCATOR_ON

void* operator new (size_t size) throw (...)
{
	if (size == 0)
		size = 1;

	if (void *ptr = ::scalable_malloc(size))
	{
#ifdef DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
		printf("Called ::scalable_malloc() !!! - Size:%zd\n", size);
#endif//DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
		return ptr;
	}

	throw std::bad_alloc();
}

void* operator new [](size_t size) throw (...)
{
	return operator new (size);
}

void* operator new (size_t size, const std::nothrow_t &th) throw ()
{
	if (size == 0)
		size = 1;

	if (void *ptr = ::scalable_malloc(size))
	{
#ifdef DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
		printf("Called ::scalable_malloc() !!! - Size:%zd\n", size);
#endif//DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
		return ptr;
	}

	return NULL;
}

void* operator new [](size_t size, const std::nothrow_t &th) throw ()
{
	return operator new (size, std::nothrow);
}

void operator delete (void *ptr) throw ()
{
	if (ptr != 0)
	{
		::scalable_free(ptr);
#ifdef DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
		printf("Called ::scalable_free() !!!");
#endif//DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
	}
}

void operator delete [](void *ptr) throw ()
{
	operator delete (ptr);
}

void operator delete (void *ptr, const std::nothrow_t &th) throw ()
{
	if (ptr != 0)
	{
		::scalable_free(ptr);
#ifdef DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
		printf("Called ::scalable_free() !!!");
#endif//DEF_TBB_MEMORY_ALLOCATOR_LOG_ON
	}
}

void operator delete [](void *ptr, const std::nothrow_t &th) throw ()
{
	operator delete (ptr, std::nothrow);
}

#endif//DEF_TBB_MEMORY_ALLOCATOR_ON


namespace TBB_Memory
{
	/*
		Windows* OS C/C++ Dynamic Memory Interface Replacement
		Last updated on September 6, 2016
	
		URL: https://software.intel.com/en-us/node/506098

		Release version the proxy library is tbbmalloc_proxy.dll, debug version tbbmalloc_debug_proxy.dll.

		The following dynamic memory functions are replaced:

			* Standard C library functions: malloc, calloc, realloc, free
			* Replaceable global C++ operators new and delete
			* Microsoft* C run-time library functions: _msize, _aligned_malloc, _aligned_realloc, _aligned_free, _aligned_msize
	
		To do the replacement use one of the following methods:

		Add the following header to a source code of any binary which is loaded during application startup.
			#include "tbb/tbbmalloc_proxy.h"

		Alternatively, add the following parameters to the linker options for the .exe or .dll file
		that is loaded during application startup.
	
			For 32-bit code (note the triple underscore):
				tbbmalloc_proxy.lib /INCLUDE:"___TBB_malloc_proxy"
		
			For 64-bit code (note the double underscore):
				tbbmalloc_proxy.lib /INCLUDE:"__TBB_malloc_proxy"

		The OS program loader must be able to find the proxy library and the scalable memory allocator library at program load time.
		For that you may include the directory containing the libraries in the PATH environment variable.

		Parent topic: Automatically Replacing malloc and Other C/C++ Functions for Dynamic Memory Allocation
		URL: https://software.intel.com/en-us/node/506096
	*/

	class do_for
	{
	public:
		const size_t chunk;

	public:
		do_for(size_t _chunk) : chunk(_chunk) { return; }

		void operator() (tbb::blocked_range<int> &r) const
		{
			for (int n = r.begin();
				n != r.end();
				++n)
			{
				/// @brief scalable_malloc 호출 !!! - justin 8/16/2012 18:15:14
				int *p = new int[chunk];

				/// @brief scalable_free 호출 !!! - justin 8/16/2012 18:15:42
				delete[] p;
			}
		}
	};


	void use_tbb_memory_alloctator()
	{
		///////////////////////////////////////////////////////////////////////////////
		/// @author justin
		/// @date 8-16-2012 17:06:53
		/// @brief 다중 스레드 환경에 메모리를 할당 할 경우 상당히 일반적인 new, delete 는 많이 성능 비용을 감수 해야 함.
		///        tbb 는 scalable_allocator & cache_aligned_allocator 를 제공 !!!
		///        cache_aligned_allocator : 기본 성능은 scalable_allocator 보다 약간 느리나 
		///        모든 로직에서 사용될 경우 false sharing 을 방지 할 수 있어서 더 빠를 수 있음.
		///        false sharing 설명: http://blog.naver.com/hermet?Redirect=Log&logNo=68290454
		///
		///        성능 비교 결과: scalable_malloc & scalable_free > C++ new & delete > cache_aligned_allocator
		///                       false sharing 발생시 cache_aligned_allocator 가장 빠름 !!!
		///
		///////////////////////////////////////////////////////////////////////////////

		// 기본 예제
		{
			tbb::tick_count t0, t1;

			const size_t size = 1000;
			const size_t chunk = 10;
			const size_t grain_size = 200;

			t0 = tbb::tick_count::now();
			int *p = new int[size]; // scalable_malloc 호출 !!!
			t1 = tbb::tick_count::now();

			printf("operator new !!! - Elapsed Time: %f msec\n", ((t1 - t0).seconds() * 1000));

			// default allocator
			std::vector<int> vtDataList;

			t0 = tbb::tick_count::now();
			for (int n = 0;
				n < 10000;
				++n)
			{
				vtDataList.push_back(n);
			}
			t1 = tbb::tick_count::now();

			printf("STL vector default allocator !!! - Elapsed Time: %f msec\n", ((t1 - t0).seconds() * 1000));

			// cache_aligned_allocator 메모리 객체 등록
			std::vector<int, tbb::cache_aligned_allocator<int>> vtDataAllocatorList;

			t0 = tbb::tick_count::now();
			for (int n = 0;
				 n < 10000;
				 ++n \)
			{
				vtDataAllocatorList.push_back(n);
			}
			t1 = tbb::tick_count::now();

			printf("STL vector tbb::cache_aligned_allocator !!! - Elapsed Time: %f msec\n", ((t1 - t0).seconds() * 1000));

			_getch();

			t0 = tbb::tick_count::now();
			tbb::parallel_for(tbb::blocked_range<int>(0, size, grain_size), do_for(chunk));
			t1 = tbb::tick_count::now();

			printf("parallel_for - operator new !!! - Elapsed Time: %f msec\n", ((t1 - t0).seconds() * 1000));

			_getch();
		}
	}


	void Test()
	{
		use_tbb_memory_alloctator();
	}
}