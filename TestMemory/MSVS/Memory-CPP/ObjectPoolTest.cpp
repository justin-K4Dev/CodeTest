#include "stdafx.h"
#include "Function.h"

#include "CRT_MemoryCheck.h"

#include "ObjectPool.hpp"

#include "MemoryComparator.h"

namespace Pool
{
	typedef unsigned int ObjectPoolKeyType;

	class Player : public IObject<ObjectPoolKeyType>
	{
	public:
		static const IObject::Type TypeID = 1;

		std::string m_name;
		unsigned int m_level;

	public:
		Player() {}
		virtual ~Player() {}

		virtual unsigned int GetTypeID() { return TypeID; }
		virtual const char* GetTypeName() { return typeid(this).name(); }
		
		bool Init(std::string& name, unsigned int level)
		{
			m_name = name;
			m_level = level;

			return true;
		}

		void Print()
		{
			printf( "Player - TypeID:%d, Name:%s, Level:%d\n"
				  , this->GetTypeID(), m_name.c_str(), m_level );
		}
	};

	void use_object_pool()
	{
		Util::MemoryComparator mc(__FUNCTION__);

		ObjectPoolFactory<ObjectPoolKeyType> objectPoolFactory;
		if (true != objectPoolFactory.CreateObjectPool<Player>(1)) {
			return;
		}

		for (int i = 0; i < 5; ++i) {
			Player* pPlayer = objectPoolFactory.CreateObject<Player>(std::string("justin"), 1);
			if (nullptr == pPlayer) {
				return;
			}

			pPlayer->Print();
		}

		mc.End();

		system("pause");
	}


	void Test()
	{
		SET_CRT_MEMORY_CHECK(CRT_MEMORY_LEAK_ALWAYS_CHECK_FLAGS);

		use_object_pool();

		_CrtDumpMemoryLeaks();
	}
}