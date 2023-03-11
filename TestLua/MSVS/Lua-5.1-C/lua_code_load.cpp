#include "stdafx.h"
#include "Function.h"

namespace LuaCodeLoad
{
	void read_table_by_lua_raw_api(lua_State *pLS)
	{
		char* szTableName = "object";
		lua_getglobal(pLS, szTableName);
		Debug::DumpStack(pLS);

		if (!lua_istable(pLS, -1))
		{
			printf("Not table !!! - TableName:%s\n", szTableName);
			return;
		}

		char* szSubTableName;

		szSubTableName = "name";
		// push key name of field into stack
		lua_pushstring(pLS, szSubTableName);
		lua_rawget(pLS, 1); // this functions use raw operations.
		                    // this is faster and, anyway,
		                    // tables used as arrays seldom use metamethods.
		Debug::DumpStack(pLS);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		szSubTableName = "tid";
		// push key name of field into stack
		lua_pushstring(pLS, szSubTableName);
		lua_rawget(pLS, 1);
		Debug::DumpStack(pLS);

		lua_pop(pLS, 1);
		Debug::DumpStack(pLS);

		szSubTableName = "slot";
		// push key name of field into stack
		lua_pushstring(pLS, szSubTableName);
		lua_rawget(pLS, 1);
		Debug::DumpStack(pLS);

		szSubTableName = "slot_type";
		lua_getfield(pLS, 2, szSubTableName);
		Debug::DumpStack(pLS);

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.
	}

	void call_lua_function(lua_State *pLS, const char* functionName)
	{
		// load the Sum function from global
		lua_getglobal(pLS, functionName);
		Debug::DumpStack(pLS);
		/*
			01 or -1 | function	| 0x00000000025eb40
		*/

		if (true != lua_isfunction(pLS, -1))
		{
			printf("Not function !!! - FunctionName:%s\n", functionName);
			return;
		}

		// push function arguments into stack
		lua_pushnumber(pLS, 5.0);
		Debug::DumpStack(pLS);
		/*
			02 or -1 | number	| 5.000000
			01 or -2 | function	| 0x00000000025eb40
		*/
			
		lua_pushnumber(pLS, 6.0);
		Debug::DumpStack(pLS);
		/*
			03 or -1 | number	| 6.000000
			02 or -2 | number	| 5.000000
			01 or -3 | function	| 0x00000000025eb40
		*/

		// Both nargs and nresults have the same meaning as in lua_call.
		// If there are no errors during the call, lua_pcall behaves exactly like lua_call.
		// However, if there is any error, lua_pcall catches it,
		// pushes a single value on the stack (the error message),
		// and returns an error code. Like lua_call, lua_pcall always removes the function and its arguments from the stack.
		int result = lua_pcall(pLS, 2, 1, 0); // Calls a function in protected mode.

		Debug::DumpStack(pLS);
		if (0 != result) {
			// LUA_ERRRUN or LUA_ERRNUM or LUA_ERRERR !!!
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));
			return;
		}
		/*
			01 or -1 | number	| 11.000000
		*/

		double sum_val = 0.0;
		if (!lua_isnil(pLS, -1))
		{
			sum_val = lua_tonumber(pLS, -1);
			Debug::DumpStack(pLS);
			/*
				01 or -1 | number	| 11.000000
			*/

			lua_pop(pLS, 1);
			Debug::DumpStack(pLS);
			/*
				empty stack
			*/
		}

		printf("sum = %lf\n", sum_val);
		/*
			sum = 11.000000
		*/

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.
	}

	void lua_code_load()
	{
		// initialization
		lua_State *pLS = lua_open();
		if (nullptr == pLS) {
			std::cout << "Failed to assign LuaState !!!" << std::endl;
			return;
		}

		// load all lua standard libraries
		luaL_openlibs(pLS);

		// execute script
		std::string luaCode;

		luaCode += "object = {";
		luaCode += "    name = 'Player'";
		luaCode += "  , tid = 1";
		luaCode += "  , slot = {";
		luaCode += "        slot_type = 'equip'";
		luaCode += "      , max_count = 10";
		luaCode += "    }";
		luaCode += "  , item_list = {";
		luaCode += "        itme_1 = {";
		luaCode += "            name = 'cloth'";
		luaCode += "          , tid = 100";
		luaCode += "        }";
		luaCode += "      , item_2 = {";
		luaCode += "            name = 'weapon'";
		luaCode += "          , tid = 1000";
		luaCode += "        }";
		luaCode += "     }";
		luaCode += "}";
		luaCode += "function sum( a, b )\n";
		luaCode += "    return a + b\n";
		luaCode += "end\n"; // a function that returns sum of two
		
		int result = luaL_loadbuffer(pLS, luaCode.c_str(), luaCode.size(), "LuaCode");
		Debug::DumpStack(pLS);
		/*
			01 or -1 | function	| 0x00000000025ead0
		*/
		if (0 != result) {
			printf("Failed to load script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		result = lua_pcall(pLS, 0, 0, 0);
		Debug::DumpStack(pLS);
		if (0 != result) {
			// LUA_ERRRUN or LUA_ERRNUM or LUA_ERRERR !!!
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}
		/*
			empty stack
		*/

		// read table from lua data
		{
			Debug::DumpTableInfoAll(pLS, "object");
		}

		// read table by lua_rawget() from lua data
		{
			read_table_by_lua_raw_api(pLS);
		}

		// call lua function
		{
			call_lua_function(pLS, "sum");
		}

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void lua_file_load()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		char luaFilename[] = { "lua_table.lua" };

		// run the script : luaL_loadfile() + lua_pcall() !!!
		if (luaL_dofile(pLS, luaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		
		// read table from lua data
		{
			Debug::DumpTableInfoAll(pLS, "LuaTable");
		}

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void lua_execute()
	{
		system("pause");
	}


	void Test()
	{
		lua_code_load();

		lua_file_load();

		lua_execute();
	}
}