// C++141.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Function.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Logic::Test();

	/*
		* What's New for Visual C++ in Visual Studio 2017

		URL:	https://docs.microsoft.com/ko-kr/cpp/what-s-new-for-visual-cpp-in-visual-studio
		Backup:	file:///Z:/data/03.Tech/VisualStudio/Lecture/What%20is%20New%20for%20Visual%20C++%20in%20VS%202017.htm

		Etc URL:	http://mariusbancila.ro/blog/2017/03/08/whats-new-in-visual-studio-2017-for-cpp-development/

		Visual Studio 2017 brings many updates and fixes to the Visual C++ environment.
		We've fixed over 250 bugs and reported issues in the compiler and tools,
		many submitted by customers through Microsoft Connect.
		Thank you for reporting bugs! For more information on what's new in all of Visual Studio,
		please visit What's new in Visual Studio 2017.

		C++ conformance improvements

		In this release, we've updated the C++ compiler and standard library with enhanced support for C++11
		and C++14 features, as well as preliminary support for certain features expected to be in the C++17 standard.
		For detailed information, see C++ Conformance Improvements in Visual Studio 2017.
	*/
	{
		Compiler::Test();
		CodeManagement::Test();
		CPP_Library::Test();
	}

	/*	
		* C++ conformance improvements in Visual Studio 2017

		URL: https://docs.microsoft.com/en-us/cpp/cpp-conformance-improvements-2017
		Backup: file:///Z:/data/03.Tech/VisualStudio/Lecture/C++%20compiler%20conformance%20improvements%20in%20VS%202017.htm

		New language features

		With support for generalized constexpr and NSDMI for aggregates,
		the compiler is now complete for features added in the C++14 Standard.
		Note that the compiler still lacks a few features from the C++11 and C++98 Standards.
		See Visual C++ Language Conformance for a table that shows the current state of the compiler.
	*/
	{
		CPP11::Test();
		CPP14::Test();
		CPP17::Test();

		UpdateV153::Test();
		BugFixes::Test();
	}

    return 0;
}

