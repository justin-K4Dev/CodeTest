#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-18-2012 5:09:21
/// @brief 
///       
///
///////////////////////////////////////////////////////////////////////////////

#include <tbb/mutex.h>
#include <tbb/spin_mutex.h>

class CNode 
{
public:
	CNode *pNext;

public:
	CNode() : pNext(NULL) { return; }
};

CNode *pNodeTail;

template<typename Mutex>
CNode* AllocateNode(Mutex &mtx)
{
	CNode *pNode = NULL;

	{
		Mutex::scoped_lock lock(mtx);
		pNode = pNodeTail;

		if( NULL != pNode )
		{
			pNodeTail = pNode->pNext;
		}
	}

	if( NULL == pNode )
	{
		pNode = new CNode();
	}

	return pNode;
}

template<typename Mutex>
void FreeNode(Mutex &mtx, CNode *pNode)
{
	Mutex::scoped_lock lock(mtx);
	pNode->pNext = pNodeTail;
	pNodeTail = pNode;
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_Mutex.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-17-2012 19:21:31
///////////////////////////////////////////////////////////////////////////////

void TestTBB_Mutex()
{
	{
		// 老馆利牢 spin lock 按眉客 悼老
		tbb::spin_mutex mtx;

		CNode *pNode = AllocateNode<tbb::spin_mutex>( mtx );
		if( NULL != pNode)
		{
			FreeNode<tbb::spin_mutex>( mtx, pNode );
		}

		_getch();
	}
}