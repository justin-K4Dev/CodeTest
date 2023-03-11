#include "stdafx.h"



namespace CodeManagement
{
	void codegen_security_diagnost_n_versioning()
	{
		/*
			Codegen, security, diagnostics and versioning

			This release brings several improvements in optimization, code generation, toolset versioning and diagnostics.
			Some notable improvements include:

				• Improved code generation of loops:
					Support for automatic vectorization of division of constant integers, better identification of memset patterns.
				
				• Improved code security:
					Improved emission of buffer overrun compiler diagnostics, and /guard:cf now guards switch statements that generate jump tables.
				
				• Versioning:
					The value of the built-in preprocessor macro _MSC_VER is now being monotonically updated at every Visual C++ toolset update.
					For more information, see Visual C++ Compiler Version.
					
				• New toolset layout:
					The compiler and related build tools have a new location and directory structure on your development machine.
					The new layout enables side-by-side installations of multiple versions of the compiler.
					For more information, see Compiler Tools Layout in Visual Studio "15".
					
				• Improved diagnostics:
					The output window now shows the column where an error occurs.
					For more information, see C++ compiler diagnostics improvements in VS "15" Preview 5.
					
				• When using co-routines, the Experimental keyword "yield" (available under /await switch) has been removed.
					Your code should be updated to use the "co_yield" instead.
					For more information, see the Visual C++ Team blog.
		*/
		{
		}
	}

	void Test()
	{

	}

}// end of CodeManagement