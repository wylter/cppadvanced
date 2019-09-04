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
