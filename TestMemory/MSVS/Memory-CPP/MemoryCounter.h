#pragma once

#include "Singleton.hpp"

namespace Memory
{
	class MemoryCountingInfo
	{
	public:
		struct ALLOCATED_MEMORY_INFO
		{
			std::string		addrString;
			void*			address = nullptr;
			uint64_t		size = 0;
			std::string		objectName; // 추후에 설정	
			std::string		filename;
			unsigned int	line = 0;
		};

		std::unordered_map<void*, std::string> m_memoryKeyList;
		std::unordered_map<void*, ALLOCATED_MEMORY_INFO> m_memoryList;

		uint64_t m_totalMemorySize = 0;
		uint64_t m_onceMaxSize = 0;
		uint64_t m_usedMaxSize = 0;
		uint64_t m_allocatedCount = 0;

		std::mutex m_lock;

		MemoryCountingInfo() {}
		virtual ~MemoryCountingInfo() {}

		void AddMemoryInfo(void* ptr, size_t size, const char* objectName, const char* file, unsigned int line);
		void DeleteMemoryInfo(void* ptr, size_t size);

		void GetAllocatedMemoryInfoAll( OUT std::unordered_map<void*, ALLOCATED_MEMORY_INFO>& mAllocatedMemoryInfoList
		                              , OUT uint64_t& totalMemorySize, OUT uint64_t& usedMaxSize, OUT uint64_t& onceMaxSize
			                          , OUT uint64_t& allocatedCount );
	};

	class MemoryCounter : public DesignPattern::ISingleton<MemoryCounter>
	{
	protected:
		bool m_isStartedCount = false;

		typedef Concurrency::concurrent_unordered_map<int, MemoryCountingInfo*> ConcurrentMap;
		ConcurrentMap m_MemoryCountingInfoList;

	public:
		MemoryCounter() {}

		void Start() { m_isStartedCount = true; }
		void Stop() { m_isStartedCount = false; }

		bool AddMemoryCountingInfoByThreadID(int threadID);

		void NotifyAllocatedMemoryInfo(void* ptr, size_t size, const char* objectName, const char* file, unsigned int line);
		void NotifyDeallocatedMemoryInfo(void* ptr, size_t size);

		int ConvertHex(OUT char* out_buf, const char* buf, unsigned int len, int wide);

		void ReportMemoryCountingInfoAll();
	};

	#define GetMemoryCounter() MemoryCounter::GetInstance()
}



