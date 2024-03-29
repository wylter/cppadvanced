#include "pch.h"
#include "SList/SList.h"
#include <algorithm>

namespace cppadvanced
{

	//back iterator is set to nullptr. As the "end()" method will return the iterator that represents the element after the last one, the last element will always point to nullptr.
	template < typename T >
	const typename SList<T>::iterator SList<T>::back = iterator(nullptr);

	template < typename T >
	SList<T>::SList()
		: before_head()
	{
		before_head.current_node = new node_base();
	}

	template < typename T >
	SList<T>::SList(size_type count) : SList()
	{
		insert_after(before_head, count, T());
	}

	template < typename T >
	SList<T>::SList(const SList& other) : SList()
	{
		insert_after(before_head, other.begin(), other.end());
	}

	template < typename T >
	SList<T>::SList(SList&& other)
	{
		before_head = other.before_head;

		other.before_head = back;
	}

	template < typename T >
	template<class InputIt>
	SList<T>::SList(InputIt first, InputIt last) : SList()
	{
		insert_after(before_head, first, last);
	}

	template < typename T >
	SList<T>::~SList()
	{
		iterator it = before_head;
		while (it != back)
		{
			const iterator current_node = it;
			it++;
			delete current_node.current_node;
		}
	}

	template < typename T >
	typename SList<T>& SList<T>::operator=(const SList<T>& other)
	{
		iterator lastInserted = before_head;
		iterator it = std::next(before_head);
		iterator otherIt = std::next(other.before_head);

		while (it != back && otherIt != other.back)
		{
			*it = *otherIt;

			lastInserted = it;

			it++;
			otherIt++;
		}

		if (it == back) //if this has less elements than other
		{
			insert_after(lastInserted, otherIt, other.back);
		}
		else //if other has less elements than this
		{
			erase_after(lastInserted, back);
		}

		return *this;
	}

	template < typename T >
	typename SList<T>& SList<T>::operator=(SList<T>&& other)
	{
		std::swap(before_head, other.before_head);

		return *this;
	}

	template < typename T >
	typename SList<T>::reference SList<T>::front()
	{
		return *std::next(before_head);
	}

	template < typename T >
	typename SList<T>::const_reference SList<T>::front() const
	{
		return *std::next(before_head);
	}

	template < typename T >
	typename SList<T>::iterator SList<T>::before_begin() noexcept
	{
		return before_head;
	}

	template < typename T >
	const typename SList<T>::iterator SList<T>::before_begin() const noexcept
	{
		return before_head;
	}

	template < typename T >
	const typename SList<T>::iterator SList<T>::cbefore_begin() const noexcept
	{
		return before_head;
	}

	template < typename T >
	typename SList<T>::iterator SList<T>::begin() noexcept
	{
		return std::next(before_head);
	}

	template < typename T >
	const typename SList<T>::iterator SList<T>::begin() const noexcept
	{
		return std::next(before_head);
	}

	template < typename T >
	const typename SList<T>::iterator SList<T>::cbegin() const noexcept
	{
		return std::next(before_head);
	}

	template < typename T >
	typename SList<T>::iterator SList<T>::end() noexcept
	{
		return back;
	}

	template < typename T >
	const typename SList<T>::iterator SList<T>::end() const noexcept
	{
		return back;
	}

	template < typename T >
	const typename SList<T>::iterator SList<T>::cend() const noexcept
	{
		return back;
	}

	template < typename T >
	bool SList<T>::empty() const noexcept
	{
		return std::next(before_head) == back;
	}

	template < typename T >
	typename SList<T>::size_type SList<T>::max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	template < typename T >
	void SList<T>::clear() noexcept
	{
		erase_after(before_head, back);
	}

	template < typename T >
	typename SList<T>::iterator SList<T>::insert_after(const_iterator pos, const T& value)
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

	template < typename T >
	typename SList<T>::iterator SList<T>::insert_after(const_iterator pos, T&& value)
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

	template < typename T >
	typename SList<T>::iterator SList<T>::insert_after(const_iterator pos, size_type count, const T& value)
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
	typename SList<T>::iterator SList<T>::insert_after(const_iterator pos, InputIt first, InputIt last)
	{
		iterator last_prepos = pos;

		for (; first != last; first++, last_prepos++)
		{
			insert_after(last_prepos, *first);
		}

		return last_prepos;
	}

	template < typename T >
	typename SList<T>::iterator SList<T>::erase_after(const_iterator pos)
	{
		const iterator erasepos = std::next(pos);
		const iterator postpos = std::next(erasepos);

		delete erasepos.current_node;

		pos.current_node->next = postpos.current_node;

		return postpos;
	}

	template < typename T >
	typename SList<T>::iterator SList<T>::erase_after(const_iterator first, const_iterator last)
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

	template < typename T >
	void SList<T>::push_front(const T& value)
	{
		insert_after(before_head, value);
	}

	template < typename T >
	void SList<T>::push_front(T&& value)
	{
		insert_after(before_head, std::move(value));
	}

	template < typename T >
	void SList<T>::pop_front()
	{
		erase_after(before_head);
	}

	template < typename T >
	void SList<T>::resize(size_type count, const value_type& value)
	{
		size_t elements_count = 0;
		iterator it = before_head;

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

	template < typename T >
	void SList<T>::swap(SList& other)
	{
		std::swap(before_head, other.before_head);
	}

	template < typename T >
	void SList<T>::remove(const T& value)
	{
		iterator it = std::next(before_head);
		iterator prevIt = before_head;

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

	template < typename T >
	void SList<T>::reverse() noexcept
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

	template < typename T >
	void SList<T>::unique()
	{
		iterator it = std::next(before_head);

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

	template < typename T >
	void SList<T>::split(iterator head, iterator& splittedHead1, iterator& splittedHead2)
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

	template < typename T >
	void SList<T>::sort()
	{
		sort(std::less<int>());
	}

	template < typename T >
	template< class Compare >
	void SList<T>::sort(Compare comp)
	{
		iterator head = std::next(before_head);

		merge_sort(head, comp);

		before_head.current_node->next = head.current_node;
	}

	template < typename T >
	template< class Compare >
	typename SList<T>::iterator SList<T>::merge_list(iterator head1, iterator head2, Compare comp)
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


	template < typename T >
	template< class Compare >
	void SList<T>::merge_sort(iterator& head_reference, Compare comp)
	{
		const iterator head = head_reference;

		if (head == back || std::next(head) == back)
		{
			return;
		}

		iterator splittedHead1;
		iterator splittedHead2;

		split(head, splittedHead1, splittedHead2);

		merge_sort(splittedHead1, comp);
		merge_sort(splittedHead2, comp);

		head_reference = merge_list(splittedHead1, splittedHead2, comp);
	}

}