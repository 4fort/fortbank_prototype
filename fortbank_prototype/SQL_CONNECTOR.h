#pragma once
#include <iostream>
#include <mysql.h>
#include <sstream>
using namespace std;

template<typename T> void printElement(T t, const int& width, char fill)
{
    cout << left << setw(width) << setfill(fill) << t;
}

class SQL_CONNECTOR {
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

	const char* host = "localhost";
	const char* user = "root";
	const char* passwd = "password123@";
	const char* db = "fortbank";
	const int port = 3306;
public :
	void connect() {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, host, user, passwd, db, port, NULL, 0);

        if (conn) {
            //puts("Connected!\n");
            print("");
        }
        else {
            puts("Connection to database failed!");
        }
	}
    void query(string query) {
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
    }
    void print(string id) {
        string q;
        if (id != "") {
            q = "SELECT * FROM Users WHERE id = " + id;
        }
        q = "SELECT * FROM Users";
        query(q);
        if (!qstate) {
            res = mysql_store_result(conn);
            printElement("", 120, '=');
            cout << '\n';
            printElement("ID", 5, ' ');
            printElement("Name", 20, ' ');
            printElement("Email", 30, ' ');
            printElement("Card Num", 20, ' ');
            printElement("Card Pin", 20, ' ');
            printElement("Balance", 20, ' ');
            cout << '\n';
            while (row = mysql_fetch_row(res)) {
                printElement(row[0], 5, ' ');
                printElement(row[1], 20, ' ');
                printElement(row[2], 30, ' ');
                printElement(row[3], 20, ' ');
                printElement(row[4], 20, ' ');
                cout << "P ";
                printElement(row[5], 0, ' ');
                cout << '\n';
            }
            printElement("", 120, '=');
            cout << '\n';
        }
        else {
            cout << "Query Failed: " << mysql_error(conn) << endl;
        }
    }
    string selectSpecific(string id, int inp) {
        string query = "SELECT * FROM Users WHERE id = " + id;
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);

            return row[inp];
        }
    }
	void Insert(string name, string email, string card_num, string card_pin, string balance) {
        connect();
        string q = "INSERT INTO Users (owner_name, email, card_num, card_pin, balance) VALUES ('" + name + "', '" + email + "', " + card_num + ", " + card_pin + ", " + balance + ')';
        query(q);
	}
    void Update(string temp_id, string name, string email, string card_pin, string balance) {
        connect();
        string q = "UPDATE Users SET owner_name = '" + name + "', email = '" + email + "', card_pin = " + card_pin + ", balance = " + balance + " WHERE id = " + temp_id;
        query(q);
    }
    void Delete(string id) {
        connect();
        string q = "DELETE FROM Users WHERE id = " + id;
        query(q);
    }
};