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

	struct node_base
	{
		node_base* next;

		node_base()
			: next(nullptr)
		{}
	};

	struct node : node_base {
		value_type value;
	};

	class SList_iterator : public std::iterator < std::forward_iterator_tag, value_type, std::ptrdiff_t, pointer, reference >
	{

		friend class SList;
		typedef int& it_reference;
		typedef int* it_pointer;

	public:
		SList_iterator();
		SList_iterator(const SList_iterator&);
		explicit SList_iterator(node_base* const);
		~SList_iterator();
		SList_iterator& operator=(const SList_iterator&);
		SList_iterator& operator++();
		it_reference operator*() const;
		friend void swap(SList_iterator& lhs, SList_iterator& rhs);
		SList_iterator operator++(int); //postfix increment
		it_pointer operator->() const;
		friend bool operator==(const SList_iterator&, const SList_iterator&);
		friend bool operator!=(const SList_iterator&, const SList_iterator&);

	protected:
		node_base* current_node;
	};

	typedef SList_iterator iterator;
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


template<class InputIt>
SList::SList(InputIt first, InputIt last) : SList()
{
	iterator it = before_head;
	
	for (; first != last; first++, it++)
	{
		node* newNode = new node();
		newNode->value = *first;

		it.current_node->next = newNode;
	}
}

template< class InputIt >
SList::iterator SList::insert_after(const_iterator pos, InputIt first, InputIt last)
{
	iterator last_prepos = pos;
	const iterator postpos = std::next(pos);

	for (; first != last; first++, last_prepos++)
	{
		node* newNode = new node();
		newNode->value = *first;

		last_prepos.current_node->next = newNode;
	}

	last_prepos.current_node->next = postpos.current_node;


	return last_prepos;
}

template< class Compare >
void SList::sort(Compare comp)
{
	iterator head = std::next(before_head);

	mergeSort(head, comp);

	before_head.current_node->next = head.current_node;
}

template< class Compare >
SList::iterator SList::mergeList(iterator head1, iterator head2, Compare comp)
{
	node_base before_head_node;
	before_head_node.next = nullptr;
	iterator before_head_result(&before_head_node);

	iterator it = before_head_result;

	while (head1 != back && head2 != back)
	{
		if (comp(*head1, *head2))
		{
			it.current_node->next = head1.current_node;
			it++;
			head1++;
		}
		else
		{
			it.current_node->next = head2.current_node;
			it++;
			head2++;
		}
	}

	if (head1 != back)
	{
		it.current_node->next = head1.current_node;
	}
	else //head2 != back
	{
		it.current_node->next = head2.current_node;
	}


	return std::next(before_head_result);
}


template< class Compare >
void SList::mergeSort(iterator& head_reference, Compare comp)
{
	const iterator head = head_reference;

	if (head == back || std::next(head) == back)
	{
		return;
	}

	iterator splittedHead1;
	iterator splittedHead2;

	split(head, splittedHead1, splittedHead2);

	mergeSort(splittedHead1, comp);
	mergeSort(splittedHead2, comp);

	head_reference = mergeList(splittedHead1, splittedHead2, comp);
}

