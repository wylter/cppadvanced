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

SList::iterator::iterator(node_base* const otherNode)
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

SList::iterator::it_reference SList::iterator::operator*() const
{
	node* const current_typed_node = static_cast<node*>(current_node);
	return current_typed_node->value;
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

SList::iterator::it_pointer SList::iterator::operator->() const
{
	node* const current_typed_node = static_cast<node*>(current_node);
	return &current_typed_node->value;
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
	: before_head()
{
	before_head.current_node = new node_base();
}

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
	iterator it = before_head;
	iterator otherIt = std::next(other.before_head);

	for (; otherIt != other.back; it++, otherIt++)
	{
		node* newNode = new node();
		newNode->value = *otherIt;

		it.current_node->next = newNode;
	}
}

SList::SList(SList&& other)
{
	before_head = other.before_head;

	other.before_head.current_node->next = nullptr;
}

SList::~SList()
{
	iterator it = std::next(before_head);
	while(it != back)
	{
		const iterator current_node = it;
		it++;
		delete current_node.current_node;
	}

	delete before_head.current_node;
}

SList& SList::operator=(const SList& other)
{
	iterator it = std::next(before_head);
	iterator otherIt = std::next(other.before_head);

	iterator preIt;

	while (it != back && otherIt != other.back)
	{
		*it = *otherIt;

		preIt = it;

		it++;
		otherIt++;
	}

	if (it == back) //if this has less elements than other
	{
		it = preIt;

		for (; otherIt != other.back; it++, otherIt++)
		{
			node* newNode = new node();
			newNode->value = *otherIt;

			it.current_node->next = newNode;
		}
	}
	else //if other has less elements than this
	{
		while (it != back)
		{
			const iterator current_pos = it;
			it++;
			delete current_pos.current_node;
		}
	}

	return *this;
}

SList& SList::operator=(SList&& other)
{
	std::swap(before_head, other.before_head);

	return *this;
}

SList::reference SList::front()
{
	return *std::next(before_head);
}

SList::const_reference SList::front() const
{
	return *std::next(before_head);
}

SList::iterator SList::before_begin() noexcept
{
	return before_head;
}

SList::const_iterator SList::before_begin() const noexcept
{
	return before_head;
}

SList::const_iterator SList::cbefore_begin() const noexcept
{
	return before_head;
}

SList::iterator SList::begin() noexcept
{
	return std::next(before_head);
}

SList::const_iterator SList::begin() const noexcept
{
	return std::next(before_head);
}

SList::const_iterator SList::cbegin() const noexcept
{
	return std::next(before_head);
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
	return std::next(before_head) == back;
}

SList::size_type SList::max_size() const noexcept
{
	return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

void SList::clear() noexcept
{
	iterator it = std::next(before_head);
	while (it != back)
	{
		const iterator current_node = it;
		it++;
		delete current_node.current_node;
	}

	before_head.current_node->next = nullptr;
}

SList::iterator SList::insert_after(const_iterator pos, const int& value)
{
	const iterator prepos = pos;
	const iterator postpos = std::next(pos);

	node* newNode = new node();
	newNode->value = value;

	prepos.current_node->next = newNode;
	newNode->next = postpos.current_node;

	const iterator posResult(newNode);
	return posResult;
}

SList::iterator SList::insert_after(const_iterator pos, int&& value)
{
	const iterator prepos = pos;
	const iterator postpos = std::next(pos);

	node* newNode = new node();
	newNode->value = std::move(value);

	prepos.current_node->next = newNode;
	newNode->next = postpos.current_node;

	const iterator posResult(newNode);
	return posResult;
}

SList::iterator SList::insert_after(const_iterator pos, size_type count, const int& value)
{
	iterator last_prepos = pos;
	const iterator postpos = std::next(pos);

	for (int i = 0; i < count; i++, last_prepos++)
	{
		node* newNode = new node();
		newNode->value = value;

		last_prepos.current_node->next = newNode;
	}

	last_prepos.current_node->next = postpos.current_node;

	return last_prepos;
}

SList::iterator SList::erase_after(const_iterator pos)
{
	const iterator erasepos = std::next(pos);

	const iterator postpos = std::next(erasepos);

	delete erasepos.current_node;

	pos.current_node->next = postpos.current_node;

	return postpos;
}

SList::iterator SList::erase_after(const_iterator first, const_iterator last)
{
	iterator it = std::next(first);

	for (; it != last; it++)
	{
		const iterator current_node = it;
		it++;
		delete current_node.current_node;
	}

	first.current_node->next = last.current_node;

	return last;
}

void SList::push_front(const int& value)
{
	const iterator head = std::next(before_head);

	node* newHead = new node();
	newHead->value = value;
	newHead->next = head.current_node;

	before_head.current_node->next = newHead;
}

void SList::push_front(int&& value)
{
	const iterator head = std::next(before_head);

	node* newHead = new node();
	newHead->value = std::move(value);
	newHead->next = head.current_node;

	before_head.current_node->next = newHead;
}

void SList::pop_front()
{
	const iterator toEraseIterator = std::next(before_head);

	before_head.current_node->next = toEraseIterator.current_node->next;

	delete toEraseIterator.current_node;
}

void SList::resize(size_type count)
{
	iterator it = before_head;
	iterator precedentIt;

	while (it != back)
	{
		precedentIt = it;
		it++;
	}
}
