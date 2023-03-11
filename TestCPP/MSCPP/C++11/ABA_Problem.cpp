#include "stdafx.h"


#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include <vector>
#include <atomic>

#include <boost/thread.hpp>


namespace ABAProblem {

	// for check lock-free
	struct A { int a[100]; }; // lock-free : false
	struct B { int x, y; }; // lock-free : true
	struct C { char id; void* nextObj; }; // lock-free : false

	// for ABA problem

	// common info
	class Obj {
	public:
		Obj(char v) { id = v; next = nullptr; }
		char id;
		Obj* next;
	};

	/* Naive lock-free stack which suffers from ABA problem.*/
	class Stack {
	public:
		std::atomic<Obj*> top_ptr;
		//
		// Pops the top object and returns a pointer to it.
		//
		Obj* Pop() {
			while (true) {
				Obj* ret_ptr = top_ptr;
				if (!ret_ptr) return nullptr;
				// For simplicity, suppose that we can ensure that this dereference is safe
				// (i.e., that no other thread has popped the stack in the meantime).
				Obj* next_ptr = ret_ptr->next;
				// If the top node is still ret, then assume no one has changed the stack.
				// (That statement is not always true because of the ABA problem)
				// Atomically replace top with next.
				if (top_ptr.compare_exchange_weak(ret_ptr, next_ptr)) {
					return ret_ptr;
				}
				// The stack has changed, start over.
			}
		}
		//
		// Pushes the object specified by obj_ptr to stack.
		//
		void Push(Obj* obj_ptr) {
			while (true) {
				Obj* next_ptr = top_ptr;
				obj_ptr->next = next_ptr;
				// If the top node is still next, then assume no one has changed the stack.
				// (That statement is not always true because of the ABA problem)
				// Atomically replace top with obj.
				if (top_ptr.compare_exchange_weak(next_ptr, obj_ptr)) {
					return;
				}
				// The stack has changed, start over.
			}
		}
	};


	void check_lock_free()
	{
		// check lock-free !!!
		{
			std::atomic<A> a;
			std::atomic<B> b;
			std::atomic<C> c;

			std::cout << std::boolalpha
				<< "std::atomic<A> is lock free? "
				<< std::atomic_is_lock_free(&a) << '\n'
				<< "std::atomic<B> is lock free? "
				<< std::atomic_is_lock_free(&b) << '\n'
				<< "std::atomic<Obj> is lock free? "
				<< std::atomic_is_lock_free(&c) << '\n';

			system("pause");
		}
	}


	void aba_problem()
	{
		// The ABA Problem
		// Before discussing pop, let's reconsider what our CAS operation is actually checking for:
		// that the top of the stack (the address of the Node, to be specific) is unchanged.
		// This does not actually mean "the stack is unchanged.
		// " The ABA problem exposes a case where this isn't a strong enough check.
		// The issue can be exposed with a sequence of push and pop operations.
		{
			Obj* obj1 = new Obj('A');
			Obj* obj2 = new Obj('B');
			Obj* obj3 = new Obj('C');

			Stack stack;
			stack.Push(obj3);
			stack.Push(obj2);
			stack.Push(obj1);

			// top -> A -> B -> C

			boost::thread th1([&stack]()
			{
				Obj* obj = stack.Pop(); // pop A, top -> B -> C
										// compare_exchange_weak( A, A, B ) <- access violation !!!!!!
										// B deleted pointer by th2
				return obj;
			});

			boost::thread th2([&stack]()
			{
				Obj* o1 = stack.Pop(); // pop A, top -> B -> C

				Obj* o2 = stack.Pop(); // pop B, top -> C
				delete o2; // delete B

				stack.Push(o1); // push A, top -> A -> C
			});

			boost::thread_group tg;
			tg.add_thread(&th1);
			tg.add_thread(&th2);

			tg.join_all();

			delete obj1;
			delete obj3;

			system("pause");
		}
	}


	void Test()
	{
		// compile with: /EHsc /O2

		//check_lock_free();

		//aba_problem();
	}
}// end of ABAProblem

