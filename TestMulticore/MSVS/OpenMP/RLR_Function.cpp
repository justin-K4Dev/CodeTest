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
/// @file OMP_RLR_Function.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-22-2012 13:04:36
///////////////////////////////////////////////////////////////////////////////

void TestOMP_RLR_Function()
{
	// 6 OpenMP 실시간 라이브러리 함수
	/*
		: 제작이 완료되어 배포된 프로그램을 사용하는 사람이 사용하는 PC의 성능이 항상 같은 환경일 수 없음
		  OpenMP 에서는 프로그램 실행중 환경에 맞추어 병렬 처리를 하고 성능 차이를 제어 하기 위해
		  실시간 라이브러리 API 를 제공 하고 있음
		  몇가지 실시간 라이브러리 함수는 OpenMP 환경 변수와 연동하여 사용

		  기본적으로 OpenMP 런타임 API를 프로그램으로 이용 하려면 omp.h 를 include 해야 함
		  omp.h 는 각 컴파일러가 제공 하는 include 파일 폴더에 포함 되어 있음
		  컴파일러 벤더 마다 내부 구현이 다르기 때문에 해당 벤더가 제공 하는 omp.h 파일을 사용 해야함

		* 스레드 실행 환경 제어 함수
			
		  omp_set_num_threads()
		  omp_get_num_threads()
		  omp_get_max_threads()
		  omp_get_thread_num()
		  omp_get_num_procs()
		  omp_in_parallel()
		  omp_set_dynamic()
		  omp_get_dynamic()
		  omp_set_nested()
		  omp_get_nested()
		  omp_set_schedule()
		  omp_get_schedule()
		  omp_get_thread_limit()
		  omp_set_max_active_levels()
		  omp_get_max_active_levels()
		  omp_get_level()
		  omp_get_ancestor_thread_num()
		  omp_get_team_size()
		  omp_get_active_level()
	*/

	// 6.1 omp_set_num_threads()
	{
	/*
		: OpenMP의 parallel 지시어를 사용하여 병렬 영역 스레드 팀을 구성할 때 생성될 스레드 갯수를 지정함
		  병렬 영역 앞에서 여러번 호출했을 경우, 제일 마지막에 설정된 값이 적용됨
		  보통 #pragma omp parallel 영역의 직전에 사용함
		  이 함수는 팀에서 생성할 스레드 수를 정할 때 사용하는 nthreads-var 내부 제어 변숫값을
		  인수로 전달하는 nthreads 값으로 변경함
		  병렬 영역 내에서 이 함수를 호출할 경우, 이미 구성된 스레드 팀의 스레드 개수는 변경할 수 없음 
		  환경변수 OMP_NUM_THREADS 로 스레드 수가 지정하는 것보다 API가 우선하여 적용됨

		void omp_set_num_threas(int nthreads)
		argument: nthreads - 스레드 팀 생성 시 설정할 스레드 수

		* 관련 함수
		omp_get_num_threads();
		omp_get_max_threads();
		환경변수 OMP_NUM_THREADS
		parallel 지시어의 num_threads 보조 지시어
	*/

		_getch();
	}

	// 6.2 omp_get_num_threads()
	{
	/*
		: 현재 동작하는 병렬 영역에서 OpenMP가 생성한 스레드 개수를 반환함
		  병렬 영역이 아닌 지역에서 호출되면 '1'을 반환함
          omp_set_num_threads() 또는 #pragma omp parallel num_threas(스레드수) 보조 지시어를 사용하여
		  스레드 수를 설정하지 않은 경우에는 시스템의 프로세서 코어 수
		  또는 환경변수 OMP_NUM_THREADS가 설정된 값으로 반환함
		  동작하고 있는 병렬 영역 내에서 omp_set_num_threads() 함수를 호출하여
		  생성할 스레드 수의 설정이 변경되어도 omp_get_num_threads()는 스레드 팀의 구성이
		  이미 끝났기 때문에 현재 동작하고 있는 스레드 수를 반환함

		int omp_get_num_threads(void)
		return: 생성된 스레드 팀의 수

		* 관련 함수
		환경변수 OMP_NUM_THREADS
		#pragma omp parallel 지시어의 num_threads 보조 지시어
		omp_set_num_threads()
	*/
		_getch();
	}

	// 6.3 omp_get_max_threads()
	{
	/*
		: 스레드 팀에서 생성할 스레드 개수에 대한 설정값을 반환함
		  omp_get_max_threads() 라는 함수 이름으로 약간이 혼동이 올수 있으나
		  단순히 omp_set_num_threads 함수를 이용하여 설정된 변수값을 반환함
		  다시 말해 이 함수는 OpenMP 실시간 라이브러리 에서 생성할 스레드 수를 정할 때
		  사용하는 nthreads-var 내부제어 변숫값을 반환함
		  omp_get_max_threads 함수는 이후 스레드 팀을 생성할 때 사용되는 변숫값을 반환 하고,
		  omp_get_num_threads 함수는 병렬 영역 실행중에 현재 동작하는 스래드 개수를 반환함
          omp_set_num_threads 함수를 이용한 스레드 개수가 설정되어 있지 않은 경우,
		  시스템의 디폴트 프로세서-코어 수 또는 환경변수 OMP_NUM_THREADS가 설정된 값을 반환함
		  omp_get_max_threads()는 병렬 영역 내외에 관계없이 omp_set_num_threads(n)로 설정된 스레드 수를 반환함

		int omp_get_max_threads(void)
		return: 생성 시 사용할 스레드 팀의 스레드 수
		
		* 관련 함수
		OMP_NUM_THREADS 환경변수
		parallel 지시어 num_threads() 보조 지시어
		omp_set_num_threads()
	*/
		_getch();
	}

	// 6.4 omp_get_thread_num()
	{
	/*
		: OpenMP 병렬 영역에서 이 함수를 호출하여 실행되고 있는 스레드의 번호를 반환함 
		  스레드 번호는 0으로 부터 시작되고 1, 2, 3, 4, 로 증가함
		  스레드 팀의 마스터 스레드는 '0'이 지정됨
		  또 순차 영역에서 호출하면 '0'을 반환함
		  OpenMP에서 병렬 작업을 배분하기 위해 스레드 ID로 사용하는데 유용함
		
		int omp_get_thread_num(void)
		return: 현재 실행되고 있는 스레드의 번호

		* 관련 함수
		omp_get_num_threads()

		[주의]
		- #pragma omp task 지시어를 사용할 때, 실행 중의 task가 중지되었다가
		  반드시 동일한 스레드로 재개해야 하는 경우를 타이드 태스크라고 함
		  다른 스레드가 중지된 작업을 재개해도 괜찮은 경우를 언타이드 태스크라고 함
		  untied-task로 실행될 때 omp_get_thread_num 함수를 호출하면
		  스레드 번호가 바뀔수 있으니 유의 해야함
	*/
		_getch();
	}

	// 6.5 omp_get_num_procs()
	{
	/*
		: omp_get_num_procs()는 프로그램이 이용 가능한 프로세서 개수를 반환함
		  통상적으로, OS가 인식하는 프로세서 개수와 동일함
		  omp_get_num_procs()는 OpenMP 병렬 영역 안이나 순차 영역에서도 같은 값을 반환함

		int omp_get_num_procs(void)
		return: 프로세서 코어의 개수
	*/
		_getch();
	}

	// 6.6 omp_set_dynamic()
	{
	/*
		: 설정된 생성 스레드 수가 시스템 프로세서 코어의 수보다 많은면 오히려 병렬처리에 효율이 떨어질 수 있음
		  인수에 1을 설정하여 이 함수를 호출하면 시스템 프로세서 코어 수보다 스레드 수가 많이 설정된 경우
		  그 값을 자동으로 프로세서 코어 수로 낮추어 줌
		  예를 들어 omp_set_num_threads(4)를 이용해 OpenMP 병렬 영역의 스레드 수가 4개로 설정된 코드를
		  듀얼코어 CPU로 실행하면 스레드 수가 CPU의 코어 수보다 많아 지는데
		  만일 omp_set_dynamic(1)로 지정 되어 있다면,
		  스레드 수를 4로 지정해도 실제로 동작하는 스레드수는 코어 수와 같은 2로 조정됨

	     void omp_set_dynamic(int dynamic_threads)
	     argument: (dynamic_threads) : true = 1, false = 0

		 * 관련 함수
		 omp_set_num_threads() 나 num_threads 보조 지시어의 설정에 영향을 줌
		 omp_get_num_threads() 로 취득하는 값은 조정 후의 값이 됨
	     환경 변수 OMP_DYNAMIC를 이용하여 똑같은 제어가 가능함
	*/
		_getch();
	}

	// 6.7 omp_in_parallel()
	{
	/*
		: omp_in_parallel() 함수가 호출된 위치가 OpenMP 병렬 영역 내인지 아닌지를 판정하는 기능을 제공함
		  OpenMP 병렬 영역이면 true, 아니면 false를 반환함

		int omp_in_parallel(void)
		return: true = 1, false = 0
	*/
		_getch();
	}

	// 6.8 omp_set_nested()
	{
	/*
		: OpenMP 2.5 이하의 버전에서는 2중 for 루프 이상 또는 매트릭스 형태로 되어 있는
		  계산에서 병렬처리를 지원하지 못했음

		  #pragma omp parallel for
		  for (int i = 0; i < 10; ++i)
		  {
		      #pragma omp prarallel for
		      for (int j = 0; j < 10; j++) 
			  {
		          //병렬처리
			  }
		  }

	      위의 코드 처럼 병렬처리 안에 또다시 병렬처리가 들어있는 것을 내포(nested)하고 있다고 함
		  2중 for 루프 이상의 경우 최외각 #pragma omp for 지시어가 호출된 영역에만 병렬처리가 지원됨
		  통상적으로 실행할 계산의 알고리즘에 맞추어 최외각 for 루프에서 프로세서 개수와 스레드 개수가
		  동일한 개수로 구현하기 때문에 내포 영역에 대해서 병렬화를 하고 추가로 스레드를 생성하여도
		  효율성은 크게 증가하지 않음

		  내포 병렬화를 지원하면 효율성이 많이 증가하지는 않겠지만
		  개발자가 알고리즘에 맞추어 병렬화 하는것을 자동화해주기 때문에 편의성을 약간 증가함
		  하지만 자동화라고 하는 것이 편리한 만큼 개발자가 집적 최적화한 것에 비해 효율이 덜어질 수 있는 문제는 항상 존재함

	      내포 병렬화는 OpenMP 3.0부터 지원을 하는데 omp_set_nested() 함수는
		  내포 병렬화에 대한 사용여부를 설정하는 기능을 함 
		  인수를 1로 설정하면 내포 병렬화를 사용하고, 0으로 설정하면 사용하지 않음
		  이 함수는 내부 제어 변수 nest-var의 값을 설정하는 기능을 함

		void omp_set_nested(int nested)
		argument: true = 1, false = 0
	*/
		_getch();
	}

}