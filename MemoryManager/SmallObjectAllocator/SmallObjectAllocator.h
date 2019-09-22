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

// 	friend bool operator==(const SmallObjAllocator& lhs, const SmallObjAllocator& rhs){ return true; } //The allocator is stateless, all instances are equals
// 	friend bool operator!=(const SmallObjAllocator&, const SmallObjAllocator&) { return !(lhs == rhs); }
	
// 	void* operator new(size_t size) { return malloc(size); }
// 	void operator delete(void* p) { free(p); }
private:
	std::vector<FixedAllocator, mallocAllocator<FixedAllocator>> pool_;
	FixedAllocator* pLastAlloc_;
	FixedAllocator* pLastDealloc_;
	size_t chunkSize_;
	size_t maxObjectSize_;
};