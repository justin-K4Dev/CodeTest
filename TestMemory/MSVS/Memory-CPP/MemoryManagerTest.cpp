#include "stdafx.h"
#include "Function.h"

#include "MemoryManager.h"

#include "MemoryComparator.h"

namespace MemoryManager
{
	void use_memory_manager()
	{
		TraceMemoryInfo* pTMI = TraceMemoryCreate();

		Util::MemoryComparator mc(__FUNCTION__);

		int *ptr = (int*)malloc(100);  // Line 14
		int *ptr2 = (int*)malloc(200);  // Line 15

		for (int i = 1; i <= 100; i++)
		{
			malloc(i); // Line 19
			if (i % 4 == 0)
			{
				malloc(i);  // Line 22
			}
		}

		free(ptr);
		free(ptr2);

		mc.End();

		TraceMemoryInfo* summary = TraceMemoryGetSummary(pTMI);
		TraceMemoryInfoPrint(summary);

		TraceMemoryDelete(summary);
		TraceMemoryDelete(pTMI);

		system("pause");
	}

	void Test()
	{
		use_memory_manager();
	}
}