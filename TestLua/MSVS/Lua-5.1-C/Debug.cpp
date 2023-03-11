#include "stdafx.h"
#include "Debug.h"

namespace Debug
{
	void DumpStack(lua_State* pLS)
	{
		int top = lua_gettop(pLS);
		for (int i = top; i >= 1; --i)
		{
			printf("%02d or %02d | ", i, i - (top + 1));
			switch (lua_type(pLS, i))
			{
			case LUA_TNONE:
				printf("none	| \n");
				break;
			case LUA_TNIL:
				printf("nil		| \n");
				break;
			case LUA_TBOOLEAN:
				printf("boolean	| %u\n", lua_toboolean(pLS, i));
				break;
			case LUA_TNUMBER:
				printf("number	| %f\n", lua_tonumber(pLS, i));
				break;
			case LUA_TSTRING:
				printf("string	| %s\n", lua_tostring(pLS, i));
				break;
			case LUA_TTABLE:
				printf("table	| 0x%08p\n", lua_topointer(pLS, i));
				break;
			case LUA_TFUNCTION:
				printf("function | 0x%08p\n", lua_topointer(pLS, i));
				break;
			case LUA_TUSERDATA:
				printf("userdata | 0x%08p\n", lua_topointer(pLS, i));
				break;
			case LUA_TLIGHTUSERDATA:
				printf("lightuserdata | 0x%08p\n", lua_topointer(pLS, i));
				break;
			case LUA_TTHREAD:
				printf("thread	| 0x%08p\n", lua_topointer(pLS, i));
				break;
			default:
				printf("unknown	| \n");
				break;
			}
		}

		if (0 == top) {
			std::cout << "empty stack\n" << std::endl;
			return;
		}

		std::cout << std::endl;
	}

	void GetTableInfoAll(lua_State *pLS, int tableIndexInStack, OUT std::string& debugInfo)
	{
		printf("StackIndex:%d, LuaTypeCode:%d, LuaTypeName:%s\n"
			, tableIndexInStack
			, lua_type(pLS, tableIndexInStack)
			, lua_typename(pLS, lua_type(pLS, tableIndexInStack))
		);

		lua_pushnil(pLS); // set to iterate from the first key in the table !!!
		Debug::DumpStack(pLS);

		bool isKey = true;

		// lua_next() - iterate in the table
		while (lua_next(pLS, tableIndexInStack) != 0) {
			Debug::DumpStack(pLS);

			for (int offset = 1; offset <= 2; ++offset) {

				if (1 == offset) {
					debugInfo += " ";
				}
				if (2 == offset && true == isKey) {
					debugInfo += " = ";
				}

				int stackIndex = tableIndexInStack + offset;
				int luaType = lua_type(pLS, stackIndex);

				switch (luaType) {
					case LUA_TBOOLEAN: {
						int value = lua_toboolean(pLS, stackIndex);
						char temp[32];
						_itoa_s(value, temp, 10);
						debugInfo += temp;
					} break;

					case LUA_TNUMBER: {
						lua_Number value = lua_tonumber(pLS, stackIndex);
						char temp[32];
						_itoa_s(value, temp, 10);
						debugInfo += temp;
					} break;

					case LUA_TSTRING: {
						const char *szValue = lua_tostring(pLS, stackIndex);
						debugInfo += szValue;
					} break;

					case LUA_TTABLE: {
						debugInfo += "{";
						GetTableInfoAll(pLS, tableIndexInStack + 2, OUT debugInfo);
						debugInfo += " }";
					} break;

					default: {
						printf("%s\n", lua_typename(pLS, luaType));
					} break;
				}
			}

			lua_pop(pLS, 1);
			Debug::DumpStack(pLS);
		}
	}

	void DumpTableInfoAll(lua_State *pLS, const char* szTableName)
	{
		// get 
		lua_getglobal(pLS, szTableName);
		Debug::DumpStack(pLS);

		int n = lua_gettop(pLS);
		if (0 >= n) {
			std::cout << "Failed to read from Table !!!, Empty stack !!!" << std::endl;
			return;
		}

		std::string luaCode;

		luaCode += szTableName;
		luaCode += " = {";

		Debug::GetTableInfoAll(pLS, 1, OUT luaCode);

		lua_settop(pLS, 0);		// 0 pos empty !!! and clear stack !!!,ll,l                 
		Debug::DumpStack(pLS);	// Remove all 0 or more nodes.

		luaCode += " }";

		printf("Read from table - TableName:%s\n", szTableName);
		printf("%s\n", luaCode.c_str());
	}
}