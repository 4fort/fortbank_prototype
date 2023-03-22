#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class custlib {
public:
	template<typename T> void printElement(T t, const int& width, char fill)
	{
		cout << fixed << setprecision(2) << left << setw(width) << setfill(fill) << t;
	}
};