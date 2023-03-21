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
void selectedUsertoUpdate(int id);
int cardNumGenerator();

int ADMIN_MAIN() {
    while (true) {
        cstmlib.printElement("", 54, '#');
        cout << " \x1b[1mADMIN PANEL\x1b[0m ";
        cstmlib.printElement("", 53, '#');
        cout << '\n';
        sll.printList();

        cout << "\n";
        string crud[] = { "LOGOUT", "ADD USER", "UPDATE USER", "DELETE USER"};
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
            cout << "Type [ !r ] to return to menu.";
            USER_ADD();
            break;
        case 2:
            USER_UPDATE();
            break;
        case 3:
            cout << "Type [ !r ] to return to menu.";
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
    if (find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()) {
        cout << "Input should be a number!";
    }
    else if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    sll_user->setBalance(stod(temp_input));

    int cardNum = cardNumGenerator();
    while (sll.nodeExistByCard(cardNum) != NULL) {
        cardNum = cardNumGenerator();
    }
    sll_user->setCardNum(cardNum);
    sll_user->setCardPin(1234);

    db_connect.Insert(sll_user);
    cout << "test";
    sll.appendNode(sll_user);
}

void USER_UPDATE() {
    string temp_input, tips = "Type [ !r ] to return to menu.";

    system("cls");
    cout << "[ " << tips << " ]" << endl;
    sll.printList();
    cout << "Select ID: ";
    cin >> temp_input;

    if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    else if(find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()) {
        selectedUsertoUpdate(stoi(temp_input));
    }
    USER_UPDATE();
}

void selectedUsertoUpdate(int id) {
    Node* user = sll.nodeExists(id);
    string menu[] = { "Return", "Name", "Email", "Pin", "Add Balance", "Minus Balance", "Set Balance"};
    string temp_input, tips;

    if (user != NULL) {
        while (true) {
            system("cls");
            cout << "[ " << tips << " ]" << endl;
            sll.printSpecific(id);
            for (int i = 0; i < (sizeof(menu) / sizeof(menu[0])); i++) {
                cout << "[" << i << "] " << menu[i] << '\n';
            }
            int choice;
            cout << "Select -> ";
            cin >> choice;
            switch (choice)
            {
            case 0:
                USER_UPDATE();
            case 1:
                cout << "Old Name [ " << user->getName() << " ]" << endl;
                cout << "New Name: ";
                cin.ignore();
                getline(cin, temp_input);
                if (temp_input == "") {
                    break;
                }
                user->setName(temp_input);
                break;
            case 2:
                cout << "Old Email [ " << user->getEmail() << " ]" << endl;
                cout << "New Email: ";
                cin.ignore();
                getline(cin, temp_input);
                if (temp_input == "") {
                    break;
                }
                user->setEmail(temp_input);
                break;
            case 3:
                cout << "Old Pin [ " << user->getCardPin() << " ]" << endl;
                cout << "New Pin: ";
                cin.ignore();
                getline(cin, temp_input);
                if (temp_input == "") {
                    break;
                }
                if (find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()) {
                    user->setCardPin(stoi(temp_input));
                    tips = "";
                }
                else {
                    tips = "Input should be a number!";
                }
                break;
            case 4:
                cout << "Old Balance [ P " << user->getBalance() << " ]" << endl;
                cout << "Add Balance: ";
                cin.ignore();
                getline(cin, temp_input);
                if (temp_input == "") {
                    break;
                }
                if(find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()){
                    user->setBalance(user->getBalance() + stod(temp_input));
                    tips = "";
                }
                else {
                    tips = "Input should be a number!";
                }
                break;
            case 5:
                cout << "Old Balance [ P " << user->getBalance() << " ]" << endl;
                cout << "Minus Balance: ";
                cin.ignore();
                getline(cin, temp_input);
                if (temp_input == "") {
                    break;
                }
                if(find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()){
                    user->setBalance(user->getBalance() - stod(temp_input));
                    tips = "";
                }
                else {
                    tips = "Input should be a number!";
                }
                break;
            case 6:
                cout << "Old Balance [ P " << user->getBalance() << " ]" << endl;
                cout << "Set Balance: ";
                cin.ignore();
                getline(cin, temp_input);
                if (temp_input == "") {
                    break;
                }
                if (find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()) {
                    user->setBalance(stod(temp_input));
                    tips = "";
                }
                else {
                    tips = "Input should be a number!";
                }
                break;
            default:
                USER_UPDATE();
            }
            db_connect.Update(user);
            sll.updateNode(user);
        }
    }
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
    else if(find_if(temp_input.begin(), temp_input.end(), isdigit) != temp_input.end()) {
        sll.deleteNodeByKey(stoi(temp_input));
        db_connect.Delete(temp_input);
    }
}

void RETURNTO_MENU() {
    system("cls");
    ADMIN_MAIN();
}

int cardNumGenerator() {
    srand(time(0));
    char randomizer;
    string random_card = "456";
    for (int i = 0; i < 3; i++) {
        randomizer = rand() % (57 - 49 + 1) + 49;
        random_card = random_card + randomizer;
    }
    return stoi(random_card);
}