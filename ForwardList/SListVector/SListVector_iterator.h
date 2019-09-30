#pragma once
#include "List_types.h"
#include <vector>

namespace cppadvanced
{

	template < typename T >
	class SListVector_iterator : public std::iterator < std::forward_iterator_tag, T, std::ptrdiff_t, T*, T& >
	{

		template<typename> friend class SListVector;
		typedef T& it_reference;
		typedef T* it_pointer;
		typedef indexed_node<T> it_node;
		typedef std::vector<it_node>* storage_type;

	public:
		SListVector_iterator<T>();
		SListVector_iterator<T>(const SListVector_iterator<T>&);
		SListVector_iterator(const size_t, storage_type const);
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
		it_node* GetCurrentNode() const;

		size_t current_node;
		storage_type storage_pointer;
	};

}

#include "SListVector_iterator.inl"