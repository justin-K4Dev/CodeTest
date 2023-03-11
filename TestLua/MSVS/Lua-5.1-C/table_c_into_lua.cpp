#include "stdafx.h"
#include "Function.h"

namespace TableCIntoLua
{
	void lua_table_creation_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		const char *szTablename = "Character";
		std::list<std::string> keys{ "nickname", "hp" };

		// create blank table
		lua_newtable(pLS);
		Debug::DumpStack(pLS);

		// create key list of table 
		// the value corresponding to the key is set to the number 0 once.
		for (auto itPos = keys.begin(); itPos != keys.end(); ++itPos)
		{
			std::string &keyname = (*itPos);

			lua_pushstring(pLS, keyname.c_str());
			Debug::DumpStack(pLS);

			if ("nickname" == keyname) {
				lua_pushstring(pLS, "empty");
			}
			else {
				lua_pushnumber(pLS, 0);
			}			
			Debug::DumpStack(pLS);

			lua_settable(pLS, -3);
			Debug::DumpStack(pLS);
		}

		// generate count variables for the table.getn() function of the Lua table module
		// (the function that determines the size of the table)
		lua_pushstring(pLS, "count");
		Debug::DumpStack(pLS);
		lua_pushnumber(pLS, (int)(keys.size()));
		Debug::DumpStack(pLS);

		lua_settable(pLS, -3);
		Debug::DumpStack(pLS);

		// register the table as a global variable so that it can be accessed elsewhere.
		lua_setglobal(pLS, szTablename);
		Debug::DumpStack(pLS);

		// read table
		Debug::DumpTableInfoAll(pLS, szTablename);

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		lua_table_creation_in_c();
	}
}