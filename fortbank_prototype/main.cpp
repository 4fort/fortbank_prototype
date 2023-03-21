#include <iostream>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"
#include "custlib.h"

using namespace std;

SQL_CONNECTOR db_connect;
SinglyLinkedList sll;
custlib cstmlib;

extern int ADMIN_MAIN();
extern int CLIENT_MAIN(Node* User);

int main()
{
    if (sll.nodeExists(1) == NULL) {
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
        else if (find_if(userCard.begin(), userCard.end(), isdigit) != userCard.end() || find_if(userPin.begin(), userPin.end(), isdigit) != userPin.end()) {
            if (sll.validate(stoi(userCard), stoi(userPin))) {
                Node* User = new Node();

                User->setId(sll.validate(stoi(userCard), stoi(userPin))->getId());
                User->setName(sll.validate(stoi(userCard), stoi(userPin))->getName());
                User->setEmail(sll.validate(stoi(userCard), stoi(userPin))->getEmail());
                User->setCardNum(sll.validate(stoi(userCard), stoi(userPin))->getCardNum());
                User->setCardPin(sll.validate(stoi(userCard), stoi(userPin))->getCardPin());
                User->setBalance(sll.validate(stoi(userCard), stoi(userPin))->getBalance());

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