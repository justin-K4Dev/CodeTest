#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-22-2012 13:04:23
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <omp.h>


///////////////////////////////////////////////////////////////////////////////
/// @file OMP_Master.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Master()
{
	// 3.1 master 지시어
	{
	/*
		: 스레드 팀에서 마스터 스레드가 해당 코드를 실행 하도록 함
		  #pragma omp master 지시어는 동기화를 지원 하지 않기 때문에
		  다른 스레드들이 이후에 나오는 코드를 수행 하게 되므로
		  마스터 스레드가 완료 될 때 까지 대기 하려면 barrier 지시어를 사용 해야 함

		#pragma omp master
		{
			to do here job
		}

		[주의]
		- #pragma omp master 지시어 영역 에서 실행된 throw 는 
		  #pragma omp master 지시어의 같은 영역 내에서 실행을 재개 해야 함
		  그리고 throw 된 예외는 동일한 스레드에 의해서 catch 해야 함
	*/

		const int MAX = 1000000;
		float *Data;
		Data = new float[MAX];

		int iCount = 0;
		for (iCount = 0; iCount < MAX; iCount++) {
			Data[iCount] = (float)iCount;
		}

		#pragma omp parallel
		{
			#pragma omp for

			for (iCount = 0; iCount < MAX; iCount++) {
				Data[iCount] = sqrt(Data[iCount]);
			}

			//결과 출력

			#pragma omp master
			for (iCount = 0; iCount < MAX; iCount++) {
				printf("Data[%d] = %.4f\n", iCount, Data[iCount]);
			}

			//명시적인 배리어
			#pragma omp barrier
			#pragma omp for
			for (iCount = 0; iCount < MAX; iCount++) {
				Data[iCount] = log(Data[iCount]);
			}

		}

		delete Data;

		_getch();
	}

}