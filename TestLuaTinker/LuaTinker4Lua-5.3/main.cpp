// TestLuaTinker.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "TestFunction.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SET_CRT_MEMORY_CHECK(CRT_MEMORY_LEAK_ALWAYS_CHECK_FLAGS);

	TestFunctionRegister();

	TestFunctionCall();

	TestGobalVariable();

	TestTableAccess();

	TestClassRegister();

	_CrtDumpMemoryLeaks();

	system("pause");

	return 0;
}

