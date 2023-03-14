#include <iostream>
#include <mysql.h>
#include <time.h>
#include <sstream>
#include <iomanip>
#include "User.h"
#include "SQL_CONNECTOR.h"
using namespace std;

SQL_CONNECTOR db_connect;

extern int main();
void USER_ADD();
void USER_UPDATE();
void USER_DELETE();
void RETURNTO_MENU();

string cardNumGenerator();

int ADMIN_MAIN() {
    while (true) {
        printElement("", 54, '#');
        cout << " \x1b[1mADMIN PANEL\x1b[0m ";
        printElement("", 53, '#');
        cout << '\n';
        db_connect.connect();
        cout << "\n";
        string crud[] = { "EXIT", "ADD USER", "UPDATE USER", "DELETE USER", "SAVE CHANGES"};
        int crudlength = sizeof(crud) / sizeof(crud[0]);
        for (int i = 0; i < crudlength; i++) {
            cout << "[" << i << "] " << crud[i] << '\n';
        }

        int choice;
        cout << "admin/# ";
        cin >> choice;
        system("cls");
        switch (choice) {
        case 0:
            system("cls");
            cout << "Thanks for using fortbank!";
            exit(0);
            break;
        case 1:
            cout << "\x1b[1m[ !r ]\x1b[0m return to menu\n\n";
            USER_ADD();
            break;
        case 2:
            cout << "\x1b[1m[ !r ]\x1b[0m return to menu\n\n";
            USER_UPDATE();
            break;
        case 3:
            cout << "\x1b[1m[ !r ]\x1b[0m return to menu\n\n";
            USER_DELETE();
            break;
        default:
            ADMIN_MAIN();
            break;
        }
        system("cls");
    }
    return 0;
}

void USER_ADD() {
    User user;
    string temp_input;

    db_connect.connect();

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    user.setName(temp_input);

    cout << "Enter Email: ";
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    user.setEmail(temp_input);

    cout << "Enter Balance: ";
    cin >> temp_input;
    cin.ignore();
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    user.setBalance(temp_input);

    user.setCardNum(cardNumGenerator());
    user.setCardPin("1234");
    
    db_connect.Insert(user.getName(), user.getEmail(), user.getCardNum(), user.getCardPin(), user.getBalance());
}

void USER_UPDATE() {
    User user;
    string temp_input;
    string temp_id;

    db_connect.connect();

    cout << "Select ID\nadmin/# ";
    cin.ignore();
    getline(cin, temp_id);
    if (temp_id == "") {
        system("cls");
        USER_UPDATE();
    }
    else if (temp_id == "!r") {
        RETURNTO_MENU();
    }

    system("cls");
    cout << "TIP: You can press \x1b[1mRETURN\x1b[0m [ <-| ] to skip or use default value.\n";
    db_connect.print(temp_id);


    cout << "Enter Updated Name: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 1);
    }
    else if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    user.setName(temp_input);

    cout << "Enter Updated Email: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 2);
    }
    user.setEmail(temp_input);

    cout << "Enter Updated Balance: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 3);
    }
    user.setBalance(temp_input);

    cout << "Enter New Pin: ";
    cin >> temp_input;
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 4);
    }
    user.setCardPin(temp_input);

    db_connect.Update(temp_id, user.getName(), user.getEmail(), user.getCardPin(), user.getBalance());
}

void USER_DELETE() {
    db_connect.connect();

    string temp_input;
    cout << "Enter ID: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }

    db_connect.Delete(temp_input);
}

void RETURNTO_MENU() {
    system("cls");
    ADMIN_MAIN();
}

string cardNumGenerator() {
    srand(time(0));
    char randomizer;
    string random_card = "456";
    for (int i = 0; i < 3; i++) {
        randomizer = rand() % (57 - 49 + 1) + 49;
        random_card = random_card + randomizer;
    }
    return random_card;
}

void printList() {

}