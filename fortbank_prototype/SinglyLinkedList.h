#pragma once
#include<iostream>

using namespace std;

class Node {
public:
    string id;
    string owner_name;
    string email;
    string balance;
    string card_num;
    string card_pin;

    Node* next;

    Node() {
        id = "";
        owner_name = "";
        email = "";
        balance = "";
        card_num = "";
        card_pin = "";
        next = NULL;
    }
    Node(string temp_id, string temp_owner_name, string temp_email, string temp_balance, string temp_card_num, string temp_card_pin) {
        id = temp_id;
        owner_name = temp_owner_name;
        email = temp_email;
        balance = temp_balance;
        card_num = temp_card_num;
        card_pin = temp_card_pin;
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
            if (ptr->id == temp_id) {
                temp = ptr;
            }
            ptr = ptr->next;

        }
        return temp;
    }

    // 2. Append a node to the list
    void appendNode(Node* n) {
        if (nodeExists(n->id) != NULL) {
            cout << "Node Already exists with key value : " << n->id << ". Append another node with different Key value" << endl;
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
                cout << "Node Appended" << endl;
            }
        }

    }
    // 3. Prepend Node - Attach a node at the start
    void prependNode(Node* n) {
        if (nodeExists(n->id) != NULL) {
            cout << "Node Already exists with key value : " << n->id << ". Append another node with different Key value" << endl;
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
            if (nodeExists(n->id) != NULL) {
                cout << "Node Already exists with key value : " << n->id << ". Append another node with different Key value" << endl;
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
            if (head->id == temp_id) {
                head = head->next;
                cout << "Node UNLINKED with keys value : " << temp_id << endl;
            }
            else {
                Node* temp = NULL;
                Node* prevptr = head;
                Node* currentptr = head->next;
                while (currentptr != NULL) {
                    if (currentptr->id == temp_id) {
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
    void updateNodeByKey(string temp_id, string temp_owner_name, string temp_email, string temp_balance, string temp_card_num, string temp_card_pin) {

        Node* ptr = nodeExists(temp_id);
        if (ptr != NULL) {
            ptr->owner_name = temp_owner_name;
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
            cout << endl << "Singly Linked List Values : ";
            Node* temp = head;

            while (temp != NULL) {
                cout << "(" << temp->id << "," << temp->owner_name << ") --> ";
                temp = temp->next;
            }
        }

    }

};

int main() {

    SinglyLinkedList s;
    int option;
    string temp_id, k1, temp_owner_name, temp_email, temp_balance, temp_card_num, temp_card_pin;
    do {
        cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
        cout << "1. appendNode()" << endl;
        cout << "2. prependNode()" << endl;
        cout << "3. insertNodeAfter()" << endl;
        cout << "4. deleteNodeByKey()" << endl;
        cout << "5. updateNodeByKey()" << endl;
        cout << "6. print()" << endl;
        cout << "7. Clear Screen" << endl << endl;

        cin >> option;
        Node* n1 = new Node();
        //Node n1;

        switch (option) {
        case 0:
            break;
        case 1:
            cout << "Append Node Operation \nEnter key & data of the Node to be Appended" << endl;
            cin >> temp_id;
            cin >> temp_owner_name;
            cin >> temp_email;
            cin >> temp_balance;
            cin >> temp_card_num;
            cin >> temp_card_pin;
            n1->id = temp_id;
            n1->owner_name = temp_owner_name;
            n1->email = temp_email;
            n1->balance = temp_balance;
            n1->card_num = temp_card_num;
            n1->card_pin = temp_card_pin;
            s.appendNode(n1);
            //cout<<n1.key<<" = "<<n1.data<<endl;
            break;

        case 2:
            cout << "Prepend Node Operation \nEnter key & data of the Node to be Prepended" << endl;
            cin >> temp_id;
            cin >> temp_owner_name;
            cin >> temp_email;
            cin >> temp_balance;
            cin >> temp_card_num;
            cin >> temp_card_pin;
            n1->id = temp_id;
            n1->owner_name = temp_owner_name;
            n1->email = temp_email;
            n1->balance = temp_balance;
            n1->card_num = temp_card_num;
            n1->card_pin = temp_card_pin;
            s.prependNode(n1);
            break;

        case 3:
            cout << "Insert Node After Operation \nEnter key of existing Node after which you want to Insert this New node: " << endl;
            cin >> k1;
            cout << "Enter key & data of the New Node first: " << endl;
            cin >> temp_id;
            cin >> temp_owner_name;
            cin >> temp_email;
            cin >> temp_balance;
            cin >> temp_card_num;
            cin >> temp_card_pin;
            n1->id = temp_id;
            n1->owner_name = temp_owner_name;
            n1->email = temp_email;
            n1->balance = temp_balance;
            n1->card_num = temp_card_num;
            n1->card_pin = temp_card_pin;

            s.insertNodeAfter(k1, n1);
            break;

        case 4:

            cout << "Delete Node By Key Operation - \nEnter key of the Node to be deleted: " << endl;
            cin >> k1;
            s.deleteNodeByKey(k1);

            break;
        case 5:
            cout << "Update Node By Key Operation - \nEnter key & NEW data to be updated" << endl;
            cin >> temp_id;
            cin >> temp_owner_name;
            cin >> temp_email;
            cin >> temp_balance;
            cin >> temp_card_num;
            cin >> temp_card_pin;
            n1->id = temp_id;
            n1->owner_name = temp_owner_name;
            n1->email = temp_email;
            n1->balance = temp_balance;
            n1->card_num = temp_card_num;
            n1->card_pin = temp_card_pin;
            s.updateNodeByKey(temp_id, temp_owner_name, temp_email, temp_balance, temp_card_num, temp_card_pin);

            break;
        case 6:
            s.printList();

            break;
        case 7:
            system("cls");
            break;
        default:
            cout << "Enter Proper Option number " << endl;
        }

    } while (option != 0);

    return 0;
}