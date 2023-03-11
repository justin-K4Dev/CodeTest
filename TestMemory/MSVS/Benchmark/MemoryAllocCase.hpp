#pragma once

#include "stdafx.h"

namespace MemoryAllocCase
{
	// c malloc api use
	static void lfh_malloc(benchmark::State& state)
	{
		int64_t size = state.range(0);
		int64_t count = state.range(1);

		while (state.KeepRunning()) {
			for (int i = 0; i < count; ++i) {
				void* ptr = malloc(size);
				free(ptr);
			}
		}
	}

	// c++ new api use
	static void lfh_new(benchmark::State& state)
	{
		int64_t size = state.range(0);
		int64_t count = state.range(1);

		while (state.KeepRunning()) {
			for (int i = 0; i < count; ++i) {
				void* ptr = operator new (size);
				delete ptr;
			}
		}
	}

	// tbb scalable_malloc api use
	static void TBB_malloc(benchmark::State& state)
	{
		int64_t size = state.range(0);
		int64_t count = state.range(1);

		while (state.KeepRunning()) {
			for (int i = 0; i < count; ++i) {
				void* ptr = scalable_malloc(size);
				scalable_free(ptr);
			}
		}
	}
}