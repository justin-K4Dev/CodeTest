// TestC++0x.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Function.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Memory::Test();

	//BasicMemory::Test();

	MemoryManager::Test();

	//Pool::Test();

	//MemoryStatus::Test();

	//MemoryCounter::Test();
	
	return 0;
}

