#include "stdafx.h"
#include "Function.h"

namespace VariableCIntoLua
{
	void access_c_variable_in_lua()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "access_c_variable_in_lua.lua";

		// Load the file containing the script we are going to run
		if (luaL_loadfile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}

		int result;

		// add variables from C into lua
		{
			lua_pushnumber(pLS, 30);
			Debug::DumpStack(pLS);
			lua_setglobal(pLS, "cpp_value");
			Debug::DumpStack(pLS);
		}

		// add table from C into lua
		{
			lua_newtable(pLS); // We will pass a table
			Debug::DumpStack(pLS);

			for (int i = 1; i <= 5; i++) {
				lua_pushnumber(pLS, i);		// Push the table index
				Debug::DumpStack(pLS);
				lua_pushnumber(pLS, i * 2); // Push the cell value
				Debug::DumpStack(pLS);
				lua_rawset(pLS, -3);		// Stores the pair in the table
				Debug::DumpStack(pLS);
			}

			lua_setglobal(pLS, "foo");
			Debug::DumpStack(pLS);
		}

		// Ask Lua to run our little script
		result = lua_pcall(pLS, 0, LUA_MULTRET, 0);
		Debug::DumpStack(pLS);
		if (result) {
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		// Get the returned value at the top of the stack (index -1)
		int sum = lua_tonumber(pLS, -1);

		printf("Script returned: %d\n", sum);

		// Take the returned value out of the stack
		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		/*
		output:
			The table the script received has:
			1       2
			2       4
			3       6
			4       8
			5       10
			Returning data back to C
			Script returned: 30
		*/

		lua_getglobal(pLS, "lua_value");
		Debug::DumpStack(pLS);

		sum = lua_tonumber(pLS, -1);
		printf("lua_value: %d\n", sum);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		// cleanup
		lua_close(pLS);

		system("pause");
	}


	void Test()
	{
		access_c_variable_in_lua();
	}
}