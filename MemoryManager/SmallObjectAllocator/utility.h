#pragma once
#include <memory>

template <typename T>
struct mallocAllocator
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
	template< class U > struct rebind { typedef mallocAllocator<U> other; };

	mallocAllocator() {};
	mallocAllocator(const mallocAllocator& other) {}
	template< class U >
	mallocAllocator(const mallocAllocator<U>& other) {}
	~mallocAllocator() {};

	pointer allocate(size_type s, void const * = 0)
	{
		if (0 == s)
		{
			return nullptr;
		}

		pointer temp = static_cast<pointer>(std::malloc(s * sizeof(T)));

		return temp;
	}

	void deallocate(pointer p, size_type)
	{
		std::free(p);
	}

	template <typename U>
	friend bool operator==(const mallocAllocator<U>& lhs, const mallocAllocator<U>& rhs);
	
	template <typename U>
	friend bool operator!=(const mallocAllocator<U>& lhs, const mallocAllocator<U>& rhs);
};

template <typename U>
bool operator==(const mallocAllocator<U>& lhs, const mallocAllocator<U>& rhs)
{
	return true;
}

template <typename U>
bool operator!=(const mallocAllocator<U>& lhs, const mallocAllocator<U>& rhs)
{
	return !(lhs == rhs);
}
