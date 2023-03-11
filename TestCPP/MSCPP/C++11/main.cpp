// TestC++0x.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Function.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Logic::Test();

	//////////////////////////////////////////////////////////////////////////////

	ABAProblem::Test();

	Auto::Test();

	CAS::Test();

	DCAS::Test();

	DeclType::Test();

	Emplacement::Test();

	Enum::Test();

	Exception::Test();

	Lambda::Test();

	Loop::Test();

	MemoryBarrier::Test();

	Mutex::Test();

	NullPtr::Test();

	Random::Test();

	RValueReference::Test();

	StaticAssert::Test();

	String::Test();

	Thread::Test();

	Volatile::Test();

	Time::Test();

	TypeInfo::Test();
	
	return 0;
}

