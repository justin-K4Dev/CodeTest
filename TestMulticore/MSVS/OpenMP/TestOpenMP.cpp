// TestMultiCore.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @file TestMultiCore.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 3:01:41
///////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	{
		/// @brief OpenMP Test function - justin 8/19/2012 3:02:29

	//	TestOMP_Concept();

	//	TestOMP_MemoryScope();

		TestOMP_Directive();

		TestOMP_RLR_Function();
	}

	return 0;
}

