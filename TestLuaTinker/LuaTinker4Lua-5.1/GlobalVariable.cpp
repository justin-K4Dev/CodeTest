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
		// Lua 초기화
		lua_State *pLS = lua_open();

		// Lua 전역 변수에 값 쓰기
		lua_tinker::set(pLS, "g_Value", 1);
		
		// GlobalVariable.lua 파일 읽기 & 실행
		lua_tinker::dofile(pLS, "GlobalVariable.lua");
		
		// Lua 전역 변수의 값을 읽기
		int value = lua_tinker::get<int>(pLS, "g_Value");
		
		// 화면 출력
		printf("g_Value:%d\n", value);

		lua_close(pLS);

		system("pause");
	}
}