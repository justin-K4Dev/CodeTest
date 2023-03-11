#include "stdafx.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
#include <vector>

std::vector<void*> myAlloc;

void* newImpl(std::size_t sz, char const* file, int line)
{
	static int counter{};
	void* ptr = std::malloc(sz);
	std::cerr << file << ": " << line << " " << ptr << std::endl;
	myAlloc.push_back(ptr);
	return ptr;
}

void* operator new(std::size_t sz, char const* file, int line)
{
	return newImpl(sz, file, line);
}

void* operator new [](std::size_t sz, char const* file, int line)
{
	return newImpl(sz, file, line);
}

void operator delete(void* ptr) noexcept
{
	auto ind = std::distance(myAlloc.begin(), std::find(myAlloc.begin(), myAlloc.end(), ptr));
	if (0 >= ind) {
		return;
	}

	myAlloc[ind - 1] = nullptr;
	std::free(ptr);
}

#define new new(__FILE__, __LINE__)

void dummyFunction()
{
	int* dummy = new int;

	system("pause");

	/*
	output:
		New.cpp: 46 0000000000654880
	*/
}

void getInfo()
{
	std::cout << "Allocation: " << std::endl;
	for (auto& i : myAlloc) {
		if (i != nullptr) {
			std::cout << " " << i << std::endl;
		}
	}
	/*
	output:
		Allocation:
		 0000000000774880
	*/
}

namespace New
{
	void Test()
	{
		dummyFunction();

		getInfo();
	}
}