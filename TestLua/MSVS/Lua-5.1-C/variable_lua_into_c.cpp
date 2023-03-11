#include "stdafx.h"
#include "Function.h"

namespace VariableLuaIntoC
{
	void access_lua_variable_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		char luaFilename[] = { "access_lua_variable_in_c.lua" };

		// run the script
		if (luaL_dofile(pLS, luaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}

		const char *szLuaVariableName = "value";
		lua_pushstring(pLS, szLuaVariableName);
		Debug::DumpStack(pLS);

		// similar to lua_gettable(), but does a raw access (i.e., without metamethods).
		lua_rawget(pLS, LUA_GLOBALSINDEX);
		Debug::DumpStack(pLS);

		if (!lua_isnumber(pLS, -1)) {
			std::cout << "Not number !!!" << std::endl;

			// cleanup
			lua_close(pLS);
			return;
		}

		int return_value = lua_tointeger(pLS, -1);
		printf( "Accessed lua variable - VariableName:%s, Value:%d\n"
			  , szLuaVariableName, return_value );

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void lua_environment_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);
		Debug::DumpStack(pLS);

		lua_newtable(pLS);
		Debug::DumpStack(pLS);

		const char* luaCode = "a = 10\n"
							  "b = 20\n"
							  "c = \"sto\"";

		luaL_loadstring(pLS, luaCode);
		Debug::DumpStack(pLS);

		lua_pushvalue(pLS, -2);
		Debug::DumpStack(pLS); 
		lua_setfenv(pLS, -2);
		Debug::DumpStack(pLS);
		lua_pcall(pLS, 0, 0, 0);
		Debug::DumpStack(pLS);

		lua_getfield(pLS, -1, "a");
		Debug::DumpStack(pLS);
		printf("a = %f\n", lua_tonumber(pLS, -1));
		lua_pop(pLS, 1);

		lua_getfield(pLS, -1, "a");
		Debug::DumpStack(pLS);
		printf("b = %f\n", lua_tonumber(pLS, -1));
		lua_pop(pLS, 1);

		lua_getfield(pLS, -1, "c");
		Debug::DumpStack(pLS);
		printf("c = %s\n", lua_tostring(pLS, -1));
		lua_pop(pLS, 1);

		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		access_lua_variable_in_c();

		lua_environment_in_c();
	}
}