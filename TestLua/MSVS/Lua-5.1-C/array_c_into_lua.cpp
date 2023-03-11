#include "stdafx.h"
#include "Function.h"

namespace ArrayCIntoLua
{
	void lua_array_creation_in_c()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		const char *szArrayName = "LuaArray";

		// create blank table
		lua_createtable(pLS, 10, 0);
		Debug::DumpStack(pLS);

		std::vector<int> dataList = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

		for (int i = 0; i < 10; ++i) {
			lua_pushinteger(pLS, dataList[i]);
			lua_rawseti(pLS, -2, i);
			Debug::DumpStack(pLS);
		}

		// register the array table as a global variable so that it can be accessed elsewhere.
		lua_setglobal(pLS, szArrayName);
		Debug::DumpStack(pLS);

		// read table
		Debug::DumpTableInfoAll(pLS, szArrayName);

		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		lua_array_creation_in_c();
	}
}