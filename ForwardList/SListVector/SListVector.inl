#include "pch.h"
#include "SListVector/SListVector.h"
#include <algorithm>
#include <limits>

namespace cppadvanced
{
	//back iterator is set to nullptr. As the "end()" method will return the iterator that represents the element after the last one, the last element will always point to nullptr.
	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::back = iterator(std::numeric_limits<size_t>::max(), nullptr, false);

	template < typename T >
	SListVector<T>::SListVector()
		: before_used_head(back, &storage, true)
		, before_free_head(back, &storage, true)
	{}

	template < typename T >
	SListVector<T>::SListVector(size_type count) : SListVector()
	{
		value_type default_value = {};
		for (size_t i = 0; i < count; i++)
		{
			push_front(default_value);
		}
	}

	template < typename T >
	SListVector<T>::SListVector(const SListVector<T>& other) 
		: storage(other.storage)
		, before_used_head(back, &storage, true)
		, before_free_head(back, &storage, true)
	{
		//Copying node indexes
		before_used_head.current_node = other.before_used_head.current_node;
		before_free_head.current_node = other.before_free_head.current_node;
	}

	template < typename T >
	SListVector<T>::SListVector(SListVector<T>&& other)
		: storage(std::move(other.storage))
		, before_used_head(back, &storage, true)
		, before_free_head(back, &storage, true)
	{

		before_used_head.current_node = other.before_used_head.current_node;
		before_free_head.current_node = other.before_free_head.current_node;
	}

	template < typename T >
	template<class InputIt>
	SListVector<T>::SListVector(InputIt first, InputIt last)
		: before_used_head(back, &storage, true)
		, before_free_head(back, &storage, true)
	{
		int i;
		for (i = 0; first != last; first++, i++)
		{
			storage.resize(storage.size() + 1);
			storage[i].value = *first;
			storage[i].next = i + 1;
		}
		storage[i - 1].next = back; //Connects the last node to back

		before_used_head.current_node = 0;
		before_free_head.current_node = back;
	}

	template < typename T >
	SListVector<T>::~SListVector()
	{}

	template < typename T >
	size_t cppadvanced::SListVector<T>::extractFreeHeadNode()
	{
		iterator newPosition = std::next(before_free_head);

		if (newPosition != back) // No space left, cant push another item
		{
			before_free_head.GetCurrentNode()->next = newPosition.GetCurrentNode()->next;  //Disconnect the node
		}
		else
		{
			const size_t newSize = storage.size() + 1;
			storage.resize(newSize);

			const size_t lastIndex = newSize - 1;
			storage[lastIndex].next = back;

			newPosition.current_node = lastIndex;
		}


		return newPosition;
	}

	template < typename T >
	void cppadvanced::SListVector<T>::pushFreeHead(iterator it)
	{
		const iterator free_head = std::next(before_free_head);

		before_free_head.GetCurrentNode()->next = it;
		it.GetCurrentNode()->next = free_head;
	}


	template < typename T >
	void cppadvanced::SListVector<T>::pushFreeHead(iterator first, iterator last)
	{
		if (first == last)
		{
			return;
		}

		iterator it = first;
		while (std::next(it) != last)
		{
			it++;
		}

		const iterator firstItToErase = first;
		const iterator lastItToErase = it;

		const iterator free_head = std::next(before_free_head);

		before_free_head.GetCurrentNode()->next = firstItToErase;
		lastItToErase.GetCurrentNode()->next = free_head;
	}

	
	template < typename T >
	typename SListVector<T>& SListVector<T>::operator=(const SListVector<T>& other)
	{
		storage = other.storage;

		//Copying node indexes
		before_used_head.current_node = other.before_used_head.current_node;
		before_free_head.current_node = other.before_free_head.current_node;

		return *this;
	}

	template < typename T >
	typename SListVector<T>& SListVector<T>::operator=(SListVector<T>&& other)
	{
		storage = std::move(other.storage);

		//Copying node indexes
		before_used_head.current_node = other.before_used_head.current_node;
		before_free_head.current_node = other.before_free_head.current_node;

		return *this;
	}

	template < typename T >
	typename SListVector<T>::reference SListVector<T>::front()
	{
		return *std::next(before_used_head);
	}

	template < typename T >
	typename SListVector<T>::const_reference SListVector<T>::front() const
	{
		return *std::next(before_used_head);
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::before_begin() noexcept
	{
		return before_used_head;
	}

	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::before_begin() const noexcept
	{
		return before_used_head;
	}

	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::cbefore_begin() const noexcept
	{
		return before_used_head;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::begin() noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::begin() const noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::cbegin() const noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::end() noexcept
	{
		return back;
	}

	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::end() const noexcept
	{
		return back;
	}

	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::cend() const noexcept
	{
		return back;
	}

	

	template < typename T >
	bool SListVector<T>::empty() const noexcept
	{
		return std::next(before_used_head) == back;
	}

	template < typename T >
	typename SListVector<T>::size_type SListVector<T>::max_size() const noexcept
	{
		return storage.max_size();
	}

	template < typename T >
	void SListVector<T>::clear() noexcept
	{
		storage.clear();

		before_used_head.current_node = back;
		before_free_head.current_node = back;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, const T& value)
	{
		node* newNode = extractFreeHeadNode();

		if (!newNode)
		{
			return back;
		}

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newNode->value = value;

		prepos.current_node->next = newNode;
		newNode->next = postpos.current_node;

		return iterator(newNode);
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, T&& value)
	{
		const size_t newIndex = extractFreeHeadNode();
		node* const newNode = &storage[newIndex];

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newNode->value = std::move(value);

		prepos.GetCurrentNode()->next = newIndex;
		newNode->next = postpos;

		const iterator newPosition(newIndex, &storage);
		return newPosition;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, size_type count, const T& value)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (size_t i = 0; i < count; i++, last_prepos++)
		{
			const size_t newIndex = extractFreeHeadNode();
			node* const newNode = &storage[newIndex];

			newNode->value = value;

			last_prepos.GetCurrentNode()->next = newIndex;
		}

		last_prepos.GetCurrentNode()->next = postpos;

		return last_prepos;
	}

	template < typename T >
	template< class InputIt >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, InputIt first, InputIt last)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (; first != last; first++, last_prepos++)
		{
			const size_t newIndex = extractFreeHeadNode();
			node* const newNode = &storage[newIndex];
			if (!newNode) //Tries to insert as much as it can. if there's no space left, it just inserts the max amout
			{
				break;
			}
			newNode->value = *first;

			last_prepos.GetCurrentNode()->next = newIndex;
		}

		last_prepos.GetCurrentNode()->next = postpos;


		return last_prepos;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::erase_after(const_iterator pos)
	{
		const iterator erasepos = std::next(pos);

		const iterator postpos = std::next(erasepos);

		pushFreeHead(erasepos);

		pos.GetCurrentNode()->next = postpos;

		return postpos;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::erase_after(const_iterator first, const_iterator last)
	{
		pushFreeHead(std::next(first), last);

		first.GetCurrentNode()->next = last;

		return last;
	}

	template < typename T >
	void SListVector<T>::push_front(const T& value)
	{
		const size_t newIndex = extractFreeHeadNode();
		node* const newNode = &storage[newIndex];

		if (!newNode)
		{
			return;
		}

		newNode->value = value;
		newNode->next = before_used_head.GetCurrentNode()->next;

		before_used_head.GetCurrentNode()->next = newIndex;
	}

	template < typename T >
	void SListVector<T>::push_front(T&& value)
	{
		const size_t newIndex = extractFreeHeadNode();
		node* const newNode = &storage[newIndex];

		if (!newNode)
		{
			return;
		}

		newNode->value = std::move(value);
		newNode->next = before_used_head.GetCurrentNode()->next;

		before_used_head.GetCurrentNode()->next = newIndex;
	}

	
	template < typename T >
	void SListVector<T>::pop_front()
	{
		const iterator toEraseIterator = std::next(before_used_head);

		before_used_head.GetCurrentNode()->next = toEraseIterator.GetCurrentNode()->next;

		pushFreeHead(toEraseIterator);
	}

	template < typename T >
	void SListVector<T>::resize(size_type count, const value_type& value)
	{
		size_t elements_count = 0;
		iterator it = before_used_head;

		while (std::next(it) != back && elements_count < count)
		{
			it++;
			elements_count++;
		}

		if (elements_count < count)
		{
			const size_t count_difference = count - elements_count;

			for (size_t i = 0; i < count_difference; i++, it++)
			{
				const size_t newIndex = extractFreeHeadNode();
				node* const newNode = &storage[newIndex];
				newNode->value = value;

				it.GetCurrentNode()->next = newIndex;
			}
		}
		else
		{
			iterator tail = it;

			pushFreeHead(std::next(tail), back);

			tail.GetCurrentNode()->next = back;
		}
	}

	template < typename T >
	void SListVector<T>::swap(SListVector<T>& other)
	{
		storage.swap(other.storage);

		std::swap(before_used_head.current_node, other.before_used_head.current_node);
		std::swap(before_free_head.current_node, other.before_free_head.current_node);
	}

	template < typename T >
	void SListVector<T>::remove(const T& value)
	{
		iterator it = std::next(before_used_head);
		iterator prevIt = before_used_head;

		while (it != back)
		{
			if (*it == value)
			{
				const iterator current_node = it;
				it++;
				pushFreeHead(current_node);

				prevIt.GetCurrentNode()->next = it;
			}
			else
			{
				it++;
				prevIt++;
			}
		}
	}

	template < typename T >
	void SListVector<T>::reverse() noexcept
	{
		const iterator head = std::next(before_used_head);

		if (head == back)
		{
			return;
		}

		iterator it = std::next(head);

		head.GetCurrentNode()->next = back;

		iterator last_head = head;

		while (it != back)
		{
			const iterator current_iterator = it;
			it++;

			current_iterator.GetCurrentNode()->next = last_head;
			last_head = current_iterator;
		}

		before_used_head.GetCurrentNode()->next = last_head;
	}

	template < typename T >
	void SListVector<T>::unique()
	{
		iterator it = std::next(before_used_head);

		while (it != back)
		{
			const iterator next = std::next(it);
			if (next != back && *it == *next)
			{
				it.GetCurrentNode()->next = next.GetCurrentNode()->next;

				pushFreeHead(next);
			}
			else
			{
				it++;
			}
		}
	}

	
	template < typename T >
	void SListVector<T>::split(iterator head, iterator& splittedHead1, iterator& splittedHead2)
	{
		iterator slow = head;
		iterator fast = std::next(head);

		while (fast != back)
		{
			fast++;
			if (fast != back)
			{
				fast++;
				slow++;
			}
		}

		splittedHead1 = head;
		splittedHead2 = std::next(slow);

		slow.GetCurrentNode()->next = back; // splitting the two lists
	}

	
	template < typename T >
	void SListVector<T>::sort()
	{
		sort(std::less<int>());
	}

	template < typename T >
	template< class Compare >
	void SListVector<T>::sort(Compare comp)
	{
		iterator head = std::next(before_used_head);

		mergeSort(head, comp);

		before_used_head.GetCurrentNode()->next = head;
	}

	
	template < typename T >
	template< class Compare >
	typename SListVector<T>::iterator SListVector<T>::mergeList(iterator head1, iterator head2, Compare comp)
	{
		iterator before_head_result(back, &storage);

		iterator it = before_head_result;

		while (head1 != back && head2 != back)
		{
			if (comp(*head1, *head2))
			{
				it.GetCurrentNode()->next = head1;
				it++;
				head1++;
			}
			else
			{
				it.GetCurrentNode()->next = head2;
				it++;
				head2++;
			}
		}

		if (head1 != back)
		{
			it.GetCurrentNode()->next = head1;
		}
		else //head2 != back
		{
			it.GetCurrentNode()->next = head2;
		}


		return std::next(before_head_result);
	}

	template < typename T >
	template< class Compare >
	void SListVector<T>::mergeSort(iterator& head_reference, Compare comp)
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
}