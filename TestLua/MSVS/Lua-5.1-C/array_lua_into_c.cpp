#include "stdafx.h"
#include "Function.h"

namespace ArrayLuaIntoC
{
	void lua_array_load_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "lua_array.lua";

		// load the file containing the script we are going to run
		if (luaL_dofile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		Debug::DumpStack(pLS);

		const char *szArrayName = "LuaArray";

		// load array table
		lua_pushstring(pLS, szArrayName);
		Debug::DumpStack(pLS);
		lua_rawget(pLS, LUA_GLOBALSINDEX);
		Debug::DumpStack(pLS);

		int n = lua_gettop(pLS);
		if (0 >= n) {
			std::cout << "Failed to read from Table !!!, Empty stack !!!" << std::endl;

			// cleanup
			lua_close(pLS);
			return;
		}

		std::string debugInfo;

		debugInfo += szArrayName;
		debugInfo += " = {";

		// trace array table
		Debug::GetTableInfoAll(pLS, 1, OUT debugInfo);

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.

		debugInfo += " }";

		printf("Read from Array - ArrayName:%s\n", szArrayName);
		printf("%s\n", debugInfo.c_str());

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void lua_array_update_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "lua_array.lua";

		// load the file containing the script we are going to run
		if (luaL_dofile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		Debug::DumpStack(pLS);

		const char *szArrayName = "LuaArray";

		lua_pushstring(pLS, szArrayName);
		Debug::DumpStack(pLS);
		lua_rawget(pLS, LUA_GLOBALSINDEX);
		Debug::DumpStack(pLS);

		int n = lua_gettop(pLS);
		if (0 >= n) {
			std::cout << "Failed to read from Array Table !!!, Empty stack !!!" << std::endl;

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_rawgeti(pLS, -1, 1);	// get value of 1 key in array table
		Debug::DumpStack(pLS);

		int oldValue = lua_tointeger(pLS, -1);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		// change value in array table
		lua_pushnumber(pLS, 200);	// push 200 value in stack
		Debug::DumpStack(pLS);
		lua_rawseti(pLS, -2, 2);	// 2 key , 200 value set in array table
		Debug::DumpStack(pLS);

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.

		// load array table from global
		lua_pushstring(pLS, szArrayName);
		Debug::DumpStack(pLS);
		lua_rawget(pLS, LUA_GLOBALSINDEX);
		Debug::DumpStack(pLS);

		lua_rawgeti(pLS, -1, 2);	// get value of 2 key in array table
		Debug::DumpStack(pLS);

		int updatedValue = lua_tointeger(pLS, -1);

		printf( "OldValue:%d, NewValue:%d\n"
			  , oldValue, updatedValue );

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.
						
		lua_close(pLS);	// cleanup

		system("pause");
	}

	void Test()
	{
		lua_array_load_in_c();

		lua_array_update_in_c();
	}
}