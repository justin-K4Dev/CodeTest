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
		// TBB Lib �ڵ� �ʱ�ȭ - ���������� Lib ������ ���� �ϴ� �޸𸮸� �ʱ�ȭ !!!
		tbb::task_scheduler_init();

		// do something...
	}

	{
		tbb::task_scheduler_init scheduler( tbb::task_scheduler_init::deferred );

		// ����ڰ� ����� thread ������ ���� !!!
		scheduler.initialize( 5 ); // thread count setting

		// do something...
	}

	{
		// ��ü�� �������� �ʱ�ȭ
		CMyClass myClass;
		myClass.DoParallel();
	}
}