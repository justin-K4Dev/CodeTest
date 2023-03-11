#include "stdafx.h"


namespace LuaThread
{
	void lua_thread_creation()
	{
		try {
			lua_State *pLS = luaL_newstate();
			if (nullptr == pLS) {
				std::cout << "Lua state assign failed" << std::endl;
				return;
			}

			luaL_openlibs(pLS);

			lua_State *pThread = lua_newthread(pLS);
			Debug::DumpStack(pLS);
			Debug::DumpStack(pThread);

			printf("%d\n", lua_gettop(pThread));
			printf("%s\n", lua_typename(pThread, -1));

			lua_pop(pLS, -1); // set thread garbage state !!!
			Debug::DumpStack(pLS);
			// thread state may be collected in the GC and an exception may occur !!!
			lua_pushstring(pThread, "justin");
			Debug::DumpStack(pThread);

			lua_close(pLS);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

		system("pause");
	}

	void lua_thread_stack_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		auto func = [](lua_State *pLS) {
			
			// get number of arguments
			int n = lua_gettop(pLS);
			double sum = 0;
			int i;

			// loop through each argument
			for (i = 1; i <= n; i++) {
				// total the arguments
				sum += lua_tonumber(pLS, i);
			}

			// push the sum
			lua_pushnumber(pLS, sum);

			// return the number of results
			return 1;
		};

		lua_State *pThread = lua_newthread(pLS);
		Debug::DumpStack(pLS);

		lua_register(pThread, "func", func);
		Debug::DumpStack(pThread);
		
		lua_getglobal(pThread, "func");
		Debug::DumpStack(pThread);
		lua_pushinteger(pThread, 100);
		Debug::DumpStack(pThread);

		lua_call(pThread, 1, 1);
		Debug::DumpStack(pThread);

		lua_xmove(pThread, pLS, 1); // move 100 value pThread stack -> pLS stack !!!
		Debug::DumpStack(pThread);
		Debug::DumpStack(pLS);

		lua_close(pLS);

		system("pause");
	}


	#define STACK_DUMP(L, Name) stack_dump(L, Name)

	bool running;

	void error(lua_State *L, const char *fmt, ...)
	{
		va_list argp;
		va_start(argp, fmt);
		vfprintf(stderr, fmt, argp);
		va_end(argp);
		lua_close(L);
		exit(EXIT_FAILURE);
	}

	static void stack_dump(lua_State *pLS, const char *stackname)
	{
		int i;
		int top = lua_gettop(pLS);
		printf("--------------- %s STACK ---------------\n", stackname);
		for (i = top; i >= 1; i--) {
			int t = lua_type(pLS, i);
			printf("[%2d - %8s] : ", i, lua_typename(pLS, t));
			switch (t) {
			case LUA_TSTRING:
				printf("%s", lua_tostring(pLS, i));
				break;
			case LUA_TBOOLEAN:
				printf(lua_toboolean(pLS, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				printf("%g", lua_tonumber(pLS, i));
				break;
			case LUA_TNIL:
				printf("nil");
				break;
			case LUA_TNONE:
				printf("none");
				break;
			case LUA_TFUNCTION:
				printf("<function %p>", lua_topointer(pLS, i));
				break;
			case LUA_TTABLE:
				printf("<table %p>", lua_topointer(pLS, i));
				break;
			case LUA_TTHREAD:
				printf("<thread %p>", lua_topointer(pLS, i));
				break;
			case LUA_TUSERDATA:
				printf("<userdata %p>", lua_topointer(pLS, i));
				break;
			case LUA_TLIGHTUSERDATA:
				printf("<lightuserdata %p>", lua_topointer(pLS, i));
				break;
			default:
				printf("unknown %s", lua_typename(pLS, t));
				break;
			}
			printf("\n");
		}
		printf("--------------- %s STACK ---------------\n", stackname);
	}

	static int lua_cb(lua_State *pLS)
	{
		printf("called lua_cb\n");
		return 0;
	}

	static int lua_mynext(lua_State *pLS)
	{
		printf("called lua_mynext\n");
		lua_pushnumber(pLS, 1);
		Debug::DumpStack(pLS);
		lua_pushnumber(pLS, 2);
		Debug::DumpStack(pLS);
		lua_pushcfunction(pLS, lua_cb);
		return lua_yield(pLS, 3);
	}

	void lua_thread_resume_yield_use()
	{
		int status = 0;
		int result = 0;

		lua_State *pLS = luaL_newstate();
		
		luaL_openlibs(pLS);

		status = luaL_loadfile(pLS, "lua_thread_start.lua"); /* L[ function ] */
		if (status) {
			fprintf(stderr, "could not load start.lua: %s\n", lua_tostring(pLS, -1));
			exit(1);
		}

		result = lua_pcall(pLS, 0, LUA_MULTRET, 0); /* L[ ] */
		if (result) {
			fprintf(stderr, "failed to run start.lua script: %s\n", lua_tostring(pLS, -1));
			exit(1);
		}

		lua_State *pThread = lua_newthread(pLS);
		Debug::DumpStack(pLS);
		luaL_openlibs(pThread);
		Debug::DumpStack(pThread);
		lua_register(pThread, "next", lua_mynext);
		Debug::DumpStack(pThread);

		luaL_dofile(pThread, "lua_thread_proc.lua");
		Debug::DumpStack(pThread);
		lua_getglobal(pThread, "step");
		Debug::DumpStack(pThread);

		do {
			lua_pushnumber(pThread, 1);
			lua_pushstring(pThread, "hello");
			Debug::DumpStack(pThread);
			status = lua_resume(pThread, 2);
			Debug::DumpStack(pThread);
			printf("lua_resume: %d\n", status);
			if (status == LUA_YIELD) {
				lua_CFunction f = lua_tocfunction(pThread, -1);
				f(pThread);
				Debug::DumpStack(pThread);
			}
		} while (status == LUA_YIELD);

		status = luaL_loadfile(pLS, "lua_thread_end.lua");
		Debug::DumpStack(pLS);
		if (status) {
			fprintf(stderr, "could not load end.lua: %s\n", lua_tostring(pLS, -1));
			exit(1);
		}

		result = lua_pcall(pLS, 0, LUA_MULTRET, 0);
		Debug::DumpStack(pLS);
		if (result) {
			fprintf(stderr, "failed to run end.lua script: %s\n", lua_tostring(pLS, -1));
			exit(1);
		}

		lua_close(pLS);

		system("pause");
	}


	void lua_thread_coroutine_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		std::string luaCode;

		luaCode += "function func1(x)\n";
		luaCode += "    coroutine.yield(10, x)\n";
		luaCode += "end\n";
		luaCode += "function func2(x)\n";
		luaCode += "    func1(x + 1)\n";
		luaCode += "    return 3\n";
		luaCode += "end\n";

		int result = luaL_loadbuffer(pLS, luaCode.c_str(), luaCode.size(), "LuaCode");
		Debug::DumpStack(pLS);
		if (0 != result) {
			printf("Failed to load script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		lua_State *pThread = lua_newthread(pLS);

		lua_getglobal(pThread, "func1");
		lua_pushinteger(pThread, 100);
		lua_resume(pThread, 1);
		Debug::DumpStack(pThread);

		printf("%d\n", lua_gettop(pThread));
		printf("%td\n", lua_tointeger(pThread, 1));
		printf("%td\n", lua_tointeger(pThread, 2));

		lua_resume(pThread, 0);
		Debug::DumpStack(pThread);

		printf("%d\n", lua_gettop(pThread));
		printf("%td\n", lua_tointeger(pThread, 1));

		lua_pop(pLS, -1); // set thread garbage state !!!
		Debug::DumpStack(pThread);

		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		lua_thread_creation();

		lua_thread_stack_use();

		lua_thread_resume_yield_use();

		lua_thread_coroutine_use();
	}
}