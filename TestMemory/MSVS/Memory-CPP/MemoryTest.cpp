#include "stdafx.h"
#include "Function.h"

#include "MemoryManager.h"


namespace Memory
{
	void Test()
	{
		{
			TraceMemoryInfo* pTMI = TraceMemoryCreate();

			int *ptr = (int*)malloc(100);  // Line 11
			int *ptr2 = (int*)malloc(200);  // Line 12

			for (int i = 1; i <= 100; i++)
			{
				malloc(i); // Line 16
				if (i % 4 == 0)
				{
					malloc(i);  // Line 19
				}
			}

			free(ptr);
			free(ptr2);

			TraceMemoryInfo* summary = TraceMemoryGetSummary(pTMI);
			TraceMemoryInfoPrint(summary);

			TraceMemoryDelete(summary);
			TraceMemoryDelete(pTMI);

			_getch();
		}
	}
}