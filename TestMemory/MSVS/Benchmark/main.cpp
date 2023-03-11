// main.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MemoryAllocCase.hpp"


#define ALLOCATION_COUNT								100000


using namespace MemoryAllocCase;


BENCHMARK(lfh_malloc)->Args({ 1, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 1, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 1, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 1, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 2, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 2, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 2, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 3, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 3, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 3, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 4, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 4, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 4, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 5, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 5, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 5, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 6, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 6, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 6, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 7, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 7, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 7, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 8, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 8, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 8, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 9, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 9, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 9, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 10, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 10, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 10, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 11, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 11, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 11, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 12, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 12, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 12, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 13, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 13, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 13, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 14, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 14, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 14, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 15, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 15, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 15, ALLOCATION_COUNT })->ThreadPerCpu();


BENCHMARK(lfh_malloc)->Args({ 1 << 16, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(lfh_new)->Args({ 1 << 16, ALLOCATION_COUNT })->ThreadPerCpu();
BENCHMARK(TBB_malloc)->Args({ 1 << 16, ALLOCATION_COUNT })->ThreadPerCpu();



int _tmain(int argc, _TCHAR* argv[])
{
	benchmark::Initialize(&argc, argv);

	if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
		return 1;
	}

	benchmark::RunSpecifiedBenchmarks();

	system("pause");
}
