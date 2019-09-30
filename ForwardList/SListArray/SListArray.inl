#include "pch.h"
#include "SListArray/SListArray.h"
#include <algorithm>

namespace cppadvanced
{

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray()
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
	SListArray<T, MAX>::SListArray(size_type count) : SListArray()
	{
		count = count <= MAX ? count : MAX;

		for (size_t i = 0; i < count; i++)
		{
			push_front(value_type());
		}
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray(const SListArray<T, MAX>& other) 
		: back(storage + MAX, storage)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i] = other.storage[i];
		}

		//Copying node indexes
		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::SListArray(SListArray<T, MAX>&& other)
		: back(storage + MAX, storage)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i] = std::move(other.storage[i]);
		}

		//Copying node indexes
		before_used_node.next = other.before_used_node.next;
		before_free_node.next = other.before_free_node.next;
	}

	template < typename T, size_t MAX >
	template<class InputIt>
	SListArray<T, MAX>::SListArray(InputIt first, InputIt last)
		: back(storage + MAX, storage)
		, before_used_head(&before_used_node, storage)
		, before_free_head(&before_free_node, storage)
	{
		iterator prevIt = before_used_head;
		int i;
		for (i = 0; first != last && i < MAX; first++, prevIt++, i++)
		{
			storage[i].value = *first;
			storage[i].next = back;

			prevIt.current_node->next = i;
		}

		before_free_node.next = i;

		//Setup rest of the nodes
		for (; i < MAX; i++)
		{
			storage[i].next = i + 1;
		}
	}

	template < typename T, size_t MAX >
	SListArray<T, MAX>::~SListArray()
	{}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::node* cppadvanced::SListArray<T, MAX>::extractFreeHeadNode()
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
	void cppadvanced::SListArray<T, MAX>::pushFreeHead(iterator it)
	{
		const iterator free_head = std::next(before_free_head);

		before_free_head.current_node->next = it;
		it.current_node->next = free_head;
	}
	
	template < typename T, size_t MAX >
	typename SListArray<T, MAX>& SListArray<T, MAX>::operator=(const SListArray<T, MAX>& other)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			storage[i] = other.storage[i];
		}

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
		erase_after(before_used_head, back);
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, const T& value)
	{
		node* newNode = extractFreeHeadNode();

		if (!newNode)
		{
			return back;
		}

		const iterator prepos = pos;
		const iterator postpos = std::next(pos);

		newNode->value = value;

		const size_t nextIndex = newNode - storage;
		prepos.current_node->next = nextIndex;
		newNode->next = postpos;

		const iterator newPosition(newNode, storage);
		return newPosition;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, T&& value)
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

	//TODO: change logic 
	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::insert_after(const_iterator pos, size_type count, const T& value)
	{
		iterator last_prepos = pos;
		const iterator postpos = std::next(pos);

		for (size_t i = 0; i < count; i++, last_prepos++)
		{
			iterator newPosition = insert_after(last_prepos, value);

			if (newPosition == back)
			{
				break;
			}
		}

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
			iterator newPosition = insert_after(last_prepos, *first);

			if (newPosition == back)
			{
				break;
			}
		}

		return last_prepos;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::erase_after(const_iterator pos)
	{
		const iterator erasepos = std::next(pos);

		const iterator postpos = std::next(erasepos);

		pushFreeHead(erasepos);

		pos.current_node->next = postpos;

		return postpos;
	}

	template < typename T, size_t MAX >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::erase_after(const_iterator first, const_iterator last)
	{
		iterator it = std::next(first);

		while (it != last)
		{
			const iterator current_it = it;
			it++;

			pushFreeHead(current_it);
		}

		first.current_node->next = last;

		return last;
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::push_front(const T& value)
	{
		insert_after(before_used_head, value);
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::push_front(T&& value)
	{
		insert_after(before_used_head, std::move(value));
	}

	
	template < typename T, size_t MAX >
	void SListArray<T, MAX>::pop_front()
	{
		erase_after(before_used_head);
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::resize(size_type count, const value_type& value)
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
			insert_after(it, count_difference, value);
		}
		else
		{
			erase_after(it, back);
		}
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::swap(SListArray<T, MAX>& other)
	{
		for (size_t i = 0; i < MAX; i++)
		{
			std::swap(storage[i], other.storage[i]);
		}

		std::swap(before_used_node, other.before_used_node);
		std::swap(before_free_node, other.before_free_node);
	}

	template < typename T, size_t MAX >
	void SListArray<T, MAX>::remove(const T& value)
	{
		iterator it = std::next(before_used_head);
		iterator prevIt = before_used_head;

		while (it != back)
		{
			if (*it == value)
			{
				it++;
				erase_after(prevIt);
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
	void SListArray<T, MAX>::unique()
	{
		iterator it = std::next(before_used_head);

		while (it != back)
		{
			const iterator next = std::next(it);
			if (next != back && *it == *next)
			{
				erase_after(it);
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

		slow.current_node->next = back; // splitting the two lists
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
		iterator head = std::next(before_used_head);

		mergeSort(head, comp);

		before_used_head.current_node->next = head;
	}

	
	template < typename T, size_t MAX >
	template< class Compare >
	typename SListArray<T, MAX>::iterator SListArray<T, MAX>::mergeList(iterator head1, iterator head2, Compare comp)
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
}