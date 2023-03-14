#include <iostream>
#include <iomanip>

using namespace std;

extern int ADMIN_MAIN();

int main()
{
    /*while (true) {
        printElement("", 54, '#');
        cout << " \x1b[1mFORT BANK\x1b[0m ";
        printElement("", 53, '#');
        cout << '\n';
        string menu[] = { "" };

        string userCard;
        cout << "User Card: ";
        cin >> userCard;
    }*/
    ADMIN_MAIN();
}