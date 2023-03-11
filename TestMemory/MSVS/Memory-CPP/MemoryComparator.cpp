#include "stdafx.h"
#include "MemoryComparator.h"

namespace Util
{
	MemoryComparator::MemoryComparator(const char* title)
	{
		m_strTitle = title;

		std::string debugInfo;
		debugInfo.append(m_strTitle + " WorkingSet Memory Comparison Start\n");

		char szBuff[1024] = { 0, };

		// 현재 application 에서 사용중인 메모리 크기
		ULONGLONG usingWorkingSetSizeOfProcess = 0;
		HANDLE hProcess = GetCurrentProcess();
		if (NULL != hProcess) {
			PROCESS_MEMORY_COUNTERS_EX memoryCounter;
			GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&memoryCounter, sizeof(memoryCounter));
			usingWorkingSetSizeOfProcess = memoryCounter.WorkingSetSize / 1024;
			::CloseHandle(hProcess);
		}

		sprintf_s(szBuff, "Current Memory Size: %I64u KByte\n", usingWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);

		m_startWorkingSetSizeOfProcess = usingWorkingSetSizeOfProcess;
		m_midWorkingSetSizeOfProcess = usingWorkingSetSizeOfProcess;

		std::cout << debugInfo << std::endl;
	}

	MemoryComparator::~MemoryComparator()
	{
		if (true == m_isEnd) {
			return;
		}

		this->End();
	}

	void MemoryComparator::CompareNow(bool updateMiddleTime /* = false */)
	{
		std::string debugInfo;
		debugInfo.append(m_strTitle + " WorkingSet Memory Comparison Now\n");

		char szBuff[1024] = { 0, };

		// 현재 application 에서 사용중인 메모리 크기
		ULONGLONG usingWorkingSetSizeOfProcess = 0;
		HANDLE hProcess = GetCurrentProcess();
		if (NULL != hProcess) {
			PROCESS_MEMORY_COUNTERS_EX memoryCounter;
			GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&memoryCounter, sizeof(memoryCounter));
			usingWorkingSetSizeOfProcess = memoryCounter.WorkingSetSize / 1024;
			::CloseHandle(hProcess);
		}

		sprintf_s(szBuff, "Mid Memory Size: %I64u KByte\n", m_midWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);
		sprintf_s(szBuff, "Current Memory Size: %I64u KByte\n", usingWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);
		sprintf_s(szBuff, "Changed Memory Size: %I64d KByte\n", usingWorkingSetSizeOfProcess - m_midWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);

		if (true == updateMiddleTime) {
			m_midWorkingSetSizeOfProcess = usingWorkingSetSizeOfProcess;
		}

		std::cout << debugInfo << std::endl;
	}

	void MemoryComparator::End()
	{
		std::string debugInfo;
		debugInfo.append(m_strTitle + " WorkingSet Memory Comparison End\n");

		char szBuff[1024] = { 0, };

		// 현재 application 에서 사용중인 메모리 크기
		ULONGLONG usingWorkingSetSizeOfProcess = 0;
		HANDLE hProcess = GetCurrentProcess();
		if (NULL != hProcess) {
			PROCESS_MEMORY_COUNTERS_EX memoryCounter;
			GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&memoryCounter, sizeof(memoryCounter));
			usingWorkingSetSizeOfProcess = memoryCounter.WorkingSetSize / 1024;
			::CloseHandle(hProcess);
		}

		sprintf_s(szBuff, "Start Memory Size: %I64u KByte\n", m_startWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);
		sprintf_s(szBuff, "Current Memory Size: %I64u KByte\n", usingWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);
		sprintf_s(szBuff, "Changed Memory Size: %I64d KByte\n", usingWorkingSetSizeOfProcess - m_startWorkingSetSizeOfProcess);
		debugInfo.append(szBuff);

		std::cout << debugInfo << std::endl;

		m_isEnd = true;
	}
}