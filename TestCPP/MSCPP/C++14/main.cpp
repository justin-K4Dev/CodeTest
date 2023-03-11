// TestC++0x.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Function.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Logic::Test();

	//////////////////////////////////////////////////////////////////////////////

	Alias::Test();

	Auto::Test();
	
	Constexpr::Test();

	Constructor::Test();

	Inheritance::Test();

	New::Test();

	NSDMI::Test();

	Lambda::Test();

	RValueReference::Test();

	Template::Test();

	SFINAE::Test();

	TypeConversion::Test();

	FloatingPointCapturingErrors::Test();

	String::Test();
	
	return 0;
}

