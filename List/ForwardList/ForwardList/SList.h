#pragma once
#include <iterator>

class SList {
public:
	typedef int value_type;
	typedef value_type& reference;
	typedef const reference const_reference;
 	typedef value_type* pointer;
 	typedef const pointer const_pointer;
	typedef size_t size_type;

	struct node {
		value_type value;
		node* next;
	};

	//TODO: Check if this works after inlinement
	struct iterator /*: std::iterator<std::forward_iterator_tag, const value_type>*/{
		iterator();
		iterator(const iterator&);
		~iterator();
		iterator& operator=(const iterator&);
		iterator& operator++();
		reference operator*() const;
		friend void swap(iterator& lhs, iterator& rhs);
		iterator operator++(int); //postfix increment
		pointer operator->() const;
		friend bool operator==(const iterator&, const iterator&);
		friend bool operator!=(const iterator&, const iterator&);

	private:
		node* current_node;
	};

	typedef const iterator const_iterator;


	//CTOR
	SList();

private:
	node* front;

};