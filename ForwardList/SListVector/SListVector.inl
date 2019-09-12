#include "pch.h"
#include "SListVector/SListVector.h"
#include <algorithm>

namespace cppadvanced
{

	template < typename T, size_t MAX >
	SListVector<T, MAX>::SListVector()
		: before_used_node(MAX) //Points to end
		, before_free_node(0) //Points to begin
		, back(storage + MAX, storage)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i].next = i + 1;
		}
	}

	template < typename T, size_t MAX >
	SListVector<T, MAX>::SListVector(size_type count) : SListVector()
	{
		count = count <= MAX ? count : MAX;

		value_type default_value = {};
		for (size_t i = 0; i < count; i++)
		{
			push_front(default_value);
		}
	}

	template < typename T, size_t MAX >
	SListVector<T, MAX>::SListVector(const SListVector<T, MAX>& other) 
		: back(storage + MAX, storage)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		std::memcpy(storage, other.storage, sizeof(storage));

		//Copying node indexes
		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;
	}

	template < typename T, size_t MAX >
	SListVector<T, MAX>::SListVector(SListVector<T, MAX>&& other)
		: back(storage + MAX, storage)
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
	SListVector<T, MAX>::SListVector(InputIt first, InputIt last)
		: back(storage + MAX, storage)
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

		//Setup rest of the nodes
		for (; i < MAX; i++)
		{
			storage[i].next = i + 1;
		}
	}

	template < typename T, size_t MAX >
	SListVector<T, MAX>::~SListVector()
	{}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::node* cppadvanced::SListVector<T, MAX>::extractFreeHeadNode()
	{
		iterator newPosition = std::next(before_free_head);

		if (newPosition == back) // No space left, cant push another item
		{
			return nullptr;
		}

		before_free_head.current_node->next = newPosition.current_node->next;  //Disconnect the node

		return static_cast<node*>(newPosition.current_node);
	}

	template < typename T, size_t MAX >
	void cppadvanced::SListVector<T, MAX>::pushFreeHead(iterator it)
	{
		const iterator free_head = std::next(before_free_head);

		before_free_head.current_node->next = it;
		it.current_node->next = free_head;
	}


	template < typename T, size_t MAX >
	void cppadvanced::SListVector<T, MAX>::pushFreeHead(iterator first, iterator last)
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

		before_free_head.current_node->next = firstItToErase;
		lastItToErase.current_node->next = free_head;
	}

	
	template < typename T, size_t MAX >
	typename SListVector<T, MAX>& SListVector<T, MAX>::operator=(const SListVector<T, MAX>& other)
	{
		std::memcpy(storage, other.storage, sizeof(storage));

		//Copying node indexes
		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;

		return *this;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>& SListVector<T, MAX>::operator=(SListVector<T, MAX>&& other)
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
	typename SListVector<T, MAX>::reference SListVector<T, MAX>::front()
	{
		return *std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::const_reference SListVector<T, MAX>::front() const
	{
		return *std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::before_begin() noexcept
	{
		return before_used_head;
	}

	template < typename T, size_t MAX >
	const typename SListVector<T, MAX>::iterator SListVector<T, MAX>::before_begin() const noexcept
	{
		return before_used_head;
	}

	template < typename T, size_t MAX >
	const typename SListVector<T, MAX>::iterator SListVector<T, MAX>::cbefore_begin() const noexcept
	{
		return before_used_head;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::begin() noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	const typename SListVector<T, MAX>::iterator SListVector<T, MAX>::begin() const noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	const typename SListVector<T, MAX>::iterator SListVector<T, MAX>::cbegin() const noexcept
	{
		return std::next(before_used_head);
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::end() noexcept
	{
		return back;
	}

	template < typename T, size_t MAX >
	const typename SListVector<T, MAX>::iterator SListVector<T, MAX>::end() const noexcept
	{
		return back;
	}

	template < typename T, size_t MAX >
	const typename SListVector<T, MAX>::iterator SListVector<T, MAX>::cend() const noexcept
	{
		return back;
	}

	

	template < typename T, size_t MAX >
	bool SListVector<T, MAX>::empty() const noexcept
	{
		return std::next(before_used_head) == back;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::size_type SListVector<T, MAX>::max_size() const noexcept
	{
		return MAX;
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::clear() noexcept
	{
		iterator it = before_free_head;

		while (std::next(it) != back)
		{
			it++;
		}

		iterator used_head = std::next(before_used_head);

		it.current_node->next = used_head; //Concatenate the used list to the free list

		before_used_head.current_node->next = MAX;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::insert_after(const_iterator pos, const T& value)
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

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::insert_after(const_iterator pos, T&& value)
	{
		node* newNode = extractFreeHeadNode();

		if (!newNode)
		{
			return back;
		}

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newNode->value = std::move(value);

		const size_t nextIndex = newNode - storage;
		prepos.current_node->next = nextIndex;
		newNode->next = postpos;

		const iterator newPosition(newNode, storage);
		return newPosition;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::insert_after(const_iterator pos, size_type count, const T& value)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (size_t i = 0; i < count; i++, last_prepos++)
		{
			node* newNode = extractFreeHeadNode();
			if (!newNode) //Tries to insert as much as it can. if there's no space left, it just inserts the max amout
			{
				break;
			}

			newNode->value = value;

			const size_t nextIndex = newNode - storage;
			last_prepos.current_node->next = nextIndex;
		}

		last_prepos.current_node->next = postpos;

		return last_prepos;
	}

	template < typename T, size_t MAX >
	template< class InputIt >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::insert_after(const_iterator pos, InputIt first, InputIt last)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (; first != last; first++, last_prepos++)
		{
			node* newNode = extractFreeHeadNode();
			if (!newNode) //Tries to insert as much as it can. if there's no space left, it just inserts the max amout
			{
				break;
			}
			newNode->value = *first;

			const size_t nextIndex = newNode - storage;
			last_prepos.current_node->next = nextIndex;
		}

		last_prepos.current_node->next = postpos;


		return last_prepos;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::erase_after(const_iterator pos)
	{
		const iterator erasepos = std::next(pos);

		const iterator postpos = std::next(erasepos);

		pushFreeHead(erasepos);

		pos.current_node->next = postpos;

		return postpos;
	}

	template < typename T, size_t MAX >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::erase_after(const_iterator first, const_iterator last)
	{
		pushFreeHead(std::next(first), last);

		first.current_node->next = last;

		return last;
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::push_front(const T& value)
	{
		node* newNode = extractFreeHeadNode();

		if (!newNode)
		{
			return;
		}

		newNode->value = value;
		newNode->next = before_used_head.current_node->next;

		const size_t nextIndex = newNode - storage;
		before_used_head.current_node->next = nextIndex;
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::push_front(T&& value)
	{
		node* newNode = extractFreeHeadNode();

		if (!newNode)
		{
			return;
		}

		newNode->value = std::move(value);
		newNode->next = before_used_head.current_node->next;

		const size_t nextIndex = newNode - storage;
		before_used_head.current_node->next = nextIndex;
	}

	
	template < typename T, size_t MAX >
	void SListVector<T, MAX>::pop_front()
	{
		const iterator toEraseIterator = std::next(before_used_head);

		before_used_head.current_node->next = toEraseIterator.current_node->next;

		pushFreeHead(toEraseIterator);
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::resize(size_type count, const value_type& value)
	{
		count = count <= MAX ? count : MAX;

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
				node* newNode = extractFreeHeadNode();
				newNode->value = value;

				const size_t nextIndex = newNode - storage;
				it.current_node->next = nextIndex;
			}
		}
		else
		{
			iterator tail = it;

			pushFreeHead(std::next(tail), back);

			tail.current_node->next = MAX;
		}
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::swap(SListVector<T, MAX>& other)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			std::swap(storage[i], other.storage[i]);
		}

		std::swap(before_used_node, other.before_used_node);
		std::swap(before_free_node, other.before_free_node);
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::remove(const T& value)
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

				prevIt.current_node->next = it;
			}
			else
			{
				it++;
				prevIt++;
			}
		}
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::reverse() noexcept
	{
		const iterator head = std::next(before_used_head);

		if (head == back)
		{
			return;
		}

		iterator it = std::next(head);

		head.current_node->next = MAX;

		iterator last_head = head;

		while (it != back)
		{
			const iterator current_iterator = it;
			it++;

			current_iterator.current_node->next = last_head;
			last_head = current_iterator;
		}

		before_used_head.current_node->next = last_head;
	}

	template < typename T, size_t MAX >
	void SListVector<T, MAX>::unique()
	{
		iterator it = std::next(before_used_head);

		while (it != back)
		{
			const iterator next = std::next(it);
			if (next != back && *it == *next)
			{
				it.current_node->next = next.current_node->next;

				pushFreeHead(next);
			}
			else
			{
				it++;
			}
		}
	}

	
	template < typename T, size_t MAX >
	void SListVector<T, MAX>::split(iterator head, iterator& splittedHead1, iterator& splittedHead2)
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

		slow.current_node->next = back; // splitting the two lists
	}

	
	template < typename T, size_t MAX >
	void SListVector<T, MAX>::sort()
	{
		sort(std::less<int>());
	}

	template < typename T, size_t MAX >
	template< class Compare >
	void SListVector<T, MAX>::sort(Compare comp)
	{
		iterator head = std::next(before_used_head);

		mergeSort(head, comp);

		before_used_head.current_node->next = head;
	}

	
	template < typename T, size_t MAX >
	template< class Compare >
	typename SListVector<T, MAX>::iterator SListVector<T, MAX>::mergeList(iterator head1, iterator head2, Compare comp)
	{
		indexed_node_base before_head_node;
		before_head_node.next = back;
		iterator before_head_result(&before_head_node, storage);

		iterator it = before_head_result;

		while (head1 != back && head2 != back)
		{
			if (comp(*head1, *head2))
			{
				it.current_node->next = head1;
				it++;
				head1++;
			}
			else
			{
				it.current_node->next = head2;
				it++;
				head2++;
			}
		}

		if (head1 != back)
		{
			it.current_node->next = head1;
		}
		else //head2 != back
		{
			it.current_node->next = head2;
		}


		return std::next(before_head_result);
	}

	template < typename T, size_t MAX >
	template< class Compare >
	void SListVector<T, MAX>::mergeSort(iterator& head_reference, Compare comp)
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