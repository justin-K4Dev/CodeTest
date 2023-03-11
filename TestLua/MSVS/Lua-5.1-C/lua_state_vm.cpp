#include "stdafx.h"
#include "Function.h"

namespace LuaStateVM
{
	void lua_state_stack_vm_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Failed to assign LuaState !!!" << std::endl;
			return;
		}

		lua_pushboolean(pLS, 1);		// 1 or -4 pos : 1.000000
		lua_pushnumber(pLS, 10);		// 2 or -3 pos : 10.000000
		lua_pushnil(pLS);				// 3 or -2 pos : nil
		lua_pushstring(pLS, "hello");	// 4 or -1 pos : "hello"
		Debug::DumpStack(pLS);
		/*
			04 or -1 | string	| hello
			03 or -2 | nil		| 
			02 or -3 | number	| 10.000000
			01 or -4 | boolean	| 1.000000
		*/

		lua_pushvalue(pLS, -4); // -4 pos value push in stack, 5 pos !!!
		Debug::DumpStack(pLS);
		/*
			05 or -1 | boolean	| 1.000000
			04 or -2 | string	| hello
			03 or -3 | nil		| 
			02 or -4 | number	| 10.000000
			01 or -5 | boolean	| 1.000000
		*/

		lua_replace(pLS, 3);	// top value (boolean:1) move target index (3)
		Debug::DumpStack(pLS);
		/*
			04 or -1 | string	| hello
			03 or -2 | boolean	| 1.000000
			02 or -3 | number	| 10.000000
			01 or -4 | boolean	| 1.000000
		*/

		lua_settop(pLS, 2);		// top value (10.0) set target index (2)
		Debug::DumpStack(pLS);	// 2 or more nodes are removed
		/*
			02 or -1 | number	| 10.000000
			01 or -2 | boolean	| 1.000000
		*/

		lua_settop(pLS, 4);		// top value (nil) set target index (4)
		Debug::DumpStack(pLS);	// If more than 4 nodes are removed,
		                        // but there are no more than 4 nodes, allocate nodes initialized to nil
		/*
			04 or -1 | nil		| <- allocated nil node
			03 or -2 | nil		| <- allocated nil node
			02 or -3 | number	| 10.000000
			01 or -4 | boolean	| 1.000000
		*/

		lua_remove(pLS, -3);	// remove value -3 pos (10.0) and node
		Debug::DumpStack(pLS);	// decrease the position of the nodes above it by one space.
		/*
			03 or -1 | nil		| 
			02 or -2 | nil		| 
			01 or -3 | boolean	| 1.000000
		*/

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.
		/*
			empty stack
		*/

		lua_pushnumber(pLS, 1);		// 1 or -3 pos : 1.000000
		lua_pushnumber(pLS, 5);		// 2 or -2 pos : 5.000000
		lua_pushnumber(pLS, 10);	// 3 or -1 pos : 10.000000
		Debug::DumpStack(pLS);
		/*
			03 or -1 | number	| 10.000000
			02 or -2 | number	| 5.000000
			01 or -3 | number	| 1.000000
		*/

		lua_insert(pLS, 2);		// move 2 or -2 pos to the top 
		Debug::DumpStack(pLS);	// top node decrese the position
		/*
			03 or -1 | number	| 5.000000
			02 or -2 | number	| 10.000000
			01 or -3 | number	| 1.000000
		*/

		lua_pop(pLS, 1);		// Pop from 1 stacks.
		Debug::DumpStack(pLS);	// If -1, empty the stack !!!
		/*
			02 or -1 | number	| 10.000000
			01 or -2 | number	| 1.000000
		*/
		
		// cleanup
		lua_close(pLS);

		system("pause");
	}

	void Test()
	{
		lua_state_stack_vm_use();
	}
}