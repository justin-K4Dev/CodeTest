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
		// Lua 초기화
		lua_State* pLS = luaL_newstate();

		// FunctionCall.lua 파일 읽기 & 실행
		lua_tinker::dofile(pLS, "FunctionCall.lua");

		// LuaTinker 이용 함수 호출
		int result = lua_tinker::call<int>(pLS, "Add", 1, 2);

		// 화면 출력
		printf("Add result:%d\n", result);

		lua_close(pLS);

		system("pause");
	}
}