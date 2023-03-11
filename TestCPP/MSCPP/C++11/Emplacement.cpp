#include "stdafx.h"


///////////////////////////////////////////////////////////////////////////////
/// @file Emplacement.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author Justin
/// @date 7-26-2012 10:51:18
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <deque>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>



namespace Emplacement
{

	void std_vector_emplace()
	{
		// std::vector::emplace()
		{
			int arr[] = { 10, 20, 30 };
			std::vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));

			auto it = v.emplace(v.begin() + 1, 100);
			v.emplace(it, 200);
			v.emplace(v.end(), 300);

			std::cout << "v contains:";
			for (auto& x : v) {
				std::cout << ' ' << x;
			}
			std::cout << '\n';

			system("pause");

			/*
			output:
				v contains: 10 200 100 20 30 300
			*/
		}
	}


	// vector::emplace_back() example
	struct President
	{
		std::string name;
		std::string country;
		int year;

		President(std::string p_name, std::string p_country, int p_year)
			: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
		{
			std::cout << "I am being constructed.\n";
		}
		President(const President& other)
			: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
		{
			std::cout << "I am being copied.\n";
		}
		President(President&& other)
			: name(move(other.name)), country(std::move(other.country)), year(other.year)
		{
			std::cout << "I am being moved.\n";
		}
		~President()
		{
			std::cout << "I am being destructed.\n";
		}
	};

	void std_vector_emplace_back()
	{
		// std::vector::emplace_back()
		{
			std::vector<std::string> v;

			const std::string value = "hi";
			v.push_back(value);

			v.emplace_back("hello"); // lower cost than push_back
			v.emplace_back();
			v.emplace_back(10, 'a');

			system("pause");
		}
		{
			// VS2013의 emplace_back
			// vector 내부에서 생성 -> 컨테이터에 추가하기에 임시 객체 생성 X
			std::vector<President> v1;
			v1.emplace_back("Nelson Mandela", "South Africa", 1994);

			// VS2010의 emplace_back 역시 아래 push_back과 동일한 방식으로만 사용이 가능했었다
			// 외부에서 생성 -> 벡터로 이동 -> 외부 객체 파괴가 발생한다
			std::vector<President> v2;
			v2.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

			for (President const& president : v1)
			{
				std::cout << president.name << " was inserted president of "
					<< president.country << " in " << president.year << ".\n";
			}
			for (President const& president : v2)
			{
				std::cout << president.name << " was inserted president of "
					<< president.country << " in " << president.year << ".\n";
			}

			system("pause");

			/*
			output:
				emplace_back:
				I am being constructed.

				push_back:
				I am being constructed.
				I am being moved.

				Contents:
				Nelson Mandela was elected president of South Africa in 1994.
				Franklin Delano Roosevelt was re-elected president of the USA in 1936.
			*/
		}
	}


	void std_deque_emplace()
	{
		// std::deque::emplace()
		{
			int arr[] = { 10, 20, 30 };
			std::deque<int> deq(arr, arr + sizeof(arr) / sizeof(arr[0]));

			auto it = deq.emplace(deq.begin() + 1, 100);
			deq.emplace(it, 200);
			deq.emplace(deq.end(), 300);

			std::cout << "deq contains:";
			for (auto& x : deq)
				std::cout << ' ' << x;
			std::cout << '\n';

			system("pause");

			/*
			output:
				deq contains: 10 200 100 20 30 300
			*/
		}
	}


	void std_deque_emplace_front()
	{
		// std::deque::emplace_front()
		{
			int arr[] = { 10, 20, 30 };
			std::deque<int> deq(arr, arr + sizeof(arr) / sizeof(arr[0]));

			deq.emplace_front(111);
			deq.emplace_front(222);

			std::cout << "deq contains:";
			for (auto& x : deq)
				std::cout << ' ' << x;
			std::cout << '\n';

			system("pause");

			/*
			output:
				deq contains: 222 111 10 20 30
			*/
		}
	}


	void std_deque_emplace_back()
	{
		// std::deque::emplace_back()
		{
			std::deque<President> deq1;
			std::cout << "emplace_back:\n";
			deq1.emplace_back("Nelson Mandela", "South Africa", 1994);

			std::deque<President> deq2;
			std::cout << "\npush_back:\n";
			deq2.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

			std::cout << "\nContents:\n";
			for (President const& president : deq1) {
				std::cout << president.name << " was inserted president of "
					<< president.country << " in " << president.year << ".\n";
			}
			for (President const& president : deq2) {
				std::cout << president.name << " was inserted president of "
					<< president.country << " in " << president.year << ".\n";
			}

			system("pause");

			/*
			output:
				emplace_back:
				I am being constructed.

				push_back:
				I am being constructed.
				I am being moved.

				Contents:
				Nelson Mandela was elected president of South Africa in 1994.
				Franklin Delano Roosevelt was re-elected president of the USA in 1936.
			*/
		}
	}


	void std_forward_list()
	{
		// std::forward_list
		{
			std::forward_list< int > flist;

			std::cout << "flist에 추가한 요소들 출력" << std::endl;
			// 추가하기
			auto iter = flist.before_begin();
			for (int i = 0; i < 5; ++i)
			{
				iter = flist.insert_after(iter, i);
			}

			// 순회
			for (iter = flist.begin(); iter != flist.end(); ++iter)
			{
				std::cout << *iter << std::endl;
			}

			std::cout << std::endl;
			std::cout << "flist의 요소들 중 일부를 삭제한 후 남은 요소들 출력" << std::endl;
			// 순회 하면서 일부 요소 삭제
			auto prev_iter = flist.before_begin();
			iter = flist.begin();
			while (iter != flist.end())
			{
				if (3 == *iter)
				{
					iter = flist.erase_after(prev_iter);
					continue;
				}
				++prev_iter;
				++iter;
			}

			// 순회
			for (iter = flist.begin(); iter != flist.end(); ++iter)
			{
				std::cout << *iter << std::endl;
			}

			system("pause");
		}
	}

	
	void std_forward_list_emplace_front()
	{
		// forward_list::emplace_front
		{
			std::forward_list< std::pair<int, char> > mylist;

			mylist.emplace_front(10, 'a');
			mylist.emplace_front(20, 'b');
			mylist.emplace_front(30, 'c');

			std::cout << "mylist contains:";
			for (auto& x : mylist)
				std::cout << " (" << x.first << "," << x.second << ")";

			std::cout << std::endl;

			system("pause");

			/*
			output:
				mylist contains: (30,c) (20,b) (10,a)
			*/
		}
	}


	void std_forward_list_emplace_after()
	{
		// std::forward_list::emplace_after()
		{
			std::forward_list< std::pair<int, char> > mylist;
			auto it = mylist.before_begin();

			it = mylist.emplace_after(it, 100, 'x');
			it = mylist.emplace_after(it, 200, 'y');
			it = mylist.emplace_after(it, 300, 'z');

			std::cout << "mylist contains:";
			for (auto& x : mylist)
				std::cout << " (" << x.first << "," << x.second << ")";

			std::cout << '\n';

			system("pause");

			/*
			output:
				mylist contains: (100,x) (200,y) (300,z)
			*/
		}
	}


	void std_set_emplace()
	{
		// set::emplace()
		{
			std::set<std::string> myset;

			myset.emplace("foo");
			myset.emplace("bar");
			auto ret = myset.emplace("foo");

			if (!ret.second)
				std::cout << "foo already exists in myset\n";

			system("pause");

			/*
			output:
				foo already exists in myset
			*/
		}
	}


	void std_set_emplace_hint()
	{
		// set::emplace_hint()
		{
			std::set<std::string> myset;
			auto it = myset.cbegin();

			myset.emplace_hint(it, "alpha");
			it = myset.emplace_hint(myset.cend(), "omega");
			it = myset.emplace_hint(it, "epsilon");
			it = myset.emplace_hint(it, "beta");

			std::cout << "myset contains:";
			for (const std::string& x : myset)
				std::cout << ' ' << x;
			std::cout << '\n';

			system("pause");

			/*
			output:
				myset contains: alpha beta epsilon omega
			*/
		}
	}


	void std_map_emplace()
	{
		// map::emplace()
		{
			std::map<char, int> mymap;

			mymap.emplace('x', 100);
			mymap.emplace('y', 200);
			mymap.emplace('z', 100);

			std::cout << "mymap contains:";
			for (auto& x : mymap)
				std::cout << " [" << x.first << ':' << x.second << ']';
			std::cout << '\n';

			system("pause");

			/*
			output:
				mymap contains: [x:100] [y:200] [z:100]
			*/
		}
	}


	void std_map_emplace_hint()
	{
		// map::emplace_hint()
		{
			std::map<char, int> mymap;
			auto it = mymap.end();

			it = mymap.emplace_hint(it, 'b', 10);
			mymap.emplace_hint(it, 'a', 12);
			mymap.emplace_hint(mymap.end(), 'c', 14);

			std::cout << "mymap contains:";
			for (auto& x : mymap)
				std::cout << " [" << x.first << ':' << x.second << ']';
			std::cout << '\n';

			system("pause");

			/*
			output:
				mymap contains: [a:12] [b:10] [c:14]
			*/
		}
	}


	void std_map()
	{
		// map
		{
			std::map<int, President> m;

			////////////////////////////////////////////////////////////////////////////////
			/// 기존의 insert
			////////////////////////////////////////////////////////////////////////////////
			{
				// p 객체 생성
				President p("Nelson Mandela", "South Africa", 1994);

				// p 객체 복사 생성 for pair -> p 객체 이동
				// 아래 두 문장은 동일하다
				//m.insert(ElectionMap::value_type(1, p));
				m.insert(std::make_pair(1, p));

				// 이 스코프가 종료되면,
				// President p("Nelson Mandela", "South Africa", 1994);에서 생성된 객체 파괴
				// std::map<int, President>::value_type(1, p)에서 생성된 임시 객체 파괴
				// map 소멸되면서 보관되어 있던 원소 파괴
			}

			////////////////////////////////////////////////////////////////////////////////
			/// C++11의 emplace
			////////////////////////////////////////////////////////////////////////////////
			{
				// President 객체 생성 -> 객체 이동 후 바로 컨테이너에 추가
				m.emplace(1, President("Nelson Mandela", "South Africa", 1994));

				// 이 스코프가 종료되면
				// President("Nelson Mandela", "South Africa", 1994)에서 생성된 객체 파괴
				// map 소멸되면서 보관되어 있던 원소 파괴
			}

			system("pause");
		}
	}


	void std_unordered_set_emplace()
	{
		// unordered_set::emplace()
		{
			std::unordered_set<std::string> myset;

			myset.emplace("potatoes");
			myset.emplace("milk");
			myset.emplace("flour");

			std::cout << "myset contains:";
			for (const std::string& x : myset) std::cout << " " << x;

			std::cout << std::endl;

			system("pause");

			/*
			output:
				myset contains: potatoes flour milk
			*/
		}
	}


	void std_unordered_map_emplace()
	{
		// unordered_map::emplace()
		{
			std::unordered_map<std::string, std::string> mymap;

			mymap.emplace("NCC-1701", "J.T. Kirk");
			mymap.emplace("NCC-1701-D", "J.L. Picard");
			mymap.emplace("NCC-74656", "K. Janeway");

			std::cout << "mymap contains:" << std::endl;
			for (auto& x : mymap)
				std::cout << x.first << ": " << x.second << std::endl;

			std::cout << std::endl;

			system("pause");

			/*
			output:
				mymap contains:
				NCC-1701: J.T. Kirk
				NCC-1701-D: J.L. Picard
				NCC-74656: K. Janeway
			*/
		}
	}


	void Test()
	{
		//std_vector_emplace();

		//std_vector_emplace_back();

		//std_deque_emplace();

		//std_deque_emplace_front();

		//std_deque_emplace_back();

		//std_forward_list();

		//std_forward_list_emplace_front();

		//std_forward_list_emplace_after();

		//std_set_emplace();

		//std_set_emplace_hint();

		//std_map_emplace();

		//std_map_emplace_hint();

		//std_map();

		//std_unordered_set_emplace();

		//std_unordered_map_emplace();
	}

}// end of Emplacement