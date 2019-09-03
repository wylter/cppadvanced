// ForwardList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <forward_list>
#include "SList.h"

void print(SList::iterator begin, SList::iterator end)
{
	while (begin != end)
	{
		std::cout << *begin++ << " ";
	}
}

int main()
{
	SList list;

	list.push_front(1);
	list.push_front(3);
	list.push_front(2);
	list.push_front(5);
	list.push_front(10);
	list.push_front(9);

	list.sort();

	print(list.begin(), list.end());
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
