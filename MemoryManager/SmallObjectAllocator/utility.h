#pragma once
#include <memory>

template <typename T>
struct tmpAllocator
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
	template< class U > struct rebind { typedef tmpAllocator<U> other; };

	tmpAllocator() {};
	tmpAllocator(const tmpAllocator& other) {}
	template< class U >
	tmpAllocator(const tmpAllocator<U>& other) {}
	~tmpAllocator() {};

	pointer allocate(size_type s, void const * = 0)
	{
		if (0 == s)
			return NULL;
		pointer temp = (pointer)malloc(s * sizeof(T));
		if (temp == NULL)
			throw std::bad_alloc();
		return temp;
	}

	void deallocate(pointer p, size_type)
	{
		free(p);
	}

	// 	template <typename U>
	// 	friend bool operator==(const tmpAllocator<U>& lhs, const tmpAllocator<U>& rhs)
	// 	{
	// 		return true;
	// 	}
	// 
	// 	template <typename U>
	// 	friend bool operator!=(const tmpAllocator<U>& lhs, const tmpAllocator<U>& rhs)
	// 	{
	// 		return !(lhs == rhs);
	// 	}
};