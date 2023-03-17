#include <iostream>
#include <sstream>
#include "SinglyLinkedList.h"
using namespace std;

Node* current_user = new Node();
extern SinglyLinkedList sll;

extern int main();
void DEPOSIT();
void WITHDRAW();
void TRANSFER();
void LOAN();

int CLIENT_MAIN(Node* loggedin_user) {
	while (true) {
		current_user = loggedin_user;

		sll.printSpecific(loggedin_user->getId());
		
		string menu[] = { "Logout", "Deposit", "Withdraw", "Transfer", "Loan" };
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
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
	return 0;
}

void DEPOSIT() {
	system("cls");
	cout << current_user->getBalance() << endl;

	int temp_input;
	cout << "Deposit: ";
	cin >> temp_input;
	if (temp_input != NULL) {
		current_user->setBalance(current_user->getBalance() + to_string(temp_input));
		sll.updateNodeByKey(current_user->getId(), current_user->getEmail(), current_user->getName(), current_user->getCardPin(), current_user->getBalance());
	}
	else {
		cout << "Invalid input!";
	}
}

void WITHDRAW() {

}

void TRANSFER() {

}

void LOAN() {

}