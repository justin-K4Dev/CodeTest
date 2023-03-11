#pragma once

#define _MALLOC(p)	realloc(NULL, p)
#define _FREE(p)	realloc(p, 0)

#define malloc(n) MemoryManager::dbgMalloc(n, __FILE__, __LINE__)
#define free(p)	MemoryManager::dbgFree(p)

namespace MemoryManager
{
	void* dbgMalloc(int size, char* file, int line);
	void dbgFree(void* ptr);

	struct MemoryInfo
	{
		void* ptr;
		char* file;
		int line;
		unsigned long size;
		int num;
		struct MemoryInfo *next;
	};

	MemoryInfo* MemoryCreate(void* ptr, char* file, int line, unsigned long size);
	void MemoryDelete(MemoryInfo* self);

	struct TraceMemoryInfo
	{
		MemoryInfo* head;
		MemoryInfo* tail;
		int num;
	};

	TraceMemoryInfo* TraceMemoryCreate();
	void TraceMemoryDelete(TraceMemoryInfo*);

	int TraceMemoryAdd(TraceMemoryInfo* self, void* ptr, char* file, int line, unsigned long size);
	MemoryInfo* TraceMemoryPop(TraceMemoryInfo* self, MemoryInfo* item);
	int TraceMemoryRemove(TraceMemoryInfo* self, void* ptr);

	TraceMemoryInfo* TraceMemoryGetSummary(TraceMemoryInfo* self);

	void TraceMemoryInfoPrint(TraceMemoryInfo* self);

	extern TraceMemoryInfo* traceMemory;
}

