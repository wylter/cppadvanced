#pragma once
#include <iterator>
#include "SList_types.h"
#include "SList_iterator.h"

namespace cppadvanced
{
	class SList {
	public:

		typedef int value_type;
		typedef value_type& reference;
		typedef const reference const_reference;
 		typedef value_type* pointer;
 		typedef const pointer const_pointer;
		typedef size_t size_type;

		typedef SList_node<int> node;
		typedef SList_iterator<int> iterator;
		typedef const iterator const_iterator;


		//CTOR
		SList();
		SList(size_type count);

		template<class InputIt>
		SList(InputIt first, InputIt last);

		SList(const SList& other); //Copy constructor
		SList(SList&& other); //Move constructor

		//DTOR
		~SList();

		//MEMBER FUNCTIONS
		SList& operator=(const SList& other); //Copy operator
		SList& operator=(SList&& other); //Move Operator

		//ELEMENT ACCESS
		reference front();
		const_reference front() const;

		//ITERATORS
		iterator before_begin() noexcept;
		const_iterator before_begin() const noexcept;
		const_iterator cbefore_begin() const noexcept;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		//CAPACITY
		bool empty() const noexcept;

		size_type max_size() const noexcept;

		//MODIFIERS
		void clear() noexcept;

		iterator insert_after(const_iterator pos, const int& value);
		iterator insert_after(const_iterator pos, int&& value);
		iterator insert_after(const_iterator pos, size_type count, const int& value);
 		template< class InputIt >
 		iterator insert_after(const_iterator pos, InputIt first, InputIt last);

		iterator erase_after(const_iterator pos);
		iterator erase_after(const_iterator first, const_iterator last);

		void push_front(const int& value);
		void push_front(int&& value);

		void pop_front();

		void resize(size_type count, const value_type& value = value_type());

		void swap(SList& other);

		//OPERATIONS
		void remove(const int& value);

		void reverse() noexcept;

		void unique();

		void sort();
		template< class Compare >
		void sort(Compare comp);

	

	private:
		void split(iterator head, iterator& splittedHead1, iterator& splittedHead2);
		template< class Compare >
		iterator mergeList(iterator head1, iterator head2, Compare comp);
		template< class Compare >
		void mergeSort(iterator& head, Compare comp);

		iterator before_head; //Front iterator of the SList
		static const iterator back; //End iterator of the SList
	};

}

#include "SList.inl"

