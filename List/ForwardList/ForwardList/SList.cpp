#include "pch.h"
#include "SList.h"
#include <algorithm>

SList::SList() {
	
}

SList::iterator::iterator() : current_node(nullptr){
}

SList::iterator::iterator(const iterator& other) {
	current_node = other.current_node;
}

SList::iterator::~iterator(){

}

SList::iterator& SList::iterator::operator=(const iterator& other){
	current_node = other.current_node;
	return *this;
}

SList::iterator& SList::iterator::operator++(){
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