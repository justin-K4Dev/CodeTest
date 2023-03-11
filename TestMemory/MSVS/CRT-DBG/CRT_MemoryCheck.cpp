#include "stdafx.h"
#include "Function.h"


namespace CRTMemoryCheck
{	
	class Object
	{
	public:
		std::string m_strName;

	public:
		Object(std::string strName) { m_strName = strName; }
	};
	

	void Test()
	{
		SET_CRT_MEMORY_CHECK(CRT_MEMORY_LEAK_ALWAYS_CHECK_FLAGS);

		{
			int *pIntByNew = new int;

			int *pIntByMalloc = (int*)malloc(sizeof(int));

			Object *pObject = new Object("½ÖÄ®ÀÚºñ");
		}

		_CrtDumpMemoryLeaks();

		_getch();
	}

}// end of CRTMemoryCheck