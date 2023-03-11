#pragma once

#include "LuaMeta.hpp"

namespace CustomMetaData
{
	/*
		* This is the main object that is actually used in the C++ code.
		* It is to be manipulated by Lua through the Lua wrapper object
		  (which will contain a pointer to this object).
	*/

	class GameObject
	{
	public:
		GameObject(int x);
		virtual ~GameObject();

		int getAttr(void);
		void setAttr(int balance);

		void setMessage(const char* new_message);
		const char* getMessage(void);

	private:
		int attribute;
		std::string message;
	};

	GameObject::GameObject(int x)
	{
		attribute = x;
	}

	GameObject::~GameObject()
	{
		printf("deleted Object (%p)\n", this);
	}

	int GameObject::getAttr()
	{
		return (int)attribute;
	}

	void GameObject::setAttr(int set)
	{
		attribute = set;
	}

	void GameObject::setMessage(const char* new_message)
	{
		message.assign(new_message);
	}

	const char* GameObject::getMessage()
	{
		return message.c_str();
	}

	/*
		* This is the wrapper around the C++ object found in object.cc
		* Everything this object has done to it is passed on FROM Lua to the real C++
		* object through the pointer 'real_object'
		* Notice that I kept the function names the same for simplicity.
	*/

	class LuaGameObject
	{
	public:
		// Constants
		static const char className[];
		static Lua::LuaMeta<LuaGameObject>::RegType methods[];

		// Initialize the pointer
		LuaGameObject(lua_State *L);
		virtual ~LuaGameObject();

		void setObject(lua_State *L);

		// Methods we will need to use
		int getAttr(lua_State *L);
		int setAttr(lua_State *L);
		int getMessage(lua_State *L);
		int setMessage(lua_State *L);

	private:
		// The pointer to the 'real object' defined in object.cc
		GameObject* real_object;
	};

	LuaGameObject::LuaGameObject(lua_State *L)
	{
		real_object = (GameObject*)lua_touserdata(L, 1);
	}
	LuaGameObject::~LuaGameObject()
	{
		printf("deleted Lua Object (%p)\n", this);
	}

	void LuaGameObject::setObject(lua_State *L)
	{
		real_object = (GameObject*)lua_touserdata(L, 1);
	}

	int LuaGameObject::setAttr(lua_State *L)
	{
		real_object->setAttr((int)luaL_checknumber(L, 1));
		return 0;
	}
	int LuaGameObject::getAttr(lua_State *L) {
		lua_pushnumber(L, real_object->getAttr());
		return 1;
	}

	int LuaGameObject::setMessage(lua_State *L)
	{
		real_object->setMessage(lua_tostring(L, 1));
		return 0;
	}
	int LuaGameObject::getMessage(lua_State *L)
	{
		lua_pushstring(L, real_object->getMessage());
		return 1;
	}

	// Define the Lua ClassName
	const char LuaGameObject::className[] = "LuaGameObject";
	
	Lua::LuaMeta<LuaGameObject>::RegType LuaGameObject::methods[] = {
		method(LuaGameObject, setAttr),
		method(LuaGameObject, getAttr),
		method(LuaGameObject, getMessage),
		method(LuaGameObject, setMessage),
		{ 0,0 }
	};


}