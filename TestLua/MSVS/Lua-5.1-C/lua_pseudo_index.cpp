#include "stdafx.h"



namespace LuaPseudoIndex
{
	void lua_registry_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);
		
		printf("LUA_REGISTRYINDEX: %d\n", LUA_REGISTRYINDEX);

		lua_pushstring(pLS, "x");
		lua_gettable(pLS, LUA_REGISTRYINDEX);
		Debug::DumpStack(pLS);

		lua_pushstring(pLS, "x");
		lua_pushnumber(pLS, 10);
		lua_settable(pLS, LUA_REGISTRYINDEX);
		Debug::DumpStack(pLS);

		lua_pushstring(pLS, "x");
		lua_gettable(pLS, LUA_REGISTRYINDEX);
		Debug::DumpStack(pLS);
		printf("%s\n", lua_typename(pLS, lua_type(pLS, -1)));
		printf("%d\n", (int)lua_tonumber(pLS, -1));

		lua_close(pLS);
		
		system("pause");
	}


	// this keeps our Lua reference to the Lua function
	int callbackRef = 0;

	// calls our Lua callback function and resets the callback reference
	void call_callback(lua_State *pLS)
	{
		// push the callback onto the stack using the Lua reference we stored in the registry
		lua_rawgeti(pLS, LUA_REGISTRYINDEX, callbackRef);

		// duplicate the value on the stack
		// NOTE: This is unnecessary, but it shows how you keep the callback for later
		lua_pushvalue(pLS, 1);

		// call the callback
		// NOTE: This is using the one we duplicated with lua_pushvalue
		if (0 != lua_pcall(pLS, 0, 0, 0)) {
			printf("Failed to call call_callback() !!!\n %s\n", lua_tostring(pLS, -1));
			return;
		}

		// get a new reference to the Lua function and store it again
		// NOTE: This is only used in conjunction with the lua_pushvalue
		// above and can be removed if you remove that
		callbackRef = luaL_ref(pLS, LUA_REGISTRYINDEX);
	}


	void lua_registry_ref_in_c()
	{
		// set up Lua
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		auto callback = [](lua_State *pLS) {
			printf("called callback !!!\n");
			callbackRef = luaL_ref(pLS, LUA_REGISTRYINDEX);
			Debug::DumpStack(pLS);
			return 0;
		};

		lua_register(pLS, "callback", callback);
		Debug::DumpStack(pLS);

		lua_getglobal(pLS, "callback");
		Debug::DumpStack(pLS);

		int result = lua_pcall(pLS, 0, 0, 0);
		Debug::DumpStack(pLS);
		if (0 != result) {
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		// call callback()
		call_callback(pLS);

		// call callback() again if you want (because we restored the Lua function reference)
		call_callback(pLS);

		// remove the reference to the callback
		// NOTE: This is also unnecessary if you didn't re-add the function to the registry
		luaL_unref(pLS, LUA_REGISTRYINDEX, callbackRef);

		// The reference system treats nil as a special case.
		// Whenever you call luaL_ref for a nil value, it does not create a new reference,
		// but instead returns the constant reference LUA_REFNIL.

		// pushes a nil, as expected.
		// int result = luaL_ref(pLS, LUA_REGISTRYINDEX, nil);
		// or lua_rawgeti(pLS, LUA_REGISTRYINDEX, LUA_REFNIL);

		// If luaL_ref() is LUA_NOREF or LUA_REFNIL, luaL_unref does nothing.
		// luaL_unref(pLS, LUA_REGISTRYINDEX, callbackRef); // nothing !!!

		// uninitialize lua
		lua_close(pLS);

		system("pause");
	}


	void lua_registry_ref_in_lua()
	{
		// set up Lua
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		// this is called by Lua to register its function
		auto callback = [](lua_State *pLS) {
			printf("called callback !!!\n");
			callbackRef = luaL_ref(pLS, LUA_REGISTRYINDEX);
			Debug::DumpStack(pLS);
			return 0;
		};

		lua_register(pLS, "RegisterCallback", callback);
		Debug::DumpStack(pLS);

		char luaFilename[] = { "./lua_pseudo_index-reference.lua" };

		/* run our Lua file */
		if (0 != luaL_dofile(pLS, luaFilename)) {
			printf( "Failed to load Lua File !!! - Filename:%s\n, LuaError:%s\n"
				  , luaFilename, lua_tostring(pLS, -1) );

			lua_close(pLS);
			return;
		}

		// call callback()
		call_callback(pLS);

		// call callback() again if you want (because we restored the Lua function reference)
		call_callback(pLS);

		// remove the reference to the callback
		// NOTE: This is also unnecessary if you didn't re-add the function to the registry
		luaL_unref(pLS, LUA_REGISTRYINDEX, callbackRef);

		// uninitialize lua
		lua_close(pLS);

		system("pause");
	}


	void lua_registry_light_user_data_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		int value = 10000;

		// variable with an unique address
		static const char Key = 'k';
		// store a number
		lua_pushlightuserdata(pLS, (void *)&Key); // push address
		lua_pushnumber(pLS, value); // push value
		// registry[&Key] = value
		lua_settable(pLS, LUA_REGISTRYINDEX);
		Debug::DumpStack(pLS);

		// retrieve a number
		lua_pushlightuserdata(pLS, (void *)&Key); // push address
		lua_gettable(pLS, LUA_REGISTRYINDEX); // retrieve value
		value = lua_tonumber(pLS, -1); // convert to number
		Debug::DumpStack(pLS);

		printf("%d\n", value);

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
		,	{ NULL, NULL }
	};

	static int luaopen_mylib(lua_State *pLS)
	{
		lua_newtable(pLS);
		lua_replace(pLS, LUA_ENVIRONINDEX);
		Debug::DumpStack(pLS);

		luaL_register(pLS, "myFuncList", funcList);
		Debug::DumpStack(pLS);

		return 1;
	}

	void lua_environment_use()
	{
		lua_State *pLS = lua_open();
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

		char luaFilename[] = { "./lua_pseudo_index-env.lua" };

		/* run our Lua file */
		if (0 != luaL_dofile(pLS, luaFilename)) {
			printf( "Failed to load Lua File !!! - Filename:%s\n, LuaError:%s\n"
				  , luaFilename, lua_tostring(pLS, -1));

			lua_close(pLS);
			return;
		}

		lua_close(pLS);

		system("pause");
	}

	static int counter(lua_State *pLS)
	{
		int val = lua_tointeger(pLS, lua_upvalueindex(1));
		Debug::DumpStack(pLS);
		lua_pushinteger(pLS, ++val);	// new value
		Debug::DumpStack(pLS);
		lua_pushvalue(pLS, -1);			// copy value
		Debug::DumpStack(pLS);
		lua_replace(pLS, lua_upvalueindex(1));	// update upvalue
		Debug::DumpStack(pLS);

		return 1;	// return new value
	}

	int newCounter(lua_State* pLS)
	{
		lua_pushinteger(pLS, 0);
		Debug::DumpStack(pLS);
		lua_pushcclosure(pLS, &counter, 1);
		Debug::DumpStack(pLS);

		return 1;
	}

	void lua_upvalue_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		lua_register(pLS, "NewCounter", newCounter);

		char luaFilename[] = { "./lua_pseudo_index-upvalue.lua" };

		/* run our Lua file */
		if (0 != luaL_dofile(pLS, luaFilename)) {
			printf( "Failed to load Lua File !!! - Filename:%s\n, LuaError:%s\n"
				  , luaFilename, lua_tostring(pLS, -1));

			lua_close(pLS);
			return;
		}

		lua_close(pLS);

		system("pause");
	}


	// getint and setint may only be called from Lua C functions that
	// have the shared table as upvalue 1.
	static int getInt(lua_State *pLS)
	{
		Debug::DumpStack(pLS);

		int v = 0;
		lua_getfield(pLS, lua_upvalueindex(1), "myInt");
		Debug::DumpStack(pLS);
		
		v = lua_tointeger(pLS, -1);
		lua_pop(pLS, 1); // remove integer from stack
		Debug::DumpStack(pLS);

		//v = lua_tointeger(pLS, lua_upvalueindex(1));
		//Debug::DumpStack(pLS);
		//lua_pop(pLS, 1); // remove integer from stack
		//Debug::DumpStack(pLS);

		return v;
	}

	static void setInt(lua_State *pLS, int v)
	{
		Debug::DumpStack(pLS);

		lua_pushinteger(pLS, v);
		Debug::DumpStack(pLS);
		lua_setfield(pLS, lua_upvalueindex(1), "myInt");
		lua_pushvalue(pLS, -1);			// copy value
		Debug::DumpStack(pLS);
		//lua_replace(pLS, lua_upvalueindex(1));	// update upvalue
		//Debug::DumpStack(pLS);
	}

	static int upvalue_1(lua_State *pLS)
	{
		Debug::DumpStack(pLS);

		int Global = getInt(pLS);
		Global++;
		setInt(pLS, Global);
		Debug::DumpStack(pLS);
		lua_pushinteger(pLS, Global);
		Debug::DumpStack(pLS);

		return 1;
	}

	static int upvalue_2(lua_State *pLS)
	{
		Debug::DumpStack(pLS);

		int Global = getInt(pLS);
		Global++;
		Global++;
		setInt(pLS, Global);
		Debug::DumpStack(pLS);
		lua_pushinteger(pLS, Global);
		Debug::DumpStack(pLS);

		return 1;
	}

	static const struct luaL_Reg upvalueFuncList[] = {
			{ "upvalue_1", upvalue_1 }
		,	{ "upvalue_2", upvalue_2 }
		,	{ NULL, NULL }
	};

	static void setFuncs(lua_State *L, const luaL_Reg *l, int nup)
	{
		luaL_checkstack(L, nup + 1, "too many upvalues");
		for (; l->name != NULL; l++) {  /* fill the table with given functions */
			int i;
			lua_pushstring(L, l->name);
			for (i = 0; i < nup; i++)  /* copy upvalues to the top */
				lua_pushvalue(L, -(nup + 1));
			lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
			lua_settable(L, -(nup + 3));
		}
		lua_pop(L, nup);  /* remove upvalues */
	}

	static int luaopen_upvalueFuncList(lua_State *pLS)
	{
		lua_newtable(pLS);
		Debug::DumpStack(pLS);
		lua_replace(pLS, LUA_ENVIRONINDEX);
		Debug::DumpStack(pLS);

		luaL_register(pLS, "upvalueFuncList", upvalueFuncList);
		Debug::DumpStack(pLS);

		// create shared table
		lua_newtable(pLS);
		Debug::DumpStack(pLS);
		lua_pushinteger(pLS, 1);
		Debug::DumpStack(pLS);
		lua_setfield(pLS, -2, "myint");
		Debug::DumpStack(pLS);

		setFuncs(pLS, upvalueFuncList, 1);
		Debug::DumpStack(pLS);

		return 0;
	}

	void lua_shared_upvalue_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		luaL_openlibs(pLS);

		lua_getglobal(pLS, "package");
		lua_getfield(pLS, -1, "preload");
		lua_pushcfunction(pLS, luaopen_upvalueFuncList);
		lua_setfield(pLS, -2, "mylib");
		lua_pop(pLS, 2); // discard package and package.preload

		char luaFilename[] = { "./lua_pseudo_index-shared_upvalue.lua" };

		// run the script : luaL_loadfile() + lua_pcall() !!!
		if (luaL_dofile(pLS, luaFilename)) {
			printf( "Failed to load Lua File !!! - Filename:%s\n, LuaError:%s\n"
				  , luaFilename, lua_tostring(pLS, -1) );

			lua_close(pLS);
			return;
		}

		Debug::DumpStack(pLS);

		system("pause");
	}

	void Test()
	{
		lua_registry_use();

		lua_registry_ref_in_c();

		lua_registry_ref_in_lua();

		lua_registry_light_user_data_use();

		lua_environment_use();

		lua_upvalue_use();

		lua_shared_upvalue_use();
	}
}