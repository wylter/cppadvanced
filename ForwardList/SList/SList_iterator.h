#pragma once
#include "List_types.h"

namespace cppadvanced
{
	template < typename T >
	class SList_iterator : public std::iterator < std::forward_iterator_tag, T, std::ptrdiff_t, T*, T& >
	{

		template<typename> friend class SList;
		typedef T& it_reference;
		typedef T* it_pointer;
		typedef SList_node<T> it_node;

	public:
		SList_iterator<T>();
		SList_iterator<T>(const SList_iterator<T>&);
		explicit SList_iterator(node_base* const);
		~SList_iterator();
		SList_iterator<T>& operator=(const SList_iterator<T>&);
		SList_iterator<T>& operator++();
		it_reference operator*() const;
		friend void swap(SList_iterator<T>& lhs, SList_iterator<T>& rhs);
		SList_iterator<T> operator++(int); //postfix increment
		it_pointer operator->() const;
		template < typename U >
		friend bool operator==(const SList_iterator<U>&, const SList_iterator<U>&);
		template < typename U >
		friend bool operator!=(const SList_iterator<U>&, const SList_iterator<U>&);

	protected:
 		node_base* current_node;
	};
}

#include "SList_iterator.inl"