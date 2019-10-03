// MemoryManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "SmallObjectAllocator/SmallAllocator.h"
#include <vector>

#define USE_CUSTOM_MEMORY

#ifdef USE_CUSTOM_MEMORY
	void* operator new(size_t size) { return MM_NEW(size); };
	void operator delete(void* ptr, size_t size) { MM_DELETE(ptr, size); };
	void* operator new[](size_t size) { return MM_NEW_A(size); };
	void operator delete[](void* ptr) { MM_DELETE_A(ptr); };
#endif 

struct test
{
	test()
	{}

	test(int val)
		: i(val)
	{}

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


	int* i = new int[20];
	std::cout << MemoryManager::byte_used << std::endl;
	delete[] i;
	std::cout << MemoryManager::byte_used << std::endl;

	{
		std::vector<test, SmallAllocator<test>> v(10);

		std::cout << MemoryManager::byte_used << std::endl;
	}

	std::cout << MemoryManager::byte_used << std::endl;
	


}
