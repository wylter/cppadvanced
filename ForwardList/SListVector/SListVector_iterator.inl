#include "pch.h"
#include "SListVector/SListVector_iterator.h"

namespace cppadvanced
{
	template < typename T >
	SListVector_iterator<T>::SListVector_iterator() 
		: current_node(nullptr)
		, storage_pointer(nullptr)
	{}

	template < typename T >
	SListVector_iterator<T>::SListVector_iterator(const SListVector_iterator<T>& other)
	{
		current_node = other.current_node;
		storage_pointer = other.storage_pointer;
	}

	template < typename T >
	SListVector_iterator<T>::SListVector_iterator(indexed_node_base* const otherNode, it_node* storage_pointer)
		: current_node(otherNode)
		, storage_pointer(storage_pointer)
	{
	}

	template < typename T >
	SListVector_iterator<T>::~SListVector_iterator()
	{
	}

	template < typename T >
	SListVector_iterator<T>& SListVector_iterator<T>::operator=(const SListVector_iterator<T>& other)
	{
		current_node = other.current_node;
		storage_pointer = other.storage_pointer;
		return *this;
	}

	template < typename T >
	SListVector_iterator<T>& SListVector_iterator<T>::operator++()
	{
		current_node = storage_pointer + current_node->next;
		return *this;
	}

	template < typename T >
	typename SListVector_iterator<T>::it_reference SListVector_iterator<T>::operator*() const
	{
		it_node* const current_typed_node = static_cast<it_node*>(current_node);
		return current_typed_node->value;
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
		it_node* const current_typed_node = static_cast<it_node*>(current_node);
		return &current_typed_node->value;
	}

	template < typename U >
	bool operator==(const SListVector_iterator<U>& lhs, const SListVector_iterator<U>& rhs)
	{
		return lhs.current_node == rhs.current_node;
	}

	template < typename U >
	bool operator!=(const SListVector_iterator<U>& lhs, const SListVector_iterator<U>& rhs)
	{
		return !(lhs == rhs);
	}

	template < typename T >
	cppadvanced::SListVector_iterator<T>::operator size_t() const
	{
		const it_node* currentPos = static_cast<it_node*>(current_node);
		return currentPos - storage_pointer;
	}
}