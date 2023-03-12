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
/// @file GlobalVariable.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-30-2012 11:41:09
///////////////////////////////////////////////////////////////////////////////

void TestGobalVariable()
{
	{
		// Lua �ʱ�ȭ
		lua_State *pLS = lua_open();

		// Lua ���� ������ �� ����
		lua_tinker::set(pLS, "g_Value", 1);
		
		// GlobalVariable.lua ���� �б� & ����
		lua_tinker::dofile(pLS, "GlobalVariable.lua");
		
		// Lua ���� ������ ���� �б�
		int value = lua_tinker::get<int>(pLS, "g_Value");
		
		// ȭ�� ���
		printf("g_Value:%d\n", value);

		lua_close(pLS);

		system("pause");
	}
}