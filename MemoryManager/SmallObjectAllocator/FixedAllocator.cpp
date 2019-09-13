#include "pch.h"
#include "FixedAllocator.h"
#include <cassert>

FixedAllocator::FixedAllocator(size_t blockSize, unsigned char numBlocks) 
	: blockSize_(blockSize)
	, numBlocks_(numBlocks)
	, allocChunk_(nullptr)
	, deallocChunk_(nullptr)
	, freeChunks(0)
	, chunks_()
{}

FixedAllocator::~FixedAllocator()
{}

void* FixedAllocator::Allocate()
{

	if (allocChunk_ == 0 || allocChunk_->blocksAvailable_ == 0)
	{

		Chunks::iterator i = chunks_.begin();
		for (;; ++i)
		{

			if (i == chunks_.end())
			{

				chunks_.reserve(chunks_.size() + 1);
				Chunk newChunk;
				newChunk.Init(blockSize_, numBlocks_);
				chunks_.push_back(newChunk);
				allocChunk_ = &chunks_.back();
				deallocChunk_ = &chunks_.back();
				deallocIndex_ = std::distance(chunks_.begin(), i);
				break;

			}
			if (i->blocksAvailable_ > 0)
			{

				allocChunk_ = &*i;
				break;

			}

		}

	}

	assert(allocChunk_ != 0);
	assert(allocChunk_->blocksAvailable_ > 0);
	return allocChunk_->Allocate(blockSize_);

}

void FixedAllocator::Deallocate(void* p)
{
	const size_t chunkSize = blockSize_ * numBlocks_;

	if (deallocChunk_ == 0 || !InsideAddress(p, deallocChunk_->pData_, deallocChunk_->pData_ + chunkSize));
	{
		for (Chunks::iterator i = chunks_.begin(); i != chunks_.end(); ++i)
		{
			if (InsideAddress(p, i->pData_, i->pData_ + chunkSize))
			{
				deallocChunk_ = &*i;
				deallocIndex_ = std::distance(chunks_.begin(), i);
				break;
			}
		}
	}

	assert(deallocChunk_ != 0);
	assert(InsideAddress(p, deallocChunk_->pData_, deallocChunk_->pData_ + chunkSize));

	deallocChunk_->Deallocate(p, blockSize_); 

	if (deallocChunk_->blocksAvailable_ == numBlocks_)
	{
		if (freeChunks >= 1)
		{
			chunks_.erase(chunks_.begin() + deallocIndex_);
		}
		else
		{
			++freeChunks;
		}
	}
}

bool FixedAllocator::InsideAddress(void* p, void* first, void* last)
{
	return p >= first && p < last;
}
