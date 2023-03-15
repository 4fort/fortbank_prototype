#include <iostream>
#include <mysql.h>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"
#include "custlib.h"

using namespace std;

extern SQL_CONNECTOR db_connect;
extern SinglyLinkedList sll;
extern custlib cstmlib;

extern int main();
void USER_ADD();
void USER_UPDATE();
void USER_DELETE();
void RETURNTO_MENU();

string cardNumGenerator();

int ADMIN_MAIN() {
    while (true) {
        cstmlib.printElement("", 54, '#');
        cout << " \x1b[1mADMIN PANEL\x1b[0m ";
        cstmlib.printElement("", 53, '#');
        cout << '\n';
        sll.printList();

        cout << "\n";
        string crud[] = { "EXIT", "ADD USER", "UPDATE USER", "DELETE USER"};
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
            main();
            break;
        case 1:
            cout << "\x1b[1m[ !r ]\x1b[0m return to menu\n\n";
            USER_ADD();
            break;
        case 2:
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
    Node* sll_user = new Node();
    string temp_input;

    //db_connect.connect();
    sll.printList();
    //db_connect.print("");

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    sll_user->setName(temp_input);

    cout << "Enter Email: ";
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    sll_user->setEmail(temp_input);

    cout << "Enter Balance: ";
    cin >> temp_input;
    cin.ignore();
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    sll_user->setBalance(temp_input);

    sll_user->setCardNum(cardNumGenerator());
    sll_user->setCardPin("1234");

    sll.appendNode(sll_user);
    db_connect.Insert(sll_user->getName(), sll_user->getEmail(), sll_user->getCardNum(), sll_user->getCardPin(), sll_user->getBalance());
}

void USER_UPDATE() {
    Node* sll_user = new Node();
    string temp_input;
    string temp_id;
    system("cls");
    cout << "\x1b[1m[ !r ]\x1b[0m return to menu\n\n";
    //db_connect.connect();
    sll.printList();

    cout << "Select ID\nadmin/# ";
    cin >> temp_id;
    if (temp_id == "") {
        USER_UPDATE();
    }
    else if (sll.selectSpecific(temp_id) == NULL) {
        USER_UPDATE();
    }
    else if (temp_id == "!r") {
        RETURNTO_MENU();
    }

    system("cls");
    cout << "TIP: You can press \x1b[1mRETURN\x1b[0m [ <-| ] to skip or use default value.\n";
    //db_connect.print(temp_id);
    sll.printSpecific(temp_id);

    cout << "Enter Updated Name: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input.empty()) {
        //temp_input = db_connect.selectSpecific(temp_id, 1);
        temp_input = sll.selectSpecific(temp_id)->getName();
    }
    else if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    sll_user->setName(temp_input);

    cout << "Enter Updated Email: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        //temp_input = db_connect.selectSpecific(temp_id, 2);
        temp_input = sll.selectSpecific(temp_id)->getEmail();
    }
    sll_user->setEmail(temp_input);

    cout << "Enter Updated Balance: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        //temp_input = db_connect.selectSpecific(temp_id, 3);
        temp_input = sll.selectSpecific(temp_id)->getBalance();
    }
    sll_user->setBalance(temp_input);

    cout << "Enter New Pin: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        //temp_input = db_connect.selectSpecific(temp_id, 4);
        temp_input = sll.selectSpecific(temp_id)->getCardPin();
    }
    sll_user->setCardPin(temp_input);

    sll.updateNodeByKey(temp_id, sll_user->getName(), sll_user->getEmail(), sll_user->getCardPin(), sll_user->getBalance());
    db_connect.Update(temp_id, sll_user->getName(), sll_user->getEmail(), sll_user->getCardPin(), sll_user->getBalance());
}

void USER_DELETE() {
    //db_connect.connect();
    sll.printList();

    string temp_input;
    cout << "Enter ID: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }

    sll.deleteNodeByKey(temp_input);
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