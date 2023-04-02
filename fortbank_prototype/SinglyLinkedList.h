#pragma once
#include <iostream>
#include <sstream>
#include "custlib.h"
using namespace std;
extern custlib cstmlib;

class Node {
    int id;
    string owner_name;
    string email;
    int card_num;
    int card_pin;
    double balance;

    int owner_id;
    string hist_type;
    string date;
    double amount;
    double user_prev_amount;
    double receiver_prev_amount;
    bool is_receiver;
    int card_sender;
    int card_receiver;
public:
    void setId(int x) {
        this->id = x;
    }
    int getId() {
        return this->id;
    }
    void setName(string x) {
        this->owner_name = x;
    }
    string getName() {
        return this->owner_name;
    }
    void setEmail(string x) {
        this->email = x;
    }
    string getEmail() {
        return this->email;
    }
    void setCardNum(int x) {
        this->card_num = x;
    }
    int getCardNum() {
        return this->card_num;
    }
    void setCardPin(int x) {
        this->card_pin = x;
    }
    int getCardPin() {
        return this->card_pin;
    }
    void setBalance(double x) {
        this->balance = x;
    }
    double getBalance() {
        return this->balance;
    }

    void setOwnerId_history(int x) {
        this->owner_id = x;
    }
    int getOwnerId_history() {
        return this->owner_id;
    }
    void setHistoryType_history(string x) {
        this->hist_type = x;
    }
    string getHistoryType_history() {
        return this->hist_type;
    }
    void setDate_history(string x) {
        this->date = x;
    }
    string getDate_history() {
        return this->date;
    }
    void setAmount_history(double x) {
        this->amount = x;
    }
    double getAmount_history() {
        return this->amount;
    }
    void setUserPrevAmount_history(double x) {
        this->user_prev_amount = x;
    }
    double getUserPrevAmount_history() {
        return this->user_prev_amount;
    }
    void setIsReceiver_history(bool x) {
        this->is_receiver = x;
    }
    bool getIsReceiver_history() {
        return this->is_receiver;
    }
    void setCardSender_history(int x) {
        this->card_sender = x;
    }
    int getCardSender_history() {
        return this->card_sender;
    }
    void setCardReceiver_history(int x) {
        this->card_receiver = x;
    }
    int getCardReceiver_history() {
        return this->card_receiver;
    }

    Node* next;

    Node() {
        id = 0;
        owner_name = "";
        email = "";
        card_num = 0;
        card_pin = 0;
        balance = 0;
        next = NULL;
    }
    Node(int temp_id, string temp_owner_name, string temp_email, int temp_card_num, int temp_card_pin, double temp_balance) {
        id = temp_id;
        owner_name = temp_owner_name;
        email = temp_email;
        card_num = temp_card_num;
        card_pin = temp_card_pin;
        balance = temp_balance;
    }
};

class SinglyLinkedList {
public:
    Node* head;

    SinglyLinkedList() {
        head = NULL;
    }
    SinglyLinkedList(Node* n) {
        head = n;
    }

    // 1. CHeck if node exists using key value
    Node* nodeExists(int temp_id) {
        Node* temp = NULL;

        Node* ptr = head;
        while (ptr != NULL) {
            if (ptr->getId() == temp_id) {
                temp = ptr;
            }
            ptr = ptr->next;

        }
        return temp;
    }

    Node* nodeExistByCard(int card) {
        Node* temp = NULL;
        Node* ptr = head;
        while (ptr != NULL) {
            if (ptr->getCardNum() == card) {
                temp = ptr;
            }
            ptr = ptr->next;

        }
        return temp;
    }

    Node* validate(int userCard, int userPin) {
        Node* temp = NULL;
        Node* ptr = head;
        while (ptr != NULL) {
            if (ptr->getCardNum() == userCard && ptr->getCardPin() == userPin) {
                temp = ptr;
            }
            ptr = ptr->next;
        }
        return temp;
    }

    // 2. Append a node to the list
    void appendNode(Node* n) {
        if (nodeExists(n->getId()) != NULL) {
            cout << "Node Already exists with key value : " << n->getId() << ". Append another node with different Key value" << endl;
        }
        else {
            if (head == NULL) {
                head = n;
                //cout << "Node Appended" << endl;
            }
            else {
                Node* ptr = head;
                while (ptr->next != NULL) {
                    ptr = ptr->next;
                }
                ptr->next = n;
                if (n->getId() == NULL) {
                    n->setId(ptr->getId() + 1);
                }
                //cout << "Node Appended" << endl;
            }
        }

    }

    // 5. Delete node by unique key
    void deleteNodeByKey(int temp_id) {
        if (head == NULL) {
            cout << "Singly Linked List already Empty. Cant delete" << endl;
        }
        else if (head != NULL) {
            if (head->getId() == temp_id) {
                head = head->next;
                cout << "Node UNLINKED with keys value : " << temp_id << endl;
            }
            else {
                Node* temp = NULL;
                Node* prevptr = head;
                Node* currentptr = head->next;
                while (currentptr != NULL) {
                    if (currentptr->getId() == temp_id) {
                        temp = currentptr;
                        currentptr = NULL;
                    }
                    else {
                        prevptr = prevptr->next;
                        currentptr = currentptr->next;
                    }
                }
                if (temp != NULL) {
                    prevptr->next = temp->next;
                    cout << "Node UNLINKED with keys value : " << temp_id << endl;
                }
                else {
                    cout << "Node Doesn't exist with key value : " << temp_id << endl;
                }
            }
        }
    }
    // 6th update node
    /*void updateNodeByKey(int temp_id, string temp_owner_name, string temp_email, int temp_card_pin, double temp_balance) {

        Node* ptr = nodeExists(temp_id);
        if (ptr != NULL) {
            ptr->setName(temp_owner_name);
            ptr->setEmail(temp_email);
            ptr->setCardPin(temp_card_pin);
            ptr->setBalance(temp_balance);
            cout << "Node Data Updated Successfully" << endl;
        }
        else {
            cout << "Node Doesn't exist with key value : " << temp_id << endl;
        }

    }*/

    void updateNode(Node* n) {
        Node* ptr = nodeExists(n->getId());
        if (ptr != NULL) {
            ptr->setName(n->getName());
            ptr->setEmail(n->getEmail());
            ptr->setCardPin(n->getCardPin());
            ptr->setBalance(n->getBalance());
            cout << "Node Data Updated Successfully" << endl;
        }
        else {
            cout << "Node Doesn't exist with key value : " << n->getId() << endl;
        }
    }

    // 7th printing
    void printList() {
        if (head == NULL) {
            cout << "No Nodes in Singly Linked List" << endl;
        }
        else {
            cstmlib.printElement("", 120, '=');
            cout << '\n';
            cstmlib.printElement("ID", 5, ' ');
            cstmlib.printElement("Name", 30, ' ');
            cstmlib.printElement("Email", 30, ' ');
            cstmlib.printElement("Card Num", 20, ' ');
            cstmlib.printElement("Card Pin", 20, ' ');
            cstmlib.printElement("Balance", 20, ' ');
            cout << '\n';
            Node* temp = head;

            while (temp != NULL) {
                cstmlib.printElement(temp->getId(), 5, ' ');
                cstmlib.printElement(temp->getName(), 30, ' ');
                cstmlib.printElement(temp->getEmail(), 30, ' ');
                cstmlib.printElement(temp->getCardNum(), 20, ' ');
                cstmlib.printElement(temp->getCardPin(), 20, ' ');
                cout << "P";
                cstmlib.printElement(temp->getBalance(), 0, ' ');
                cout << '\n';
                temp = temp->next;
            }
            cstmlib.printElement("", 120, '=');
        }

    }

    void printSpecific(int temp_id) {
        if (head == NULL) {
            cout << "No Nodes in Singly Linked List" << endl;
        }
        else {
            Node* ptr = nodeExists(temp_id);
            if (ptr != NULL) {
                cstmlib.printElement("", 120, '=');
                cout << endl;
                cstmlib.printElement("ID", 5, ' ');
                cstmlib.printElement("Name", 30, ' ');
                cstmlib.printElement("Email", 30, ' ');
                cstmlib.printElement("Card Num", 20, ' ');
                cstmlib.printElement("Card Pin", 20, ' ');
                cstmlib.printElement("Balance", 20, ' ');
                cout << '\n';
                cstmlib.printElement(ptr->getId(), 5, ' ');
                cstmlib.printElement(ptr->getName(), 30, ' ');
                cstmlib.printElement(ptr->getEmail(), 30, ' ');
                cstmlib.printElement(ptr->getCardNum(), 20, ' ');
                cstmlib.printElement(ptr->getCardPin(), 20, ' ');
                cout << "P";
                cstmlib.printElement(ptr->getBalance(), 0, ' ');
                cout << endl;
                cstmlib.printElement("", 120, '=');
            }
        }
    }

    void printSpecificHistory(Node* current_user) {
        if (head == NULL) {
            cout << "No Nodes in Singly Linked List" << endl;
        }
        else {
            Node* temp = head;
            cstmlib.printElement("", 120, '=');
            cout << endl;
            cstmlib.printElement("ID", 5, ' ');
            cstmlib.printElement("Transaction Type", 20, ' ');
            cstmlib.printElement("Date & Time", 25, ' ');
            cstmlib.printElement("Amount", 15, ' ');
            cstmlib.printElement("Prev. Amount", 20, ' ');
            cstmlib.printElement("Sender Number", 15, ' ');
            cstmlib.printElement("Receiver Number", 15, ' ');
            cout << '\n';
            while (temp != NULL) {
                if (current_user->getCardNum() == temp->getCardSender_history() || current_user->getCardNum() == temp->getCardReceiver_history() || current_user->getId() == temp->getOwnerId_history()) {
                    cstmlib.printElement(temp->getId(), 5, ' ');
                    cstmlib.printElement(temp->getHistoryType_history(), 20, ' ');
                    cstmlib.printElement(temp->getDate_history(), 25, ' ');
                    cstmlib.printElement(temp->getAmount_history(), 15, ' ');
                    cstmlib.printElement(temp->getPrevAmount_history(), 20, ' ');
                    cstmlib.printElement(temp->getCardSender_history(), 15, ' ');
                    cstmlib.printElement(temp->getCardReceiver_history(), 15, ' ');
                    cout << endl;
                }
                temp = temp->next;
            }
            cstmlib.printElement("", 120, '=');
        }
    }
};