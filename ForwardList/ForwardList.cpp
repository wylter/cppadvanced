// ForwardList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <forward_list>
#include "SList/SList.h"
#include "SListArray/SListArray.h"

using namespace cppadvanced;

class Integer
{
public:
	static size_t allocated_count;

	Integer()
		: value()
	{
		allocated_count++;
	}

	Integer(int value) 
		: value(value)
	{
		allocated_count++;
	}

	~Integer()
	{
		allocated_count--;
	}

	operator int() const { 
		return value; 
	}

	friend bool operator==(const Integer& lhs, const Integer&rhs)
	{
		return lhs.value == rhs.value;
	}

	friend bool operator!=(const Integer& lhs, const Integer&rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const Integer& lhs, const Integer&rhs)
	{
		return lhs.value < rhs.value;
	}

	friend bool operator>(const Integer& lhs, const Integer&rhs)
	{
		return rhs < lhs;
	}

	friend bool operator<=(const Integer& lhs, const Integer&rhs)
	{
		return !(lhs > rhs);
	}

	friend bool operator>=(const Integer& lhs, const Integer&rhs)
	{
		return !(lhs < rhs);
	}


private:
	int value;

};

size_t Integer::allocated_count = 0;

template < typename ForwardIt >
void print(ForwardIt begin, ForwardIt end)
{
	while (begin != end)
	{
		std::cout << *begin++ << " ";
	}
}

template < typename List >
void TestListInteger()
{

	//Default Constructor
	{
		std::cout << "\n***\nDefault Constructor\n***\n";
		List list = {};

		std::cout << "Result:" << std::endl;

		print(list.begin(), list.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
	}

	//Count Insertion of Default Values constructor
	{
		std::cout << "\n***\nCount constructor\n***\n";
		List list(10);

		std::cout << "Result:" << std::endl;

		print(list.begin(), list.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;

		for (int i = 0; i < 10; i++)
		{
			std::cout << 0 << " ";
		}
		std::cout << std::endl;
	}

	//Iterator constructor
	{
		std::cout << "\n***\nIterator constructor\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };

		List list(vect, vect + 10);

		std::cout << "Result:" << std::endl;

		print(list.begin(), list.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;

		for (int i = 0; i < 10; i++)
		{
			std::cout << vect[i] << " ";
		}
		std::cout << std::endl;
	}

	//Copy constructor
	{
		std::cout << "\n***\nCopy constructor\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List* list1pointer = new List(vect, vect + 10);
		List list2(*list1pointer);
		delete list1pointer;

		std::cout << "Result:" << std::endl;

		print(list2.begin(), list2.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << vect[i] << " ";
		}
		std::cout << std::endl;
	}

	//Move constructor
	{
		std::cout << "\n***\nMove constructor\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list1(vect, vect + 10);
		List list2(std::move(list1));

		std::cout << "Result:" << std::endl;

		std::cout << (list1.before_begin() == list1.end() ? "true" : "false");
		std::cout << std::endl;
		print(list2.begin(), list2.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		std::cout << "true" << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << vect[i] << " ";
		}
		std::cout << std::endl;
	}

	//Copy Operator
	{
		std::cout << "\n***\nCopy operator\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List* list1pointer = new List(vect, vect + 10);
		List list2;
		list2 = *list1pointer;
		delete list1pointer;

		std::cout << "Result:" << std::endl;

		print(list2.begin(), list2.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << vect[i] << " ";
		}
		std::cout << std::endl;
	}

	//Move operator
	{
		std::cout << "\n***\nMove operator\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List* list1pointer = new List(vect, vect + 10);
		List list2;
		list2 = std::move(*list1pointer);
		delete list1pointer;

		std::cout << "Result:" << std::endl;
		print(list2.begin(), list2.end());
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << vect[i] << " ";
		}
		std::cout << std::endl;
	}

	//front()
	{
		std::cout << "\n***\nFunction front()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		std::cout << "Result:" << std::endl;
		std::cout << list.front();
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		std::cout << vect[0];
		std::cout << std::endl;
	}

	//empty()
	{
		std::cout << "\n***\nFunction empty()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list1(vect, vect + 10);
		List list2;

		std::cout << "Result:" << std::endl;
		std::cout << list1.empty() << std::endl;
		std::cout << list2.empty();
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		std::cout << 0 << std::endl;
		std::cout << 1;
		std::cout << std::endl;
	}

	//max_size()
	{
		std::cout << "\n***\nFunction max_size()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list;

		std::cout << "Result:" << std::endl;
		std::cout << list.max_size();
		std::cout << std::endl;
	}

	//clear()
	{
		std::cout << "\n***\nFunction clear()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		std::cout << "Result:" << std::endl;
		std::cout << list.empty() << std::endl;
		list.clear();
		std::cout << list.empty();
		std::cout << std::endl;

		std::cout << "Attended Result:" << std::endl;
		std::cout << 0 << std::endl;
		std::cout << 1;
		std::cout << std::endl;
	}

	//insert_after()
	{
		std::cout << "\n***\nFunction insert_after() case 1\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		typename List::iterator it = std::next(list.begin(), 2); //3rd position
		list.insert_after(it, 99);

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[11] = { 0, 1, 2, 99, 3, 4 , 5, 6, 7, 8, 9 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 11; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//insert_after()
	{
		std::cout << "\n***\nFunction insert_after() case 2\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		typename List::iterator it = std::next(list.begin(), 2); //3rd position
		size_t size = 3;
		list.insert_after(it, size, 99);

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[13] = { 0, 1, 2, 99, 99, 99, 3, 4 , 5, 6, 7, 8, 9 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 13; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//insert_after()
	{
		std::cout << "\n***\nFunction insert_after() case 3\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		int vect2[3] = { 11, 12, 13 };
		List list(vect, vect + 10);

		typename List::iterator it = std::next(list.begin(), 2); //3rd position
		list.insert_after(it, vect2, vect2 + 3);

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[13] = { 0, 1, 2, 11, 12, 13, 3, 4 , 5, 6, 7, 8, 9 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 13; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//erase_after()
	{
		std::cout << "\n***\nFunction erase_after() case 1\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		list.erase_after(list.before_begin());

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int* vect_result = vect + 1;
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//erase_after()
	{
		std::cout << "\n***\nFunction insert_after() case 2\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		list.erase_after(list.before_begin(), std::next(list.before_begin(), 4));

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int* vect_result = vect + 3;
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 7; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//push_front()
	{
		std::cout << "\n***\nFunction push_front()\n***\n";

		List list = {};
		int a = 10;

		list.push_front(10);
		list.push_front(2);
		list.push_front(1);

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[3] = { 1, 2, 10 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 3; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//pop_front()
	{
		std::cout << "\n***\nFunction pop_front()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		list.pop_front();

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int* vect_result = vect + 1;
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//resize()
	{
		std::cout << "\n***\nFunction resize()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list1(vect, vect + 10);
		List list2(vect, vect + 10);

		list1.resize(5);
		list2.resize(15, 20);
		list2.resize(15);

		std::cout << "Result:" << std::endl;
		print(list1.begin(), list1.end());
		std::cout << std::endl;
		print(list2.begin(), list2.end());
		std::cout << std::endl;

		int vect_result[15] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9, 20, 20, 20, 20, 20 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < 15; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//swap()
	{
		std::cout << "\n***\nFunction swap()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
		List list1(vect, vect + 5);
		List list2(vect, vect + 10);

		list1.swap(list2);

		std::cout << "Result:" << std::endl;
		print(list1.begin(), list1.end());
		std::cout << std::endl;
		print(list2.begin(), list2.end());
		std::cout << std::endl;

		int* vect_result = vect;
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//remove()
	{
		std::cout << "\n***\nFunction remove()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4 , 5, 2, 7, 8, 9 };
		List list(vect, vect + 10);

		list.remove(2);

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[8] = { 0, 1, 3, 4 , 5, 7, 8, 9 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 8; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//reverse()
	{
		std::cout << "\n***\nFunction reverse()\n***\n";

		int vect[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		List list(vect, vect + 10);

		list.reverse();

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int* vect_result = vect;
		std::cout << "Attended Result:" << std::endl;
		for (int i = 9; i >= 0; i--)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//unique()
	{
		std::cout << "\n***\nFunction unique()\n***\n";

		int vect[10] = { 0, 1, 3, 3, 3, 5, 6, 6, 8, 0 };
		List list(vect, vect + 10);

		list.unique();

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[7] = { 0, 1, 3, 5, 6, 8, 0 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 7; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	//sort()
	{
		std::cout << "\n***\nFunction sort()\n***\n";

		int vect[10] = { 2, 4, 6, 8, 0, 1, 3, 5, 7, 9 };
		List list(vect, vect + 10);

		list.sort(std::greater<int>());

		std::cout << "Result:" << std::endl;
		print(list.begin(), list.end());
		std::cout << std::endl;

		int vect_result[10] = { 9, 8, 7, 6, 5, 4, 3, 2 , 1, 0 };
		std::cout << "Attended Result:" << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << vect_result[i] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
	std::cout << "Memory leaked: " << Integer::allocated_count * sizeof(Integer) << std::endl << std::endl;
}

int main()
{
	while (true)
	{
		std::cout << "Test List: \n1)Single-Linked List \n2)Vector SList \n3)Array SList\n";
		unsigned short choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "\n\n---------------------------------------\nSingle-Linked List\n---------------------------------------\n\n";
			TestListInteger<cppadvanced::SList<Integer>>();
			break;
		case 2:
			std::cout << "\n\n---------------------------------------\nVector SList\n---------------------------------------\n\n";
			break;
		case 3:
			std::cout << "\n\n---------------------------------------\nArray SList\n---------------------------------------\n\n";
			break;
		default:
			break;
		}
	}

}
