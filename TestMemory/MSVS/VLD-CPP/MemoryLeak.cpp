#include "stdafx.h"
#include "Function.h"

#ifdef ON_VLD
#include <vld.h>
#endif//ON_VLD

namespace VLD
{
	void use_vld()
	{
		int *ptr = (int*)malloc(100);  // Line 12
		int *ptr2 = (int*)malloc(200);  // Line 13

		for (int i = 1; i <= 100; i++)
		{
			malloc(i); // Line 17
			if (i % 4 == 0)
			{
				malloc(i);  // Line 20
			}
		}

		free(ptr);
		free(ptr2);

		_getch();
	}


	void Test()
	{
		use_vld();
	}

}//end of VLD