#pragma once
#include <iostream>
using namespace std;
class User {
    string id;
    string name;
    string email;
    string balance;
    string card_num;
    string card_pin;

public:
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
    void setCardNum(string x) {
        this->card_num = x;
    }
    string getCardNum() {
        return this->card_num;
    }
    void setCardPin(string x) {
        this->card_pin = x;
    }
    string getCardPin() {
        return this->card_pin;
    }
};