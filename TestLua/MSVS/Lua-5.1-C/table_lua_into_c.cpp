#include "stdafx.h"
#include "Function.h"

namespace TableLuaIntoC
{
	void lua_table_load_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "lua_table.lua";

		// Load the file containing the script we are going to run
		if (luaL_dofile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		Debug::DumpStack(pLS);

		const char *szTablename = "LuaTable";

		lua_getglobal(pLS, szTablename);
		Debug::DumpStack(pLS);

		int n = lua_gettop(pLS);
		if (0 >= n) {
			std::cout << "Failed to read from Table !!!, Empty stack !!!" << std::endl;
			
			// cleanup
			lua_close(pLS);
			return;
		}

		std::string debugInfo;

		debugInfo += szTablename;
		debugInfo += " = {";

		Debug::GetTableInfoAll(pLS, 1, OUT debugInfo);

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.

		debugInfo += " }";

		printf("Read from table - TableName:%s\n", szTablename);
		printf("%s\n", debugInfo.c_str());

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void lua_table_update_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		const char *szLuaFilename = "lua_table.lua";

		// Load the file containing the script we are going to run
		if (luaL_dofile(pLS, szLuaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", szLuaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		Debug::DumpStack(pLS);

		const char *szTablename = "LuaTable";

		lua_getglobal(pLS, szTablename); // get table to stack from global
		Debug::DumpStack(pLS);

		int n = lua_gettop(pLS);
		if (0 >= n) {
			std::cout << "Failed to read from Table !!!, Empty stack !!!" << std::endl;

			// cleanup
			lua_close(pLS);
			return;
		}

		const char *szSubTablename = "LuaObject-1";

		lua_pushstring(pLS, szSubTablename); // push key of table in stack
		Debug::DumpStack(pLS);
		lua_gettable(pLS, -2); // get table of key from table
		Debug::DumpStack(pLS);

		const char *key = "Amount";
		int newValue = 10001;

		lua_pushstring(pLS, key); // push "Amount" key of table in stack
		Debug::DumpStack(pLS);
		lua_gettable(pLS, -2); // get value of "Amount" key of table
		Debug::DumpStack(pLS);

		int oldValue = lua_tointeger(pLS, -1);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		lua_pushstring(pLS, key); // push "Amount" key of table in stack
		Debug::DumpStack(pLS);
		lua_pushnumber(pLS, newValue); // push 10001 value of "Amount" key in stack
		Debug::DumpStack(pLS);
		lua_settable(pLS, -3); // "Amount" key, 10001 value set in table
		Debug::DumpStack(pLS);

		lua_settop(pLS, 0);	// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS); // Remove all 0 or more nodes.

		lua_getglobal(pLS, szTablename); // get table to stack from global
		Debug::DumpStack(pLS);

		lua_pushstring(pLS, szSubTablename); // push key of table in stack
		Debug::DumpStack(pLS);
		lua_gettable(pLS, -2); // get table of key from table
		Debug::DumpStack(pLS);

		lua_pushstring(pLS, key); // push "Amount" key of table in stack
		lua_gettable(pLS, -2); // get value of "Amount" key in table
		Debug::DumpStack(pLS);

		int updatedValue = lua_tointeger(pLS, -1);
		printf( "OldValue:%d, NewValue:%d\n"
			  , oldValue, updatedValue );

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.
			
		lua_close(pLS); // cleanup

		system("pause");
	}

	void Test()
	{
		lua_table_load_in_c();

		lua_table_update_in_c();
	}
}