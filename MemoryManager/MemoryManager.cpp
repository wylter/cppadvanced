// MemoryManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "SmallObjectAllocator/SmallAllocator.h"

#define USE_CUSTOM_MEMORY

#ifdef USE_CUSTOM_MEMORY
	void* operator new(size_t size) { return MM_NEW(size); };
	void operator delete(void* ptr, size_t size) { MM_DELETE(ptr, size); };
#endif // 

struct test
{
	test()
	{

	}

	test(int val)
		: i(val)
	{

	}

	int i;
};

int main()
{
	test* t = new test();

	std::cout << MemoryManager::byte_used << std::endl;

	test* t2 = new test();
	std::cout << MemoryManager::byte_used << std::endl;
	delete t;
	delete t2;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
