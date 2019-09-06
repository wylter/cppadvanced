#pragma once
#include "List_types.h"

namespace cppadvanced
{
	template < typename T >
	class SListArray_iterator : public std::iterator < std::forward_iterator_tag, T, std::ptrdiff_t, T*, T& >
	{

		template<typename> friend class SList;
		typedef T& it_reference;
		typedef T* it_pointer;
		typedef SListArray_node<T> it_node;

	public:
		SListArray_iterator<T>();
		SListArray_iterator<T>(const SListArray_iterator<T>&);
		explicit SListArray_iterator(indexed_node_base* const);
		~SListArray_iterator();
		SListArray_iterator<T>& operator=(const SListArray_iterator<T>&);
		SListArray_iterator<T>& operator++();
		it_reference operator*() const;
		friend void swap(SListArray_iterator<T>& lhs, SListArray_iterator<T>& rhs);
		SListArray_iterator<T> operator++(int); //postfix increment
		it_pointer operator->() const;
		template < typename U >
		friend bool operator==(const SListArray_iterator<U>&, const SListArray_iterator<U>&);
		template < typename U >
		friend bool operator!=(const SListArray_iterator<U>&, const SListArray_iterator<U>&);

	protected:
		indexed_node_base* current_node;
	};
}

#include "SListArray_iterator.inl"