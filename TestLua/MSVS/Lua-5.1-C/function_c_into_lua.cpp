#include "stdafx.h"
#include "Function.h"

namespace FunctionCIntoLua
{
	// Lua Glue function

	static int cf_average(lua_State *pLS)
	{
		// get number of arguments
		int n = lua_gettop(pLS);
		double sum = 0;
		int i;

		// loop through each argument
		for (i = 1; i <= n; i++) {
			// total the arguments
			sum += lua_tonumber(pLS, i);
		}

		// push the average
		lua_pushnumber(pLS, sum / n);

		// push the sum
		lua_pushnumber(pLS, sum);

		// return the number of results
		return 2;
	}

	void call_c_function_in_lua()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "call_c_function_in_lua.lua";

		// register cpp function, same api lua_pushcfunction(pLS, cf_average)
		lua_register(pLS, "cf_average", cf_average);
		Debug::DumpStack(pLS);

		// run the script
		if (luaL_dofile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_getglobal(pLS, "avg");
		Debug::DumpStack(pLS);

		int avg = lua_tonumber(pLS, -1);
		printf("avg: %d\n", avg);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		lua_getglobal(pLS, "sum");
		Debug::DumpStack(pLS);

		int sum = lua_tonumber(pLS, -1);
		printf("sum: %d\n", sum);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		call_c_function_in_lua();
	}
}