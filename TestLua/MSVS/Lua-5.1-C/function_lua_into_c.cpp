#include "stdafx.h"
#include "Function.h"

namespace FunctionLuaIntoC
{
	// Lua API function

	void call_lua_function_in_c()
	{
		lua_State *pLS = luaL_newstate();

		if (nullptr == pLS) {
			std::cout << "Lua state (environment) assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "call_lua_function_in_c.lua";

		// run the script
		if (luaL_dofile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_getglobal(pLS, "lua_function");
		Debug::DumpStack(pLS);
		lua_pushnumber(pLS, 5);
		Debug::DumpStack(pLS);
		lua_pushnumber(pLS, 100);
		Debug::DumpStack(pLS);

		int result = lua_pcall(pLS, 2, 1, 0);
		Debug::DumpStack(pLS);
		if (0 != result) {
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		int sum = lua_tonumber(pLS, -1);
		printf("Script returned: %d\n", sum);

		// cleanup
		lua_close(pLS);

		system("pause");
	}


	void Test()
	{
		call_lua_function_in_c();
	}
}