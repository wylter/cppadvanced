#pragma once
#include "SmallObjectAllocator.h"

static SmallObjAllocator small_allocator = SmallObjAllocator(255, 64);
static size_t byte_used = 0;

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
		byte_used += n;
		return static_cast<pointer>(small_allocator.Allocate(n));
	}
	
	void deallocate(T* p)
	{
		const size_t size = sizeof(T);

		byte_used -= size;
		small_allocator.Deallocate(p, size);
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
void* MM_DELETE(void* ptr) noexcept;
