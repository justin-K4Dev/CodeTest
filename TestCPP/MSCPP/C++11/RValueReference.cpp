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
			//식이 끝난 후에 존재 하는 것은 L-Value.
			//식이 끝난 후에 존재 하지 않는 것은 R-Value.

			//L-Value는 지속성이 있는 값이고, R-Value는 지속성이 없는 값을 의미.
			//L-Value는 수식에서 identity를 가지는 value를 의미하며,
			//R-Value는 identity를 가지지 않는 값을 R-Value 라고도 함.
			//다시 말하면 주소를 취할 수 있으면 L-Value, 취할 수 없으면 R-Value !!!.

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

			//여기서 알아둬야 할 것은 L-Value ⇒ R-Value 변환 가능, R-Value ⇒ L-Value로 변환 불가능 !!!.
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
			func_const(CX()); //const reference 는 R-Value 참조 가능
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

			//이후로는 tempObj 객체를 사용하면 않됨 !!!
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

				// move copy constructor : CX obj(func_cx_return()); 처리시 호출 !!!
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
			//L-Value reference 의 경우는 L-Value reference 이므로 move copy constructor 는 호출 되지 않으며,
			//copy constructor 가 호출됨.
		*/
		{
			CX tempObj; //L-Value
			CX obj2(static_cast<CX&&>(tempObj)); //R-Value reference casting, call CX::CX(CX&& r)

			CX obj3(std::move(tempObj)); //R-Value reference, call CX::CX(CX&& r)
		}
		/*
			std::move() 함수 구현 내용

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
			Exceptional Compiler - N3000 § 12.8 Copying class objects p19

			- 영리한 컴파일러일 경우에는 copy constructor, move copy constructor 도 불리지 않을 경우가 있음.
			- 어떤 경우에는 실제로 객체를 복사 하지 않고 원본 객체를 그대로 사용하는 경우도 있음.

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

			//template 형태일 경우
			//§ 14.9.2.1 Deducing template arguments from a function call p3
			//template 인수를 R-Value && 로 정의 했어도 L-Value 를 전달할 경우 L-Value 로 인식 하도록 처리 !!!
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

		//func_move_in_template() 인수가 L-Value or R-Value 인지 알 수 없는 문제 !!!

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

			// 인수가 많아질 수록 if 문 증가 !!!
		*/

		//casting
		/*
			template <typename T>
			void f(T && t) {
				T x(static_cast<T &&>(t));
			}

			//t 가 L-Value 일 경우 T 가 T& 가 되고 && 는 무시 되며,
			//t 가 R-Value 일 경우 T 는 T&& 그대로 인식함.
			//따라서 static_cast 처리 됨.
		*/

		// std::forward()
		/*
			template <typename T>
			void f(T && t) {
				T x(std::forward<T>(t));
			}

			//std::forward() 도 std::move()와 마찬가지로 본질은 casting !!!
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
		// 이후 부터 vtDataList 객체는 사용 되면 위험 !!!
	}


	//User calling R-Value reference example
	class CQuestInfo
	{
	public:
		char *m_pszName;
		int m_nNameSize;

	public:
		//기본 생성자
		CQuestInfo()
		{
			m_pszName = NULL;
			m_nNameSize = 0;

			std::cout << "Called Default Constructor !!!" << std::endl;
		}

		//인자가 있는 생성자
		CQuestInfo(const char *pszName, int nNameSize)
		{
			_ASSERT(NULL != pszName);

			m_pszName = new char[nNameSize];
			_ASSERT(NULL != pszName);

			::memcpy(m_pszName, pszName, nNameSize);

			m_nNameSize = nNameSize;

			std::cout << "Called Argument Constructor !!!" << std::endl;
		}

		//복사 생성자 (Copy Constructor)
		CQuestInfo(const CQuestInfo & QuestInfo)
			: m_pszName(new char[QuestInfo.m_nNameSize]), m_nNameSize(QuestInfo.m_nNameSize)
		{
			::memcpy(m_pszName, QuestInfo.m_pszName, QuestInfo.m_nNameSize);

			std::cout << "Called Copy Constructor !!!" << std::endl;
		}

		//소멸자
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

		//대입 연산자
		CQuestInfo& operator= (const CQuestInfo & QuestInfo)
		{
			if (this != &QuestInfo)
			{
				if (m_nNameSize < QuestInfo.m_nNameSize)
				{
					//버퍼 추가
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

		//Move 를 위한 생성자
		CQuestInfo(CQuestInfo && QuestInfo)
			: m_pszName(QuestInfo.m_pszName), m_nNameSize(QuestInfo.m_nNameSize)
		{
			QuestInfo.m_pszName = NULL;
			QuestInfo.m_nNameSize = 0;

			std::cout << "Called Move Constructor !!!" << std::endl;
		}

		//Move 를 위한 대입 연산자
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
		func(std::forward<T>(t)); //L-Value ⇒ L-Value, R-Value ⇒ R-Value 로 casting 해줌 !!!
	}

	void user_calling_r_value_reference()
	{
		//User calling RValue Reference 를 통한 Move operator= 호출 절차 예제
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
		//이후 부터 qi6 객체는 사용 되면 위험 !!!
		//그리고 qi6.m_pszName 변수의 메모리가 수정되면 않됨 !!!
		//이 부분이 RValue Reference 의 Move 기능을 사용시 위험한 부분임 !!!
		//구조적으로 접근할 수 있는 시점을 명확하게 하여 사용 해야 함 !!!

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