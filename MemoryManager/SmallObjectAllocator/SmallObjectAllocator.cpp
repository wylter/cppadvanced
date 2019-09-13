#include "pch.h"
#include "SmallObjectAllocator.h"
#include <cassert>

SmallObjAllocator::SmallObjAllocator(size_t chunkSize, size_t maxObjectSize)
	: chunkSize_(chunkSize)
	, maxObjectSize_(maxObjectSize)
	, pLastAlloc_(nullptr)
	, pLastDealloc_(nullptr)
{}

void* SmallObjAllocator::Allocate(size_t numBytes)
{
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

