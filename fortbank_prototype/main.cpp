#include <iostream>
#include <regex>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"
#include "custlib.h"

using namespace std;

SQL_CONNECTOR db_connect;
SinglyLinkedList userList;
SinglyLinkedList historyList;
custlib cstmlib;

regex input_regex("(?:\\d*\\.)?\\d+");

extern int ADMIN_MAIN();
extern int CLIENT_MAIN(Node* User);

int main()
{
    if (userList.nodeExists(1) == NULL) {
        db_connect.connect();
    }
    while (true) {
        cstmlib.printElement("", 54, '#');
        cout << " \x1b[1mFORT BANK\x1b[0m ";
        cstmlib.printElement("", 53, '#');
        cout << '\n';
        string menu[] = { "" };

        string userCard;
        cout << "User Card: ";
        cin >> userCard;

        string userPin;
        cout << "User Pin: ";
        cin >> userPin;

        if (userCard == "admin" && userPin == "admin123") {
            system("cls");
            ADMIN_MAIN();
        }
        else if (regex_match(userCard, input_regex) && regex_match(userPin, input_regex)) {
            if (userList.validate(stoi(userCard), stoi(userPin))) {
                Node* User = new Node();

                User->setId(userList.validate(stoi(userCard), stoi(userPin))->getId());
                User->setName(userList.validate(stoi(userCard), stoi(userPin))->getName());
                User->setEmail(userList.validate(stoi(userCard), stoi(userPin))->getEmail());
                User->setCardNum(userList.validate(stoi(userCard), stoi(userPin))->getCardNum());
                User->setCardPin(userList.validate(stoi(userCard), stoi(userPin))->getCardPin());
                User->setBalance(userList.validate(stoi(userCard), stoi(userPin))->getBalance());

                CLIENT_MAIN(User);
            }
            else {
                system("cls");
                cout << "Account does not exist!\n";
            }
        }
        else {
            system("cls");
            cout << "Account does not exist!\n";
        }
    }
}