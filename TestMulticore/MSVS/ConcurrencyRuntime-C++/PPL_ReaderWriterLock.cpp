#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-18-2012 5:09:21
/// @brief 
///       
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <Windows.h>
#include <ppl.h>

//number of iterations each thread performs
static const int NUM_ITERATIONS = 2;
//the shared data that needs protection from race/tearing
static unsigned int sharedData = 0;

//Demonstrates the use of the reader lock
void Reader(Concurrency::reader_writer_lock &mtx)
{
	for( int i = 0; 
		 i < NUM_ITERATIONS; 
		 ++i )
	{
		mtx.lock_read(); // �б� ������ ���� �� �Լ��� ��� !!!

		std::cout << "Reading - Value:" << sharedData << std::endl;
		
		//Sleep for some time, this is to simulate potential work done while holding the lock
		Sleep(1000);

		mtx.unlock();
	}
}

//Demonstrates the use of the writer lock
void Writer(Concurrency::reader_writer_lock &mtx)
{
	for( int i = 0;
		 i < NUM_ITERATIONS; 
		 ++i )
	{
		mtx.lock(); // ���� ������ �����尣 ��Ÿ������ ���� ���� !!! ( data race condition ���� )

		std::cout << "Writing - Value:" << ++sharedData << std::endl;

		//Sleep for some time, this is to simulate potential work done while holding the lock
		Sleep(1000);

		mtx.unlock();
	}

}

///////////////////////////////////////////////////////////////////////////////
/// @file PPL_ReaderWriterLock.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-17-2012 19:21:31
///////////////////////////////////////////////////////////////////////////////

void TestPPL_ReaderWriterLock()
{
	// �⺻ ����
	{
		Concurrency::reader_writer_lock mtx;

		//performs reader writer operations in parallel
		Concurrency::parallel_invoke(
									  [&] { Reader(mtx); },
									  [&] { Reader(mtx); },
									  [&] { Reader(mtx); },
									  [&] { Reader(mtx); },
									  [&] { Writer(mtx); }
									);

		_getch();
	}
}