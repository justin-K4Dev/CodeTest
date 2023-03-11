#include "stdafx.h"
#include "Function.h"

#include "CRT_MemoryCheck.h"

#include <malloc.h>

#include "MemoryComparator.h"

namespace BasicMemory
{
	void use_malloc()
	{
		printf("\n");
		printf("use malloc() function\n");
		
		Util::MemoryComparator mc(__FUNCTION__);

		const int AllocCount = 10;
		int *pArr;	// pointer int array

		pArr = (int*)malloc(sizeof(int) * AllocCount);

		printf("allocated address\n");
		for (int i = 0; i <= AllocCount - 1; i++) {
			printf("array [%d], allocated address : %p\n"
				  , i, &pArr[i]);
		}

		printf("assigned value\n");
		for (int i = 0; i <= AllocCount - 1; i++) {
			printf("array [%d], value = %d\n"
				  , i, pArr[i]);
		}

		free(pArr);

		mc.End();

		/*
		output:
			use malloc() function
			allocated address
			array[0], allocated address : 000000000030A770
			array[1], allocated address : 000000000030A774
			array[2], allocated address : 000000000030A778
			array[3], allocated address : 000000000030A77C
			array[4], allocated address : 000000000030A780
			array[5], allocated address : 000000000030A784
			array[6], allocated address : 000000000030A788
			array[7], allocated address : 000000000030A78C
			array[8], allocated address : 000000000030A790
			array[9], allocated address : 000000000030A794
			assigned value
			array[0], value = -842150451
			array[1], value = -842150451
			array[2], value = -842150451
			array[3], value = -842150451
			array[4], value = -842150451
			array[5], value = -842150451
			array[6], value = -842150451
			array[7], value = -842150451
			array[8], value = -842150451
			array[9], value = -842150451
		*/

		system("pause");
	}

	void use_calloc()
	{
		printf("\n");
		printf("use calloc() function\n");

		const int AllocCount = 10;
		int *pArr;	// pointer int array

		Util::MemoryComparator mc(__FUNCTION__);

		pArr = (int*)calloc(AllocCount, sizeof(int));

		printf("allocated address\n");
		for (int i = 0; i <= AllocCount - 1; i++) {
			printf("array [%d], allocated address : %p\n"
				, i, &pArr[i]);
		}

		printf("assigned value\n");
		for (int i = 0; i <= AllocCount - 1; i++) {
			printf("array [%d], value = %d\n"
				, i, pArr[i]);
		}

		free(pArr);

		mc.End();

		/*
		output:
			use calloc() function
			allocated address
			array [0], allocated address : 000000000027A770
			array [1], allocated address : 000000000027A774
			array [2], allocated address : 000000000027A778
			array [3], allocated address : 000000000027A77C
			array [4], allocated address : 000000000027A780
			array [5], allocated address : 000000000027A784
			array [6], allocated address : 000000000027A788
			array [7], allocated address : 000000000027A78C
			array [8], allocated address : 000000000027A790
			array [9], allocated address : 000000000027A794
			assigned value
			array [0], value = 0
			array [1], value = 0
			array [2], value = 0
			array [3], value = 0
			array [4], value = 0
			array [5], value = 0
			array [6], value = 0
			array [7], value = 0
			array [8], value = 0
			array [9], value = 0		
		*/

		system("pause");
	}

	void use_realloc()
	{
		printf("\n");
		printf("use realloc() function\n");

		int allocSize = 0;
		int* pArr = NULL;	// pointer int array
		int* pTemp = NULL;

		Util::MemoryComparator mc(__FUNCTION__);

		allocSize = 5;
		pArr = (int*)calloc(allocSize, sizeof(int));

		printf("calloc heap size:%d, address:%p\n"
			  , (int)(sizeof(int) * allocSize), pArr);
		pTemp = pArr; // backup for old heap block free
		
		printf("assigned value\n");
		for (int i = 0; i <= allocSize - 1; i++) {
			printf("array [%d], value = %d\n"
				, i, pArr[i]);
		}

		// resize heap block
		allocSize = 100000;
		pArr = (int*)realloc(pArr, sizeof(int) * allocSize);
		printf("realloc heap size:%d, address:%p\n"
			  , (int)(sizeof(int) * allocSize), pArr);

		printf("assigned value\n");
		for (int i = 0; i <= allocSize - 1; i++) {
			if (0 == pArr[i]) {
				printf("NULL array [%d], value = %d\n"
					, i, pArr[i]);
			}
		}

		if (0 == pArr) {
			free(pTemp); // free old heep block
		}
		else {
			free(pArr); // free old and new heap block !!!
		}

		mc.End();

		/*
		output:
			use realloc() function
			calloc heap size:20, address:0000000000278B20
			assigned value
			array [0], value = 0
			array [1], value = 0
			array [2], value = 0
			array [3], value = 0
			array [4], value = 0
			realloc heap size:400000, address:000000000027CD50
			assigned value
			NULL array [0], value = 0
			NULL array [1], value = 0
			NULL array [2], value = 0
			NULL array [3], value = 0
			NULL array [4], value = 0
		*/

		system("pause");
	}

	void use_realloc_memory_resize()
	{
		printf("\n");
		printf("show memory change by realloc()\n");

		int allocSize = 0;
		int *pArr = NULL; // pointer int array

		Util::MemoryComparator mc(__FUNCTION__);

		// alloc heap block
		allocSize = 10;
		pArr = (int*)realloc(NULL, sizeof(int) * allocSize);
		printf( "old heap size:%d, address:%p\n"
			  , (int)(sizeof(int) * allocSize), pArr );

		// extended heap block
		allocSize = 100000;
		pArr = (int*)realloc(pArr, sizeof(int) * allocSize);
		printf( "extended heap size:%d, address:%p\n"
			  , (int)(sizeof(int) * allocSize), pArr );

		// reduced heap block
		allocSize = 1;
		pArr = (int*)realloc(pArr, sizeof(int) * allocSize);
		printf( "reduced heap size:%d, address:%p\n"
			  , (int)(sizeof(int) * allocSize), pArr );

		free(pArr);

		mc.End();

		/*
		output:
			show memory change by realloc()
			old heap size:40, address:000000000014A770
			extended heap size:400000, address:000000000014CD50
			reduced heap size:4, address:000000000014CD50		
		*/

		_getch();
	}

	void* ExtendMemory(void* oldHeapBlock, int oldCount, int dataCount, int dataSize)
	{
		void* heapBlock;

		if (NULL == oldHeapBlock) {
			heapBlock = calloc(dataCount, dataSize);
			printf( "new alloc heap size:%d, address:%p\n"
				  , (int)(dataSize * dataCount), heapBlock );

			return heapBlock;
		}

		if (oldCount >= dataCount) {
			heapBlock = oldHeapBlock;
			printf( "reduced heap size:%d, address:%p\n"
				  , (int)(dataSize * dataCount), heapBlock );
		}
		else {
			heapBlock = calloc(dataCount, dataSize);
			printf( "extended heap size:%d, address:%p\n"
				  , (int)(dataSize * dataCount), heapBlock );

			memcpy(heapBlock, oldHeapBlock, oldCount * dataSize);
			printf( "copy data heap size:%d, address:%p\n"
				  , (int)(oldCount * dataSize), oldHeapBlock );

			free(oldHeapBlock);
		}

		return heapBlock;
	}

	void FillDataInArray(int* pArray, int dataSize)
	{
		for (int i = 0; i < dataSize; ++i) {
			
			pArray[i] = rand() % 100;
		}
	}

	void PrintArray(int* pArray, int dataSize)
	{
		printf("assigned value\n");
		for (int i = 0; i <= dataSize - 1; i++) {

			printf( "array [%d], value = %d\n"
				  , i, pArray[i] );
		}
	}

	void use_ExtendMemory()
	{
		/*
			maked realloc function 
		*/
		int* pArray = NULL;
		int allocCount, oldAllocCount = 0;

		Util::MemoryComparator mc(__FUNCTION__);

		while (true) {

			printf("input Alloc Count:");
			scanf("%d", &allocCount);

			if (allocCount <= 0) {
				break;
			}

			pArray = (int*)ExtendMemory(pArray, oldAllocCount, allocCount, sizeof(int));
			if (allocCount > oldAllocCount) {
				FillDataInArray(pArray, allocCount);
			}

			oldAllocCount = allocCount;

			PrintArray(pArray, allocCount);
		}


		allocCount = oldAllocCount * 2;
		pArray = (int*)ExtendMemory(pArray, oldAllocCount, allocCount, sizeof(int));

		PrintArray(pArray, allocCount);

		free(pArray);

		mc.End();

		system("pause");
	}

	void Test()
	{
		SET_CRT_MEMORY_CHECK(CRT_MEMORY_LEAK_ALWAYS_CHECK_FLAGS);

		use_malloc();

		use_calloc();

		use_realloc();

		use_realloc_memory_resize();

		use_ExtendMemory();

		_CrtDumpMemoryLeaks();
	}
}