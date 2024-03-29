#pragma once


struct Chunk
{
	void Init(size_t blockSize, unsigned char blocks);
	void Close();
	void* Allocate(size_t blockSize);
	void Deallocate(void* p, size_t blockSize);
	unsigned char* pData_;
	unsigned char
		firstAvailableBlock_,
		blocksAvailable_;

};