#include "stdafx.h"
#include "Function.h"

#include "Lua.h"


namespace LuaLightUserData
{
	struct Object
	{
		char* name;
		int type;
		bool isAlloc;
	};

	int getName(lua_State* L)
	{
		Object* pObj = (Object*)lua_touserdata(L, 1);
		lua_pushstring(L, (const char*)pObj->name);
		return 1;
	}

	int getType(lua_State* L)
	{
		Object* pObj = (Object*)lua_touserdata(L, 1);
		lua_pushnumber(L, pObj->type);
		return 1;
	}

	int isAlloc(lua_State* L)
	{
		Object* pObj = (Object*)lua_touserdata(L, 1);
		lua_pushboolean(L, pObj->isAlloc);
		return 1;
	}

	void light_user_data_use()
	{
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		Object obj;
		obj.name = "Mana Potion";
		obj.type = 10;
		obj.isAlloc = true;

		lua_pushlightuserdata(L, (void*)&obj);
		lua_setglobal(L, "obj");

		luaL_Reg module[] = {
				{ "getName", &getName }
			,	{ "getType", &getType }
			,	{ "isAlloc", &isAlloc }
			,	{ NULL, NULL }
		};

		luaL_register(L, "_G", module);

		luaL_dostring(L, "print('Type: \t\t'..type(obj))");

		luaL_dostring( L
					 , "print('Name: \t\t'..getName(obj));"
					   "print('Type: \t\t'..getType(obj));"
					   "print('isAlloc:\t'.. ( (isAlloc(obj) and 'yes') or 'no') );"
		);

		lua_close(L);
		
		system("pause");
	}

	void Test()
	{
		light_user_data_use();
	}
}