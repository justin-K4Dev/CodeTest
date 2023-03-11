#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:32:55
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/tick_count.h>
#include <tbb/task_scheduler_init.h>


const int COUNT = 10000;

class CUserData
{
public:
	std::string m_strName;
	std::vector<int> m_vtNoList;
	
public:
	CUserData(std::string &strName) : m_strName(strName) { return; }
};

class COverlappedParallelCalculationBody
{
public:
	std::vector<int> *m_pvtNoList;
	int m_nSum;

public:
	COverlappedParallelCalculationBody(std::vector<int> *pvtNoList) : m_pvtNoList(pvtNoList), m_nSum(0)
	{
		return; 
	}
	COverlappedParallelCalculationBody(COverlappedParallelCalculationBody &x, tbb::split) 
	{
		m_pvtNoList = x.m_pvtNoList;
		m_nSum = 0;
	}

	void join( const COverlappedParallelCalculationBody &y )
	{
		m_nSum += y.m_nSum;
	}

	void operator() (const tbb::blocked_range<int> &r)
	{
		for ( int i = r.begin();
			i != r.end();
			++i )
		{
			m_nSum += (*m_pvtNoList)[i];
		}
	}
};

class CMain
{
public:
	std::map<int, CUserData> m_mInfoList;

	int m_nSum[COUNT];

	bool m_bOverlappedParallel;
	
public:
	CMain() 
	{
		memset(m_nSum, 0, sizeof(int) * COUNT);
		m_bOverlappedParallel = false;
	}

	void Init(bool bOverlappedParallel) { m_bOverlappedParallel = bOverlappedParallel; }

	void CalculateBySTL()
	{

	}

	int GetInfo(int nNo)
	{
		auto itPos = m_mInfoList.find(nNo);
		if( itPos == m_mInfoList.end() )
		{
			return 0;
		}

		if( false == m_bOverlappedParallel )
		{
			int nNo = 0;

			CUserData &userInfo = itPos->second;
			for( auto itNoPos = userInfo.m_vtNoList.begin();
				 itNoPos != userInfo.m_vtNoList.end();
				 ++itNoPos )
			{
				nNo += *itNoPos;
			}

			return nNo;
		}
		// 중첩 병렬 처리일 경우
		else
		{
			COverlappedParallelCalculationBody body(&itPos->second.m_vtNoList);

			tbb::parallel_reduce( tbb::blocked_range<int>(0, (int)itPos->second.m_vtNoList.size(), 10000), body);

			return body.m_nSum;
		}

		return 0;
	}
};

class CParallelCalculationBody
{
public:
	std::vector<CUserData*> *m_pvtInfoList;
	CMain *m_pMain;

public:
	CParallelCalculationBody(CMain *pMain)
	{
		_ASSERT(NULL != pMain);
		
		m_pMain = pMain;
	}
	virtual ~CParallelCalculationBody()
	{
		m_pMain = NULL;
	}

	void operator() (const tbb::blocked_range<int> &r) const
	{
		for ( int i = r.begin();
			i != r.end();
			++i )
		{
			m_pMain->m_nSum[i] = m_pMain->GetInfo(i + 1);
		}
	}
};

void CalculateByParallelFor(CMain *pMain)
{
	_ASSERT( NULL != pMain );

	CParallelCalculationBody body( pMain );

	tbb::parallel_for( tbb::blocked_range<int>(0, (int)pMain->m_mInfoList.size()), body, tbb::auto_partitioner() );
}

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_OverlappedParallel.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 4:32:33
///////////////////////////////////////////////////////////////////////////////

void TestTBB_OverlappedParallel()
{
	CMain main;

	for( int n = 1;
		 n <= COUNT;
		 ++n )
	{
		char szBuff[128];
		sprintf_s(szBuff, 128, "Object:%d", n);

		std::string strName;
		strName = szBuff;

		CUserData userInfo( strName );

		for( int j = 1;
				j <= 100;
				++j )
		{
			userInfo.m_vtNoList.push_back(j);
		}

		std::map<int, CUserData>::value_type value(n, userInfo);
		main.m_mInfoList.insert( value );
	}

	{
		std::cout << "parallel_for Algorithm !!!" << std::endl; 
		std::cout << std::endl;

		tbb::task_scheduler_init();

		// parallel for
		main.Init(false);

		tbb::tick_count t0, t1;

		t0 = tbb::tick_count::now();
		CalculateByParallelFor( &main );
		t1 = tbb::tick_count::now();

		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();
	}

	{
		std::cout << "Overlapped Parallel ( parallel_for + parallel_reduce ) Algorithm !!!" << std::endl; 
		std::cout << std::endl;

		tbb::task_scheduler_init();

		// overlapped parallel
		main.Init(true);

		tbb::tick_count t0, t1;

		t0 = tbb::tick_count::now();
		CalculateByParallelFor( &main );
		t1 = tbb::tick_count::now();

		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		_getch();
	}
}


