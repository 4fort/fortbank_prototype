#include <iostream>
#include <iomanip>

using namespace std;


template<typename T> void printElement(T t, const int& width, char fill)
{
    cout << left << setw(width) << setfill(fill) << t;
}

extern void SQL_CONNECT(string temp_id);
extern string USER_GET(string temp_id, int inp);
extern void QUERY_CMD(string query);
extern void USER_ADD();
extern void USER_UPDATE();
extern void USER_DELETE();
extern void RETURNTO_MENU();

int main()
{
    while (true) {
        printElement("", 54, '#');
        cout << " \x1b[1mADMIN PANEL\x1b[0m ";
        printElement("", 53, '#');
        cout << '\n';
        SQL_CONNECT("");
        cout << "\n";
        string crud[] = { "EXIT", "ADD USER", "UPDATE USER", "DELETE USER" };
        int crudlength = sizeof(crud) / sizeof(crud[0]);
        for (int i = 0; i < crudlength; i++) {
            cout << "[" << i << "] " << crud[i] << '\n';
        }

        int choice;
        cout << "admin/# ";
        cin >> choice;
        system("cls");
        cout << "\x1b[1m[ !r ]\x1b[0m return to menu\n\n";
        if (choice == 0) {
            system("cls");
            cout << "Thanks for using fortbank!";
            return 0;
        }
        else if (choice == 1) {
            USER_ADD();
        }
        else if (choice == 2) {
            USER_UPDATE();
        }
        else if (choice == 3) {
            USER_DELETE();
        }
        /*else if (choice == 4) {
            cout << USER_GET("7", 1) << '\n';
            system("pause");
        }*/
        system("cls");
    }
}