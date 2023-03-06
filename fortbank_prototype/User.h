#pragma once
#include <iostream>
using namespace std;
class User {
    string name;
    string email;
    string balance;

public:
    static void test() {
        static int num = 0;
        num++;
        cout << num;
    }
    void setName(string x) {
        this->name = x;
    }
    string getName() {
        return this->name;
    }
    void setEmail(string x) {
        this->email = x;
    }
    string getEmail() {
        return this->email;
    }
    void setBalance(string x) {
        this->balance = x;
    }
    string getBalance() {
        return this->balance;
    }
};