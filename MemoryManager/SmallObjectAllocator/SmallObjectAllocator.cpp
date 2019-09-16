#include "pch.h"
#include "SmallObjectAllocator.h"
#include <cassert>
#include <new>

SmallObjAllocator::SmallObjAllocator(size_t chunkSize, size_t maxObjectSize)
	: chunkSize_(chunkSize)
	, maxObjectSize_(maxObjectSize)
	, pLastAlloc_(nullptr)
	, pLastDealloc_(nullptr)
{}

void* SmallObjAllocator::Allocate(size_t numBytes)
{
	if (numBytes > maxObjectSize_)
	{
		return new(std::nothrow) unsigned char[numBytes];
	}

	if (pLastAlloc_ == 0 || pLastAlloc_->GetBlockSize() != numBytes)
	{
		auto i = pool_.begin();
		for (;; ++i)
		{
			if (i == pool_.end())
			{	
				pool_.reserve(pool_.size() + 1);
				FixedAllocator allocator(chunkSize_, maxObjectSize_);
				pool_.push_back(allocator);

				pLastAlloc_ = &pool_.back();
				pLastDealloc_ = &pool_.back();
				break;
			}

			if (i->GetBlockSize() == numBytes)
			{
				pLastAlloc_ = &*i;
				break;
			}
		}
	}

	assert(pLastAlloc_ != 0);
	assert(pLastAlloc_->GetBlockSize() == numBytes);

	return pLastAlloc_->Allocate();
}

void SmallObjAllocator::Deallocate(void* p, size_t size)
{
	if (size > maxObjectSize_)
	{
		operator delete[] (p, std::nothrow);
	}

	if (pLastDealloc_ == 0 || pLastDealloc_->GetBlockSize() != size)
	{
		for (auto i = pool_.begin(); i != pool_.end(); ++i)
		{
			if (i->GetBlockSize() == size)
			{
				pLastDealloc_ = &*i;
				break;
			}
		}
	}

	assert(pLastDealloc_ != 0);
	assert(pLastDealloc_->GetBlockSize() == size);

	return pLastDealloc_->Deallocate(p);
}

