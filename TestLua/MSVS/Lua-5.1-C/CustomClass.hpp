#pragma once

#include "stdafx.h"

namespace CustomMetaData
{
	class CustomClass
	{
	protected:
		lua_State* m_pLS = nullptr;

		static const luaL_reg m_methodList[7];
		static const luaL_reg m_metaList[4];

		int x = 0;
		int y = 0;


	public:
		CustomClass(lua_State* pLS);
		virtual ~CustomClass();

		static const char* GetClassName();

		static int RegisterToLua(lua_State *pLS);

		static int SetX(lua_State *pLS);

		static int SetY(lua_State *pLS);

		static CustomClass* GetObject(lua_State* pLS, int index);

		static CustomClass* CheckObject(lua_State *pLS, int index);

		static CustomClass* pushObject(lua_State *pLS);

		static int NewObject(lua_State *pLS);

		static int CallFunction(lua_State *pLS);

		static int SumObject(lua_State *pLS);

		static int DotObject(lua_State *pLS);

		static int GC(lua_State *pLS);

		static int toString(lua_State *pLS);
	};

	const luaL_reg CustomClass::m_methodList[] = {

		 { "new",			CustomClass::NewObject }
		,{ "callFunction",	CustomClass::CallFunction }
		,{ "setX",			CustomClass::SetX }
		,{ "setY",			CustomClass::SetY }
		,{ "add",			CustomClass::SumObject }
		,{ "dot",			CustomClass::DotObject }
		,{ 0, 0 }
	};

	const luaL_reg CustomClass::m_metaList[] = {

		 { "__gc",       CustomClass::GC }
		,{ "__tostring", CustomClass::toString }
		,{ "__add",      CustomClass::SumObject }
		,{ 0, 0 }
	};

	CustomClass::CustomClass(lua_State* pLS)
		: m_pLS(pLS)
	{
	}
	CustomClass::~CustomClass()
	{
	}

	const char* CustomClass::GetClassName()
	{
		//return (char*)typeid(CustomClass).name();
		return "CustomClass";
	}

	int CustomClass::RegisterToLua(lua_State *pLS)
	{
		const char* szClassName = GetClassName();

		luaL_openlib(pLS, szClassName, m_methodList, 0);  // create methods table, add it to the globals

		luaL_newmetatable(pLS, szClassName);	// create metatable for szClassName, and add it to the Lua registry
		Debug::DumpStack(pLS);

		luaL_openlib(pLS, 0, m_metaList, 0);	// fill metatable

		lua_pushliteral(pLS, "__index");
		Debug::DumpStack(pLS);
		lua_pushvalue(pLS, -3);					// dup methods table
		Debug::DumpStack(pLS);
		lua_rawset(pLS, -3);					// metatable.__index = methods
		Debug::DumpStack(pLS);

		lua_pushliteral(pLS, "__metatable");
		Debug::DumpStack(pLS);
		lua_pushvalue(pLS, -3);					// dup methods table
		Debug::DumpStack(pLS);
		lua_rawset(pLS, -3);					// hide metatable: metatable.__metatable = methods
		Debug::DumpStack(pLS);

		lua_pop(pLS, 1);						// drop metatable
		Debug::DumpStack(pLS);

		return 1;								// return methods on the stack
	}

	CustomClass* CustomClass::GetObject(lua_State* pLS, int index)
	{
		CustomClass *pObj = (CustomClass*)lua_touserdata(pLS, index);
		if (nullptr == pObj) {
			luaL_typerror(pLS, index, typeid(CustomClass).name());
		}

		return pObj;
	}

	CustomClass* CustomClass::CheckObject(lua_State *pLS, int index)
	{
		luaL_checktype(pLS, index, LUA_TUSERDATA);

		CustomClass *pObj = (CustomClass*)luaL_checkudata(pLS, index, GetClassName());
		if (nullptr == pObj) {
			luaL_typerror(pLS, index, GetClassName());
		}

		return pObj;
	}

	CustomClass* CustomClass::pushObject(lua_State *pLS)
	{
		CustomClass *pObj = (CustomClass*)lua_newuserdata(pLS, sizeof(CustomClass));
		luaL_getmetatable(pLS, GetClassName());
		lua_setmetatable(pLS, -2);

		return pObj;
	}

	int CustomClass::NewObject(lua_State *pLS)
	{
		int x = luaL_optint(pLS, 1, 0);
		int y = luaL_optint(pLS, 2, 0);

		CustomClass *pObj = pushObject(pLS);
		pObj->x = x;
		pObj->y = y;

		return 1;
	}

	int CustomClass::CallFunction(lua_State *pLS)
	{
		CustomClass *pObj = CheckObject(pLS, 1);
		printf("called C CustomClass::CallFunction() !!!\n");

		lua_pushnumber(pLS, pObj->x);
		lua_pushnumber(pLS, pObj->y);
		Debug::DumpStack(pLS);

		return 2;
	}

	int CustomClass::SetX(lua_State *pLS)
	{
		CustomClass *pObj = CheckObject(pLS, 1);

		pObj->x = luaL_checkint(pLS, 2);
		lua_settop(pLS, 1);

		return 1;
	}

	int CustomClass::SetY(lua_State *pLS)
	{
		CustomClass *pObj = CheckObject(pLS, 1);

		pObj->y = luaL_checkint(pLS, 2);
		lua_settop(pLS, 1);

		return 1;
	}

	int CustomClass::SumObject(lua_State *pLS)
	{
		CustomClass *pObj1 = CheckObject(pLS, 1);
		CustomClass *pObj2 = CheckObject(pLS, 2);
		CustomClass *newObj = pushObject(pLS);

		newObj->x = pObj1->x + pObj2->x;
		newObj->y = pObj1->y + pObj2->y;

		return 1;
	}

	int CustomClass::DotObject(lua_State *pLS)
	{
		CustomClass *pObj1 = CheckObject(pLS, 1);
		CustomClass *pObj2 = CheckObject(pLS, 2);

		lua_pushnumber(pLS, pObj1->x * pObj2->x + pObj1->y * pObj2->y);

		return 1;
	}

	int CustomClass::GC(lua_State *pLS)
	{
		printf("Bye, Bye, CustomClass = %p\n", GetObject(pLS, 1));
		return 0;
	}

	int CustomClass::toString(lua_State *pLS)
	{
		char buff[32];
		sprintf_s(buff, sizeof(char) * 32, "%p", GetObject(pLS, 1));

		lua_pushfstring(pLS, "CustomClass = (%s)\n", buff);

		return 1;
	}


}