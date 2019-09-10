#include "pch.h"
#include "SListArray/SListArray.h"
#include <algorithm>

namespace cppadvanced
{

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray()
		: before_used_node(MAX) //Points to end
		, before_free_node(0) //Points to begin
		, back(storage + MAX)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i].next = i + 1;
		}
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray(size_type count) : SListArray()
	{
		count = count <= MAX ? count : MAX;

		value_type default_value = {};
		for (size_t i = 0; i < count; i++)
		{
			push_front(default_value);
		}
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray(const SListArray<T, MAX>& other) 
		: back(storage + MAX)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		std::memcpy(storage, other.storage, sizeof(storage));

		//Copying node indexes
		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray(SListArray<T, MAX>&& other)
		: back(storage + MAX)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i] = std::move(other.storage[i]);
		}

		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;
	}

	template < typename T, size_t MAX >
	template<class InputIt>
	SListArray<T, MAX>::SListArray(InputIt first, InputIt last)
		: back(storage + MAX)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		int i;
		for (i = 0; first != last && i < MAX; first++, i++)
		{
			storage[i].value = *first;
			storage[i].next = i + 1;
		}

		storage[i - 1].next = MAX; //Connects the last node to back
		before_used_node.next = 0;
		before_free_node.next = i;
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::~SListArray()
	{}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator cppadvanced::SListArray<T, MAX>::extractFreeHead()
	{
		iterator newPosition = std::next(before_free_head);

		if (newPosition == back) // No space left, cant push another item
		{
			return back;
		}

		before_free_head.current_node->next = newPosition.current_node->next;  //Disconnect the node

		return newPosition;
	}

	
	template < typename T, size_t MAX >
	typename SListArray<T, MAX>& SListArray<T, MAX>::operator=(const SListArray<T, MAX>& other)
	{
		std::memcpy(storage, other.storage, sizeof(storage));

		//Copying node indexes
		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;

		return *this;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>& SListArray<T, MAX>::operator=(SListArray<T, MAX>&& other)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i] = std::move(other.storage[i]);
		}

		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;

		return *this;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::reference SListArray<T, MAX>::front()
	{
		return *std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::const_reference SListArray<T, MAX>::front() const
	{
		return *std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::before_begin() noexcept
	{
		return before_used_head;
	}

	template < typename T, size_t MAX >
	const typename SListArray<T, MAX>::iterator SListArray<T, MAX>::before_begin() const noexcept
	{
		return before_used_head;
	}

	template < typename T, size_t MAX >
	const typename SListArray<T, MAX>::iterator SListArray<T, MAX>::cbefore_begin() const noexcept
	{
		return before_used_head;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::begin() noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	const typename SListArray<T, MAX>::iterator SListArray<T, MAX>::begin() const noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	const typename SListArray<T, MAX>::iterator SListArray<T, MAX>::cbegin() const noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::end() noexcept
	{
		return back;
	}

	template < typename T, size_t MAX >
	const typename SListArray<T, MAX>::iterator SListArray<T, MAX>::end() const noexcept
	{
		return back;
	}

	template < typename T, size_t MAX >
	const typename SListArray<T, MAX>::iterator SListArray<T, MAX>::cend() const noexcept
	{
		return back;
	}

	

	template < typename T, size_t MAX >
	bool SListArray<T, MAX>::empty() const noexcept
	{
		return std::next(before_used_head) == back;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::size_type SListArray<T, MAX>::max_size() const noexcept
	{
		return MAX;
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::clear() noexcept
	{
		iterator it = before_free_head;

		while (std::next(it) != back)
		{
			it++;
		}

		iterator used_head = std::next(before_used_head);

		it.current_node.next = used_head.current_node; //Concatenate the used list to the free list

		before_used_head.current_node.next = MAX;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, const T& value)
	{
		iterator newPosition = extractFreeHead();

		if (newPosition == back)
		{
			return back;
		}

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newPosition.current_node.value = value;

		prepos.current_node->next = newPosition.current_node;
		newPosition.current_node->next = postpos.current_node;

		return newPosition;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, T&& value)
	{
		iterator newPosition = extractFreeHead();

		if (newPosition == back)
		{
			return back;
		}

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newPosition.current_node.value = std::move(value);


		prepos.current_node->next = newPosition.current_node;
		newPosition.current_node->next = postpos.current_node;

		return newPosition;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, size_type count, const T& value)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (int i = 0; i < count; i++, last_prepos++)
		{
			iterator newPosition = extractFreeHead();
			if (newPosition == back) //Tries to insert as much as it can. if there's no space left, it just inserts the max amout
			{
				break;
			}
			newPosition.current_node.value = value;

			last_prepos.current_node->next = newPosition.current_node;
		}

		last_prepos.current_node->next = postpos.current_node;

		return last_prepos;
	}

	template < typename T, size_t MAX >
	template< class InputIt >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, InputIt first, InputIt last)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (; first != last; first++, last_prepos++)
		{
			iterator newPosition = extractFreeHead();
			if (newPosition == back) //Tries to insert as much as it can. if there's no space left, it just inserts the max amout
			{
				break;
			}
			newPosition.current_node.value = value;

			last_prepos.current_node->next = newPosition.current_node;
		}

		last_prepos.current_node->next = postpos.current_node;


		return last_prepos;
	}

	/*
	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::erase_after(const_iterator pos)
	{
		const iterator erasepos = std::next(pos);

		const iterator postpos = std::next(erasepos);

		delete erasepos.current_node;

		pos.current_node->next = postpos.current_node;

		return postpos;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::erase_after(const_iterator first, const_iterator last)
	{
		iterator it = std::next(first);

		while (it != last)
		{
			const iterator current_node = it;
			it++;
			delete current_node.current_node;
		}

		first.current_node->next = last.current_node;

		return last;
	}
	*/

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::push_front(const T& value)
	{
		iterator newPosition = extractFreeHead();

		if (newPosition == back)
		{
			return;
		}

		newPosition.current_node->value = value;
		newPosition.current_node->next = before_used_head.current_node->next;

		before_used_head.current_node->next = newPosition.current_node;
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::push_front(T&& value)
	{
		iterator newPosition = extractFreeHead();

		if (newPosition == back)
		{
			return;
		}

		newPosition.current_node->value = std::move(value);
		newPosition.current_node->next = before_used_head.current_node->next;

		before_used_head.current_node->next = newPosition.current_node;
	}

	/*
	template < typename T, size_t MAX >
	void SListArray<T, MAX>::pop_front()
	{
		const iterator toEraseIterator = std::next(before_head);

		before_head.current_node->next = toEraseIterator.current_node->next;

		delete toEraseIterator.current_node;
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::resize(size_type count, const value_type& value)
	{
		int elements_count = 0;
		iterator it = before_head;

		while (std::next(it) != back && elements_count < count)
		{
			it++;
			elements_count++;
		}

		if (elements_count < count)
		{
			const int count_difference = count - elements_count;

			for (int i = 0; i < count_difference; i++, it++)
			{
				node* newNode = new node();
				newNode->value = value;

				it.current_node->next = newNode;
			}
		}
		else
		{
			iterator tail = it;
			it++;

			while (it != back)
			{
				const iterator current_node = it;
				it++;
				delete current_node.current_node;
			}

			tail.current_node->next = nullptr;
		}
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::swap(SListArray& other)
	{
		std::swap(before_head, other.before_head);
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::remove(const T& value)
	{
		iterator it = std::next(before_head);
		iterator prevIt = before_head;

		while (it != back)
		{
			if (*it == value)
			{
				const iterator current_node = it;
				it++;
				delete current_node.current_node;

				prevIt.current_node->next = it.current_node;
			}
			else
			{
				it++;
				prevIt++;
			}
		}
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::reverse() noexcept
	{
		const iterator head = std::next(before_head);

		if (head == back)
		{
			return;
		}

		iterator it = std::next(head);

		head.current_node->next = nullptr;

		iterator last_head = head;

		while (it != back)
		{
			const iterator current_iterator = it;
			it++;

			current_iterator.current_node->next = last_head.current_node;
			last_head = current_iterator;
		}

		before_head.current_node->next = last_head.current_node;
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::unique()
	{
		iterator it = std::next(before_head);

		while (it != back)
		{
			const iterator next = std::next(it);
			if (next != back && *it == *next)
			{
				it.current_node->next = next.current_node->next;

				delete next.current_node;
			}
			else
			{
				it++;
			}
		}
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::split(iterator head, iterator& splittedHead1, iterator& splittedHead2)
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

		slow.current_node->next = nullptr; // splitting the two lists
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::sort()
	{
		sort(std::less<int>());
	}

	template < typename T, size_t MAX >
	template< class Compare >
	void SListArray<T, MAX>::sort(Compare comp)
	{
		iterator head = std::next(before_head);

		mergeSort(head, comp);

		before_head.current_node->next = head.current_node;
	}

	template < typename T, size_t MAX >
	template< class Compare >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::mergeList(iterator head1, iterator head2, Compare comp)
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


	template < typename T, size_t MAX >
	template< class Compare >
	void SListArray<T, MAX>::mergeSort(iterator& head_reference, Compare comp)
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
	*/
}