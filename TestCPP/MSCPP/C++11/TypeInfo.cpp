#include "stdafx.h"

#include <typeinfo>
#include <typeindex>

namespace TypeInfo
{
	class Object
	{
	public:
		int ID;
		Object() { ID = 0; }

		int GetID(int) { return ID; }
	};

	static int GetNo() { return 1; }

	class ObjectEx : public Object
	{
	public:
		int(*m_func)(void);

	public:
		ObjectEx() 
		{
			m_func = &GetNo;
		}
	};

	void typeid_use()
	{
		//typeid().hash_code
		{
			std::cout << typeid(int).hash_code() << std::endl;
			std::cout << typeid(int&).hash_code() << std::endl;
			std::cout << typeid(int*).hash_code() << std::endl;
			std::cout << typeid(type_info).hash_code() << std::endl;
			std::cout << typeid(typeid_use).hash_code() << std::endl;
			std::cout << typeid(__FUNCTION__).hash_code() << std::endl;
			std::cout << typeid(std::cout).hash_code() << std::endl;
			std::cout << typeid(Object).hash_code() << std::endl;
			std::cout << typeid(Object&).hash_code() << std::endl;
			std::cout << typeid(Object*).hash_code() << std::endl;

			ObjectEx obj;
			std::cout << typeid(obj.m_func).hash_code() << std::endl;

			system("pause");

			/*
			output:
				3143511547772090151
				3143511547772090151
				4057924443418372602
				605961751599869582
				12190168669607903068
				8696602986200640419
				11668689189311269656
				2893448790909641650
				2893448790909641650
				1366259026366434286
				13588506851993930617
			*/
		}

		//typeid().raw_name()
		{
			std::cout << typeid(int).raw_name() << std::endl;
			std::cout << typeid(int&).raw_name() << std::endl;
			std::cout << typeid(int*).raw_name() << std::endl;
			std::cout << typeid(type_info).raw_name() << std::endl;
			std::cout << typeid(typeid_use).raw_name() << std::endl;
			std::cout << typeid(__FUNCTION__).raw_name() << std::endl;
			std::cout << typeid(std::cout).raw_name() << std::endl;
			std::cout << typeid(Object).raw_name() << std::endl;
			std::cout << typeid(Object&).raw_name() << std::endl;
			std::cout << typeid(Object*).raw_name() << std::endl;

			ObjectEx obj;
			std::cout << typeid(obj.m_func).raw_name() << std::endl;

			system("pause");

			/*
			output:
				.H
				.H
				.PEAH
				.?AVtype_info@@
				.$$A6AXXZ
				.$$BY0BF@$$CBD
				.?AV?$basic_ostream@DU?$char_traits@D@std@@@std@@
				.?AVObject@TypeInfo@@
				.?AVObject@TypeInfo@@
				.PEAVObject@TypeInfo@@
				.P6AHXZ
			*/
		}

		//typeid().name()
		{
			std::cout << typeid(int).name() << std::endl;
			std::cout << typeid(int&).name() << std::endl;
			std::cout << typeid(int*).name() << std::endl;
			std::cout << typeid(type_info).name() << std::endl;
			std::cout << typeid(typeid_use).name() << std::endl;
			std::cout << typeid(__FUNCTION__).name() << std::endl;
			std::cout << typeid(std::cout).name() << std::endl;
			std::cout << typeid(Object).name() << std::endl;
			std::cout << typeid(Object&).name() << std::endl;
			std::cout << typeid(Object*).name() << std::endl;

			ObjectEx obj;
			std::cout << typeid(obj.m_func).name() << std::endl;

			system("pause");

			/*
			output:
				int
				int
				int * __ptr64
				class type_info
				void __cdecl(void)
				char const [21]
				class std::basic_ostream<char,struct std::char_traits<char> >
				class TypeInfo::Object
				class TypeInfo::Object
				class TypeInfo::Object * __ptr64
				int (__cdecl*)(void)
			*/
		}
	}


	class IA
	{
	public:
		virtual void Update() { return; } //virtual function 필요 !!!
	};

	class B : public IA
	{};

	class C : public B
	{};

	class D : public C
	{};

	void override_object_type()
	{
		IA* objList[] = { &B(), &C(), &D() };

		std::cout << typeid(*objList[0]).name() << std::endl; //virtual address 로 child 객체 type 으로 변환 !!!
		std::cout << typeid(*objList[1]).name() << std::endl; //virtual address 로 child 객체 type 으로 변환 !!!
		std::cout << typeid(*objList[2]).name() << std::endl; //virtual address 로 child 객체 type 으로 변환 !!!

		system("pause");

		/*
		output:
			class TypeInfo::B
			class TypeInfo::C
			class TypeInfo::D
		*/
	}

	struct ADT {
		virtual ~ADT() {}
	};

	struct DrivenB : ADT {};
	struct DrivenC : ADT {};

	void type_index_use()
	{
		std::unordered_map<std::type_index, std::string> type_names;

		type_names[std::type_index(typeid(int))] = "int";
		type_names[std::type_index(typeid(double))] = "double";
		type_names[std::type_index(typeid(ADT))] = "ADT";
		type_names[std::type_index(typeid(DrivenB))] = "DrivenB";
		type_names[std::type_index(typeid(DrivenC))] = "DrivenC";

		int i;
		double d;
		ADT adt;

		//note that we're storing pointer to type ADT
		std::unique_ptr<ADT> b(new DrivenB);
		std::unique_ptr<ADT> c(new DrivenC);

		std::cout << "i is " << type_names[std::type_index(typeid(i))] << '\n';
		std::cout << "d is " << type_names[std::type_index(typeid(d))] << '\n';
		std::cout << "a is " << type_names[std::type_index(typeid(adt))] << '\n';
		std::cout << "b is " << type_names[std::type_index(typeid(*b))] << '\n';
		std::cout << "c is " << type_names[std::type_index(typeid(*c))] << '\n';

		system("pause");

		/*
		output:
			i is int
			d is double
			a is ADT
			b is DrivenB
			c is DrivenC
		*/
	}


	void Test()
	{
		//type_index_use();

		//override_object_type();

		typeid_use();
	}

}