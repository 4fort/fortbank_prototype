#include <iostream>
#include <mysql.h>
#include <sstream>
#include <iomanip>
#include "User.h"
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

template<typename T> void printElement(T t, const int& width, char fill)
{
    cout << left << setw(width) << setfill(fill) << t;
}

extern int main();
void SQL_CONNECT(string temp_id);
string USER_GET(string temp_id, int inp);
void QUERY_CMD(string query);
void USER_ADD();
void USER_UPDATE();
void USER_DELETE();
void RETURNTO_MENU();

void SQL_CONNECT(string temp_id) {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, host, user, passwd, db, port, NULL, 0);

    if (conn) {
        //puts("Connected!\n");

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
            printElement("", 120, '=');
            cout << '\n';
            printElement("ID", 5, ' ');
            printElement("Name", 30, ' ');
            printElement("Email", 50, ' ');
            printElement("Balance", 0, ' ');
            cout << '\n';
            while (row = mysql_fetch_row(res)) {
                printElement(row[0], 5, ' ');
                printElement(row[1], 30, ' ');
                printElement(row[2], 50, ' ');
                cout << "P ";
                printElement(row[3], 0, ' ');
                cout << '\n';
            }
            printElement("", 120, '=');
            cout << '\n';
        }
        else {
            cout << "Query Failed: " << mysql_error(conn) << endl;
        }
    }
    else {
        puts("Connection to database failed!");
    }
}

string USER_GET(string temp_id, int inp) {
    string query = "SELECT * FROM Users WHERE id = " + temp_id;
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        return row[inp];
    }
}

void QUERY_CMD(string query) {
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
}

void USER_ADD() {
    User user;
    string temp_input;

    SQL_CONNECT("");

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

    string query = "INSERT INTO Users (owner_name, email, balance) VALUES ('" + user.getName() + "', '" + user.getEmail() + "' , " + user.getBalance() + ')';
    QUERY_CMD(query);
}

void USER_UPDATE() {
    User user;
    string temp_input;
    string temp_id;

    SQL_CONNECT("");

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
    SQL_CONNECT(temp_id);

    cout << "Enter Updated Name: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = USER_GET(temp_id, 1);
    }
    else if (temp_input == "!r") {
        RETURNTO_MENU();
    }
    user.setName(temp_input);

    cout << "Enter Updated Email: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = USER_GET(temp_id, 2);
    }
    user.setEmail(temp_input);

    cout << "Enter Updated Balance: ";
    getline(cin, temp_input);
    if (temp_input.empty()) {
        temp_input = USER_GET(temp_id, 3);
    }
    user.setBalance(temp_input);

    string query = "UPDATE Users SET owner_name = '" + user.getName() + "', email = '" + user.getEmail() + "', balance = " + user.getBalance() + " WHERE id = " + temp_id;
    QUERY_CMD(query);
}

void USER_DELETE() {
    SQL_CONNECT("");

    string temp_input;
    cout << "Enter ID: ";
    cin.ignore();
    getline(cin, temp_input);
    if (temp_input == "!r") {
        RETURNTO_MENU();
    }

    string query = "DELETE FROM Users WHERE id = " + temp_input;
    QUERY_CMD(query);
}

void RETURNTO_MENU() {
    system("cls");
    main();
}