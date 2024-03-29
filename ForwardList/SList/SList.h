#pragma once
#include <iterator>
#include "List_types.h"
#include "SList/SList_iterator.h"

namespace cppadvanced
{
	template < typename T >
	class SList {
	public:

		typedef T value_type;
		typedef value_type& reference;
		typedef const reference const_reference;
 		typedef value_type* pointer;
 		typedef const pointer const_pointer;
		typedef size_t size_type;

		typedef SList_node<T> node;
		typedef SList_iterator<T> iterator;
		typedef const iterator const_iterator;


		//CTOR
		SList();
		SList(size_type count);

		template<class InputIt>
		SList(InputIt first, InputIt last);

		SList(const SList<T>& other); //Copy constructor
		SList(SList<T>&& other); //Move constructor

		//DTOR
		~SList();

		//MEMBER FUNCTIONS
		SList<T>& operator=(const SList<T>& other); //Copy operator
		SList<T>& operator=(SList<T>&& other); //Move Operator

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

		void swap(SList<T>& other);

		//OPERATIONS
		void remove(const T& value);

		void reverse() noexcept;

		void unique();

		void sort();
		template< class Compare >
		void sort(Compare comp);

	

	private:
		void split(iterator head, iterator& splittedHead1, iterator& splittedHead2);
		template< class Compare >
		iterator merge_list(iterator head1, iterator head2, Compare comp);
		template< class Compare >
		void merge_sort(iterator& head, Compare comp);

		iterator before_head; //Front iterator of the SList
		static const iterator back; //End iterator of the SList
	};

}

#include "SList.inl"

