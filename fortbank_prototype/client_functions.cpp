#include <iostream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include "SQL_CONNECTOR.h"
#include "SinglyLinkedList.h"
using namespace std;

Node* current_user = new Node();
extern SQL_CONNECTOR db_connect;
extern SinglyLinkedList userList;
extern SinglyLinkedList historyList;

extern int main();
void DEPOSIT();
void WITHDRAW();
void TRANSFER();
void CHANGE_PIN();
void TRANSACTION_HISTORY();
void transaction_handler(int owner_id, string type, double amount, double prev_amount, bool isReceiver, int receiver_cardNum);

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

		cout << "\t\t\t\t\t\t" << char(201);      for (int i = 0; i < 21; i++) { cout << char(205); }      cout << char(187) << endl;
		cout << "\t\t\t\t\t\t" << char(186) << "                     " << char(186) << endl;
		cout << "\t\t\t\t\t\t" << char(186) << "                     " << char(186) << endl;
		cout << "\t\t\t\t\t\t" << char(186) << "      FORT BANK      " << char(186) << endl;
		cout << "\t\t\t\t\t\t" << char(186) << "                     " << char(186) << endl;
		cout << "\t\t\t\t\t\t" << char(186) << "                     " << char(186) << endl;
		cout << "\t\t\t\t\t\t" << char(200);      for (int i = 0; i < 21; i++) { cout << char(205); }      cout << char(188) << endl;

		userList.printSpecific(current_user->getId());
		
		string menu[] = { "Logout", "Deposit", "Withdraw", "Transfer", "Change Pin", "Transaction History"};
		for (int i = 0; i < (sizeof(menu) / sizeof(menu[0])); i++) {
			cout << "[" << i << "] " << menu[i] << '\n';
		}

		string choice;
		cout << "select -> ";
		cin >> choice;
		if (regex_match(choice, input_regex)) {
			switch (stoi(choice))
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
			case 5:
				TRANSACTION_HISTORY();
			default:
				break;
			}
		}
	}
	return 0;
}

void DEPOSIT() {
	cout << current_user->getBalance() << endl;

	string temp_input;
	cout << "Deposit: ";
	cin >> temp_input;
	if (regex_match(temp_input, input_regex)) {
		transaction_handler(current_user->getId(), "deposit", stod(temp_input), current_user->getBalance(), NULL, NULL);

		current_user->setBalance(current_user->getBalance() + stod(temp_input));
		userList.updateNode(current_user);
		db_connect.Update(current_user);
	}
	else if (temp_input == "!r") {
		return;
	}
	else {
		DEPOSIT();
	}
}

void WITHDRAW() {
	cout << current_user->getBalance() << endl;

	string temp_input;
	cout << "Withdraw: ";
	cin >> temp_input;
	if (regex_match(temp_input, input_regex)) {
		if (current_user->getBalance() > stod(temp_input)) {
			transaction_handler(current_user->getId(), "withdraw", stod(temp_input), current_user->getBalance(), NULL, NULL);

			current_user->setBalance(current_user->getBalance() - stod(temp_input));
			userList.updateNode(current_user);
			db_connect.Update(current_user);
		}
		else {
			cout << "Not enough Balance!";
		}
	}
	else if (temp_input == "!r") {
		return;
	}
	else {
		WITHDRAW();
	}
}

void TRANSFER() {
	cout << current_user->getBalance() << endl;

	string temp_input;
	string receiver_card;
	Node* receiver = NULL;

	cout << "Receiver Card Number: ";
	cin >> receiver_card;
	if (regex_match(receiver_card, input_regex)) {
		if(userList.nodeExistByCard(stoi(receiver_card))) receiver = userList.nodeExistByCard(stoi(receiver_card));
		cout << "Transfer Amount: ";
		cin >> temp_input;
		if (receiver != NULL) {
			if (current_user->getBalance() > stod(temp_input) && current_user->getCardNum() != receiver->getCardNum()) {
				if (regex_match(temp_input, input_regex)) {
					transaction_handler(current_user->getId(), "transfer", stod(temp_input), current_user->getBalance(), false, receiver->getCardNum());
					current_user->setBalance(current_user->getBalance() - stod(temp_input));
					userList.updateNode(current_user);
					db_connect.Update(current_user);

					transaction_handler(receiver->getId(), "transfer", stod(temp_input), receiver->getBalance(), true, receiver->getCardNum());
					receiver->setBalance(receiver->getBalance() + stod(temp_input));
					userList.updateNode(receiver);
					db_connect.Update(receiver);
				}
			}
			else {
				cout << "Not enough Balance!";
			}
		}
		else {
			cout << "Invalid input!";
			return;
		}
	}
	else if (temp_input == "!r") {
		return;
	}
	else {
		cout << "User does not exist!";
		return;
	}
}

void CHANGE_PIN() {
	cout << current_user->getCardPin() << endl;

	string temp_input;
	cout << "Enter new pin: ";
	cin >> temp_input;

	if (regex_match(temp_input, input_regex)) {
		current_user->setCardPin(stoi(temp_input));
		userList.updateNode(current_user);
		db_connect.Update(current_user);
	}
	else if (temp_input == "!r") {
		return;
	}
	else {
		cout << "Invalid input!";
	}
}

void TRANSACTION_HISTORY() {
	system("cls");
	historyList.printSpecificHistory(current_user);

	cout << endl << "[ !r ] Return\nPrint ID: ";
	string temp_input;
	cin >> temp_input;
	if (temp_input == "!r") {
		return;
	}
	else if (regex_match(temp_input, input_regex)) {
		// PRINT GIVEN ID
	}
	TRANSACTION_HISTORY();
}

void transaction_handler(int owner_id, string type, double amount, double prev_amount, bool isReceiver, int receiver_cardNum) {
	Node* temp_hist = new Node();
	temp_hist->setOwnerId_history(owner_id);
	temp_hist->setHistoryType_history(type);
	temp_hist->setAmount_history(amount);
	temp_hist->setPrevAmount_history(prev_amount);
	temp_hist->setIsReceiver_history(isReceiver);
	if (isReceiver != NULL) {
		temp_hist->setCardSender_history(current_user->getCardNum());
		temp_hist->setCardReceiver_history(receiver_cardNum);
	}

	historyList.appendNode(temp_hist);
}