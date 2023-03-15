#include <iostream>
#include "custlib.h"

using namespace std;

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

        if (userCard == "admin" && userPin == "admin123") {
            system("cls");
            ADMIN_MAIN();
        }

    }
}