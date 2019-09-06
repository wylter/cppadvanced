#include "pch.h"
#include "SListArray/SListArray_iterator.h"

namespace cppadvanced
{
	template < typename T >
	SListArray_iterator<T>::SListArray_iterator() 
		: current_node(nullptr)
		, storage_pointer(nullptr)
	{}

	template < typename T >
	SListArray_iterator<T>::SListArray_iterator(const SListArray_iterator<T>& other)
	{
		current_node = other.current_node;
		storage_pointer = other.storage_pointer;
	}

	template < typename T >
	SListArray_iterator<T>::SListArray_iterator(indexed_node_base* const otherNode, it_node* storage_pointer)
		: current_node(otherNode)
		, storage_pointer(storage_pointer)
	{
	}

	template < typename T >
	SListArray_iterator<T>::~SListArray_iterator()
	{
	}

	template < typename T >
	SListArray_iterator<T>& SListArray_iterator<T>::operator=(const SListArray_iterator<T>& other)
	{
		current_node = other.current_node;
		storage_pointer = other.storage_pointer;
		return *this;
	}

	template < typename T >
	SListArray_iterator<T>& SListArray_iterator<T>::operator++()
	{
		current_node = storage_pointer + current_node->next;
		return *this;
	}

	template < typename T >
	typename SListArray_iterator<T>::it_reference SListArray_iterator<T>::operator*() const
	{
		it_node* const current_typed_node = static_cast<it_node*>(current_node);
		return current_typed_node->value;
	}

	template < typename T >
	void swap(SListArray_iterator<T>& lhs, SListArray_iterator<T>& rhs)
	{
		std::swap(lhs, rhs);
	}

	template < typename T >
	SListArray_iterator<T> SListArray_iterator<T>::operator++(int a)
	{
		SListArray_iterator result(*this);
		++(*this);
		return result;
	}

	template < typename T >
	typename SListArray_iterator<T>::it_pointer SListArray_iterator<T>::operator->() const
	{
		it_node* const current_typed_node = static_cast<it_node*>(current_node);
		return &current_typed_node->value;
	}

	template < typename U >
	bool operator==(const SListArray_iterator<U>& lhs, const SListArray_iterator<U>& rhs)
	{
		return lhs.current_node == rhs.current_node;
	}

	template < typename U >
	bool operator!=(const SListArray_iterator<U>& lhs, const SListArray_iterator<U>& rhs)
	{
		return !(lhs == rhs);
	}
}