#include <iostream>
#include <mysql.h>
#include <time.h>
#include <sstream>
#include <iomanip>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"

using namespace std;

SQL_CONNECTOR db_connect;
SinglyLinkedList ssl;

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
    Node* ssl_user = new Node();
    string temp_input;

    //db_connect.connect();
    ssl.printList();

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    ssl_user->setName(temp_input);

    cout << "Enter Email: ";
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    ssl_user->setEmail(temp_input);

    cout << "Enter Balance: ";
    cin >> temp_input;
    cin.ignore();
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    ssl_user->setBalance(temp_input);

    ssl_user->setCardNum(cardNumGenerator());
    ssl_user->setCardPin("1234");

    ssl.appendNode(ssl_user);
    //db_connect.Insert(user.getName(), user.getEmail(), user.getCardNum(), user.getCardPin(), user.getBalance());
}

void USER_UPDATE() {
    Node* ssl_user = new Node();
    string temp_input;
    string temp_id;

    //db_connect.connect();
    ssl.printList();

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
    ssl_user->setName(temp_input);

    cout << "Enter Updated Email: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 2);
    }
    ssl_user->setEmail(temp_input);

    cout << "Enter Updated Balance: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 3);
    }
    ssl_user->setBalance(temp_input);

    cout << "Enter New Pin: ";
    cin >> temp_input;
    if (temp_input.empty()) {
        temp_input = db_connect.selectSpecific(temp_id, 4);
    }
    ssl_user->setCardPin(temp_input);

    ssl.updateNodeByKey(temp_id, ssl_user->getName(), ssl_user->getEmail(), ssl_user->getCardPin(), ssl_user->getBalance());
    //db_connect.Update(temp_id, user.getName(), user.getEmail(), user.getCardPin(), user.getBalance());
}

void USER_DELETE() {
    //db_connect.connect();
    ssl.printList();

    string temp_input;
    cout << "Enter ID: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }

    ssl.deleteNodeByKey(temp_input);
    //db_connect.Delete(temp_input);
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