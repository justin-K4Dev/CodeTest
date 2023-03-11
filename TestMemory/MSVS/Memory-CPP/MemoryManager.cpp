#include "stdafx.h"
#include "MemoryManager.h"


namespace MemoryManager
{
	TraceMemoryInfo* traceMemory = NULL;

	void* dbgMalloc(int size, char* file, int line)
	{
		void* ptr = _MALLOC(size);

		TraceMemoryAdd(traceMemory, ptr, file, line, size);

		return ptr;
	}

	void dbgFree(void* ptr)
	{
		TraceMemoryRemove(traceMemory, ptr);

		_FREE(ptr);
	}

	/* ��ũ�� ����Ʈ ��� ������ */
	MemoryInfo* MemoryCreate(void* ptr, char* file, int line, unsigned long size)
	{
		MemoryInfo* self = (MemoryInfo*)_MALLOC(sizeof(MemoryInfo));

		size_t length = strlen(file) + 1;
		self->file = (char*)_MALLOC(length);
		strncpy_s(self->file, length, file, length);
		self->line = line;
		self->size = size;
		self->num = 1;
		self->ptr = ptr;

		return self;
	}

	/* �Ҹ��� */
	void MemoryDelete(MemoryInfo* self)
	{
		if (self == NULL)
		{
			return;
		}

		_FREE(self->file);
		_FREE(self);
	}

	void MemoryInfoPrint(MemoryInfo* self)
	{
		printf(" ++ [%s:%d:%p] : %d/%d\n", self->file, self->line, self->ptr, self->num, self->size);
	}

	/* �޸� ������ ������ */
	TraceMemoryInfo* TraceMemoryCreate()
	{
		TraceMemoryInfo* self = (TraceMemoryInfo*)_MALLOC(sizeof(TraceMemoryInfo));

		self->head = MemoryCreate(0, "Head", 0, 0);
		self->tail = MemoryCreate(0, "Tail", 0, 0);

		self->head->next = self->tail;
		self->tail->next = NULL;

		self->num = 0;

		return self;
	}

	/* �Ҹ��� */
	void TraceMemoryDelete(TraceMemoryInfo* self)
	{
		while (self->head->next != self->tail)
		{
			MemoryDelete(TraceMemoryPop(self, self->head->next));
		}

		if (self->num != 0)
		{
			printf(" ++++ ERROR : TraceMem has Items %d", self->num);
		}

		_FREE(self->head);
		_FREE(self->tail);
		_FREE(self);
	}

	/* �ּҰ��� �̿��� ��� �˻� */
	MemoryInfo* TraceMemoryFindPtr(TraceMemoryInfo* self, void* ptr)
	{
		MemoryInfo* iter;

		for (iter = self->head->next; iter != self->tail; iter = iter->next)
		{
			if (ptr == iter->ptr)
				return iter;
		}

		return NULL;
	}

	int TraceMemoryPush(TraceMemoryInfo* self, MemoryInfo* item)
	{
		MemoryInfo* next = self->head->next;

		self->head->next = item;
		item->next = next;

		return (self->num++);
	}

	MemoryInfo* TraceMemoryPop(TraceMemoryInfo* self, MemoryInfo* item)
	{
		MemoryInfo *iter;

		for (iter = self->head; iter != self->tail; iter = iter->next)
		{
			if (iter->next == item)
			{
				iter->next = iter->next->next;
				item->next = NULL;
				self->num--;

				return item;
			}
		}

		return NULL;
	}

	/* �޸� ������ ����Ʈ�� �߰� */
	int TraceMemoryAdd(TraceMemoryInfo* self, void* ptr, char* file, int line, unsigned long size)
	{
		MemoryInfo *tar;

		if ((tar = TraceMemoryFindPtr(self, ptr)) == NULL)
		{
			MemoryInfo* item = MemoryCreate(ptr, file, line, size);
			TraceMemoryPush(self, item);
		}
		else
		{
			TraceMemoryInfoPrint(self);
		}

		return 0;
	}

	/* �޸� ������ ����Ʈ���� ���� */
	int TraceMemoryRemove(TraceMemoryInfo* self, void* ptr)
	{
		MemoryInfo *tar;

		if ((tar = TraceMemoryFindPtr(self, ptr)) != NULL)
		{
			MemoryDelete(TraceMemoryPop(self, tar));
		}
		else
		{
			TraceMemoryInfoPrint(self);
		}

		return 0;
	}

	/* �޸� ������ ���� ��� */
	void TraceMemoryInfoPrint(TraceMemoryInfo* self)
	{
		MemoryInfo *iter;

		printf("\n ++ TraceMemPrint\n");

		for (iter = self->head->next; iter != self->tail; iter = iter->next)
		{
			MemoryInfoPrint(iter);
		}
	}

	/* ���ϸ�� ���μ��� ��带 ã�� �Լ� */
	MemoryInfo* TraceMemoryFindFileLine(TraceMemoryInfo* self, char* file, int line)
	{
		MemoryInfo* iter;

		for (iter = self->head->next; iter != self->tail; iter = iter->next)
		{
			if (line == iter->line && strcmp(file, iter->file) == 0)
				return iter;
		}

		return NULL;
	}

	/* ������ �޸� ���¸� �ִ� �Լ� */
	TraceMemoryInfo* TraceMemoryGetSummary(TraceMemoryInfo* self)
	{
		MemoryInfo *iter, *tar;
		TraceMemoryInfo* sum = TraceMemoryCreate();

		for (iter = self->head->next; iter != self->tail; iter = iter->next)
		{
			if ((tar = TraceMemoryFindFileLine(sum, iter->file, iter->line)) == NULL)
			{
				MemoryInfo *item = MemoryCreate(0, iter->file, iter->line, iter->size);
				TraceMemoryPush(sum, item);
			}
			else
			{
				tar->num++;
				tar->size += iter->size;
			}
		}

		return sum;
	}
}