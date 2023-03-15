#include <iostream>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"
#include "custlib.h"

using namespace std;

SQL_CONNECTOR db_connect;
SinglyLinkedList sll;
custlib cstmlib;

extern int ADMIN_MAIN();

int main()
{
    if (sll.nodeExists("1") == NULL) {
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

        if (sll.validate(userCard, userPin)) {
            sll.printSpecific(sll.validate(userCard, userPin)->getId());
        }
        else {
            cout << "Account does not exist!";
        }

        if (userCard == "admin" && userPin == "admin123") {
            system("cls");
            ADMIN_MAIN();
        }

    }
}