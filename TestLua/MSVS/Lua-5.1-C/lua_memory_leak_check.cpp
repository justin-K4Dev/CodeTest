#include "stdafx.h"
#include "Function.h"
#include <Windows.h>

#include "MemoryComparator.h"

namespace LuaMemoryLeakCheck
{
	static DWORDLONG g_preWorkingSetMemorySize = 0;

	void lua_gc_non_cache()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Failed to assign LuaState !!!" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		uint64_t initGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
		printf("Lua openLib loaded GC memory usage: [%I64d] Bytes\n", initGCMemSize);

		int result;

		lua_gc(pLS, LUA_GCSTOP, 0);

		char luaFilename[] = { "./lua_gc.lua" };

		// run the script : luaL_loadfile() + lua_pcall() !!!
		if (luaL_dofile(pLS, luaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}

		uint64_t luaLoadedGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
		printf("Lua file %s loaded GC memory usage: [%I64d] Bytes\n", luaFilename, luaLoadedGCMemSize);

		lua_getglobal(pLS, "eventHandler");
		lua_pushstring(pLS, "reset");

		result = lua_pcall(pLS, 1, 0, 0);
		if (0 != result) {
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_settop(pLS, 0);

		Util::MemoryComparator mc(__FUNCTION__);

		uint64_t minCollectedGCMemSize = 0;
		uint64_t collectedGCMemSize = 0;
		int sameGCMemSizeCount = 0;
		int collectedGCCount = 0;

		// do full gc
		do {
			lua_gc(pLS, LUA_GCCOLLECT, 0);
			
			++collectedGCCount;

			printf("# After GC call count : %d\n", collectedGCCount);
			collectedGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
			printf("Collected GC memory usage: [%I64d] Bytes\n", collectedGCMemSize);

			if (0 == minCollectedGCMemSize) {
				minCollectedGCMemSize = collectedGCMemSize;
			}

			if (minCollectedGCMemSize == collectedGCMemSize) {
				++sameGCMemSizeCount;
			}

			minCollectedGCMemSize = min(minCollectedGCMemSize, collectedGCMemSize);

		} while (sameGCMemSizeCount < 2);

		mc.End();

		// cleanup
		lua_close(pLS);
	}

	void lua_gc_cache(lua_State *pLS)
	{
		luaL_openlibs(pLS);

		uint64_t initGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
		printf("Lua GC cached memory usage: [%I64d] Bytes\n", initGCMemSize);

		int result;

		lua_gc(pLS, LUA_GCSTOP, 0);

		char luaFilename[] = { "./lua_gc.lua" };

		// run the script : luaL_loadfile() + lua_pcall() !!!
		if (luaL_dofile(pLS, luaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}

		uint64_t luaLoadedGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
		printf("Lua file %s loaded mem usage: [%I64d] Bytes\n", luaFilename, luaLoadedGCMemSize);

		lua_getglobal(pLS, "eventHandler");
		lua_pushstring(pLS, "reset");

		result = lua_pcall(pLS, 1, 0, 0);
		if (0 != result) {
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_settop(pLS, 0);

		Util::MemoryComparator mc(__FUNCTION__);

		lua_gc(pLS, LUA_GCCOLLECT, 0);

		uint64_t collectedGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
		printf("Collected GC memory usage: [%I64d] Bytes\n", collectedGCMemSize);

		mc.End();
	}

	void lua_check_of_non_cache()
	{
		// Lua state Non-Cache
		{
			printf("Lua state Non-Cache Test Start ...\n");

			Util::MemoryComparator mc(__FUNCTION__);

			for (int i = 1; i <= 1000000; ++i) {
				
				system("cls");
				printf("Lua state Non-cache Test !!! - count:%d\n", i);

				lua_gc_non_cache();
			}

			mc.End();
		}

		system("pause");
	}

	void lua_check_of_cache()
	{
		// Lua state Cache
		{
			printf("Lua state Cache Test Start ...\n");

			Util::MemoryComparator mc(__FUNCTION__);

			lua_State *pLS = luaL_newstate();
			if (nullptr == pLS) {
				std::cout << "Failed to assign LuaState !!!" << std::endl;
				return;
			}

			for (int i = 1; i <= 1000000; ++i) {

				system("cls");
				printf("Lua state Cache Test !!! - count:%d\n", i);

				lua_gc_cache(pLS);
			}

			// cleanup
			lua_close(pLS);

			mc.End();
		}

		system("pause");
	}

	void Test()
	{
		lua_check_of_cache();

		//lua_check_of_non_cache();
	}
}