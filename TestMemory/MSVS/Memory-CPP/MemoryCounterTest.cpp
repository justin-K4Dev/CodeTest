#include "stdafx.h"

#include "ObjectAllocator.h"
#include "STLMemoryCountingAllocator.h"

namespace MemoryCounter
{
	class CustomObject : public Memory::ObjectAllocator<CustomObject>
	{
	public:

	};

	void Test()
	{
		Memory::GetMemoryCounter().AddMemoryCountingInfoByThreadID(GetCurrentThreadId());

		Memory::GetMemoryCounter().Start();

		CustomObject* pObject = new CustomObject;
		delete pObject;

		{
			std::vector<CustomObject*, Memory::STLMemoryCountingAllocator<CustomObject*>> objectList;
			objectList.push_back(new CustomObject);

			std::vector<int, Memory::STLMemoryCountingAllocator<int>> vectorContainer;
			vectorContainer.push_back(1000);

			std::map<int, int, std::less<int>, Memory::STLMemoryCountingAllocator<std::pair<int, int>>> mapContainer;
			mapContainer.emplace(100, 100);
		}

		int* pInt = new int; // compile error : error C2661: 'operator new':
		delete pInt;

		Memory::GetMemoryCounter().Stop();

		Memory::GetMemoryCounter().ReportMemoryCountingInfoAll();

		system("pause");
	}
}