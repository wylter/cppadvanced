#pragma once
#include "FixedAllocator.h"
#include <vector>
#include "utility.h"

class SmallObjAllocator
{
public:
	SmallObjAllocator(size_t chunkSize, size_t maxObjectSize);
	void* Allocate(size_t numBytes);
	void Deallocate(void* p, size_t size);

private:
	std::vector<FixedAllocator, mallocAllocator<FixedAllocator>> pool_;
	FixedAllocator* pLastAlloc_;
	FixedAllocator* pLastDealloc_;
	size_t chunkSize_;
	size_t maxObjectSize_;
};