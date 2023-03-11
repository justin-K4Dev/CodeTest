#include "stdafx.h"
#include "Function.h"
#include "LuaAllocator.hpp"

#include <Windows.h>


namespace LuaStateAlloc
{
	void lua_state_alloc_dealloc()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Failed to assign LuaState !!!" << std::endl;
			return;
		}

		// load all lua standard libraries
		luaL_openlibs(pLS);

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

		int result;

		result = lua_pcall(pLS, 1, 0, 0);
		if (0 != result) {
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_settop(pLS, 0);

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

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void lua_state_realloc()
	{
		Lua::LuaAllocator alloctor;

		lua_State *pLS = lua_newstate(Lua::LuaAllocator::callAlloc, &alloctor);
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

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		lua_state_alloc_dealloc();

		lua_state_realloc();
	}
}