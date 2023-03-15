#pragma once
#include<iostream>

using namespace std;

template<typename T> void printElement(T t, const int& width, char fill)
{
    cout << left << setw(width) << setfill(fill) << t;
}

class Node {
    string id;
    string owner_name;
    string email;
    string card_num;
    string card_pin;
    string balance;
public:
    void setId(string x) {
        this->id = x;
    }
    string getId() {
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
    void setBalance(string x) {
        this->balance = x;
    }
    string getBalance() {
        return this->balance;
    }

    Node* next;

    Node() {
        id = "";
        owner_name = "";
        email = "";
        card_num = "";
        card_pin = "";
        balance = "";
        next = NULL;
    }
    Node(string temp_id, string temp_owner_name, string temp_email, string temp_card_num, string temp_card_pin, string temp_balance) {
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
    Node* nodeExists(string temp_id) {
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

    // 2. Append a node to the list
    void appendNode(Node* n) {
        if (nodeExists(n->getId()) != NULL) {
            cout << "Node Already exists with key value : " << n->getId() << ". Append another node with different Key value" << endl;
        }
        else {
            if (head == NULL) {
                head = n;
                cout << "Node Appended" << endl;
            }
            else {
                Node* ptr = head;
                while (ptr->next != NULL) {
                    ptr = ptr->next;
                }
                ptr->next = n;
                if (n->getId() == "") {
                    n->setId(to_string(stoi(ptr->getId()) + 1));
                }
                cout << "Node Appended" << endl;
            }
        }

    }
    // 3. Prepend Node - Attach a node at the start
    void prependNode(Node* n) {
        if (nodeExists(n->getId()) != NULL) {
            cout << "Node Already exists with key value : " << n->getId() << ". Append another node with different Key value" << endl;
        }
        else {
            n->next = head;
            head = n;
            cout << "Node Prepended" << endl;
        }
    }

    // 4. Insert a Node after a particular node in the list
    void insertNodeAfter(string temp_id, Node* n) {
        Node* ptr = nodeExists(temp_id);
        if (ptr == NULL) {
            cout << "No node exists with key value: " << temp_id << endl;
        }
        else {
            if (nodeExists(n->getId()) != NULL) {
                cout << "Node Already exists with key value : " << n->getId() << ". Append another node with different Key value" << endl;
            }
            else {
                n->next = ptr->next;
                ptr->next = n;
                cout << "Node Inserted" << endl;
            }
        }
    }

    // 5. Delete node by unique key
    void deleteNodeByKey(string temp_id) {
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
    void updateNodeByKey(string temp_id, string temp_owner_name, string temp_email, string temp_card_pin, string temp_balance) {

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

    }

    // 7th printing
    void printList() {
        if (head == NULL) {
            cout << "No Nodes in Singly Linked List";
        }
        else {
            printElement("", 120, '=');
            cout << '\n';
            printElement("ID", 5, ' ');
            printElement("Name", 20, ' ');
            printElement("Email", 30, ' ');
            printElement("Card Num", 20, ' ');
            printElement("Card Pin", 20, ' ');
            printElement("Balance", 20, ' ');
            cout << '\n';
            Node* temp = head;

            while (temp != NULL) {
                printElement(temp->getId(), 5, ' ');
                printElement(temp->getName(), 20, ' ');
                printElement(temp->getEmail(), 30, ' ');
                printElement(temp->getCardNum(), 20, ' ');
                printElement(temp->getCardPin(), 20, ' ');
                cout << "P ";
                printElement(temp->getBalance(), 0, ' ');
                cout << '\n';
                temp = temp->next;
            }
            printElement("", 120, '=');
        }

    }

    // 8th printing specific
    Node* selectSpecific(string temp_id) {
        if (head == NULL) {
            cout << "No Nodes in Singly Linked List";
        }
        else {
            Node* ptr = nodeExists(temp_id);
            if (ptr != NULL) {
                return ptr;
            }
            else {
                return NULL;
            }
        }
    }

    void printSpecific(string temp_id) {
        if (head == NULL) {
            cout << "No Nodes in Singly Linked List";
        }
        else {
            Node* ptr = nodeExists(temp_id);
            if (ptr != NULL) {
                printElement("", 120, '=');
                cout << '\n';
                printElement("ID", 5, ' ');
                printElement("Name", 20, ' ');
                printElement("Email", 30, ' ');
                printElement("Card Num", 20, ' ');
                printElement("Card Pin", 20, ' ');
                printElement("Balance", 20, ' ');
                cout << '\n';
                printElement(ptr->getId(), 5, ' ');
                printElement(ptr->getName(), 20, ' ');
                printElement(ptr->getEmail(), 30, ' ');
                printElement(ptr->getCardNum(), 20, ' ');
                printElement(ptr->getCardPin(), 20, ' ');
                cout << "P ";
                printElement(ptr->getBalance(), 0, ' ');
                cout << '\n';
                printElement("", 120, '=');
            }
        }
    }
};