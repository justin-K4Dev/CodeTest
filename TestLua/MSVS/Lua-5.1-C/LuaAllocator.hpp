#pragma once

#include "stdafx.h"

namespace Lua
{
	class LuaAllocator
	{
	protected:
		std::size_t m_allocSize = 0;
		//std::size_t m_freeSize = 0;
		std::unordered_map<void*, std::size_t> m_blockList;

	public:
		LuaAllocator() { return; }
		virtual ~LuaAllocator() 
		{
			Clear();
		}

		void Clear()
		{
			for (auto &p : m_blockList) {
				free(p.first);
			}

			m_blockList.clear();
		}

		static void* callAlloc(void* pAllocObj, void* ptr, std::size_t oSize, std::size_t nSize)
		{
			auto luaAllocator = static_cast<LuaAllocator*>(pAllocObj);
			if (0 == nSize) {
				luaAllocator->Dealloc(ptr);
				return nullptr;
			}
			else {
				return luaAllocator->Alloc(ptr, oSize, nSize);
			}
		}

		void* Alloc(void* ptr, std::size_t osize, std::size_t size)
		{
			void* nptr = nullptr;

			if (ptr != nullptr) {
				nptr = realloc(ptr, size);
			}
			else {
				nptr = malloc(size);
			}

			if (nptr == nullptr) {
				// error log : failed to alloc !!!
				printf("Failed to allocate Lua state !!! - AllocSize:%I64u\n", m_allocSize);
				return nullptr;
			}

			if (nullptr == ptr) {
				m_allocSize += size;
			}
			else {
				m_allocSize += size;

				auto itPos = m_blockList.find(ptr);
				if (itPos == m_blockList.end()) {
					// error log : not found block
					printf("Failed to find allocated block address !!! - AllocSize:%I64u\n", m_allocSize);
				}
				else {
					m_allocSize -= itPos->second;
					printf("Deallocated block address - AllocSize:%I64u\n", m_allocSize);
				}

				if (ptr == nptr) {
					// block extension !!!
				}
				else {
					m_blockList.erase(itPos);
				}
			}

			m_blockList[nptr] = size;

			printf("Lua allocated size: [%I64d] Bytes, AllocSize:%I64d\n", size, m_allocSize);

			return nptr;
		}

		void Dealloc(void* ptr)
		{
			std::size_t nSize = 0;

			auto itPos = m_blockList.find(ptr);

			if (m_blockList.end() == itPos) {
				free(ptr);

				if (nullptr != ptr) {
					// error log : failed to dealloc
					printf("Failed to deallocate Lua state !!! - AllocSize:%I64u\n", m_allocSize);
				}
			}
			else {
				m_allocSize -= nSize = itPos->second;

				m_blockList.erase(itPos);

				free(ptr);
			}

			printf("Lua deallocated size: [%I64d] Bytes, AllocSize:%I64u\n", nSize, m_allocSize);
		}
	};
}