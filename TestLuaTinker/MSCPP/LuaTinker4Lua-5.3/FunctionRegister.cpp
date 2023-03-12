#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-30-2012 11:41:03
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

void ShowText(char *pszText)
{
	printf("Called Text:%s - function %s !!!\n", pszText, __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////
/// @file FunctionRegister.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-30-2012 11:41:09
///////////////////////////////////////////////////////////////////////////////

void TestFunctionRegister()
{
	{
		// Lua �ʱ�ȭ
		lua_State *pLS = luaL_newstate();
		
		// C �Լ� ���
		lua_tinker::def(pLS, "ShowText", ShowText);

		// FunctionRegister.lua ���� �б� & ����
		lua_tinker::dofile(pLS, "FunctionRegister.lua");

		lua_close(pLS);

		system("pause");	
	}

}