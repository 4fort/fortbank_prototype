#include <iostream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"
using namespace std;

Node* current_user = new Node();
extern SQL_CONNECTOR db_connect;
extern SinglyLinkedList sll;

extern int main();
void DEPOSIT();
void WITHDRAW();
void TRANSFER();
void CHANGE_PIN();

void coord(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int CLIENT_MAIN(Node* loggedin_user) {
	while (true) {
		current_user = loggedin_user;

		system("cls");

		cout << char(201);      for (int i = 0; i < 21; i++) { cout << char(205); }      cout << char(187) << endl;
		cout << char(186) << "                     " << char(186) << endl;
		cout << char(186) << "                     " << char(186) << endl;
		cout << char(186) << "      FORT BANK      " << char(186) << endl;
		cout << char(186) << "                     " << char(186) << endl;
		cout << char(186) << "                     " << char(186) << endl;
		cout << char(200);      for (int i = 0; i < 21; i++) { cout << char(205); }      cout << char(188) << endl;

		sll.printSpecific(loggedin_user->getId());
		
		string menu[] = { "Logout", "Deposit", "Withdraw", "Transfer", "Change Pin" };
		for (int i = 0; i < (sizeof(menu) / sizeof(menu[0])); i++) {
			cout << "[" << i << "] " << menu[i] << '\n';
		}

		int choice;
		cout << "select -> ";
		cin >> choice;
		switch (choice)
		{
		case 0:
			system("cls");
			main();
			break;
		case 1:
			DEPOSIT();
			break;
		case 2:
			WITHDRAW();
			break;
		case 3:
			TRANSFER();
			break;
		case 4:
			CHANGE_PIN();
			break;
		default:
			break;
		}
	}
	return 0;
}

void DEPOSIT() {
	cout << current_user->getBalance() << endl;

	int temp_input;
	cout << "Deposit: ";
	cin >> temp_input;
	if (temp_input != NULL) {
		current_user->setBalance(to_string(stod(current_user->getBalance()) + temp_input));
		sll.updateNode(current_user);
		db_connect.Update(current_user);
	}
	else {
		cout << "Invalid input!";
	}
}

void WITHDRAW() {
	cout << current_user->getBalance() << endl;

	int temp_input;
	cout << "Withdraw: ";
	cin >> temp_input;
	if (temp_input != NULL) {
		if (stod(current_user->getBalance()) > temp_input) {
			current_user->setBalance(to_string(stod(current_user->getBalance()) - temp_input));
			sll.updateNode(current_user);
			db_connect.Update(current_user);
		}
		else {
			cout << "Not enough Balance!";
		}
	}
	else {
		cout << "Invalid input!";
	}
}

void TRANSFER() {
	cout << current_user->getBalance() << endl;

	int temp_input;
	string receiver_card;

	cout << "Receiver Card Number: ";
	cin >> receiver_card;
	Node* receiver = sll.nodeExistByCard(receiver_card);
	if (receiver != NULL) {
		cout << "Transfer Amount: ";
		cin >> temp_input;
		if (temp_input != NULL) {
			if (stod(current_user->getBalance()) > temp_input) {
				current_user->setBalance(to_string(stod(current_user->getBalance()) - temp_input));
				sll.updateNode(current_user);
				db_connect.Update(current_user);

				receiver->setBalance(to_string(stod(receiver->getBalance()) + temp_input));
				sll.updateNode(receiver);
				db_connect.Update(receiver);
			}
			else {
				cout << "Not enough Balance!";
			}
		}
		else {
			cout << "Invalid input!";
		}
	}
	else {
		cout << "User does not exist!";
		return;
	}
}

void CHANGE_PIN() {

}