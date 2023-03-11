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
	// L-Value, R-Value example
	class CInfo {};

	int foo() { return 0; };

	void l_value_n_r_value()
	{
		// L-Value, R-Value
		{
			//���� ���� �Ŀ� ���� �ϴ� ���� L-Value.
			//���� ���� �Ŀ� ���� ���� �ʴ� ���� R-Value.

			//L-Value�� ���Ӽ��� �ִ� ���̰�, R-Value�� ���Ӽ��� ���� ���� �ǹ�.
			//L-Value�� ���Ŀ��� identity�� ������ value�� �ǹ��ϸ�,
			//R-Value�� identity�� ������ �ʴ� ���� R-Value ��� ��.
			//�ٽ� ���ϸ� �ּҸ� ���� �� ������ L-Value, ���� �� ������ R-Value !!!.

			int nNo = 0;
			nNo; //L-Value
			0; //R-Value

			CInfo info;
			info; //L-Value
			CInfo(); //R-Value
			foo(); //R-Value

			int nCount = 1;
			int &lrefCount = nCount; //L-Value reference
			lrefCount; //L-Value

			int nData = 100;
			int &lrefData1 = nData; //L-Value reference
									//int &lrefData2 = 10; // error !!!

			int &&rrefData1 = 10;	//R-Value reference
									//int &&rrefData2 = nData; // error !!!

			//���⼭ �˾Ƶ־� �� ���� L-Value �� R-Value ��ȯ ����, R-Value �� L-Value�� ��ȯ �Ұ��� !!!.
		}
	}


	// Reference example
	class CX {};

	void func(CX && t) { std::cout << "Called R-Value" << std::endl; }

	void func(CX & t) { std::cout << "Called L-Value" << std::endl; }

	void func_const(CX const & t) { std::cout << "Called R-Value" << std::endl; }

	void reference()
	{
		//Reference
		{
			CX obj;

			func(obj); //L-Value reference : call void func( CX& t )
			func(CX()); //R-Value reference : call void func( CX&& t )
			func_const(CX()); //const reference �� R-Value ���� ����
		}
	}
	

	void r_value_reference()
	{
		//R-Value Reference
		{
			CX obj;

			//L-Value reference
			CX& lr1 = obj;	//ok
			CX& lr2 = CX();	//ok

			//R-Value reference
			//CX&& rr1 = data; //error !!!
			CX&& rr2 = CX(); //ok
		}
	}


	//Move Semantics example
	CX func_cx_return() { return CX(); } //R-Value return;

	void move_semantics()
	{
		//Move Semantics
		{
			CX obj(func_cx_return()); //R-Value reference, R-Value CX return !!!

			CX tempObj; //L-Value 
			CX obj2(tempObj); //L-Value reference

			//���ķδ� tempObj ��ü�� ����ϸ� �ʵ� !!!
		}
	}


	void move_constructor()
	{
		/*
			Move Constructor

			class CX
			{
			public:
				CX() {
					ptr = new char[1000];
				}

				// copy constructor
				CX(CX const & r) {
					ptr = new char[1000];
					memcpy(r.ptr, ptr, 1000);
				}

				// move copy constructor : CX obj(func_cx_return()); ó���� ȣ�� !!!
				CX(CX && r) {
					ptr = r.ptr;
					r.ptr = nullptr;
				}

				~CX() {
					delete[] ptr;
				}

			private:
				char * ptr;
			};

			CX obj2(tempObj);
			//L-Value reference �� ���� L-Value reference �̹Ƿ� move copy constructor �� ȣ�� ���� ������,
			//copy constructor �� ȣ���.
		*/
		{
			CX tempObj; //L-Value
			CX obj2(static_cast<CX&&>(tempObj)); //R-Value reference casting, call CX::CX(CX&& r)

			CX obj3(std::move(tempObj)); //R-Value reference, call CX::CX(CX&& r)
		}
		/*
			std::move() �Լ� ���� ����

			namespace std {
				template <class T>
				inline typename std::remove_reference<T>::type&& move(T&& t)
				{
					return static_cast< std::remove_reference<T>::type&&>(t); <- R-Value reference casting !!!
				}
			}
		*/
	}


	void exceptional_compiler()
	{
		/*
			Exceptional Compiler - N3000 �� 12.8 Copying class objects p19

			- ������ �����Ϸ��� ��쿡�� copy constructor, move copy constructor �� �Ҹ��� ���� ��찡 ����.
			- � ��쿡�� ������ ��ü�� ���� ���� �ʰ� ���� ��ü�� �״�� ����ϴ� ��쵵 ����.

			class CX
			{
			public:
				CX() {
					ptr = new char[1000];
				}

				CX & CX(CX && r) {
					if (this == &r) {
						return *this;
					}

					delete[] ptr;

					ptr = r.ptr;
					r.ptr = nullptr;

					return *this;
				}

				~CX() {
					delete[] ptr;
				}

			private:
				char * ptr;
			};
		*/

		//CX tempObj;
		//CX x;
		//x = std::move(tempObj);
	}


	//Overload example
	template <typename T>
	void func_template(T && t) {}

	void overload()
	{
		//Overload
		{
			CX orgObj;

			func(orgObj); //L-Value reference : call void func( CX& t )
			func(CX()); //R-Value reference : call void func( CX&& t )

			//template ������ ���
			//�� 14.9.2.1 Deducing template arguments from a function call p3
			//template �μ��� R-Value && �� ���� �߾ L-Value �� ������ ��� L-Value �� �ν� �ϵ��� ó�� !!!
			func_template(orgObj); //L-Value reference
			func_template(CX()); //R-Value reference
		}
	}


	void perfect_forwarding()
	{
		//Perfect Forwarding
		/*
			template <typename T>
			void func_move_in_template(T && t)
			{
				CX obj(t) or obj(std::move(t)); <- dangerous !!!, t : Universal reference ( L-Value or R-Value reference )
			}
		*/

		//func_move_in_template() �μ��� L-Value or R-Value ���� �� �� ���� ���� !!!

		//Solution...
		//Meta Programming
		/*
			template <typename T>
			void f(T && t) {
				if (std::is_lvalue_reference<T>::value) { // check L-Value reference !!!
					T x(t);
				}
				else {
					T x(std::move(t));
				}
			}

			// �μ��� ������ ���� if �� ���� !!!
		*/

		//casting
		/*
			template <typename T>
			void f(T && t) {
				T x(static_cast<T &&>(t));
			}

			//t �� L-Value �� ��� T �� T& �� �ǰ� && �� ���� �Ǹ�,
			//t �� R-Value �� ��� T �� T&& �״�� �ν���.
			//���� static_cast ó�� ��.
		*/

		// std::forward()
		/*
			template <typename T>
			void f(T && t) {
				T x(std::forward<T>(t));
			}

			//std::forward() �� std::move()�� ���������� ������ casting !!!
		*/
	}


	void stl_calling_r_value_reference()
	{
		//STL calling RValue Reference
		{
			std::vector<int> vtDataList;
			vtDataList.push_back(1);
			vtDataList.push_back(2);
			vtDataList.push_back(3);

			std::vector<int> vtTemp;

			vtTemp = std::move(vtDataList); //LValue -> RValue casting

			std::cout << vtTemp[0] << std::endl;

			std::cout << "vtDataList Element Size: " << vtDataList.size() << std::endl;
			std::cout << "vtTemp Element Size: " << vtTemp.size() << std::endl;
		}
		// ���� ���� vtDataList ��ü�� ��� �Ǹ� ���� !!!
	}


	//User calling R-Value reference example
	class CQuestInfo
	{
	public:
		char *m_pszName;
		int m_nNameSize;

	public:
		//�⺻ ������
		CQuestInfo()
		{
			m_pszName = NULL;
			m_nNameSize = 0;

			std::cout << "Called Default Constructor !!!" << std::endl;
		}

		//���ڰ� �ִ� ������
		CQuestInfo(const char *pszName, int nNameSize)
		{
			_ASSERT(NULL != pszName);

			m_pszName = new char[nNameSize];
			_ASSERT(NULL != pszName);

			::memcpy(m_pszName, pszName, nNameSize);

			m_nNameSize = nNameSize;

			std::cout << "Called Argument Constructor !!!" << std::endl;
		}

		//���� ������ (Copy Constructor)
		CQuestInfo(const CQuestInfo & QuestInfo)
			: m_pszName(new char[QuestInfo.m_nNameSize]), m_nNameSize(QuestInfo.m_nNameSize)
		{
			::memcpy(m_pszName, QuestInfo.m_pszName, QuestInfo.m_nNameSize);

			std::cout << "Called Copy Constructor !!!" << std::endl;
		}

		//�Ҹ���
		virtual ~CQuestInfo()
		{
			if (NULL != m_pszName)
			{
				delete[] m_pszName;
				m_pszName = NULL;
			}

			m_nNameSize = 0;

			std::cout << "Called Destructor !!!" << std::endl;
		}

		//���� ������
		CQuestInfo& operator= (const CQuestInfo & QuestInfo)
		{
			if (this != &QuestInfo)
			{
				if (m_nNameSize < QuestInfo.m_nNameSize)
				{
					//���� �߰�
					if (NULL != m_pszName)
					{
						delete[] m_pszName;
					}

					m_pszName = new char[QuestInfo.m_nNameSize];
				}

				::memcpy(m_pszName, QuestInfo.m_pszName, QuestInfo.m_nNameSize);

				m_nNameSize = QuestInfo.m_nNameSize;

				std::cout << "Called operator= !!!" << std::endl;
			}

			return *this;
		}

		//Move �� ���� ������
		CQuestInfo(CQuestInfo && QuestInfo)
			: m_pszName(QuestInfo.m_pszName), m_nNameSize(QuestInfo.m_nNameSize)
		{
			QuestInfo.m_pszName = NULL;
			QuestInfo.m_nNameSize = 0;

			std::cout << "Called Move Constructor !!!" << std::endl;
		}

		//Move �� ���� ���� ������
		CQuestInfo& operator= (CQuestInfo && QuestInfo)
		{
			if (this != &QuestInfo)
			{
				delete[] m_pszName;

				m_pszName = QuestInfo.m_pszName;
				m_nNameSize = QuestInfo.m_nNameSize;

				QuestInfo.m_pszName = NULL;
				QuestInfo.m_nNameSize = 0;
			}

			std::cout << "Called Move operator= !!!" << std::endl;

			return *this;
		}
	};

	class CItem {};

	void g_GetItem(CItem & Item) { std::cout << "Called L-Value Reference !!!" << std::endl; }

	void g_GetItem(CItem && Item) { std::cout << "Called R-Value Reference !!!" << std::endl; }

	template<typename T>
	void foo2(T && t)
	{
		func(std::forward<T>(t)); //L-Value �� L-Value, R-Value �� R-Value �� casting ���� !!!
	}

	void user_calling_r_value_reference()
	{
		//User calling RValue Reference �� ���� Move operator= ȣ�� ���� ����
		{
			std::string strName = "Quest1";

			CQuestInfo qi1(strName.c_str(), (int)strName.size());

			CQuestInfo qi2(qi1);

			std::string strName3 = "Quest3";

			CQuestInfo qi3(strName3.c_str(), (int)strName3.size());
			CQuestInfo qi4;
			qi4 = qi3; //call CQuestInfo& operator= (const CQuestInfo &QuestInfo)


			std::string strName5 = "Quest5";
			CQuestInfo qi5 = CQuestInfo(strName5.c_str(), (int)strName5.size());

			std::string strName6 = "Quest6";
			CQuestInfo qi6(strName6.c_str(), (int)strName6.size()), qi7;
			qi7 = std::move(qi6); // call CQuestInfo& operator= (CQuestInfo &&QuestInfo)
		}
		//���� ���� qi6 ��ü�� ��� �Ǹ� ���� !!!
		//�׸��� qi6.m_pszName ������ �޸𸮰� �����Ǹ� �ʵ� !!!
		//�� �κ��� RValue Reference �� Move ����� ���� ������ �κ��� !!!
		//���������� ������ �� �ִ� ������ ��Ȯ�ϰ� �Ͽ� ��� �ؾ� �� !!!

		//User calling RValue Reference Function Overloading
		{
			CItem Item;
			g_GetItem(Item);
			g_GetItem(CItem());
		}

		//User Template calling RValue Reference
		{
			CX x;

			foo2(x); //called LValue

			foo2(CX()); //called RValue
		}
	}


	void Test()
	{
		//l_value_n_r_value();

		//reference();

		//r_value_reference();

		//move_semantics();

		//move_constructor();

		//exceptional_compiler();

		//overload();

		//perfect_forwarding();

		//stl_calling_r_value_reference();

		//user_calling_r_value_reference();
	}

}//end of RValueReference