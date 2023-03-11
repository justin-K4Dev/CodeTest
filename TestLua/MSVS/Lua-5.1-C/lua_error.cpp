#include "stdafx.h"
#include "Lua.h"

extern std::jmp_buf Lua::HandleExceptionJump;

namespace LuaError
{
	void lua_error_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Failed to assign LuaState !!!" << std::endl;
			return;
		}

		// load all lua standard libraries
		luaL_openlibs(pLS);

		char luaFilename[] = { "./lua_error.lua" };

		// run the script : luaL_loadfile() + lua_pcall() !!!
		if (luaL_dofile(pLS, luaFilename)) {
			Lua::Error(pLS, "Failed to dofile() !!! - FileName:%s", luaFilename);
		}

		lua_close(pLS);

		system("pause");
	}

	lua_State* myLuaState;
	lua_State* myLuaSandbox;
	int myErrHandler;
 
	// spell out type names
	std::string lua_typeof(int index)
	{
		switch (index)
		{
		case LUA_TNIL:            return "nil";
		case LUA_TNUMBER:         return "number";
		case LUA_TBOOLEAN:        return "boolean";
		case LUA_TSTRING:         return "string";
		case LUA_TTABLE:          return "table";
		case LUA_TFUNCTION:       return "function";
		case LUA_TUSERDATA:       return "userdata";
		case LUA_TTHREAD:         return "thread";
		case LUA_TLIGHTUSERDATA:  return "light userdata";
 
		default: return "unknown type";
		}
	}
 
	// this is the API function we expose to lua.
	int HAPI_echo(lua_State* L)
	{
		int args_from_lua = lua_gettop(L);
 
		//in this example, we'll take any number of args
		printf("HAPI_echo() called with %d arguments\n",
			   args_from_lua);
		for (int n = 1; n <= args_from_lua; ++n)
		{
			printf(" * arg %02d (%s):\t%s\n",
				   n,
				   lua_typeof(lua_type(L, n)).c_str(),
				   lua_tostring(L, n));
			//note: lua_tostring coerces stack value!
		}
 
		//return (123, "abc") to lua
		lua_pushnumber(L, 123);
		lua_pushstring(L, "abc");
		Debug::DumpStack(L);

		return 2; // 2 return values are on the stack
	}
 
	void InitLua(lua_State* &L)
	{
		//open new state
		L = luaL_newstate();
		luaL_openlibs(L);
 
		//register a very minimal API
		lua_register(L, "h_echo", HAPI_echo);

		Debug::DumpStack(L);
	}
 
	void HaltLua(lua_State* L)
	{
		lua_close(L);
	}
 
	bool LuaFuncExists(lua_State* L, std::string func)
	{
		//try to put the function on top of the stack
		lua_getglobal(L, func.c_str());
		Debug::DumpStack(L);

		//check that value on top of stack is not nil
		bool ret = !lua_isnil(L, -1);
 
		//get rid of the value we put on the stack
		lua_pop(L, 1);
		Debug::DumpStack(L);

		return ret;
	}
 
	std::string describe(int resultcode)
	{
		switch (resultcode)
		{
		case 0:
			return "Success";
		case LUA_ERRRUN:
			return "Runtime error";
		case LUA_ERRSYNTAX:
			return "Syntax error";
		case LUA_ERRERR:
			return "Error with error alert mechanism.";
		case LUA_ERRFILE:
			return "Couldn't open or read file";
		}

		return "";
	}
 
	// call a lua function.
	// you must specify the quantity of of params and returns.
	int CallLua(lua_State* L, std::string func,
				int num_params, int num_returns)
	{
		//on error, execute lua function debug.traceback
		// debug is a table, put it on the stack
		lua_getglobal(L, "debug");
		Debug::DumpStack(L);

		//-1 is the top of the stack
		lua_getfield(L, -1, "traceback");
		Debug::DumpStack(L);

		//traceback is on top, remove debug from 2nd spot
		lua_remove(L, -2);
		Debug::DumpStack(L);

		myErrHandler = lua_gettop(L);
		printf("lua's error handler at pos %d\n",
			   myErrHandler);
 
		//get the lua function and execute it
		lua_getglobal (L, func.c_str());
		Debug::DumpStack(L);

		int ret = lua_pcall(L, num_params, num_returns,
							myErrHandler);
		Debug::DumpStack(L);
		if (ret)
		{
			printf("\nLua call failed (%s): %s\n",
				   describe(ret).c_str(),
				   lua_tostring(myLuaState, -1));
		}
 
		//remove the error handler from the stack
		lua_pop(myLuaState, 1);
		Debug::DumpStack(L);

		return ret;
	}

	void lua_traceback_use()
	{
		std::string myfn   = "Init";
		std::string myfile = "./lua_traceback.lua";
 
		printf("initializing lua environment\n");
		InitLua(myLuaState);
 
		printf("function '%s' exists in lua? %d\n",
			   myfn.c_str(),
			   LuaFuncExists(myLuaState, myfn));
 
		printf("loading/executing lua file %s\n",
			   myfile.c_str());
		luaL_dofile(myLuaState, myfile.c_str());
		Debug::DumpStack(myLuaState);

		printf("function '%s' exists in lua? %d\n",
			   myfn.c_str(),
			   LuaFuncExists(myLuaState, myfn));
 
		printf("calling %s in %s\n",
			   myfn.c_str(), myfile.c_str());
 
		int res = CallLua(myLuaState, myfn, 0, 0);
		printf("returned from call to %s in %s\n",
			   myfn.c_str(), myfile.c_str());
 
		printf("destroying lua environment\n");
		HaltLua(myLuaState);

		system("pause");
	}

	void lua_exception_use()
	{
		try {
			lua_State *pLS = luaL_newstate();
			if (nullptr == pLS) {
				std::cout << "Failed to assign LuaState !!!" << std::endl;
				return;
			}

			// load all lua standard libraries
			luaL_openlibs(pLS);

			char luaFilename[] = { "./lua_error.lua" };

			// run the script : luaL_loadfile() + lua_pcall() !!!
			if (luaL_dofile(pLS, luaFilename)) {
				throw Lua::LuaError(pLS);
			}

			lua_close(pLS);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

		system("pause");
	}

	void lua_atpanic_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Failed to assign LuaState !!!" << std::endl;
			return;
		}

		// immediately install panic handler
		lua_atpanic(pLS, &Lua::HandleException);

		// load all lua standard libraries
		luaL_openlibs(pLS);

		// set exception jump position
		int except = setjmp(Lua::HandleExceptionJump);
		if (except != 0) {
			std::cout << "Called setjmp() exception handler !!!" << std::endl;

			// cleanup
			lua_close(pLS);
			return;
		}

		char luaFilename[] = { "./lua_error.lua" };

		// load the file containing the script we are going to run
		int result = luaL_loadfile(pLS, luaFilename);
		if (0 != result) {
			Lua::ErrorReport(pLS, result);
		}

		// ask Lua to run our little script
		lua_call(pLS, 0, 0);

		lua_close(pLS);

		system("pause");
	}


	void Test()
	{
		//lua_error_use();

		//lua_traceback_use();

		//lua_exception_use();

		//lua_atpanic_use();
	}
}