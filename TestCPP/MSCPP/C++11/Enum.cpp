#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Enum.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <regex>

namespace Enum
{
	// unscoped enumeration example
	enum ITEM_TYPE : short
	{
		WEAPON,
		EQUIPMENT,
		GEM = 10,
		DEFENCE,
	};

	void unscoped_enumeration()
	{
		// use unscoped enumeration
		{
			short ItemType1 = WEAPON;

			short ItemType2 = ITEM_TYPE::WEAPON;
		}	
	}

	// scoped enumeration example
	enum class CHARACTER_CLASS : short
	{
		WARRIOR = 1,
		MONK,
		FIGHTER,
	};

	void scoped_enumeration()
	{
		// use scoped enumeration
		{
			CHARACTER_CLASS charClass = CHARACTER_CLASS::WARRIOR;

			//short charClassType = FIGHTER; // compile error
		}
	}


	void casting_enumeration()
	{
		// casting enumeration
		{
			// unscoped enumeration 의 형변환
			int i = WEAPON;

			// scoped enumeration 의 형변환
			int j = static_cast<int>(CHARACTER_CLASS::WARRIOR);
		}
	}

	#define STRINGIFY(x)	#x
	#define TO_STRING(x)	STRINGIFY(x)

	void print_enumeration()
	{
		std::cout << TO_STRING(WEAPON) << std::endl;
		std::cout << TO_STRING(ITEM_TYPE::WEAPON) << std::endl;
		std::cout << TO_STRING(CHARACTER_CLASS::WARRIOR) << std::endl;

		std::cout << typeid(ITEM_TYPE::WEAPON).name() << std::endl;
		std::cout << typeid(WEAPON).name() << std::endl;

		std::cout << typeid(CHARACTER_CLASS::WARRIOR).name() << std::endl;
	}


	void Test()
	{
		//unscoped_enumeration();

		//scoped_enumeration();

		//casting_enumeration();

		//print_enumeration();
	}

}//end of Enum