// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "../../Stati�Lib/Stati�Lib/StaticLib.h"

#pragma comment(lib, "../../Stati�Lib/Debug/Stati�Lib.lib")


using namespace std;

int main()
{
    cout << "++ Calculator ++\n\n"; 


	while (true)
	{
		cout << "> ";

		double x;
		cin >> x;

		char sym;
		cin >> sym;

		double y;
		cin >> y;

		double res;
		bool error = false;

		switch (sym)
		{
		case '+':
			res = x + y;
			
			break;

		case '-':
			res = x - y;
			break;

		case '*':
			res = x * y;
			break;

		case '/':
			res = x / y;
			break;

		default:
			error = true;
			break;
		}
		if (error)
		{
			cout << "error";
		}
		else
		{
			cout << "result = " << res;
		}
		
		cout << endl << endl;
	}


	system("pause");
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
