#pragma once
#include <iterator>
#include "List_types.h"
#include "SListVector/SListVector_iterator.h"

namespace cppadvanced
{
	template < typename T, size_t MAX >
	class SListVector {
	public:

		typedef T value_type;
		typedef value_type& reference;
		typedef const reference const_reference;
 		typedef value_type* pointer;
 		typedef const pointer const_pointer;
		typedef size_t size_type;

		typedef SListArray_node<T> node;
		typedef SListVector_iterator<T> iterator;
		typedef const iterator const_iterator;


		//CTOR
		SListVector();
		SListVector(size_type count);

		template<class InputIt>
		SListVector(InputIt first, InputIt last);

		SListVector(const SListVector<T, MAX>& other); //Copy constructor
		SListVector(SListVector<T, MAX>&& other); //Move constructor

		//DTOR
		~SListVector();

		//MEMBER FUNCTIONS
		SListVector<T, MAX>& operator=(const SListVector<T, MAX>& other); //Copy operator
		SListVector<T, MAX>& operator=(SListVector<T, MAX>&& other); //Move Operator

		//ELEMENT ACCESS
		reference front();
		const_reference front() const;

		//ITERATORS
		iterator before_begin() noexcept;
		const iterator before_begin() const noexcept;
		const iterator cbefore_begin() const noexcept;

		iterator begin() noexcept;
		const iterator begin() const noexcept;
		const iterator cbegin() const noexcept;

		iterator end() noexcept;
		const iterator end() const noexcept;
		const iterator cend() const noexcept;

		//CAPACITY
		bool empty() const noexcept;

		size_type max_size() const noexcept;

		//MODIFIERS
		void clear() noexcept;

		iterator insert_after(const_iterator pos, const T& value);
		iterator insert_after(const_iterator pos, T&& value);
		iterator insert_after(const_iterator pos, size_type count, const T& value);
 		template< class InputIt >
 		iterator insert_after(const_iterator pos, InputIt first, InputIt last);

		iterator erase_after(const_iterator pos);
		iterator erase_after(const_iterator first, const_iterator last);

		void push_front(const T& value);
		void push_front(T&& value);

		void pop_front();

		void resize(size_type count, const value_type& value = value_type());

		void swap(SListVector<T, MAX>& other);

		//OPERATIONS
		void remove(const T& value);

		void reverse() noexcept;

		void unique();

		void sort();
		template< class Compare >
		void sort(Compare comp);

	

	private:
		node* extractFreeHeadNode();
		void pushFreeHead(iterator it);
		void pushFreeHead(iterator first, iterator last);
		void split(iterator head, iterator& splittedHead1, iterator& splittedHead2);
		template< class Compare >
		iterator mergeList(iterator head1, iterator head2, Compare comp);
		template< class Compare >
		void mergeSort(iterator& head, Compare comp);

		iterator before_used_head; //Front iterator of the SList
		iterator before_free_head;
		const iterator back; //End iterator of the SList

		indexed_node_base before_used_node;
		indexed_node_base before_free_node;
		node storage[MAX];
	};

}

#include "SListVector.inl"

