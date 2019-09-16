#include "pch.h"
#include "SmallAllocator.h"
#include <iostream>

SmallObjAllocator MemoryManager::small_allocator(255, 64);
size_t MemoryManager::byte_used(0);

void* MM_NEW(std::size_t count) noexcept
{
	MemoryManager::byte_used += count;
	std::cout << "NEW\t" << MemoryManager::byte_used << std::endl;
	void* p = MemoryManager::small_allocator.Allocate(count);
	return p;
}

void MM_DELETE(void* ptr, std::size_t count) noexcept
{
	if (ptr)
	{
		MemoryManager::small_allocator.Deallocate(ptr, count);
		MemoryManager::byte_used -= count;
		std::cout << "DELETE\t" << MemoryManager::byte_used << std::endl;
	}
}
