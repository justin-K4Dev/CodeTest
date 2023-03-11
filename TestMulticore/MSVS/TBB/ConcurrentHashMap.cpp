#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-19-2012 4:41:07
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <hash_map>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_hash_map.h>
#include <array>
#include <tbb/task_scheduler_init.h>
#include <process.h>
#include <tbb/tick_count.h>

/// @brief 해쉬 키, 값 비교 사용자 정의 객체 - justin 8/16/2012 15:22:30
///        아래 맴버 함수들은 필수 !!!
class CHashCompare
{
public:
	// string hash key 생성
	static size_t hash ( const std::string &x )
	{
		size_t h = 0;
		for ( const char* s = x.c_str();
			  *s;
			  ++s )
		{
			h = ( h * 17 ) ^ * s;
			return h;
		}

		return 0;
	}
	// int hash key 생성
	static size_t hash ( const int &x )
	{
		size_t h = x;
		return h;
	}

	// 문자열 비교
	static bool equal ( const std::string &x, const std::string &y )
	{
		return x == y;
	}
	// int 비교
	static bool equal ( const int &x, const int &y )
	{
		return x == y;
	}
};

/// @brief Hash compare 를 재정의 한 것을 사용할  경우 - justin 8/16/2012 15:34:04
typedef tbb::concurrent_hash_map<std::string, int, CHashCompare> CStringUserTable;
/// @brief 기본 tbb_hash_compare 를 사용할 경우 - justin 8/16/2012 15:35:44
typedef tbb::concurrent_hash_map<std::string, int> CStringTable;


/// @brief 병렬 처리용 템플리트 객체 - justin 8/16/2012 15:22:12
template <class T>
class CHashParallelIteration
{
public:
	T m_st;

public:
	CHashParallelIteration(T &st) : m_st(st) { return; }

	void operator() (typename T::range_type &r) const
	{
		for ( auto itPos = r.begin();
			  itPos != r.end();
			  ++itPos )
		{
			char szBuff[128];
			sprintf_s(szBuff, 128, "Parallel concurrent_hash_map - Key:%s, Value:%d", itPos->first.c_str(), itPos->second);

			std::cout << szBuff << std::endl;
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
/// @file TBB_ConcurrentHashMap.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-16-2012 13:33:32
///////////////////////////////////////////////////////////////////////////////

void TestTBB_ConcurrentHashMap()
{
	// 기본 예제
	{
		CStringUserTable st;
		CStringUserTable::accessor ac; // 요소 등록 / 조회시 사용하는 객체 - 내부적 scope lock !!!

		// 요소 추가
		if( st.insert( ac, "test01") )
		{
			ac->second = 1;
			ac.release(); // scope lock 해제
		}

		// 요소 순회
		for ( auto itPos = st.begin();
			  itPos != st.end();
			  ++itPos )
		{
			char szBuff[128];
			sprintf_s(szBuff, 128, "concurrent_hash_map - Key:%s, Value:%d", itPos->first.c_str(), itPos->second);

			std::cout << szBuff << std::endl;
		}

		// 요소 검색
		if ( st.find( ac, "test02") )
		{
			ac.release(); // scope lock 해제
		}

		// 멀티 스레드 기간 검색
		const int nGrainSize = 1000;
		CStringUserTable::range_type r = st.range( nGrainSize );

		tbb::parallel_for( r, CHashParallelIteration<CStringUserTable>( st ), tbb::auto_partitioner() );

		_getch();
	}

	// STL hash_map & concurrent_hash_map 성능 비교
}