#include "pch.h"
#include "SListVector/SListVector_iterator.h"
#include <vector>

namespace cppadvanced
{
	template < typename T >
	SListVector_iterator<T>::SListVector_iterator() 
		: current_node_index()
		, storage_pointer(nullptr)
	{}

	template < typename T >
	SListVector_iterator<T>::SListVector_iterator(const SListVector_iterator<T>& other)
	{
		current_node_index = other.current_node_index;
		storage_pointer = other.storage_pointer;
	}

	template < typename T >
	SListVector_iterator<T>::SListVector_iterator(const size_t nodeIndex, storage_type const storage_pointer)
		: current_node_index(nodeIndex)
		, storage_pointer(storage_pointer)
	{}

	template < typename T >
	SListVector_iterator<T>::~SListVector_iterator()
	{}

	template < typename T >
	SListVector_iterator<T>& SListVector_iterator<T>::operator=(const SListVector_iterator<T>& other)
	{
		current_node_index = other.current_node_index;
		storage_pointer = other.storage_pointer;
		return *this;
	}

	template < typename T >
	SListVector_iterator<T>& SListVector_iterator<T>::operator++()
	{
		current_node_index = (*storage_pointer)[current_node_index].next;
		return *this;
	}

	template < typename T >
	typename SListVector_iterator<T>::it_reference SListVector_iterator<T>::operator*() const
	{
		it_node& current_typed_node = (*storage_pointer)[current_node_index];
		return current_typed_node.value;
	}

	template < typename T >
	void swap(SListVector_iterator<T>& lhs, SListVector_iterator<T>& rhs)
	{
		std::swap(lhs, rhs);
	}

	template < typename T >
	SListVector_iterator<T> SListVector_iterator<T>::operator++(int a)
	{
		SListVector_iterator result(*this);
		++(*this);
		return result;
	}

	template < typename T >
	typename SListVector_iterator<T>::it_pointer SListVector_iterator<T>::operator->() const
	{
		it_node& current_typed_node = (*storage_pointer)[current_node_index];
		return &current_typed_node.value;
	}

	template < typename U >
	bool operator==(const SListVector_iterator<U>& lhs, const SListVector_iterator<U>& rhs)
	{
		return lhs.current_node_index == rhs.current_node_index;
	}

	template < typename U >
	bool operator!=(const SListVector_iterator<U>& lhs, const SListVector_iterator<U>& rhs)
	{
		return !(lhs == rhs);
	}

	template < typename T >
	SListVector_iterator<T>::operator size_t() const
	{
		return current_node_index;
	}

	template < typename T >
	typename SListVector_iterator<T>::it_node* SListVector_iterator<T>::GetCurrentNodeAddress() const
	{
		it_node* current_node_address = &(*storage_pointer)[current_node_index];
		return current_node_address;
	}
}