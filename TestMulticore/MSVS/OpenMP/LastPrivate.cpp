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
/// @file OMP_LastPrivate.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_LastPrivate()
{
	// 5.1.5 lastprivate ���� ���þ�
	{
	/*
		: lastprivate ���� ���þ�� �����̺� ���� ���þ�� �⺻���� ����� �����ϰ� �����ϰ�
		  ���� ������ �ִ� ������ ������� ���� �ϴ� ����� �߰� �Ǿ���
		  ��� �������� ���� ���� ������ �ִ� ������ �ߺ� �Ǿ� ���� �Ǵ� ���� �ƴ϶�
		  ���������� ���� �Ǵ� �������� �������� ���� ������ ������ ���� ��
		  private & lastprivate ���� ���þ�� ������ ������ �����尡 ���� �Ǹ鼭
		  �޸𸮰� �Ҵ�� �� ���� ������ �ִ� ���� ���� ���� �ʰ� 0 �Ǵ� ������ ������ �ʱ�ȭ �ǹǷ�
		  ������ ���� ���� ������ �ʱ�ȭ ����� ��

		#pragma omp for lastprivate(������)
		#pragma omp for sections lastprivate(������)

		[����]
		- nowait ���� ���þ�� �Բ� ���� lastprivate ���� ���þ�� ������ ����ÿ� ������ �߻� ��
		  �� �ܴ� private �� ����
	*/

		int a = 1;

		#pragma omp parallel
		{

			#pragma omp sections firstprivate(a), lastprivate(a)
			{
				#pragma omp section
				{
					printf("Section 1 - a Init:%d\n", a); // ���� a ������ �ʱⰪ�� ���� a �� ���޵�

					a = 2;

					printf("Section 1 - a Change:%d\n", a); // ���� a ������ ����� ���� ���޵�
				}

				#pragma omp section
				{
					printf("Section 2 : a Init:%d\n", a); // ���� a ������ �ʱⰪ�� ���� a �� ���޵�

					a = 3;

					printf("Section 2 : a Change:%d\n", a); // ���� a ������ ����� ���� ���޵�
				}
			}
		}

		printf("a Last:%d\n", a);

		_getch();
	}
}