#include "pch.h"
#include "SmallAllocator.h"

void* MM_NEW(std::size_t count) noexcept
{
	return small_allocator.Allocate(count);
}
