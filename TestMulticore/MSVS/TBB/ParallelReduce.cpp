#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:34:19
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/tick_count.h>
#include <math.h>
#include <vector>

class CTBBTest2
{
public:
	std::vector<int>* const m_vecTest;
	int m_nSum;

public:
	CTBBTest2(std::vector<int> &vecTemp) : m_vecTest(&vecTemp), m_nSum(0) { return; }
	// 분열 생성자 - 스레드별로 분열 생성자를 통해서 CTBBTest2 객체를 생성 시킴 !!!
	CTBBTest2(CTBBTest2 &tbbTest, tbb::split) : m_vecTest(tbbTest.m_vecTest), m_nSum(0) { return; }

	void FillValue()
	{
		int n = 0;
		for( auto itPos = m_vecTest->begin(); 
			 itPos != m_vecTest->end(); 
			 ++itPos )    
		{      
			(*m_vecTest)[n] = n;

			++n;
		} 
	}

	void Calculate()
	{
		if( NULL == m_vecTest )
			return;

		int n = 0;
		for( auto itPos = m_vecTest->begin(); 
			 itPos != m_vecTest->end(); 
			 ++itPos )    
		{      
			m_nSum += *itPos;
		} 
	}

	void Reset() { m_nSum = 0; }

	void operator() (const tbb::blocked_range<int> &r)
	{
		std::vector<int>* vecTemp = m_vecTest;    

		for( int i = r.begin(); 
			i != r.end(); 
			++i )    
		{      
			m_nSum += (*vecTemp)[i];
		}  
	} 

	// 각 스레드별로 생성된 CTBBTest2 객체들은 operator() 맴버 함수 처리 후
	// CTBBTest2 root 객체의 join 맴버 함수를 호출 !!!
	void join(const CTBBTest2 &tbbTest)
	{
		m_nSum += tbbTest.m_nSum;
	}
};


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelReduce.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-13-2012 13:57:50
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ParallelReduce()
{
	{
		// reduce
		std::cout << "parallel_reduce Algorithm !!!" << std::endl; 
		std::cout << std::endl;

		const int MAX_NUM = 100000000; 
		tbb::tick_count t0, t1;

		std::vector<int> vecTest(MAX_NUM);

		CTBBTest2 tbbTest(vecTest);
		tbbTest.FillValue();	


		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief None Parallel
		///      
		t0 = tbb::tick_count::now();
		tbbTest.Calculate();
		t1 = tbb::tick_count::now();

		std::cout << "Generic STL Use" << std::endl; 
		std::cout << "Sum: " << tbbTest.m_nSum << std::endl;
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;


		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief User Grain Use
		///
		tbbTest.Reset();
		t0 = tbb::tick_count::now();
		tbb::parallel_reduce( tbb::blocked_range<int>(0, MAX_NUM, MAX_NUM / 4), tbbTest );
		t1 = tbb::tick_count::now();


		std::cout << "User Grain Use" << std::endl; 
		std::cout << "Block range (" << "0 ~ " << MAX_NUM << ") " << "GrainSize: " << MAX_NUM / 4 << std::endl; 
		std::cout << "Sum: " << tbbTest.m_nSum << std::endl;
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;


		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief Lambda Parallel
		///
		int nSum = 0;
		t0 = tbb::tick_count::now();
		tbb::parallel_for( tbb::blocked_range<int>(0, MAX_NUM, MAX_NUM / 4), [&] ( const tbb::blocked_range<int> &r )  
																			 {
																				for( int i = r.begin(); 
																				     i != r.end();
																					 ++i )    
																				{     
																					nSum += vecTest[i];
																				}  
																			 } );
		t1 = tbb::tick_count::now();

		std::cout << "Lambda Parallel Use" << std::endl; 
		std::cout << "Block range (" << "0 ~ " << MAX_NUM << ") " << "GrainSize: " << MAX_NUM / 4 << std::endl; 
		std::cout << "Sum: " << nSum << std::endl;
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;
		
		_getch();
	}
}