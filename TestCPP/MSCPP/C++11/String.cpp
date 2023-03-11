#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file String.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <regex>

namespace String
{
	void regular_expression()
	{
		std::string s = "Some people, when confronted with a problem, think "
						"\"I know, I'll use regular expressions.\" "
						"Now they have two problems.";
 
		std::regex self_regex( "REGULAR EXPRESSIONS"
			                 , std::regex_constants::ECMAScript | std::regex_constants::icase );
		if (std::regex_search(s, self_regex)) {
			std::cout << "Text contains the phrase 'regular expressions'\n";
		}
 
		std::regex word_regex("(\\S+)");
		auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
		auto words_end = std::sregex_iterator();
 
		std::cout << "Found "
	              << std::distance(words_begin, words_end)
			      << " words\n";
 
		const int N = 6;
		std::cout << "Words greater than " << N << " characters:\n";
		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			std::string match_str = match.str();
			if (match_str.size() > N) {
				std::cout << "  " << match_str << '\n';
			}
		}
 
		std::regex long_word_regex("(\\w{7,})");
		std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
		std::cout << new_s << '\n';

		system("pause");
	}


	void split_by_regex()
	{
		std::string s("this subject has a submarine as a subsequence");
		std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

		//default constructor = end-of-sequence:
		std::regex_token_iterator<std::string::iterator> rend;

		std::cout << "entire matches:";
		std::regex_token_iterator<std::string::iterator> a(s.begin(), s.end(), e);
		while (a != rend) {
			std::cout << " [" << *a++ << "]";
		}
		std::cout << std::endl;

		std::cout << "2nd submatches:";
		std::regex_token_iterator<std::string::iterator> b(s.begin(), s.end(), e, 2);
		while (b != rend) {
			std::cout << " [" << *b++ << "]";
		}
		std::cout << std::endl;

		std::cout << "1st and 2nd submatches:";
		int submatches[] = { 1, 2 };
		std::regex_token_iterator<std::string::iterator> c(s.begin(), s.end(), e, submatches);
		while (c != rend) {
			std::cout << " [" << *c++ << "]";
		}
		std::cout << std::endl;

		std::cout << "matches as splitters:";
		std::regex_token_iterator<std::string::iterator> d(s.begin(), s.end(), e, -1);
		while (d != rend) {
			std::cout << " [" << *d++ << "]";
		}
		std::cout << std::endl;

		system("pause");
	}


	void Test()
	{
		//regular_expression();

		//split_by_regex();
	}

}// end of EmplaceBack