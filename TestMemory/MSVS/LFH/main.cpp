// main.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Function.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
		LFH ( Low fragmentation Heap )

		URL : https://msdn.microsoft.com/ko-kr/library/windows/desktop/aa366750(v=vs.85).aspx
		      https://msdn.microsoft.com/en-us/library/windows/desktop/aa366705.aspx
		      
	*/
	{
		LFH::Test();
	}
	
	return 0;
}

