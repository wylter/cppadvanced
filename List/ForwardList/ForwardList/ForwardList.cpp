// ForwardList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <forward_list>
#include "SList.h"

typedef SList List;

void print(List::iterator begin, List::iterator end)
{
	while (begin != end)
	{
		std::cout << *begin++ << " ";
	}
}

int main()
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

		List list(vect, vect+10);

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

		List::iterator it = std::next(list.begin(), 2); //3rd position
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

		List::iterator it = std::next(list.begin(), 2); //3rd position
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
		int vect2[3] = { 11, 12, 13};
		List list(vect, vect + 10);

		List::iterator it = std::next(list.begin(), 2); //3rd position
		list.insert_after(it, vect2, vect2+3);

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

		int vect_result[15] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9, 20, 20, 20, 20, 20};
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


}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
