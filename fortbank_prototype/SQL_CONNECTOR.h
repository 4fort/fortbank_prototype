#pragma once
#include <iostream>
#include <mysql.h>
#include <sstream>
#include "SinglyLinkedList.h"
using namespace std;
extern SinglyLinkedList userList;
extern SinglyLinkedList historyList;

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

        if (userList.nodeExists(1) == NULL) {
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
                sll_user->setId(stoi(row[0]));
                sll_user->setName(row[1]);
                sll_user->setEmail(row[2]);
                sll_user->setCardNum(stoi(row[3]));
                sll_user->setCardPin(stoi(row[4]));
                sll_user->setBalance(stod(row[5]));
                userList.appendNode(sll_user);
            }
        }
        else {
            cout << "Query Failed: " << mysql_error(conn) << endl;
        }
        createHistoryList();
    }
    void createHistoryList() {
        string q;
        q = "SELECT * FROM Transac_History";
        query(q);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                Node* sll_history = new Node();
                if (row[0] != NULL) sll_history->setId(stoi(row[0]));
                if (row[1] != NULL) sll_history->setOwnerId_history(stoi(row[1]));
                if (row[2] != NULL) sll_history->setHistoryType_history(row[2]);
                if (row[3] != NULL) sll_history->setDate_history(row[3]);
                if (row[4] != NULL) sll_history->setAmount_history(stod(row[4]));
                if (row[5] != NULL) sll_history->setPrevAmount_history(stod(row[5]));
                if (row[6] != NULL) sll_history->setIsReceiver_history(row[6]);
                if (row[7] != NULL) sll_history->setCardSender_history(stoi(row[7]));
                if (row[8] != NULL) sll_history->setCardReceiver_history(stoi(row[8]));
                historyList.appendNode(sll_history);
            }
        }
        else {
            cout << "Query Failed: " << mysql_error(conn) << endl;
        }
    }
    int getLastId() {
        return mysql_insert_id(conn);
    }
	void Insert(Node* user) {
        connect();
        string q = "INSERT INTO Users (owner_name, email, card_num, card_pin, balance) VALUES ('" + user->getName() + "', '" + user->getEmail() + "', " + to_string(user->getCardNum()) + ", " + to_string(user->getCardPin()) + ", " + to_string(user->getBalance()) + ')';
        query(q);
	}
    void Update(Node* user) {
        connect();
        string q = "UPDATE Users SET owner_name = '" + user->getName() + "', email = '" + user->getEmail() + "', card_pin = " + to_string(user->getCardPin()) + ", balance = " + to_string(user->getBalance()) + " WHERE id = " + to_string(user->getId());
        query(q);
    }
    void Delete(string id) {
        connect();
        string q = "DELETE FROM Users WHERE id = " + id;
        query(q);
    }
    void InsertHistory(Node* history) {
        connect();
        string q = "INSERT INTO Transac_History (owner_id, hist_type, hist_datetime, amount, prev_amount, is_receiver, card_sender, card_receiver) VALUES ( 1, 'transfer', NOW(), 50.5, 2000.75, NULL, 456123, 456629)";
    }
};