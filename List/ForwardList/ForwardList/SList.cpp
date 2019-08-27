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
	, count(0)
{

}

void SList::push_front(const int& value)
{
	node* newHead = new node();
	newHead->value = value;
	newHead->next = head.current_node;

	head.current_node = newHead;

	count++;
}

void SList::push_front(int&& value)
{
	node* newHead = new node();
	newHead->value = std::move(value);
	newHead->next = head.current_node;

	head.current_node = newHead;

	count++;
}