#include <iostream>
#include <iomanip>

using namespace std;

template<typename T> void printElement(T t, const int& width, char fill)
{
    cout << left << setw(width) << setfill(fill) << t;
}

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