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
            Node* User = new Node();

            User->setId(sll.validate(userCard, userPin)->getId());
            User->setName(sll.validate(userCard, userPin)->getName());
            User->setEmail(sll.validate(userCard, userPin)->getEmail());
            User->setCardNum(sll.validate(userCard, userPin)->getCardNum());
            User->setCardPin(sll.validate(userCard, userPin)->getCardPin());
            User->setBalance(sll.validate(userCard, userPin)->getBalance());

            CLIENT_MAIN(User);
        }
        else if (userCard == "admin" && userPin == "admin123") {
            system("cls");
            ADMIN_MAIN();
        }
        else {
            system("cls");
            cout << "Account does not exist!\n";
        }
    }
}