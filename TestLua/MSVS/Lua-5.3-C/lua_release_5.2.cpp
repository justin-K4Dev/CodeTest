#include "stdafx.h"
#include "Debug.h"

namespace LuaRelease52
{
	void LUA_GLOBALSINDEX_remove_on_array()
	{
		// lua_State *pLS = lua_open(); // lua_open() removed in Lua 5.2
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		char luaCode[] = { "LuaArray = { 10, 88, 50 }" };

		luaL_dostring(pLS, luaCode);

		const char *szArrayName = "LuaArray";

		// load array table
		lua_pushstring(pLS, szArrayName);
		Debug::DumpStack(pLS);
		// lua_rawget(pLS, LUA_GLOBALSINDEX); // LUA_GLOBALSINDEX removed in Lua 5.2
		lua_rawgeti(pLS, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS); // instead get global environment table from registry
		// or call lua_pushglobaltable()
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
		Debug::GetTableInfoAll(pLS, LUA_RIDX_GLOBALS, OUT debugInfo);

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.

		debugInfo += " }";

		printf("Read from Array - ArrayName:%s\n", szArrayName);
		printf("%s\n", debugInfo.c_str());

		lua_close(pLS);

		system("pause");
	}

	void LUA_GLOBALSINDEX_remove_on_variable()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		lua_pushstring(pLS, "global");
		Debug::DumpStack(pLS);
		lua_setglobal(pLS, "globalstring");
		Debug::DumpStack(pLS);

		lua_getglobal(pLS, "globalstring");
		Debug::DumpStack(pLS);
		std::cout << lua_tostring(pLS, -1) << std::endl;
		lua_pop(pLS, 1);

		lua_pushglobaltable(pLS);
		Debug::DumpStack(pLS);

		lua_newtable(pLS);
		lua_rawseti(pLS, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
		Debug::DumpStack(pLS);
		lua_getglobal(pLS, "globalstring");
		Debug::DumpStack(pLS);

		if (lua_isstring(pLS, -1)) {
			std::cout << "string " << lua_tostring(pLS, -1) << std::endl;
		}
		else {
			std::cout << "type id " << lua_type(pLS, -1) << std::endl;
			std::cout << "is nil " << (lua_type(pLS, -1) == LUA_TNIL) << std::endl;
		}

		lua_pop(pLS, 1);

		lua_pushstring(pLS, "inner global");
		Debug::DumpStack(pLS);
		lua_setglobal(pLS, "globalstring");
		Debug::DumpStack(pLS);
		lua_getglobal(pLS, "globalstring");
		Debug::DumpStack(pLS);
		std::cout << "inner global: " << lua_tostring(pLS, -1) << std::endl;
		lua_pop(pLS, 1);

		lua_pushglobaltable(pLS);
		Debug::DumpStack(pLS);
		lua_pushvalue(pLS, -2);
		Debug::DumpStack(pLS);
		lua_remove(pLS, -3);
		Debug::DumpStack(pLS);
		lua_rawseti(pLS, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
		Debug::DumpStack(pLS);

		lua_getglobal(pLS, "globalstring");
		Debug::DumpStack(pLS);
		std::cout << "outer global: " << lua_tostring(pLS, -1) << std::endl;
		lua_pop(pLS, 1);
		lua_getfield(pLS, -1, "globalstring");
		Debug::DumpStack(pLS);
		std::cout << "inner global: " << lua_tostring(pLS, -1) << std::endl;
		lua_pop(pLS, 2);

		lua_close(pLS);

		system("pause");
	}

	void LUA_ENVIRONINDEX_remove_on_global()
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
		//lua_setfenv(pLS, -2); // lua_setfenv() removed in Lua 5.2
		lua_setupvalue(pLS, -2, 1); // instead lua_setupvalue()
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

	struct Object
	{
		static const char* name;
	};
	const char* Object::name = "justin";

	void LUA_ENVIRONINDEX_remove_on_lightuserdata()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		Object obj;

		lua_pushlightuserdata(pLS, (void*)&Object::name);
		lua_pushstring(pLS, "3.141592");
		// lua_settable(pLS, LUA_ENVIRONINDEX); // LUA_ENVIRONINDEX removed in Lua 5.2
		lua_settable(pLS, LUA_REGISTRYINDEX);	// instead set environment to registry table

		lua_pushlightuserdata(pLS, (void*)&obj.name);
		// lua_gettable(pLS, LUA_ENVIRONINDEX); // LUA_ENVIRONINDEX removed in Lua 5.2
		lua_gettable(pLS, LUA_REGISTRYINDEX);

		const char* name = lua_tostring(pLS, -1);
		printf("Object name is %s\n", name);

		lua_close(pLS);

		system("pause");
	}

	static int setValue(lua_State *pLS)
	{	// Internal name of func
		int argValue = lua_tointeger(pLS, -1);	// Get the single integer arg
		printf("setValue() : argValue=%d\n", argValue);

		lua_pushinteger(pLS, argValue * argValue);	// Push the return
		Debug::DumpStack(pLS);

		return 1;						// One return value
	};

	static luaL_Reg funcList[] = {
		{ "setValue", &setValue }
		,{ NULL, NULL }
	};

	static int luaopen_mylib(lua_State *pLS)
	{
		// create a new library table on top of the stack using luaL_newlibtable()
		// and register all our functions there with luaL_setfuncs()
		// or luaL_newlib() macro takes a list of C functions with their respective names
		// and registers all of them inside a new table

		// lua_newtable(pLS);
		luaL_newlibtable(pLS, funcList); // new function in Lua 5.2
		// lua_replace(pLS, LUA_ENVIRONINDEX); // LUA_ENVIRONINDEX removed in Lua 5.2
		Debug::DumpStack(pLS);

		//luaL_register(pLS, "myFuncList", funcList); // luaL_register removed in Lua 5.2
		luaL_setfuncs(pLS, funcList, 0);
		Debug::DumpStack(pLS);

		// or luaL_newlib(pLS, funcList); // luaL_newlibtable() + luaL_setfuncs() macro !!!
		// Debug::DumpStack(pLS);

		return 1;
	}

	void luaL_register_remove()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		lua_getglobal(pLS, "package");
		lua_getfield(pLS, -1, "preload");
		lua_pushcfunction(pLS, luaopen_mylib);
		lua_setfield(pLS, -2, "mylib");
		lua_pop(pLS, 2); // discard package and package.preload

		const char* luaCode = "mylib = require(\"mylib\")\n"
							  "mylib.setValue(100)\n";

		luaL_loadstring(pLS, luaCode);
		Debug::DumpStack(pLS);

		lua_pcall(pLS, 0, 0, 0);
		Debug::DumpStack(pLS);

		lua_close(pLS);

		system("pause");
	}


	const static char *objTypeName = "objTypeName";

	void checkObj(lua_State *L, int i)
	{
		luaL_checkudata(L, i, objTypeName);
	}

	int makeObj(lua_State *L)
	{
		printf("In makeObj\n");
		lua_newuserdata(L, sizeof(int*));
		luaL_setmetatable(L, objTypeName);

		return 1;
	}

	int gcObj(lua_State *L)
	{
		printf("In gcObj\n");

		return 0;
	}
	
	int methodObj(lua_State *L)
	{
		printf("In methodObj\n");
		checkObj(L, 1);
		return 0;
	}

	int luaopen_myLib(lua_State *L)
	{
		static const luaL_Reg objLib[] = {
			{ "method", &methodObj },
			{ NULL, NULL }
		};

		static const luaL_Reg myLib[] = {
			{ "makeObj", &makeObj },
			{ NULL, NULL }
		};

		luaL_newlib(L, myLib);

		// stack: myLib
		luaL_newmetatable(L, objTypeName); // Stack: myLib meta
		luaL_newlib(L, objLib);
		lua_setfield(L, -2, "__index"); // Stack: myLib meta

		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, gcObj); // Stack: myLib meta "__gc" fptr
		lua_settable(L, -3); // Stack: myLib meta
		lua_pop(L, 1); // Stack: myLib

		return 1;
	}

	void luaL_requiref_add_on_module()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		// The module/luaL_register functions are deprecated
		// and replaced by luaL_newlib and luaL_setfuncs.
		// There is also a new function luaL_requiref.
		luaL_requiref(pLS, "myLib", &luaopen_myLib, 1);
		lua_pop(pLS, 1); // requiref leaves the library table on the stack

		printf(" stack top: %d\n", lua_gettop(pLS));

		const char* luaCode = "function foo()\n"
							  "    local obj = myLib.makeObj()\n"
							  "    obj:method()\n"
							  "end\n"
							  "foo()\n";

		luaL_loadstring(pLS, luaCode);
		Debug::DumpStack(pLS);

		lua_pcall(pLS, 0, 0, 0);
		Debug::DumpStack(pLS);

		lua_close(pLS);

		system("pause");
	}


	void Test()
	{
		//LUA_GLOBALSINDEX_remove_on_array();

		//LUA_GLOBALSINDEX_remove_on_variable();

		//LUA_ENVIRONINDEX_remove_on_global();

		//LUA_ENVIRONINDEX_remove_on_lightuserdata();

		//luaL_register_remove();

		//luaL_requiref_add_on_module();

		//lua_yeildk_add_with_yield();
	}
}