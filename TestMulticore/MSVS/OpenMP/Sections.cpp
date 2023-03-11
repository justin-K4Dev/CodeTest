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
/// @file OMP_Sections.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_Sections()
{
	// 2.2 sections ���þ�
	{
	/*
		: ������ �ݺ� �۾� ���� ���� �����忡�� �۾� ������ ��� �Ͽ� ���ķ� ó�� �ϴ� ���

		#pragma omp sections [���� ���þ� [,���� ���þ�]...]
		{
			#pragma omp section
			{
				to do here job 1
			}

			#pragma omp section
			{
				to do here job 2
			}
		}

		* ��� ������ ���� ���þ�
		#pragma omp parallel private(������)
		#pragma omp parallel firstprivate(������)
		#pragma omp parallel lastprivate(������)
		#pragma omp parallel reduction(���䷹����:������)
		#pragma omp parallel schedule(���� [,üũ������])
		#pragma omp parallel collapse(����)
		#pragma omp parallel ordered
		#pragma omp parallel nowait

		[����]
		- #pragma omp section ���þ�� �ܵ����� ��� �� �� ����, #pragma omp sections ���þ� ���� �ȿ� �־�� ��
		- #pragma omp section ���þ� �ȿ� �� section �� �ڵ�� ���԰� ���ᰡ 1���� ���� �� �̾�� ��
		  �ϳ��� section �ȿ��� �ٸ� section �������� �б� �� �� ����
		- #pragma omp section ���þ�� 1���� nowait ���� ���þ ��� �� �� �ְ�,
		  #pragma omp parallel sections ó�� ���� ���þ� ������ nowait ���� ���þ ��� �� �� ����
		- ���� for ���� �ȿ��� throw �� ���ܴ� ���� ���� ���������� catch �ؾ� �� !!!
	*/

		const int MAX = 10000;
		int nCount = 0;

		float *pData1 = new float[MAX];
		float *pData2 = new float[MAX];

		for ( int nCount = 0;
			  nCount < MAX;
			  ++nCount )
		{
			pData1[nCount] = (float)nCount;
		}

		for ( int nCount = 0;
			  nCount < MAX;
			  ++nCount )
		{
			pData2[nCount] = (float)nCount;
		}

		printf("omp sections Start !!!\n");

		#pragma omp parallel
		{
			#pragma omp sections // ���� �й� ���� ����
			{
				#pragma omp section // ���� �й� 1 ���� ���� ���� - 1 ���� thread ���
				{
					for ( int nCount = 0;
						nCount < MAX;
						++nCount )
					{
						pData1[nCount] = sqrt (pData1[nCount]);

						printf("section 1 - LoopID:%d, ThreadNo:%d\n", nCount, omp_get_thread_num());
					}
				}

				#pragma omp section // ���� �й� 2 ���� ���� ���� - 1 ���� thread ���
				{
					for ( int nCount = 0;
						  nCount < MAX;
						  ++nCount )
					{
						pData2[nCount] = sqrt (pData2[nCount]);

						printf("section 2 - LoopID:%d, ThreadNo:%d\n", nCount, omp_get_thread_num());
					}
				}
			}
		}

		printf("omp sections End !!!\n");

		delete [] pData1;
		delete [] pData2;

		_getch();
	}
}