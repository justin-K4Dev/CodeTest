#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:34:42
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/tick_count.h>
#include <math.h>
#include <vector>
#include <tbb/task_scheduler_init.h>


class CTBBTest1
{
public:
	std::vector<int>* const m_vecTest;

public:
	CTBBTest1(std::vector<int> &vecTemp) : m_vecTest(&vecTemp) { return; }

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

	void Do()
	{
		if( NULL == m_vecTest )
			return;

		int n = 0;
		for( auto itPos = m_vecTest->begin(); 
			 itPos != m_vecTest->end(); 
			 ++itPos )    
		{      
			(*m_vecTest)[n] = *itPos;

			++n;
		}  
	}

	void operator() (tbb::blocked_range<int> &r) const
	{
		std::vector<int>* vecTemp = m_vecTest;    
		
		for( int i = r.begin(); 
			 i != r.end(); 
			 ++i )    
		{      
			(*vecTemp)[i] = i;    
		}  
	}
};

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ParallelFor.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-13-2012 14:00:20
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ParallelFor()
{
	std::cout << "Example for TBB Parallel Algorithm" << std::endl;
	std::cout << std::endl;

	{
		// for
		std::cout << "parallel_for Algorithm !!!" << std::endl; 
		std::cout << std::endl;

		const int MAX_NUM = 100000000; 
 		tbb::tick_count t0, t1;
		
		std::vector<int> vecTest(MAX_NUM);

		CTBBTest1 tbbTest(vecTest);
		tbbTest.FillValue();

		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief None Parallel
		///      
		t0 = tbb::tick_count::now();
		tbbTest.Do();
		t1 = tbb::tick_count::now();

		std::cout << "Generic STL Use" << std::endl; 
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;

		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief None Grain Size
		///   
		t0 = tbb::tick_count::now();
		tbb::parallel_for( tbb::blocked_range<int>(0, MAX_NUM), CTBBTest1(vecTest) );
		t1 = tbb::tick_count::now();

		std::cout << "None Grain Use" << std::endl; 
		std::cout << "Block range (" << "0 ~ " << MAX_NUM << ") " << "GrainSize: None" << std::endl;
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;


		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief User Grain Size
		///  
		t0 = tbb::tick_count::now();
		tbb::parallel_for( tbb::blocked_range<int>(0, MAX_NUM, MAX_NUM / 4), CTBBTest1(vecTest) );
		t1 = tbb::tick_count::now();

		std::cout << "User Parallel Use" << std::endl; 
		std::cout << "Block range (" << "0 ~ " << MAX_NUM << ") " << "GrainSize: " << MAX_NUM / 4 << std::endl; 
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;


		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief Auto Parallel
		///  
		t0 = tbb::tick_count::now();
		tbb::parallel_for( tbb::blocked_range<int>(0, MAX_NUM), CTBBTest1(vecTest), tbb::auto_partitioner() );
		t1 = tbb::tick_count::now();

		std::cout << "Auto Parallel Use" << std::endl; 
		std::cout << "Block range (" << "0 ~ " << MAX_NUM << ") " << "GrainSize: Auto" << std::endl; 
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;


		/// @author justin  @date 8-10-2012 17:56:05
		/// @brief Lambda Parallel
		///  
		t0 = tbb::tick_count::now();
		tbb::parallel_for( tbb::blocked_range<int>(0, MAX_NUM), [&vecTest] ( const tbb::blocked_range<int> &r )  
		                                                        {
																	for( int i = r.begin(); 
																		 i != r.end();
																		 ++i )    
																	{     
																		vecTest[i] = i;    
																	}  
		                                                        } );
		t1 = tbb::tick_count::now();

		std::cout << "Lambda Parallel Use" << std::endl; 
		std::cout << "Block range (" << "0 ~ " << MAX_NUM << ") " << "GrainSize: None" << std::endl; 
		std::cout << "Elapsed Time: " << ((t1 - t0).seconds() * 1000) << " msec" << std::endl;
		std::cout << std::endl;


		_getch();
	}
}