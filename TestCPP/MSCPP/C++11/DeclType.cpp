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
			// ������ Ÿ������ ���
			int nHP = 0;
			decltype (nHP) nNPCHP = 5; // int nNPCHP = 5 �� ����
			decltype (nHP + nNPCHP) nTotalHP = 10; // int nTotalHP �� ����
			decltype (nHP) *pnHP = &nHP; // int *pnHP �� ����

			// �Լ��� ��ȯ Ÿ������ ���
			decltype (foo5()) value = 100;
		}
	}

	
	void Test()
	{
		//decltype_keyword();
	}

}// end of DeclType