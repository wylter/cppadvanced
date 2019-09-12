#pragma once
#include "List_types.h"

namespace cppadvanced
{
	template < typename T >
	class SListVector_iterator : public std::iterator < std::forward_iterator_tag, T, std::ptrdiff_t, T*, T& >
	{

		template<typename, size_t> friend class SListVector;
		typedef T& it_reference;
		typedef T* it_pointer;
		typedef SListArray_node<T> it_node;

	public:
		SListVector_iterator<T>();
		SListVector_iterator<T>(const SListVector_iterator<T>&);
		explicit SListVector_iterator(indexed_node_base* const, it_node* const);
		~SListVector_iterator();
		SListVector_iterator<T>& operator=(const SListVector_iterator<T>&);
		SListVector_iterator<T>& operator++();
		it_reference operator*() const;
		friend void swap(SListVector_iterator<T>& lhs, SListVector_iterator<T>& rhs);
		SListVector_iterator<T> operator++(int); //postfix increment
		it_pointer operator->() const;
		template < typename U >
		friend bool operator==(const SListVector_iterator<U>&, const SListVector_iterator<U>&);
		template < typename U >
		friend bool operator!=(const SListVector_iterator<U>&, const SListVector_iterator<U>&);

	protected:
		operator size_t() const;

		indexed_node_base* current_node;
		it_node* storage_pointer;
	};

}

#include "SListVector_iterator.inl"