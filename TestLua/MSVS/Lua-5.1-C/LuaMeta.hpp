#pragma once

#include "stdafx.h"

namespace Lua
{
	#define method(class, name) { #name, &class::name }

	template <typename T>
	class LuaMeta
	{
		typedef struct { T *pT; } userdataType;
	
	public:
		typedef int (T::*mfp)(lua_State *pLS);
		typedef struct { const char *name; mfp mfunc; } RegType;

		static void Register(lua_State *pLS)
		{
			lua_newtable(pLS);
			int methods = lua_gettop(pLS);

			luaL_newmetatable(pLS, T::className);
			int metatable = lua_gettop(pLS);

			// store method table in globals so that
			// scripts can add functions written in Lua.
			lua_pushstring(pLS, T::className);
			lua_pushvalue(pLS, methods);
			lua_settable(pLS, LUA_GLOBALSINDEX);

			lua_pushliteral(pLS, "__metatable");
			lua_pushvalue(pLS, methods);
			lua_settable(pLS, metatable);  // hide metatable from Lua getmetatable()

			lua_pushliteral(pLS, "__index");
			lua_pushvalue(pLS, methods);
			lua_settable(pLS, metatable);

			lua_pushliteral(pLS, "__tostring");
			lua_pushcfunction(pLS, tostring_T);
			lua_settable(pLS, metatable);

			lua_pushliteral(pLS, "__gc");
			lua_pushcfunction(pLS, gc_T);
			lua_settable(pLS, metatable);

			lua_newtable(pLS);                // mt for method table
			int mt = lua_gettop(pLS);
			lua_pushliteral(pLS, "__call");
			lua_pushcfunction(pLS, new_T);
			lua_pushliteral(pLS, "new");
			lua_pushvalue(pLS, -2);           // dup new_T function
			lua_settable(pLS, methods);       // add new_T to method table
			lua_settable(pLS, mt);            // mt.__call = new_T
			lua_setmetatable(pLS, methods);

			// fill method table with methods from class T
			for (RegType *l = T::methods; l->name; l++)
			{
				/* edited by Snaily: shouldn't it be const RegType *l ... ? */
				lua_pushstring(pLS, l->name);
				lua_pushlightuserdata(pLS, (void*)l);
				lua_pushcclosure(pLS, thunk, 1);
				lua_settable(pLS, methods);
			}

			lua_pop(pLS, 2);  // drop metatable and method table
		}

		// get userdata from Lua stack and return pointer to T object
		static T *check(lua_State *pLS, int narg)
		{
			userdataType *ud = static_cast<userdataType*>(luaL_checkudata(pLS, narg, T::className));
			if (!ud) luaL_typerror(pLS, narg, T::className);

			return ud->pT;  // pointer to T object
		}

	private:
		LuaMeta();  // hide default constructor

		 // member function dispatcher
		static int thunk(lua_State *pLS)
		{
			// stack has userdata, followed by method args
			T *obj = check(pLS, 1);  // get 'self', or if you prefer, 'this'
			lua_remove(pLS, 1);  // remove self so member function args start at index 1
							   // get member function from upvalue
			RegType *l = static_cast<RegType*>(lua_touserdata(pLS, lua_upvalueindex(1)));

			return (obj->*(l->mfunc))(pLS);  // call member function
		}

		// create a new T object and
		// push onto the Lua stack a userdata containing a pointer to T object
		static int new_T(lua_State *pLS)
		{
			lua_remove(pLS, 1);   // use classname:new(), instead of classname.new()
			T *obj = new T(pLS);  // call constructor for T objects
			userdataType *ud = static_cast<userdataType*>(lua_newuserdata(pLS, sizeof(userdataType)));
			ud->pT = obj;  // store pointer to object in userdata
			luaL_getmetatable(pLS, T::className);  // lookup metatable in Lua registry
			lua_setmetatable(pLS, -2);

			return 1;  // userdata containing pointer to T object
		}

		// garbage collection metamethod
		static int gc_T(lua_State *pLS) 
		{
			userdataType *ud = static_cast<userdataType*>(lua_touserdata(pLS, 1));
			T *obj = ud->pT;
			delete obj;  // call destructor for T objects

			return 0;
		}

		static int tostring_T(lua_State *pLS) 
		{
			char buff[32];
			userdataType *ud = static_cast<userdataType*>(lua_touserdata(pLS, 1));
			T *obj = ud->pT;
			sprintf_s(buff, 32, "%p", obj);
			lua_pushfstring(pLS, "%s (%s)", T::className, buff);

			return 1;
		}
	};
}