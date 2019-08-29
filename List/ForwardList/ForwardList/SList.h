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

		node()
			: next(nullptr)
		{}
	};

	//TODO: Check if this works after inlinement
	class iterator : std::iterator<std::forward_iterator_tag, const value_type>{

		friend class SList;
		typedef int& it_reference;
		typedef int* it_pointer;

	public:
		iterator();
		iterator(const iterator&);
		explicit iterator(node* const);
		~iterator();
		iterator& operator=(const iterator&);
		iterator& operator++();
		it_reference operator*() const;
		friend void swap(iterator& lhs, iterator& rhs);
		iterator operator++(int); //postfix increment
		it_pointer operator->() const;
		friend bool operator==(const iterator&, const iterator&);
		friend bool operator!=(const iterator&, const iterator&);

	protected:
		node* current_node;
	};

	typedef const iterator const_iterator;


	//CTOR
	SList();
	SList(size_type count, const int& value);
	explicit SList(size_type count);

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

	void resize(size_type count);
	void resize(size_type count, const value_type& value);

	void swap(SList& other);

	//OPERATIONS
	void merge(SList& other);
	void merge(SList&& other);

	void remove(const int& value);

	void reverse() noexcept;

	void unique();

	void sort();
// 	template< class Compare >
// 	void sort(Compare comp);

	

private:
	iterator head; //Front iterator of the SList
	static const iterator back; //End iterator of the SList
	size_type elements_count;
};


template<class InputIt>
SList::SList(InputIt first, InputIt last) : SList()
{
	for (; first != last; first++)
	{
		push_front(*first);
	}
}

template< class InputIt >
SList::iterator SList::insert_after(const_iterator pos, InputIt first, InputIt last)
{
	iterator it = head;
	size_type count = 0;

	while (it != pos)
	{
		it++;
	}

	iterator last_prepos = it;
	const iterator postpos = ++it;

	for (; first != last; first++, last_prepos++)
	{
		node* newNode = new node();
		newNode->value = *first;

		last_prepos.current_node->next = newNode;

		count++;
	}

	last_prepos.current_node->next = postpos.current_node;

	elements_count += count;

	return last_prepos;
}

