// main.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Function.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
		Visual Leak Detector

		URL : https://vld.codeplex.com/

		Warning : Only debug support !!!

		vld.ini file edit the following changes

			; Sets the report file destination, if reporting to file is enabled. A relative
			; path may be specified and is considered relative to the process' working
			; directory.
			;
			;   Valid Values: Any valid path and filename.
			;   Default: .\memory_leak_report.txt
			;
			ReportFile =

			; Sets the report destination to either a file, the debugger, or both. If
			; reporting to file is enabled, the report is sent to the file specified by the
			; ReportFile option.
			;
			;   Valid Values: debugger, file, both
			;   Default: debugger
			;
			ReportTo = both
			
	*/
	{
		VLD::Test();
	}
	
	return 0;
}

