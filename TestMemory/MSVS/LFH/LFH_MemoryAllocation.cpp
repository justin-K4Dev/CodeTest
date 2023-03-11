#include "stdafx.h"
#include "Function.h"

#include <windows.h>

namespace LFH
{
	#define HEAP_LFH 2

	void use_lfh_in_custom_heap()
	{
		/*
			Create a new heap with default parameters.
		*/
		{
			HANDLE hHeap = HeapCreate(0, 0, 0);
			if (NULL == hHeap) {
				_tprintf( TEXT("Failed to create a new heap with Last Error %d.\n")
						, GetLastError() );
			}

			// Enable the low-fragmenation heap (LFH).
			// Starting with Windows Vista, the LFH is enabled by default
			// but this call does not cause an error.

			BOOL bResult;
			ULONG enableLFH = HEAP_LFH;

			bResult = HeapSetInformation( hHeap
										, HeapCompatibilityInformation
										, &enableLFH
										, sizeof(enableLFH) );
			if (TRUE == bResult) {
				_tprintf( TEXT("The LFH has been enabled.\n") );
			}
			else {
				_tprintf( TEXT("Failed to enable the LFH with Last Error %d.\n")
						, GetLastError() );
			}

			// When a process is run under any debugger,
			// certain heap debug options are automatically enabled for all heaps in the process.
			// These heap debug options prevent the use of the LFH.
			// To enable the low-fragmentation heap when running under a debugger,
			// set the _NO_DEBUG_HEAP environment variable to 1.

			// example
			// Menu > Property Pages > Configuration Properties > Debugging > Environment : _NO_DEBUG_HEAP = 1

			_getch();
		}
	}

	void disable_lfh_in_custom_heap()
	{
		/*
			The LFH cannot be enabled for heaps created with HEAP_NO_SERIALIZE or for heaps created with a fixed size.
			The LFH also cannot be enabled if you are using the heap debugging tools in Debugging Tools for Windows
			or Microsoft Application Verifier.

			After the LFH has been enabled for a heap, it cannot be disabled.
			Applications that benefit most from the LFH are multithreaded applications that allocate memory frequently
			and use a variety of allocation sizes under 16 KB.
			However, not all applications benefit from the LFH.
			To assess the effects of enabling the LFH in your application, use performance profiling data.
		*/
		{
			HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
			if (NULL == hHeap) {
				_tprintf( TEXT("Failed to create a new heap with Last Error %d.\n")
						, GetLastError());
			}

			BOOL bResult;
			ULONG enableLFH = HEAP_LFH;

			bResult = HeapSetInformation( hHeap
										, HeapCompatibilityInformation
										, &enableLFH
										, sizeof(enableLFH) );
			if (TRUE == bResult) {
				_tprintf( TEXT("The LFH has been disable in heap.\n") );
			}
			else {
				_tprintf( TEXT("Failed to disable the LFH with Last Error %d.\n")
						, GetLastError() );
			}

			_getch();
		}
	}


	void use_lfh_in_process()
	{
		// use LFH in process
		{
			BOOL bResult;

			ULONG enableLFH = HEAP_LFH;
			bResult = HeapSetInformation( GetProcessHeap()
										, HeapCompatibilityInformation
										, &enableLFH
										, sizeof(enableLFH) );
			if (TRUE == bResult) {
				_tprintf( TEXT("Heap LFH has been enabled.\n") );
			}
			else {
				_tprintf( TEXT("Failed to enable heap LFH with Last Error %d.\n")
						, GetLastError() );
			}

			_getch();
		}
	}


	void use_lfh_in_process_all()
	{
		// use LFH in process all
		{
			BOOL bResult;

			HANDLE heapList[1024];
			DWORD Count = GetProcessHeaps(1024, heapList);

			for (DWORD i = 0; i < Count; ++i) {
				ULONG  enableLFH = HEAP_LFH;

				bResult = HeapSetInformation( heapList[i]
											, HeapCompatibilityInformation
											, &enableLFH
											, sizeof(enableLFH) );

				if (TRUE == bResult) {
					_tprintf( TEXT("Process Heap LFH has been enabled.\n") );
				}
				else {
					_tprintf( TEXT("Failed to enable Process heap LFH with Last Error %d.\n")
							, GetLastError() );
				}
			}

			_getch();
		}
	}


	void use_lfh_in_crt()
	{
		// use LFH in CRT
		{
			BOOL bResult;

			intptr_t hCrtHeap = _get_heap_handle();

			ULONG enableLFH = HEAP_LFH;

			bResult = HeapSetInformation( (PVOID)hCrtHeap
										, HeapCompatibilityInformation
										, &enableLFH
										, sizeof(enableLFH) );
			if (TRUE == bResult) {
				_tprintf( TEXT("Heap LFH has been enabled in CRT.\n") );
			}
			else {
				_tprintf( TEXT("Failed to enable heap LFH in CRT with Last Error %d.\n")
						, GetLastError() );
			}

			_getch();
		}
	}


	void enalbe_heap_terminate_on_corruption()
	{
		/*
			Enable heap terminate-on-corruption. 
			A correct application can continue to run even if this call fails, 
			so it is safe to ignore the return value and call the function as follows:
			(void)HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
			If the application requires heap terminate-on-corruption to be enabled, 
			check the return value and exit on failure as shown in this example.
		*/
		{
			BOOL bResult;

			bResult = HeapSetInformation( NULL
										, HeapEnableTerminationOnCorruption
										, NULL
										, 0 );

			if (TRUE == bResult) {
				_tprintf( TEXT("Heap terminate-on-corruption has been enabled.\n") );
			}
			else {
				_tprintf( TEXT("Failed to enable heap terminate-on-corruption with Last Error %d.\n")
						, GetLastError() );
			}

			_getch();
		}

	}


	void Test()
	{
		disable_lfh_in_custom_heap();

		use_lfh_in_custom_heap();

		use_lfh_in_process();

		use_lfh_in_process_all();

		use_lfh_in_crt();

		enalbe_heap_terminate_on_corruption();
	}
}