#include "stdafx.h"
#include "MemoryCounter.h"

namespace Memory
{
	void MemoryCountingInfo::AddMemoryInfo(void *ptr, size_t size, const char* objectName, const char *file, unsigned int line)
	{
		std::lock_guard<std::mutex> safeLock(m_lock);

		char szBuf[2048];
		sprintf_s(szBuf, sizeof(szBuf), "_Address:0x%I64x_", (uint64_t)ptr);

		auto itFound = m_memoryList.find(ptr);
		if (m_memoryList.end() == itFound) {

			ALLOCATED_MEMORY_INFO info;
			info.addrString = szBuf;
			info.address = ptr;
			info.size = size;
			info.objectName = objectName;
			info.filename = file;
			info.line = line;

			m_memoryList.emplace(ptr, info);
		}
		else {
			itFound->second.size += size;
		}

		m_totalMemorySize += size;
		m_usedMaxSize = max(m_totalMemorySize, m_usedMaxSize);
		m_onceMaxSize = max(m_onceMaxSize, size);

		m_allocatedCount++;
	}

	void MemoryCountingInfo::DeleteMemoryInfo(void* ptr, size_t size)
	{
		std::lock_guard<std::mutex> safeLock(m_lock);

		auto itFoundMemoryInfo = m_memoryList.find(ptr);
		if (m_memoryList.end() == itFoundMemoryInfo) {
			return;
		}

		uint64_t decreaseSize = 0;

		if (0 < size) {
			itFoundMemoryInfo->second.size -= size;
			decreaseSize = size;
		}
		else {
			itFoundMemoryInfo->second.size = 0;
			decreaseSize = itFoundMemoryInfo->second.size;
		}

		m_totalMemorySize -= decreaseSize;

		if (0 >= itFoundMemoryInfo->second.size) {
			m_memoryList.erase(itFoundMemoryInfo);
		}

		m_allocatedCount--;
	}

	void MemoryCountingInfo::GetAllocatedMemoryInfoAll( OUT std::unordered_map<void*, ALLOCATED_MEMORY_INFO>& allocatedMemoryInfoList
	                                                  , OUT uint64_t& totalMemorySize, OUT uint64_t& usedMaxSize, OUT uint64_t& onceMaxSize
	                                                  , OUT uint64_t& allocatedCount )
	{
		std::lock_guard<std::mutex> safeLock(m_lock);

		for (auto pair_info : m_memoryList) {

			void* ptr = pair_info.first;

			auto itFound = allocatedMemoryInfoList.find(ptr);
			if (allocatedMemoryInfoList.end() == itFound) {
				allocatedMemoryInfoList.emplace(ptr, pair_info.second);
			}
			else {
				itFound->second.size += pair_info.second.size;
			}
		}

		totalMemorySize += m_totalMemorySize;
		usedMaxSize += m_usedMaxSize;
		onceMaxSize += m_onceMaxSize;
		allocatedCount += m_allocatedCount;
	}

	int MemoryCounter::ConvertHex(OUT char* out_buf, const char* buf, unsigned int len, int wide)
	{
		int i;
		int ret = 0;
		int nlines = 0;
		const char hex_char[] = "0123456789ABCDEF";
		const unsigned char *ptr = (const unsigned char*)buf;
		char *dst = out_buf;
		if (wide == 8) {
			nlines = (len + 0x07) >> 3;
		}
		else {
			wide = 16;
			nlines = (len + 0x0f) >> 4;
		}

		for (i = 0; i < nlines; i++) {
			int j;
			int nbytes = ((int)len < wide) ? len : wide;
			*dst++ = ' ';
			*dst++ = ' ';
			*dst++ = ' ';
			*dst++ = ' ';

			for (j = 0; j < nbytes; j++) {
				unsigned char ival = *ptr++;
				*dst++ = hex_char[(ival >> 4) & 0x0F];
				*dst++ = hex_char[ival & 0x0F];
				*dst++ = ' ';
			}

			for (j = 0; j < wide - nbytes + 1; j++) {
				*dst++ = ' ';
				*dst++ = ' ';
				*dst++ = ' ';
			}

			ptr -= nbytes;
			
			for (j = 0; j < nbytes; j++) {
				if ((*ptr >= 0x20) && (*ptr <= 0x7e)) {
					*dst = *ptr;
				}
				else {
					*dst = '.';
				}
				ptr++;
				dst++;
			}
			*dst++ = '\n';
			len -= nbytes;
		}
		*dst++ = 0;

		return ret;
	}

	bool MemoryCounter::AddMemoryCountingInfoByThreadID(int threadID)
	{
		if (true == m_isStartedCount)
			return false;

		auto result = m_MemoryCountingInfoList.insert(ConcurrentMap::value_type(threadID, new MemoryCountingInfo()));
		if (false == result.second) {
			return false;
		}

		return true;
	}

	void MemoryCounter::NotifyAllocatedMemoryInfo(void* ptr, size_t size, const char* objectName, const char* file, unsigned int line)
	{
		uint32_t threadID = GetCurrentThreadId();

		auto itFound = m_MemoryCountingInfoList.find(threadID);
		if (m_MemoryCountingInfoList.end() == itFound) {
			return;
		}

		itFound->second->AddMemoryInfo(ptr, size, objectName, file, line);
	}

	void MemoryCounter::NotifyDeallocatedMemoryInfo(void* ptr, size_t size)
	{
		uint32_t threadID = GetCurrentThreadId();

		auto itFound = m_MemoryCountingInfoList.find(threadID);
		if (m_MemoryCountingInfoList.end() == itFound) {
			return;
		}

		itFound->second->DeleteMemoryInfo(ptr, size);
	}

	void MemoryCounter::ReportMemoryCountingInfoAll()
	{
		if (true == m_isStartedCount)
			return;

		SYSTEMTIME logTime;
		::GetLocalTime(&logTime);

		uint64_t totalMemorySize = 0, usedMaxSize = 0, onceMaxSize = 0, allocatedCount = 0;
		std::unordered_map<void*, MemoryCountingInfo::ALLOCATED_MEMORY_INFO> allocatedMemoryInfoList;

		for (auto pair_info : m_MemoryCountingInfoList) {
			pair_info.second->GetAllocatedMemoryInfoAll( OUT allocatedMemoryInfoList
				                                       , OUT totalMemorySize, OUT usedMaxSize, OUT onceMaxSize
			                                           , OUT allocatedCount );
		}

		MemoryCountingInfo::ALLOCATED_MEMORY_INFO* pMemoryInfo = nullptr;

		char szLogFileName[512];
		sprintf_s( szLogFileName, sizeof(szLogFileName), "MemroyCounter_%02d-%02d-%02d_%02d-%02d-%02d.txt"
				 , logTime.wYear, logTime.wMonth, logTime.wDay
			     , logTime.wHour, logTime.wMinute, logTime.wSecond
		);

		FILE* fp_write = nullptr;
		if (fopen_s(&fp_write, szLogFileName, "wt") != 0) {
			std::string errMsg;
			errMsg = "Failed to create File !!! - Filename:" + std::string(szLogFileName);
			::perror(errMsg.c_str());
			return;
		}

		char info[1024];
		int print_size;
		if (fp_write != NULL)
		{
			sprintf( info, "Memory Leak Summary - written time:%d/%d/%d %d:%d:%d:%d\n"
				   , logTime.wMonth, logTime.wDay, logTime.wYear, logTime.wHour, logTime.wMinute, logTime.wSecond, logTime.wMilliseconds );
			fwrite(info, (strlen(info)), 1, fp_write);
			sprintf(info, "%s\n", "---------------------------------------------------");
			fwrite(info, (strlen(info)), 1, fp_write);
			sprintf( info
				   , "LeakTotal:%I64dbyte, UsedMaxSize:%I64dbyte, OnceMaxSize:%I64dbyte, AllocatedCount:%I64d\n\n"
				   , totalMemorySize, usedMaxSize, onceMaxSize
			       , allocatedCount );
			fwrite(info, (strlen(info)), 1, fp_write);

			sprintf_s(info, sizeof(info), "%s\n", "---------------------------------------------------");
			fwrite(info, (strlen(info)), 1, fp_write);

			for (auto itPos_memoryInfo : allocatedMemoryInfoList) {
				pMemoryInfo = &itPos_memoryInfo.second;

				sprintf_s( info, sizeof(info), "Address:0x%I64x, ClassName:%s, Size:%I64d bytes\n"
					   , (uint64_t)pMemoryInfo->address, pMemoryInfo->objectName.c_str(), pMemoryInfo->size );
				fwrite(info, (strlen(info)), 1, fp_write);

				print_size = pMemoryInfo->size > 64 ? 64 : pMemoryInfo->size;
				ConvertHex(OUT info, (char*)pMemoryInfo->address, print_size, 16);
				fwrite(info, (strlen(info)), 1, fp_write);

				sprintf_s( info, sizeof(info), "File:%s, Line:%d \n", pMemoryInfo->filename.c_str(), pMemoryInfo->line );
				fwrite( info, (strlen(info)), 1, fp_write );

				sprintf_s( info, sizeof(info), "%s\n", "---------------------------------------------------" );
				fwrite( info, (strlen(info)), 1, fp_write );
			}

			fflush(fp_write);
			fclose(fp_write);
		}
	}
}
