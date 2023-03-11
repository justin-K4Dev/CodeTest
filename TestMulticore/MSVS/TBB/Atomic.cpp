#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-18-2012 5:09:21
/// @brief 
///        TBB 원자적 연산 (Atomic Operation)
///        - Multi-thread 기반 개발시 데이터 동기화를 간단하게 보장
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
	g_nValue = 0; // 초기화

	// + 연산 ( + 10 )	
	g_nValue.fetch_and_add( 10 );

	// ++ 연산
	g_nValue.fetch_and_increment();

	// -- 연산
	g_nValue.fetch_and_decrement();

	// = 연산
	g_nValue.fetch_and_store( 100 );

	// == 경우에는 = 연산 (조건적 = 연산)
	g_nValue.compare_and_swap( 1000, 100 ); // ( New, Compare )

	_getch();
}
