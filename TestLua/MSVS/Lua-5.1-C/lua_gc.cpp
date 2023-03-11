#include "stdafx.h"
#include "Function.h"
#include <Windows.h>

#include "MemoryComparator.h"

namespace LuaGC
{
	/*
		Controls the garbage collector.

		This function performs several tasks, according to the value of the parameter what:

			* LUA_GCSTOP: stops the garbage collector.
			* LUA_GCRESTART: restarts the garbage collector.
			* LUA_GCCOLLECT: performs a full garbage-collection cycle.
			* LUA_GCCOUNT: returns the current amount of memory (in Kbytes) in use by Lua.
			* LUA_GCCOUNTB: returns the remainder of dividing the current amount of bytes of memory in use by Lua by 1024.
			* LUA_GCSTEP: performs an incremental step of garbage collection.
			              The step "size" is controlled by data (larger values mean more steps) in a non-specified way.
						  If you want to control the step size you must experimentally tune the value of data.
						  The function returns 1 if the step finished a garbage-collection cycle.
			* LUA_GCSETPAUSE: sets data as the new value for the pause of the collector (see ¡×2.10).
			                  The function returns the previous value of the pause.
			* LUA_GCSETSTEPMUL: sets data as the new value for the step multiplier of the collector (see ¡×2.10).
			                    The function returns the previous value of the step multiplier.
	
	*/

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

			Sleep(1);

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

		system("pause");
	}

	void lua_gc_cache(lua_State *pLS)
	{
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

		Sleep(1);

		uint64_t collectedGCMemSize = ((uint64_t)lua_gc(pLS, LUA_GCCOUNT, 0) << 10) + lua_gc(pLS, LUA_GCCOUNTB, 0);
		printf("Collected GC memory usage: [%I64d] Bytes\n", collectedGCMemSize);

		mc.End();

		system("pause");
	}

	void lua_gc_memory()
	{
		// Lua state Non-Cache
		{
			printf("Lua state Non-Cache Test Start ...\n");

			Util::MemoryComparator mc(__FUNCTION__);

			for (int i = 1; i <= 10; ++i) {
				
				system("cls");
				printf("Lua state Non-cache Test !!! - count:%d\n", i);

				lua_gc_non_cache();
			}

			mc.End();
		}
		system("pause");

		// Lua state Cache
		{
			printf("Lua state Cache Test Start ...\n");

			Util::MemoryComparator mc(__FUNCTION__);

			lua_State *pLS = luaL_newstate();
			if (nullptr == pLS) {
				std::cout << "Failed to assign LuaState !!!" << std::endl;
				return;
			}

			luaL_openlibs(pLS);

			for (int i = 1; i <= 50; ++i) {
				
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
		lua_gc_memory();
	}
}