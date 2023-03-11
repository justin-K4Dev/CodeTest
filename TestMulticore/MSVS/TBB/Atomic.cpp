#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-18-2012 5:09:21
/// @brief 
///        TBB ������ ���� (Atomic Operation)
///        - Multi-thread ��� ���߽� ������ ����ȭ�� �����ϰ� ����
///
///////////////////////////////////////////////////////////////////////////////

#include <tbb/atomic.h>

tbb::atomic<int> g_nValue;


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_Atomic.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-18-2012 5:15:11
///////////////////////////////////////////////////////////////////////////////

void TestTBB_Atomic()
{
	g_nValue = 0; // �ʱ�ȭ

	// + ���� ( + 10 )	
	g_nValue.fetch_and_add( 10 );

	// ++ ����
	g_nValue.fetch_and_increment();

	// -- ����
	g_nValue.fetch_and_decrement();

	// = ����
	g_nValue.fetch_and_store( 100 );

	// == ��쿡�� = ���� (������ = ����)
	g_nValue.compare_and_swap( 1000, 100 ); // ( New, Compare )

	_getch();
}
