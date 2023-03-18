#pragma once
#include <iostream>
#include <mysql.h>
#include <sstream>
#include "SinglyLinkedList.h"
#include "custlib.h"
using namespace std;
extern SinglyLinkedList sll;


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

        if (sll.nodeExists("1") == NULL) {
            if (conn) {
                //puts("Connected!\n");
                createList();
            }
            else {
                puts("Connection to database failed!");
            }
        }
	}
    void query(string query) {
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
    }
    void createList() {
        string q;
        q = "SELECT * FROM Users";
        query(q);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                Node* sll_user = new Node();
                sll_user->setId(row[0]);
                sll_user->setName(row[1]);
                sll_user->setEmail(row[2]);
                sll_user->setCardNum(row[3]);
                sll_user->setCardPin(row[4]);
                sll_user->setBalance(row[5]);
                sll.appendNode(sll_user);
            }
        }
        else {
            cout << "Query Failed: " << mysql_error(conn) << endl;
        }
    }
	void Insert(Node* user) {
        connect();
        string q = "INSERT INTO Users (owner_name, email, card_num, card_pin, balance) VALUES ('" + user->getName() + "', '" + user->getEmail() + "', " + user->getCardNum() + ", " + user->getCardPin() + ", " + user->getBalance() + ')';
        query(q);
	}
    void Update(Node* user) {
        connect();
        string q = "UPDATE Users SET owner_name = '" + user->getName() + "', email = '" + user->getEmail() + "', card_pin = " + user->getCardPin() + ", balance = " + user->getBalance() + " WHERE id = " + user->getId();
        query(q);
    }
    void Delete(string id) {
        connect();
        string q = "DELETE FROM Users WHERE id = " + id;
        query(q);
    }
};