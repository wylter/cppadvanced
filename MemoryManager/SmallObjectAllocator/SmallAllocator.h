#pragma once
#include "SmallObjectAllocator.h"
#include <map>

#define MAXBYTECOUNT 64

struct MemoryManager
{
public:
	static SmallObjAllocator small_allocator;
	static size_t byte_used;
};

template <typename T>
struct SmallAllocator
{
	typedef T value_type;
	typedef value_type& reference;
	typedef const reference const_reference;
	typedef value_type* pointer;
	typedef const pointer const_pointer;
	typedef size_t size_type;
	typedef	std::ptrdiff_t difference_type;
	typedef	std::true_type propagate_on_container_move_assignment;
	typedef std::true_type is_always_equal;

	SmallAllocator() {};
	~SmallAllocator() {};

	pointer allocate(size_type n)
	{
		MemoryManager::byte_used += n;
		return static_cast<pointer>(MemoryManager::small_allocator.Allocate(n));
	}
	
	void deallocate(T* p)
	{
		const size_t size = sizeof(T);
		MemoryManager::small_allocator.Deallocate(p, size);

		MemoryManager::byte_used -= size;
	}

	template <typename U>
	friend bool operator==(const SmallAllocator<U>& lhs, const SmallAllocator<U>& rhs)
	{
		return true;
	}

	template <typename U>
	friend bool operator!=(const SmallAllocator<U>& lhs, const SmallAllocator<U>& rhs)
	{
		return !(lhs == rhs);
	}
};

void* MM_NEW(std::size_t count) noexcept;
void MM_DELETE(void* ptr, std::size_t count) noexcept;
void* MM_NEW_A(std::size_t count) noexcept;
void MM_DELETE_A(void* ptr) noexcept;
void* MM_ALLOC(std::size_t count) noexcept;
void MM_FREE(void* ptr, std::size_t count) noexcept;
