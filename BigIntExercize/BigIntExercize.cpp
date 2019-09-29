// BigIntExercize.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "BigInt/BigInt.h"

int main()
{
	{
		BigInt a{ "1" };
		BigInt b{ "100" };

		a <<= b;

		std::cout << "B: " << b << std::endl;
		std::cout << "A: " << a << std::endl;
	}

	{
		BigInt a{ "1" };
		BigInt b{ "100" };

		a <<= b;
		a >>= 90;

		std::cout << "B: " << b << std::endl;
		std::cout << "A: " << a << std::endl;
	}

	{
		BigInt a{ "2" };
		BigInt b{ "10" };

		BigInt c = pow(a, b);

		std::cout << "B: " << b << std::endl;
		std::cout << "A: " << a << std::endl;
		std::cout << "C: " << c << std::endl;
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
