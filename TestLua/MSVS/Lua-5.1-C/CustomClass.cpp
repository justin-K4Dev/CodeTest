#include "stdafx.h"

#include "CustomClass.hpp"

namespace Example
{
	void custom_class_example()
	{
		lua_State *pLS = lua_open();

		// load all lua standard libraries
		luaL_openlibs(pLS);

		CustomMetaData::CustomClass::RegisterToLua(pLS);

		// after foo register the methods are still on the stack, remove them.
		lua_pop(pLS, 1);

		char luaFilename[] = { "./custom_class.lua" };

		// run the script
		int result = luaL_loadfile(pLS, luaFilename);
		if (0 != result) {
			Debug::DumpStack(pLS);

			printf( "Failed to load Lua File !!! - Filename:%s, EM:%s\n"
				  , luaFilename, lua_tostring(pLS, -1) );

			// cleanup
			lua_close(pLS);
			return;
		}

		result = lua_pcall(pLS, 0, LUA_MULTRET, 0);
		if (0 != result) {
			Debug::DumpStack(pLS);

			// LUA_ERRRUN or LUA_ERRNUM or LUA_ERRERR !!!
			printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

			// cleanup
			lua_close(pLS);
			return;
		}

		Debug::DumpStack(pLS);

		lua_close(pLS);
	}

	void CustomClassTest()
	{
		custom_class_example();
	}
}