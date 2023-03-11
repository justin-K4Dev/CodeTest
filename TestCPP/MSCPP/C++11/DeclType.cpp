#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file decltype.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 7-27-2012 2:23:21
///////////////////////////////////////////////////////////////////////////////

namespace DeclType
{
	// decltype keyword example
	int foo5() { return 0; }

	void decltype_keyword()
	{
		// decltype keyword
		{
			// 변수의 타입으로 사용
			int nHP = 0;
			decltype (nHP) nNPCHP = 5; // int nNPCHP = 5 과 동일
			decltype (nHP + nNPCHP) nTotalHP = 10; // int nTotalHP 와 동일
			decltype (nHP) *pnHP = &nHP; // int *pnHP 와 동일

			// 함수의 반환 타입으로 사용
			decltype (foo5()) value = 100;
		}
	}

	
	void Test()
	{
		//decltype_keyword();
	}

}// end of DeclType