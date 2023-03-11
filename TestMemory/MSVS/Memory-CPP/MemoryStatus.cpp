#include "stdafx.h"
#include "Function.h"

#include <Windows.h>
#include <psapi.h>

namespace MemoryStatus
{
	void memory_status_query()
	{
		std::string debugInfo;

		debugInfo.append("\nMemory Information\n");

		char szBuff[1024] = { 0, };

		// 시스템 메모리 정보
		DWORDLONG totalPhysicalMemorySize = 0;
		DWORDLONG usablePhysicalMemorySize = 0;
		MEMORYSTATUSEX memoryStatus;
		memoryStatus.dwLength = sizeof(memoryStatus);

		if (TRUE == ::GlobalMemoryStatusEx(&memoryStatus)) {
			totalPhysicalMemorySize = memoryStatus.ullTotalPhys / 1024 / 1024;
			usablePhysicalMemorySize = memoryStatus.ullAvailPhys / 1024 / 1024;
		}

		sprintf_s(szBuff, "System Memory Total Size: %I64u MByte\n", totalPhysicalMemorySize);
		debugInfo.append(szBuff);
		sprintf_s(szBuff, "System Memory Usable Size: %I64u MByte\n", usablePhysicalMemorySize);
		debugInfo.append(szBuff);

		// 현재 application 에서 사용중인 메모리 크기
		ULONGLONG usingWorkingSetSizeOfProcess = 0;
		ULONGLONG usingVirtualMemorySizeOfProcess = 0;
		HANDLE hProcess = GetCurrentProcess();
		if (NULL != hProcess) {
			PROCESS_MEMORY_COUNTERS_EX memoryCounter;
			GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&memoryCounter, sizeof(memoryCounter));
			usingWorkingSetSizeOfProcess = memoryCounter.WorkingSetSize / 1024 / 1024;
			usingVirtualMemorySizeOfProcess = memoryCounter.PrivateUsage / 1024 / 1024;
			::CloseHandle(hProcess);
		}

		sprintf_s(szBuff, "Application Using Physical Memory Size: %I64u MByte\n", usingWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);
		sprintf_s(szBuff, "Application Using Virtual Memory Size: %I64u MByte\n", usingVirtualMemorySizeOfProcess);
		debugInfo.append(szBuff);

		std::cout << debugInfo << std::endl;

		system("pause");
	}


	void Test()
	{
		memory_status_query();
	}
}