#pragma once
#include <iostream>
#include <iomanip>
#include <regex>
using namespace std;

extern regex input_regex;

class custlib {
public:
	template<typename T> void printElement(T t, const int& width, char fill)
	{
		cout << fixed << setprecision(2) << left << setw(width) << setfill(fill) << t;
	}
};