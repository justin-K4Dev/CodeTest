#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 1:02:20
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tbb/tbb.h>
#include <tbb/concurrent_unordered_map.h>

class CDoUnorderMapBody 
{
public:  
	void operator() (tbb::concurrent_unordered_map<int, int>::range_type& range) const
	{
		for ( auto itPos = range.begin(); 
			  itPos != range.end();
			  ++itPos )
		{      
			char szBuff[128];
			sprintf_s(szBuff, 128, "Map Info - Key: %d, Value: %d", itPos->first, itPos->second);
			std::cout << szBuff << std::endl;
		}  
	}
};


///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentUnorderedMap.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-19-2012 0:52:54
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ConcurrentUnorderedMap()
{
	{
		// body 객체 사용

		tbb::concurrent_unordered_map<int, int> mapTest;   
		
		for ( int i = 0;
			  i < 100;
			  ++i )  
		{
			mapTest.insert(tbb::concurrent_unordered_map<int, int>::value_type(i, i * 100));  
		}   
		
		tbb::parallel_for( mapTest.range(), CDoUnorderMapBody(), tbb::auto_partitioner() );

		_getch();
	}
	
	{
		// lambda 사용

		tbb::concurrent_unordered_map<int, int> mapTest;   
		
		for ( int i = 0;
			  i < 100;
			  ++i )  
		{
			mapTest.insert(tbb::concurrent_unordered_map<int, int>::value_type(i, i * 100));  
		}   
		
		tbb::parallel_for( mapTest.range(), 
			               [] ( const tbb::concurrent_unordered_map<int, int>::range_type &range)
						   {
							   for ( auto itPos = range.begin();
								     itPos != range.end();
								     ++itPos )
							   {      
								   char szBuff[128];
								   sprintf_s(szBuff, 128, "Map Info - Key: %d, Value: %d", itPos->first, itPos->second);
								   std::cout << szBuff << std::endl;
							   }  
		                   }, tbb::auto_partitioner()
					     );

		_getch();
	}
}