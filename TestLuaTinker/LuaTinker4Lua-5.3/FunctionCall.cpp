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
/// @file FunctionCall.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-30-2012 11:41:09
///////////////////////////////////////////////////////////////////////////////

void TestFunctionCall()
{
	{
		// Lua �ʱ�ȭ
		lua_State* pLS = luaL_newstate();

		// FunctionCall.lua ���� �б� & ����
		lua_tinker::dofile(pLS, "FunctionCall.lua");

		// LuaTinker �̿� �Լ� ȣ��
		int result = lua_tinker::call<int>(pLS, "Add", 1, 2);

		// ȭ�� ���
		printf("Add result:%d\n", result);

		lua_close(pLS);

		system("pause");
	}
}