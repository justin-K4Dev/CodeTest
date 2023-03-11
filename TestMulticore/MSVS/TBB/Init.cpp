#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:46:35
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <tbb/task_scheduler_init.h>

class CMyClass
{
public:
	tbb::task_scheduler_init *m_pTBBInit;

public:
	CMyClass() { m_pTBBInit = NULL; }
	~CMyClass() { if (m_pTBBInit != NULL) delete m_pTBBInit; }

	void DoParallel()
	{
		m_pTBBInit = new tbb::task_scheduler_init();
	}
};

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_Init.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 4:46:43
///////////////////////////////////////////////////////////////////////////////

void TestTBB_Init()
{
	{
		// TBB Lib 자동 초기화 - 내부적으로 Lib 내에서 관리 하는 메모리를 초기화 !!!
		tbb::task_scheduler_init();

		// do something...
	}

	{
		tbb::task_scheduler_init scheduler( tbb::task_scheduler_init::deferred );

		// 사용자가 사용할 thread 갯수를 설정 !!!
		scheduler.initialize( 5 ); // thread count setting

		// do something...
	}

	{
		// 객체로 생성으로 초기화
		CMyClass myClass;
		myClass.DoParallel();
	}
}