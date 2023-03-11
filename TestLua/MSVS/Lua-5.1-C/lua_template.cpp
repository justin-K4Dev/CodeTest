#include "stdafx.h"

#include "Account.hpp"

namespace LuaTemplate
{
	void template_use()
	{
		try {
			lua_State *pLS = lua_open();

			// load all lua standard libraries
			luaL_openlibs(pLS);

			Lua::LuaMeta<CustomMetaData::Account>::Register(pLS);

			char luaFilename[] = { "./lua_template.lua" };

			// run the script
			int result = luaL_loadfile(pLS, luaFilename);
			if(0 != result)	{
				printf("Failed to load Lua File !!! - Filename:%s\n", luaFilename);

				// cleanup
				lua_close(pLS);
				return;
			}

			result = lua_pcall(pLS, 0, LUA_MULTRET, 0);
			if (0 != result) {
				// LUA_ERRRUN or LUA_ERRNUM or LUA_ERRERR !!!
				printf("Failed to run script: %s\n", lua_tostring(pLS, -1));

				// cleanup
				lua_close(pLS);
				return;
			}

			lua_close(pLS);

		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

		system("pause");
	}

	void Test()
	{
		template_use();
	}
}