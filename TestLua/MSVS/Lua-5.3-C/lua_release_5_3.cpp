#include "stdafx.h"
#include "Debug.h"

namespace LuaRelease53
{
	struct GeneratorState
	{
		int a;
		int b;
	};

	int nextFib(lua_State* L, int status, lua_KContext ctx)
	{
		GeneratorState* state = (GeneratorState*)ctx;
		int c = state->a + state->b;
		if (c > 1000000000) {
			return 0;
		}
		state->a = state->b;
		state->b = c;
		lua_pushinteger(L, state->a);
		return lua_yieldk(L, 1, (lua_KContext)state, nextFib);
	}

	int genFib(lua_State* L) {
		GeneratorState* state = static_cast<GeneratorState*>(lua_newuserdata(L, sizeof(GeneratorState)));
		state->a = 0;
		state->b = 1;
		lua_pushinteger(L, state->a);
		return lua_yieldk(L, 1, (lua_KContext)state, nextFib);
	}

	int luaopen_fib(lua_State* L) {
		lua_pushcfunction(L, genFib);
		return 1;
	}

	void lua_yeildk_add_with_yield()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		lua_getglobal(pLS, "package");
		lua_getfield(pLS, -1, "preload");
		lua_pushcfunction(pLS, luaopen_fib);
		lua_setfield(pLS, -2, "fib");
		lua_pop(pLS, 2); // discard package and package.preload

		lua_State *pThread = lua_newthread(pLS);

		luaL_dofile(pThread, "./lua_yeildk_in_c.lua");
		Debug::DumpStack(pThread);

		lua_close(pLS);

		system("pause");
	}


	void Test()
	{
		lua_yeildk_add_with_yield();
	}
}