#include "stdafx.h"



#include <atomic>
#include <bitset>

namespace CAS
{
	// std::atomic simple example
	void printValue(int atm, int tVal, int newVal, bool exchanged)
	{
		std::cout << "atm=" << atm
			<< " tVal=" << tVal
			<< " newVal=" << newVal
			<< " exchanged=" << std::boolalpha << exchanged
			<< "\n";
	}

	void std_automic_simple()
	{
		// std::atomic simple
		{
			std::atomic<int> atm;

			int  tVal = 4;
			int  newVal = 5;
			bool exchanged = false;

			atm = 3;
			printValue(atm, tVal, newVal, exchanged);

			// tVal != atm	==> tVal is modified
			exchanged = atm.compare_exchange_strong(tVal, newVal);
			printValue(atm, tVal, newVal, exchanged);

			// tVal == atm  ==>  atm is modified
			exchanged = atm.compare_exchange_strong(tVal, newVal);
			printValue(atm, tVal, newVal, exchanged);
		}
	}


	// stack by std::automic example
	class Obj {
	public:
		Obj(char v) { id = v; next = nullptr; }
		char id;
		Obj* next;
	};

	template<class T>
	struct node
	{
		T data;
		node* next;
		node(const T& data) : data(data), next(nullptr) {}
	};

	template<class T>
	class stack
	{
	protected:
		std::atomic<node<T>*> head;

	public:

		void push(const T& data)
		{
			node<T>* new_node = new node<T>(data);

			// put the current value of head into new_node->next
			new_node->next = head.load(std::memory_order_relaxed);

			// now make new_node the new head, but if the head
			// is no longer what's stored in new_node->next
			// (some other thread must have inserted a node just now)
			// then put that new head into new_node->next and try again
			while ( !std::atomic_compare_exchange_weak_explicit(
															&head,
															&new_node->next,
															new_node,
															std::memory_order_release,
															std::memory_order_relaxed) );
			// the body of the loop is empty
			// note: the above loop is not thread-safe in at least
			// GCC prior to 4.8.3 (bug 60272), clang prior to 2014-05-05 (bug 18899)
			// MSVC prior to 2014-03-17 (bug 819819). See member function version for workaround
		}

		bool pop(T& data)
		{
			node<T>* ret_node = head.load(std::memory_order_acquire);
			if (nullptr == ret_node) {
				return false;
			}

			node<T>* next = ret_node->next;

			if (!std::atomic_compare_exchange_weak_explicit(
														&head,
														&ret_node,
														next,
														std::memory_order_release,
														std::memory_order_relaxed)) {
				return false;
			}

			data = ret_node->data;
			return true;
		}
	};

	void stack_by_std_automic()
	{
		// stack by std::automic
		{
			Obj* obj1 = new Obj('A');
			Obj* obj2 = new Obj('B');
			Obj* obj3 = new Obj('C');

			stack<Obj*> stack;
			stack.push(obj3);
			stack.push(obj2);
			stack.push(obj1);

			// top -> A -> B -> C

			while (true) {
				Obj* pObj;
				bool result = stack.pop(pObj);
				if (false == result) {
					break;
				}
				else {
					std::cout << "return value:" << pObj->id << std::endl;
				}
			}

			delete obj1;
			delete obj2;
			delete obj3;

			system("pause");

		}
	}


	void std_automic_advance()
	{
		// std::automic advance
		{
			//�� �������� / �����ϱ�
			std::atomic<int> int_atomic(3);
			int_atomic = 2;//intAtomic�� 2 ����
			std::atomic_store(&int_atomic, 4);//intAtomic�� 3 ����
			int temp = int_atomic.load();//intAtomic �� ��������

			////////////////////////////////////////////////////////////////////////////////
			/// ��ƿ �Լ�
			////////////////////////////////////////////////////////////////////////////////
			// std::atomic�� �ش� ������Ʈ ũ�Ⱑ 8����Ʈ �����̸� atomic�� �����Ѵ�.
			// _ATOMIC_MAXBYTES_LOCK_FREE = 8
			bool is_lock_free = int_atomic.is_lock_free();


			//atomic ����, �پ��� �����..
			int before_value1 = std::atomic_fetch_add(&int_atomic, 5); // int_atomic�� 5�� ���ϱ�.
			int_atomic++;
			int before_value2 = std::atomic_fetch_sub(&int_atomic, 6); // int_atomic���� 6 ����.
			int_atomic--;

			//bit����
			int bit_mask = 0x0a;
			std::cout << std::bitset<4>(int_atomic).to_string() << std::endl;
			std::atomic_fetch_and(&int_atomic, bit_mask); // bit_mask�� and �����ϱ�.
			std::cout << std::bitset<4>(int_atomic).to_string() << std::endl;
			std::atomic_fetch_or(&int_atomic, bit_mask); // bit_mask�� or �����ϱ�.
			std::cout << std::bitset<4>(int_atomic).to_string() << std::endl;
			std::atomic_fetch_xor(&int_atomic, bit_mask); // bit_mask�� xor �����ϱ�.
			std::cout << std::bitset<4>(int_atomic).to_string() << std::endl;

			//�� ��ȯ
			int temp_value = 100;
			int before_value3 = int_atomic.exchange(temp_value);
			int before_value4 = std::atomic_exchange(&int_atomic, 10);

			//VS2013������ compare_exchange_weak�� ���������� compare_exchange_strong�� ȣ��
			int compare_value = 10;
			int new_value = 30;
			//int_atomic �� compare_value ���� ������ int_atomic�� new_value �����ϴ� ��� 2����
			bool isEqual1 = int_atomic.compare_exchange_weak(compare_value, new_value);
			bool ieEqual2 = std::atomic_compare_exchange_weak(&int_atomic, &compare_value, new_value);

			// VS2013������ compare_exchange_weak�� compare_exchange_strong ������ �����ϴ�.
			// compare_exchange_weak�� compare_exchange_strong�� ȣ���Ѵ�.
		}
	}

	void Test()
	{
		//std_automic_simple();

		//stack_by_std_automic();

		//std_automic_advance();
	}

}// end of CAS