#include "pch.h"
#include "SList.h"
#include <algorithm>

SList::iterator::iterator() : current_node(nullptr)
{
}

SList::iterator::iterator(const iterator& other)
{
	current_node = other.current_node;
}

SList::iterator::iterator(node* const otherNode)
{
	current_node = otherNode;
}

SList::iterator::~iterator()
{

}

SList::iterator& SList::iterator::operator=(const iterator& other)
{
	current_node = other.current_node;
	return *this;
}

SList::iterator& SList::iterator::operator++()
{
	current_node = current_node->next;
	return *this;
}

SList::reference SList::iterator::operator*() const
{
	return current_node->value;
}

void swap(SList::iterator& lhs, SList::iterator& rhs)
{
	std::swap(lhs, rhs);
}

SList::iterator SList::iterator::operator++(int a)
{
	iterator result(*this);
	++(*this);
	return result;
}

SList::pointer SList::iterator::operator->() const
{
	return &current_node->value;
}

bool operator==(const SList::iterator& lhs, const SList::iterator& rhs)
{
	return lhs.current_node == rhs.current_node;
}

bool operator!=(const SList::iterator& lhs, const SList::iterator& rhs)
{
	return !(lhs == rhs);
}

//back iterator is set to nullptr. As the "end()" method will return the iterator that represents the element after the last one, the last element will always point to nullptr.
const SList::iterator SList::back = SList::iterator(nullptr); 

SList::SList()
	: head()
	, elements_count(0)
{}

SList::SList(size_type count, const int& value) : SList()
{
	for (size_t i = 0; i < count; i++)
	{
		push_front(value);
	}
}


SList::SList(size_type count) : SList()
{
	const int default_object = {};

	for (size_t i = 0; i < count; i++)
	{
		push_front(default_object);
	}
}



SList::SList(const SList& other) : SList()
{
	if (other.elements_count == 0)
	{
		return;
	}

	node* newHead = new node();
	newHead->value = *other.head;
	head.current_node = newHead;

	iterator it = head;
	iterator otherIt = other.head;

	otherIt++;
	for (; otherIt != other.back; it++, otherIt++)
	{
		node* newNode = new node();
		newNode->value = *otherIt;

		it.current_node->next = newNode;
	}

	elements_count = other.elements_count;
}

SList::SList(SList&& other)
{
	head = other.head;
	elements_count = other.elements_count;

	other.head.current_node = nullptr;
	other.elements_count = 0;
}

SList::~SList()
{
	while(head != back)
	{
		const iterator it = head;
		head++;
		delete it.current_node;
	}
}

SList& SList::operator=(const SList& other)
{
	const size_type min_elements_count = elements_count < other.elements_count ? elements_count : other.elements_count;

	iterator it = head;
	iterator otherIt = other.head;

	for (size_t i = 0; i < min_elements_count - 1; i++, it++, otherIt++)
	{
		*it = *otherIt;
	}

	*it = *otherIt;

	if (elements_count < other.elements_count)
	{
		otherIt++;
		for (; otherIt != other.back; it++, otherIt++)
		{
			node* newNode = new node();
			newNode->value = *otherIt;

			it.current_node->next = newNode;
		}
	}
	else if (elements_count > other.elements_count)
	{
		it++;
		while (it != back)
		{
			const iterator current_pos = it;
			it++;
			delete current_pos.current_node;
		}
	}

	elements_count = other.elements_count;

	return *this;
}

SList& SList::operator=(SList&& other)
{
	//TODO: maybe changed this with the swap method once it has been implemented
	std::swap(head, other.head);
	std::swap(elements_count, other.elements_count);

	return *this;
}

SList::reference SList::front()
{
	return *head;
}

SList::const_reference SList::front() const
{
	return *head;
}

SList::iterator SList::begin() noexcept
{
	return head;
}

SList::const_iterator SList::begin() const noexcept
{
	return head;
}

SList::const_iterator SList::cbegin() const noexcept
{
	return head;
}

SList::iterator SList::end() noexcept
{
	return back;
}

SList::const_iterator SList::end() const noexcept
{
	return back;
}

SList::const_iterator SList::cend() const noexcept
{
	return back;
}

bool SList::empty() const noexcept
{
	return head == back;
}

SList::size_type SList::max_size() const noexcept
{
	return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

void SList::clear() noexcept
{
	while (head != back)
	{
		const iterator it = head;
		head++;
		delete it.current_node;
	}

	elements_count = 0;
}

SList::iterator SList::insert_after(const_iterator pos, const int& value)
{
	iterator it = head;

	while (it != pos)
	{
		it++;
	}

	if (it == back)
	{
		return back;
	}

	const iterator prepos = it;
	const iterator postpos = ++it;

	node* newNode = new node();
	newNode->value = value;

	prepos.current_node->next = newNode;
	newNode->next = postpos.current_node;

	elements_count++;

	const iterator posResult(newNode);
	return posResult;
}

SList::iterator SList::insert_after(const_iterator pos, int&& value)
{
	iterator it = head;

	while (it != pos)
	{
		it++;
	}

	if (it == back)
	{
		return back;
	}

	const iterator prepos = it;
	const iterator postpos = ++it;

	node* newNode = new node();
	newNode->value = std::move(value);

	prepos.current_node->next = newNode;
	newNode->next = postpos.current_node;

	elements_count++;

	const iterator posResult(newNode);
	return posResult;
}

SList::iterator SList::insert_after(const_iterator pos, size_type count, const int& value)
{
	iterator it = head;

	while (it != pos)
	{
		it++;
	}

	if (it == back)
	{
		return back;
	}

	iterator last_prepos = it;
	const iterator postpos = ++it;

	for (int i = 0; i < count; i++, last_prepos++)
	{
		node* newNode = new node();
		newNode->value = value;

		last_prepos.current_node->next = newNode;
	}

	last_prepos.current_node->next = postpos.current_node;

	elements_count += count;

	return last_prepos;
}

SList::iterator SList::erase_after(const_iterator pos)
{
	const iterator erasepos = std::next(pos, 1);

	if (erasepos == back)
	{
		return back;
	}

	const iterator postpos = std::next(erasepos, 1);

	delete erasepos.current_node;

	pos.current_node->next = postpos.current_node;

	elements_count--;

	return postpos;
}

SList::iterator SList::erase_after(const_iterator first, const_iterator last)
{
	iterator it = head;
	iterator prepos;

	while (it != first)
	{
		prepos = it;
		it++;
	}

	if (it == back)
	{
		return back;
	}

	while (head != back)
	{
		const iterator it = head;
		head++;
		delete it.current_node;
	}

	const iterator postpos = ++it;

	delete it.current_node;

	prepos.current_node->next = postpos.current_node;

	elements_count--;

	return postpos;
}

void SList::push_front(const int& value)
{
	node* newHead = new node();
	newHead->value = value;
	newHead->next = head.current_node;

	head.current_node = newHead;

	elements_count++;
}

void SList::push_front(int&& value)
{
	node* newHead = new node();
	newHead->value = std::move(value);
	newHead->next = head.current_node;

	head.current_node = newHead;

	elements_count++;
}