#include "..\stdafx.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <new>
#include <array>

/*
	현재 프로젝트를 빌드 후에
	디버깅시 디어셈블리로 변환 하여
	분석할 함수의 어셈블리 코드를 리뷰 해보자.

	호출하는 함수를 주석 처리하면 어셈블리 코드는 생성하지 않는다.
*/

namespace Cpp2Asm
{
	int asm_simple()
	{
		return 1;
	}

	void asm_integer()
	{
		int num1, num2, result;

		num1 = 5;
		num2 = 6;
		result = num1 + num2;

		printf("%d + %d = %d\n", num1, num2, result);

		return;
	}

	void asm_string()
	{
		char chArray[] = "Hello World";

		printf("%s\n", chArray);
	}

	void asm_loop()
	{
		for (int i = 0; i < 5; i++)
		{
			printf("loop Count: %d\n", i);
		}

		return;
	}

	void asm_if()
	{
		int cond = 100;

		if(cond == 100)
		{
			printf("Condition: True");
		}
		else
		{
			printf("Condition: False !!!");
		}

		return;
	}

	bool function_params_16( bool arg01, __int16 arg02, __int32 arg03, __int64 arg04
		                   , bool arg05, __int16 arg06, __int32 arg07, __int64 arg08
	                       , bool arg09, __int16 arg10, __int32 arg11, __int64 arg12
	                       , bool arg13, __int16 arg14, __int32 arg15, __int64 arg16 )
	{
		int local_value = 10000;

		printf( "arg1:%d, arg2:%d, arg3:%d, arg4:%lld, arg5:%d, arg6:%d, arg7:%d, arg8:%lld, arg9:%d, arg10:%d, arg11:%d, arg12:%lld, arg13:%d, arg14:%d, arg15:%d, arg16:%lld\n"
			  , arg01, arg02, arg03, arg04, arg05, arg06, arg07, arg08
		      , arg09, arg10, arg11, arg12, arg13, arg14, arg15, arg16 );

		return true;
	}

	bool function_params_7( __int32 arg01, __int32 arg02, __int32 arg03, __int32 arg04
		                  , __int32 arg05, __int32 arg06, __int32 arg07 )
	{
		printf( "arg1:%d, arg2:%d, arg3:%d, arg4:%d, arg5:%d, arg6:%d, arg7:%d\n"
			  , arg01, arg02, arg03, arg04, arg05, arg06, arg07 );

		return true;
	}

	__int32 function_params_2( __int32 arg01, __int32 arg02 )
	{
		__int32 local1 = 30;
		__int32 local2 = 60;

		__int32 sum = arg01 + arg02 + local1 + local2;

		return sum;
	}

	void asm_function_args()
	{
		function_params_2( 1, 2 );

		function_params_7( 1, 2, 3, 4, 5, 6, 7 );

		function_params_16( true, 2, 3, 4, false, 6, 7, 8, true, 10, 11, 12, false, 14, 15, 16 );

		return;
	}


	void Test()
	{
		asm_function_args();

		asm_if();

		asm_loop();

		asm_string();

		asm_integer();

		asm_simple();

		system("pause");
	}
}