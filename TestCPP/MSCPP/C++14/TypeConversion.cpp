#include "stdafx.h"

#include <map>
#include <typeinfo>
#include <typeindex>

namespace TypeConversion
{

	void user_defined_conversion()
	{
		// user-defined conversion
		{
			/*
				Enables implicit conversion or explicit conversion from a class type to another type.

					Syntax	
						explicit operator conversion-type-id
				
					Declares a user-defined conversion function that participates in direct-initialization and explicit conversions only.

				conversion-type-id is a type-id except that function and array operators [] or () are not allowed in its declarator
				(thus conversion to types such as pointer to array requires a type alias/typedef or an identity template: see below).
				Regardless of typedef, conversion-type-id cannot represent an array or a function type.
				Although the return type is not allowed in the declaration of a user-defined conversion function,
				the decl-specifier-seq of the declaration grammar may be present and may include any specifier other than type-specifier or
				the keyword static, In particular, besides explicit, the specifiers inline, virtual, constexpr, and friend are also allowed
				(note that friend requires a qualified name: friend A::operator B();).
				When such member function is declared in class X, it performs conversion from X to conversion-type-id:
			*/
			{
				struct X
				{
					// implicit conversion
					operator int() const { return 7; }

					// explicit conversion
					explicit operator int*() const { return nullptr; }

					// Error: array operator not allowed in conversion-type-id
					// operator int(*)[3]() const { return nullptr; }
					using arr_t = int[3];
					operator arr_t*() const { return nullptr; } // OK if done through typedef
					// operator arr_t () const; // Error: conversion to array not allowed in any case
				};

				X x;

				int* p = static_cast<int*>(x);  // OK: sets p to null
				//int* q = x; // Error: no implicit conversion

				int(*pa)[3] = x;  // OK

				system("pause");
			}
		}
	}

	void Test()
	{
		//user_defined_conversion();
	}
}