#include <iostream>
#include <string.h>
#include <vector>
#include <sqlite3.h>
#include <dirent.h>

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


    Notice:
        - create multiple database objects for multiple databases
        
    TODO:
        - path + databasename -> create database / delte database / open database / close database etc.
        --> in database.cpp

*/

using namespace std;

class Database{
    public:
        Database(string statement);
        ~Database();

    private:
        bool searchDB(string databaseName);
        vector <string> getAllDatabases();

        bool createDatabase(string databaseName);
        bool deleteDatabase(string databaseName);

        bool openDatabase(string databaseName);
        bool closeDatabase(string databaseName);

        bool executeStatement(string statement);
        //vector <string> getDatabasestructure(); // -> get the structure of the database (tables, columns, rows, etc.)

        sqlite3 *db;
        sqlite3_stmt *query;
        int rc;
        char *sql;
        char *zErrMsg;
        const char* data = "Callback function called";

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};