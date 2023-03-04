#include <iostream>
#include <mysql.h>
#include <sstream>
using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

const char* host = "localhost";
const char* user = "root";
const char* passwd = "password123@";
const char* db = "fortbank";
const int port = 3306;

class User {
    string name;
    string email;
    string balance;

public:
    void setName(string x) {
        this->name = x;
    }
    string getName() {
        return this->name;
    }
    void setEmail(string x) {
        this->email = x;
    }
    string getEmail() {
        return this->email;
    }
    void setBalance(string x) {
        this->balance = x;
    }
    string getBalance() {
        return this->balance;
    }
};

void SQL_CONNECT(string temp_id) {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, host, user, passwd, db, port, NULL, 0);

    if (conn) {
        puts("Connected!");

        string query;
        if (temp_id != "") {
            query = "SELECT * FROM Users WHERE id = " + temp_id;
        }
        else {
            query = "SELECT * FROM Users";
        }
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                printf("\tID: %s\t\tName: %s\t\tEmail: %s\t\tbalance: %s\n", row[0], row[1], row[2], row[3]);
            }
        }
        else {
            cout << "Query Failed: " << mysql_error(conn) << endl;
        }
    }
    else {
        puts("Connection to database failed!");
    }
}

void QUERY_CMD(string query) {
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
}

void USER_ADD() {
    User user;

    cout << "Enter Name: ";
    string temp_name;
    cin.ignore();
    getline(cin, temp_name);
    user.setName(temp_name);

    cout << "Enter Email: ";
    string temp_email;
    cin >> temp_email;
    user.setEmail(temp_email);

    cout << "Enter Balance: ";
    string temp_balance;
    cin >> temp_balance;
    user.setBalance(temp_balance);

    string query = "INSERT INTO Users (owner_name, email, balance) VALUES ('" + user.getName() + "', '" + user.getEmail() + "' , " + user.getBalance() + ')';
    QUERY_CMD(query);
}

void USER_UPDATE() {
    User user;

    cout << "Enter ID: ";
    string temp_id;
    cin >> temp_id;

    system("cls");
    SQL_CONNECT(temp_id);

    cout << "Enter Updated Name: ";
    string temp_name;
    cin.ignore();
    getline(cin, temp_name);
    user.setName(temp_name);

    cout << "Enter Updated Email: ";
    string temp_email;
    cin >> temp_email;
    user.setEmail(temp_email);

    cout << "Enter Updated Balance: ";
    string temp_balance;
    cin >> temp_balance;
    user.setBalance(temp_balance);

    string query = "UPDATE Users SET owner_name = '" + user.getName() + "', email = '" + user.getEmail() + "', balance = " + user.getBalance() + " WHERE id = " + temp_id;
    QUERY_CMD(query);
}

void USER_DELETE() {
    cout << "Enter ID: ";
    string temp_id;
    cin >> temp_id;

    string query = "DELETE FROM Users WHERE id = " + temp_id;
    QUERY_CMD(query);
}

int main()
{
    while (true) {
        cout << "======================================================ADMIN PANEL======================================================\n";
        SQL_CONNECT("");
        cout << "\n\n";
        string crud[] = { "EXIT", "ADD USER", "UPDATE USER", "DELETE USER" };
        for (int i = 0; i < crud->length(); i++) {
            cout << "[" << i << "] " << crud[i] << '\n';
        }

        int choice;
        cout << "|->";
        cin >> choice;
        system("cls");
        SQL_CONNECT("");
        if (choice == 0) {
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
        system("cls");
    }
}