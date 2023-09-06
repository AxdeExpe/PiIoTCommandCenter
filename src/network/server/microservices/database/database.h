#include <iostream>
#include <sqlite3.h>

/*
    Only the admin can use the database (Server-Raspi) 
    -> means a direct insertion, update, delete or select is from outside (client -> server) not possible
    -> the client can send a request to the server and the server can do the action but nothing more

    Admin (Server-Raspi):
        - Create Database
        - Delete Database
        - Create Table
        - Insert Data
        - Update Data
        - Delete Data
        - Select Data

    User (Client):
        - send requests to the server
        - get responses from the server
        -> client doesn't care directly about the databasestructure (tables, columns, rows, etc.)
        -> client can request the structure of the database (tables, columns, rows, etc.)
        -> client can send requests to the server but it is not possible to do a direct insertion, update, delete or select from the client side

*/


class Database{
    public:
        Database();
        ~Database();

        bool createDatabase();
        bool deleteDatabase();

        bool openDatabase();
        bool closeDatabase();

        bool createTable();
        bool insertData();
        bool updateData();
        bool deleteData();
        bool selectData();

        //vector <string> getDatabasestructure(); // -> get the structure of the database (tables, columns, rows, etc.)

    private:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        const char* data = "Callback function called";

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};