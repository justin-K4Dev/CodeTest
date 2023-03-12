#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-30-2012 11:41:03
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

class Object
{
public:
	int m_nID;
	std::string m_strName;

public:
	Object(int nID, std::string &strName) : m_nID(nID), m_strName(strName) { return; }

	void Print() 
	{ 
		printf("Object - ID:%d, Name:%s\n", m_nID, m_strName.c_str());
	}
};

///////////////////////////////////////////////////////////////////////////////
/// @file ClassRegister.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-30-2012 11:41:09
///////////////////////////////////////////////////////////////////////////////

void TestClassRegister()
{
	Object object(10, std::string("justin"));

	{
		// Lua 초기화
		lua_State* pLS = lua_open();

		// Lua 기본 IO 함수 읽기
		luaopen_base(pLS);
		
		// class 등록
		lua_tinker::class_add<Object>(pLS, "Object");
		lua_tinker::class_mem<Object>(pLS, "m_nID", &Object::m_nID);
		lua_tinker::class_def<Object>(pLS, "Print", &Object::Print);

		// g_Object 를 Lua 등록
		lua_tinker::set(pLS, "g_Object", &object);
	
		// ClassRegister.lua 파일 읽기/실행
		lua_tinker::dofile(pLS, "ClassRegister.lua");

		lua_close(pLS);

		system("pause");
	}
}