#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:35:29
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_while.h>
#include <tbb/tick_count.h>

const int COUNT = 10000;

class CObject
{
public:
	CObject *m_pNext;
	
public:
	CObject() : m_pNext(NULL) { return; }

	CObject* GetNext() { return m_pNext; }
};

class CStream
{
public:
	CObject *m_pElement;

public:
	CStream(CObject *pRoot) : m_pElement(pRoot) { return; }

	bool pop_if_present(CObject *&pObj)
	{
		if(NULL == pObj)
			return false;

		pObj = m_pElement;

		m_pElement = m_pElement->GetNext();
		return true;
	}
};

void ProcessSerial( CObject *pRoot ) 
{
	int nCount = 0;
	for( CObject *ptr = pRoot; 
		 ptr != NULL;
		 ++nCount, ptr = ptr->GetNext() ) 
	{
		if(nCount > COUNT)
		{
			std::cout << "Overrun Object Count !!!" << std::endl;
		}
	}
}

class CProcessParallelBody
{
public:
	typedef CObject * argument_type;

public:
	void operator() ( CObject *pObj ) const
	{
		ProcessSerial(pObj);
	}
};

void DoSerial( CObject *pRoot )
{
	CObject *pObj = pRoot;
	while( pObj != NULL )
	{
		ProcessSerial(pObj);

		pObj = pObj->GetNext();
	}
}

void DoParallel(CObject *pObj)
{
	tbb::parallel_while<CProcessParallelBody> w;
	CStream stream(pObj);
	CProcessParallelBody body;
	w.run(stream, body);
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelWhile.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-8-2012 13:22:49
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ParallelWhile()
{
	{
		// while
		std::cout << "parallel_while Algorithm !!!" << std::endl; 
		std::cout << std::endl;

		tbb::tick_count t0, t1;

		CObject *pFirst = NULL;
		CObject *pPrevItem = NULL;
		for( int n = 0;
			 n <= COUNT;
			 ++n )
		{
			 CObject *pNext = new CObject;

			 if(NULL == pPrevItem)
			 {
				 pPrevItem = pNext;
				 pFirst = pNext;
			 }
			 else
			 {
				 pPrevItem->m_pNext = pNext;
				 pPrevItem = pNext;
			 }
		}

		// 일반적인 직렬 순회 연산
		t0 = tbb::tick_count::now();
		DoSerial(pFirst);
		t1 = tbb::tick_count::now();

		std::cout << "Normal navigating Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		// Parallel While 순회 연산
		t0 = tbb::tick_count::now();
		DoParallel(pFirst);
		t1 = tbb::tick_count::now();

		std::cout << "parallel_while Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();
	}
}