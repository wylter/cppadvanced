#include "pch.h"
#include "SmallAllocator.h"
#include <iostream>

SmallObjAllocator MemoryManager::small_allocator(255, MAXBYTECOUNT);
size_t MemoryManager::byte_used(0);

void* MM_NEW(std::size_t count) noexcept
{
	MemoryManager::byte_used += count;

	if (count < MAXBYTECOUNT)
	{
		void* p = MemoryManager::small_allocator.Allocate(count);
		return p;
	}
	else
	{
		return std::malloc(count);
	}
}

void MM_DELETE(void* ptr, std::size_t count) noexcept
{
	if (ptr)
	{
		if (count < MAXBYTECOUNT)
		{
			MemoryManager::small_allocator.Deallocate(ptr, count);
		}
		else
		{
			std::free(ptr);
		}
		
		MemoryManager::byte_used -= count;
	}
}

void* MM_NEW_A(std::size_t count) noexcept
{
	void* const ptr = MM_NEW(count + sizeof(size_t));
	size_t* const ptrNumeric = static_cast<size_t*>(ptr);

	*ptrNumeric = count;

	void* const resultPtr = ptrNumeric + 1;

	return resultPtr;
}

void MM_DELETE_A(void* ptr) noexcept
{
	size_t* ptrNumeric = static_cast<size_t*>(ptr);

	--ptrNumeric;

	void* const ptrToDelete = ptrNumeric;

	MM_DELETE(ptrToDelete, *ptrNumeric + sizeof(size_t));
}

void* MM_ALLOC(std::size_t count) noexcept
{
	return MM_NEW(count);
}

void MM_FREE(void* ptr, std::size_t count) noexcept
{
	MM_DELETE(ptr, count);
}
