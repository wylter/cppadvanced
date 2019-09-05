#include "pch.h"
#include "SList_iterator.h"

namespace cppadvanced
{
	template < typename T >
	SList_iterator<T>::SList_iterator() : current_node(nullptr)
	{
	}

	template < typename T >
	SList_iterator<T>::SList_iterator(const SList_iterator<T>& other)
	{
		current_node = other.current_node;
	}

	template < typename T >
	SList_iterator<T>::SList_iterator(node_base* const otherNode)
	{
		current_node = otherNode;
	}

	template < typename T >
	SList_iterator<T>::~SList_iterator()
	{

	}

	template < typename T >
	SList_iterator<T>& SList_iterator<T>::operator=(const SList_iterator<T>& other)
	{
		current_node = other.current_node;
		return *this;
	}

	template < typename T >
	SList_iterator<T>& SList_iterator<T>::operator++()
	{
		current_node = current_node->next;
		return *this;
	}

	template < typename T >
	typename SList_iterator<T>::it_reference SList_iterator<T>::operator*() const
	{
		it_node* const current_typed_node = static_cast<it_node*>(current_node);
		return current_typed_node->value;
	}

	template < typename T >
	void swap(SList_iterator<T>& lhs, SList_iterator<T>& rhs)
	{
		std::swap(lhs, rhs);
	}

	template < typename T >
	SList_iterator<T> SList_iterator<T>::operator++(int a)
	{
		SList_iterator result(*this);
		++(*this);
		return result;
	}

	template < typename T >
	typename SList_iterator<T>::it_pointer SList_iterator<T>::operator->() const
	{
		it_node* const current_typed_node = static_cast<it_node*>(current_node);
		return &current_typed_node->value;
	}

	template < typename U >
	bool operator==(const SList_iterator<U>& lhs, const SList_iterator<U>& rhs)
	{
		return lhs.current_node == rhs.current_node;
	}

	template < typename U >
	bool operator!=(const SList_iterator<U>& lhs, const SList_iterator<U>& rhs)
	{
		return !(lhs == rhs);
	}
}