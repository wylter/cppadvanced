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

	push_front(*other.head);

	iterator it = head;
	iterator otherIt = other.head;

	otherIt++;

	for (size_t i = 1; i < other.elements_count; i++, it++, otherIt++)
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