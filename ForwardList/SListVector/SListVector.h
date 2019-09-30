#pragma once
#include <iterator>
#include "List_types.h"
#include "SListVector/SListVector_iterator.h"
#include <vector>

namespace cppadvanced
{
	template < typename T >
	class SListVector {
	public:

		typedef T value_type;
		typedef value_type& reference;
		typedef const reference const_reference;
 		typedef value_type* pointer;
 		typedef const pointer const_pointer;
		typedef size_t size_type;

		typedef indexed_node<T> node;
		typedef SListVector_iterator<T> iterator;
		typedef const iterator const_iterator;

		typedef std::vector<node> storage_type;


		//CTOR
		SListVector();
		SListVector(size_type count);

		template<class InputIt>
		SListVector(InputIt first, InputIt last);

		SListVector(const SListVector<T>& other); //Copy constructor
		SListVector(SListVector<T>&& other); //Move constructor

		//DTOR
		~SListVector();

		//MEMBER FUNCTIONS
		SListVector<T>& operator=(const SListVector<T>& other); //Copy operator
		SListVector<T>& operator=(SListVector<T>&& other); //Move Operator

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

		void swap(SListVector<T>& other);

		//OPERATIONS
		void remove(const T& value);

		void reverse() noexcept;

		void unique();

		void sort();
		template< class Compare >
		void sort(Compare comp);

	

	private:
		size_t extractFreeHeadNode();
		void pushFreeHead(iterator it);
		void pushFreeHead(iterator first, iterator last);
		void split(iterator head, iterator& splittedHead1, iterator& splittedHead2);
		template< class Compare >
		iterator mergeList(iterator head1, iterator head2, Compare comp);
		template< class Compare >
		void mergeSort(iterator& head, Compare comp);

		iterator before_used_head; //Front iterator of the SList
		iterator before_free_head;
		static const iterator back; //End iterator of the SList

		static constexpr size_t MINSIZE = 2;

		storage_type storage;
	};

}

#include "SListVector.inl"

