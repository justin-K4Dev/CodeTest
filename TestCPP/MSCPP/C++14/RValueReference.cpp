#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////////
/// @file RValueReference.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 12:26:09
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

namespace RValueReference
{
	// variadic template, universal reference, std::forward() 를 사용하면 극강의 코드가 나옴 !!!
	template<typename T, typename... Args>
	T* factory(Args&&... args)
	{
		return new T(std::forward<Args>(args)...);
	}

	void variadic_template_n_std_forward()
	{
		// variadic template
		{
			class Object
			{
			protected:
				int m_id;
				std::string m_name;

			public:
				Object(int id, std::string& objName)
				{
					m_id = id;
					m_name = objName;
				}

				void Print()
				{
					std::cout << "Object ID:" << m_id << "Name:" << m_name << std::endl;
				}
			};

			Object* pObject = factory<Object>(1, std::string("my_object"));
			pObject->Print();

			system("pause");

			/*
			output:
				Object ID:1Nmae:my_object
			*/
		}

	}

	
	void Test()
	{
		//variadic_template_n_std_forward();
	}

}// end of RValueReference