#pragma once
#include "Chunk.h"
#include "utility.h"
#include <vector>

class FixedAllocator
{
public:
	FixedAllocator(size_t, unsigned char);
	~FixedAllocator();
	void* Allocate();
	void Deallocate(void* p);

	inline size_t GetBlockSize() { return blockSize_; }
private:
	bool inline InsideAddress(void* p, void* first, void* last);
	size_t blockSize_;
	size_t deallocIndex_;
	typedef std::vector<Chunk, mallocAllocator<Chunk>> Chunks;
	Chunks chunks_;
	Chunk* allocChunk_;
	Chunk* deallocChunk_;
	unsigned char numBlocks_;
	unsigned char freeChunks;
};