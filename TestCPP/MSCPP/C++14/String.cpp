#include "stdafx.h"

#include <locale>
#include <codecvt>

namespace String
{
	void string_convert_unicode_utf8()
	{
		// wchar(unicode) -> utf8
		{
			std::u16string utf16Str = u"©Лгого";
			std::wstring_convert<std::codecvt_utf8<uint16_t>, uint16_t> utf8Conv;
			auto utf8Str = utf8Conv.to_bytes(reinterpret_cast<const uint16_t*>(utf16Str.c_str()));

			std::cout << "UTF-8 : ";
			for (char c : utf8Str) {
				std::cout << '[' << int(static_cast<unsigned char>(c)) << ']';
			}
			std::cout << '\n';
		}

		// utf8 -> wchar(unicode)
		{

		}

		system("pause");
	}

	void Test()
	{
		//string_convert_unicode_utf8();
	}
}