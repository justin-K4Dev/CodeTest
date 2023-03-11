#include "stdafx.h"

#include "LuaMeta.hpp"
#include "GameObject.hpp"


namespace Example
{
	void lua_meta_custom_class_example()
	{
		// Init Lua
		lua_State *pLS = lua_open();

		// load all lua standard libraries
		luaL_openlibs(pLS);

		// Register the LuaGameObject data type with Lua
		Lua::LuaMeta<CustomMetaData::LuaGameObject>::Register(pLS);

		char luaFilename[] = { "./lua_meta_custom_object.lua" };

		// In C++ - Create a GameObject for use in our program
		CustomMetaData::GameObject temp(20);
		temp.setMessage("I'm set in C++");

		// Push a pointer to this GameObject to the Lua stack
		lua_pushlightuserdata(pLS, (void*)&temp);
		// And set the global name of this pointer
		lua_setglobal(pLS, "gameobject");

		printf("In C: %p => %d, %s\n", &temp, temp.getAttr(), temp.getMessage());

		int result;

		// Test 1
		///////////////////////////////////////////////////////////////////////////////////////

		printf("Test-1 Loading %s\n", luaFilename);
		// Load the file containing the script we are going to run
		if (luaL_loadfile(pLS, luaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		printf("Test-1 Lua is loaded %s\n", luaFilename);

		printf("Test-1 Running Lua %s\n", luaFilename);
		result = lua_pcall(pLS, 0, 0, 0);
		if (0 != result) {
			// LUA_ERRRUN or LUA_ERRNUM or LUA_ERRERR !!!
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));
			return;
		}		
		printf("Test-1 Lua is done %s\n", luaFilename);

		// Test 2
		///////////////////////////////////////////////////////////////////////////////////////

		printf("Test-2 Loading %s\n", luaFilename);
		// Load the file containing the script we are going to run
		if (luaL_loadfile(pLS, luaFilename)) {
			printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

			// cleanup
			lua_close(pLS);
			return;
		}
		printf("Test-2 Lua is loaded %s\n", luaFilename);

		printf("Test-2 Running Lua %s\n", luaFilename);
		result = lua_pcall(pLS, 0, 0, 0);
		if (0 != result) {
			// LUA_ERRRUN or LUA_ERRNUM or LUA_ERRERR !!!
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));
			return;
		}
		printf("Test-2 Lua is done %s\n", luaFilename);

		// GC + Close out Lua
		lua_close(pLS);

		printf("In C++: %p => %d, %s\n", &temp, temp.getAttr(), temp.getMessage());

		system("pause");
	}

	void LuaMetaCustomClassTest()
	{
		lua_meta_custom_class_example();
	}
}