#include "pch.h"
#include "Chunk.h"

void Chunk::Init(size_t blockSize, unsigned char blocks)
{

	pData_ = new unsigned char[blockSize * blocks];

	firstAvailableBlock_ = 0;
	blocksAvailable_ = blocks;

	unsigned char i = 0;
	unsigned char* p = pData_;
	for (; i != blocks; p += blockSize)
	{
		*p = ++i;
	}
}

void* Chunk::Allocate(size_t blockSize)
{
	if (!blocksAvailable_)
	{
		return 0;
	}

	unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
	firstAvailableBlock_ = *pResult;
	--blocksAvailable_;

	return pResult;
}

void Chunk::Deallocate(void* p, size_t blockSize)
{
	unsigned char* const freePos = static_cast<unsigned char*>(p);

	*freePos = firstAvailableBlock_;
	firstAvailableBlock_ = (freePos - pData_) / blockSize;

	blocksAvailable_++;
}
