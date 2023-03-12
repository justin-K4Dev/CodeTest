#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-30-2012 11:41:03
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file TableAccess.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-30-2012 11:41:09
///////////////////////////////////////////////////////////////////////////////

void TestTableAccess()
{
	{
		// Lua �ʱ�ȭ
		lua_State* pLS = luaL_newstate();

		// TableAccess.lua ���� �б� / ����
		lua_tinker::dofile(pLS, "TableAccess.lua");
		{
			// table �б�
			lua_tinker::table window(pLS, "g_Window");
			//or lua_tinker::table window = lua_tinker::get<lua_tinker::table>(pLS, "g_Window");

			// ȭ�� ���
			printf("window: %s\n", window.get<const char*>("name"));
			printf("x, y: %d, %d\n", window.get<int>("x"), window.get<int>("y"));
			printf("w, h: %d, %d\n", window.get<int>("w"), window.get<int>("h"));

			// you must destroy the table object before calling lua_close() function.
			// {} or window.~table();
		}
		lua_close(pLS);

		system("pause");
	}
}