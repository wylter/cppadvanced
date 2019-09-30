#include "pch.h"
#include "SListVector/SListVector.h"
#include <algorithm>
#include <limits>

namespace cppadvanced
{
	//back iterator is set to nullptr. As the "end()" method will return the iterator that represents the element after the last one, the last element will always point to nullptr.
	template < typename T >
	const typename SListVector<T>::iterator SListVector<T>::back = iterator(std::numeric_limits<size_t>::max(), nullptr);

	template < typename T >
	SListVector<T>::SListVector()
		: storage(2)
		, before_used_head(0, &storage)
		, before_free_head(1, &storage)
	{
		before_used_head.GetCurrentNodeAddress()->next = back;
		before_free_head.GetCurrentNodeAddress()->next = back;
	}

	template < typename T >
	SListVector<T>::SListVector(size_type count) : SListVector()
	{
		for (size_t i = 0; i < count; i++)
		{
			push_front(value_type());
		}
	}

	template < typename T >
	SListVector<T>::SListVector(const SListVector<T>& other) 
		: storage(other.storage)
		, before_used_head(other.before_used_head.current_node_index, &storage)
		, before_free_head(other.before_free_head.current_node_index, &storage)
	{}

	template < typename T >
	SListVector<T>::SListVector(SListVector<T>&& other)
		: storage(std::move(other.storage))
		, before_used_head(other.before_used_head.current_node_index, &storage)
		, before_free_head(other.before_free_head.current_node_index, &storage)
	{}

	template < typename T >
	template<class InputIt>
	SListVector<T>::SListVector(InputIt first, InputIt last) : SListVector()
	{
		int i;
		for (i = MINSIZE; first != last; first++, i++)
		{
			storage.resize(storage.size() + 1);
			storage[i].value = *first;
			storage[i].next = i + 1;
		}

		if (i != 0)// If at least 1 element was inserted
		{
			before_used_head.GetCurrentNodeAddress()->next = MINSIZE;
			before_free_head.GetCurrentNodeAddress()->next = back;
			storage[i - 1].next = back; //Connects the last node to back
		}
		else
		{
			before_used_head.GetCurrentNodeAddress()->next = back;
			before_free_head.GetCurrentNodeAddress()->next = back;
		}
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
			before_free_head.GetCurrentNodeAddress()->next = newPosition.GetCurrentNodeAddress()->next;  //Disconnect the node
		}
		else
		{
			const size_t newSize = storage.size() + 1;
			storage.resize(newSize);

			const size_t lastIndex = newSize - 1;
			storage[lastIndex].next = back;

			newPosition.current_node_index = lastIndex;
		}


		return newPosition.current_node_index;
	}

	template < typename T >
	void cppadvanced::SListVector<T>::pushFreeHead(iterator it)
	{
		const iterator free_head = std::next(before_free_head);

		before_free_head.GetCurrentNodeAddress()->next = it;
		it.GetCurrentNodeAddress()->next = free_head;
	}


	template < typename T >
	void cppadvanced::SListVector<T>::pushFreeHead(iterator first, iterator last)
	{
		while(first != last)
		{
			const iterator current_it = first;
			first++;

			pushFreeHead(current_it);
		}
	}

	
	template < typename T >
	typename SListVector<T>& SListVector<T>::operator=(const SListVector<T>& other)
	{
		storage = other.storage;

		return *this;
	}

	template < typename T >
	typename SListVector<T>& SListVector<T>::operator=(SListVector<T>&& other)
	{
		storage = std::move(other.storage);

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
		return storage.max_size() - MINSIZE;
	}

	template < typename T >
	void SListVector<T>::clear() noexcept
	{
		storage.resize(MINSIZE);

		before_used_head.GetCurrentNodeAddress()->next = back;
		before_free_head.GetCurrentNodeAddress()->next = back;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, const T& value)
	{
		const size_t newIndex = extractFreeHeadNode();
		node* const newNode = &storage[newIndex];

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newNode->value = value;

		prepos.GetCurrentNodeAddress()->next = newIndex;
		newNode->next = postpos;

		const iterator newPosition(newIndex, &storage);
		return newPosition;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, T&& value)
	{
		const size_t newIndex = extractFreeHeadNode();
		node* const newNode = &storage[newIndex];

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newNode->value = std::move(value);

		prepos.GetCurrentNodeAddress()->next = newIndex;
		newNode->next = postpos;

		const iterator newPosition(newIndex, &storage);
		return newPosition;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, size_type count, const T& value)
	{
		iterator last_prepos = pos;

		for (size_t i = 0; i < count; i++, last_prepos++)
		{
			insert_after(last_prepos, value);
		}

		return last_prepos;
	}

	template < typename T >
	template< class InputIt >
	typename SListVector<T>::iterator SListVector<T>::insert_after(const_iterator pos, InputIt first, InputIt last)
	{
		iterator last_prepos = pos;

		for (; first != last; first++, last_prepos++)
		{
			insert_after(last_prepos, *first);
		}

		return last_prepos;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::erase_after(const_iterator pos)
	{
		const iterator erasepos = std::next(pos);

		const iterator postpos = std::next(erasepos);

		pushFreeHead(erasepos);

		pos.GetCurrentNodeAddress()->next = postpos;

		return postpos;
	}

	template < typename T >
	typename SListVector<T>::iterator SListVector<T>::erase_after(const_iterator first, const_iterator last)
	{
		pushFreeHead(std::next(first), last);

		first.GetCurrentNodeAddress()->next = last;

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
		newNode->next = before_used_head.GetCurrentNodeAddress()->next;

		before_used_head.GetCurrentNodeAddress()->next = newIndex;
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
		newNode->next = before_used_head.GetCurrentNodeAddress()->next;

		before_used_head.GetCurrentNodeAddress()->next = newIndex;
	}

	
	template < typename T >
	void SListVector<T>::pop_front()
	{
		const iterator toEraseIterator = std::next(before_used_head);

		before_used_head.GetCurrentNodeAddress()->next = toEraseIterator.GetCurrentNodeAddress()->next;

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

				it.GetCurrentNodeAddress()->next = newIndex;
			}
		}
		else
		{
			iterator tail = it;

			pushFreeHead(std::next(tail), back);

			tail.GetCurrentNodeAddress()->next = back;
		}
	}

	template < typename T >
	void SListVector<T>::swap(SListVector<T>& other)
	{
		storage.swap(other.storage);
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

				prevIt.GetCurrentNodeAddress()->next = it;
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

		head.GetCurrentNodeAddress()->next = back;

		iterator last_head = head;

		while (it != back)
		{
			const iterator current_iterator = it;
			it++;

			current_iterator.GetCurrentNodeAddress()->next = last_head;
			last_head = current_iterator;
		}

		before_used_head.GetCurrentNodeAddress()->next = last_head;
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
				it.GetCurrentNodeAddress()->next = next.GetCurrentNodeAddress()->next;

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

		slow.GetCurrentNodeAddress()->next = back; // splitting the two lists
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

		before_used_head.GetCurrentNodeAddress()->next = head;
	}

	
	template < typename T >
	template< class Compare >
	typename SListVector<T>::iterator SListVector<T>::mergeList(iterator head1, iterator head2, Compare comp)
	{
		const bool head1OverHead2 = comp(*head1, *head2);
		iterator head_result = head1OverHead2 ? head1 : head2;
		
		if (head1OverHead2)
		{
			head1++;
		}
		else
		{
			head2++;
		}

		iterator it = head_result;

		while (head1 != back && head2 != back)
		{
			if (comp(*head1, *head2))
			{
				it.GetCurrentNodeAddress()->next = head1;
				it++;
				head1++;
			}
			else
			{
				it.GetCurrentNodeAddress()->next = head2;
				it++;
				head2++;
			}
		}

		if (head1 != back)
		{
			it.GetCurrentNodeAddress()->next = head1;
		}
		else //head2 != back
		{
			it.GetCurrentNodeAddress()->next = head2;
		}


		return head_result;
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