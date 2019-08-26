#pragma once

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

	struct iterator{
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


	//CTOR
	SList();

private:
	node* front;

};