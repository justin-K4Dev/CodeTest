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
		// Lua 초기화
		lua_State *pLS = luaL_newstate();
		
		// C 함수 등록
		lua_tinker::def(pLS, "ShowText", ShowText);

		// FunctionRegister.lua 파일 읽기 & 실행
		lua_tinker::dofile(pLS, "FunctionRegister.lua");

		lua_close(pLS);

		system("pause");	
	}

}