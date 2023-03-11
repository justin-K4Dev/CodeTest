#include "stdafx.h"


namespace Compiler
{	
	void new_compiler_switches()
	{
		/*
			New compiler switches

			-/std:c++14 and /std:c++latest:
			These compiler switches enable you to opt-in to specific versions of the ISO C++ programming language in a project.
			For more information, see Standards version switches in the compiler.
			Most of the new draft standard features are guarded by the /std:c++latest switch.  

			-/permissive-:
			Enable all strict standards conformance compiler options
			and disable most Microsoft-specific compiler extensions
			(but not __declspec(dllimport), for example).
			(Off by default but will be on by default at some point in the future.) 

			-/diagnostics:
			Enable display of the line number, the line number and column,
			or the line number and column and a caret under the line of code where the diagnostic error
			or warning was found. 

			-/debug:fastlink:
			Enable up to 30% faster incremental link times (vs. Visual Studio 2015) by not copying all debug information into the PDB file.
			The PDB file instead points to the debug information for the object
			and library files used to create the executable.
			See Faster C++ build cycle in VS ¡°15¡± with /Debug:fastlink
			and Recommendations to speed C++ builds in Visual Studio. 

			Visual Studio 2017 allows using /sdl with /await.
			We removed the /RTC limitation with Coroutines. 
		*/
	}

	void Test()
	{

	}

}// end of CompilerSwitch