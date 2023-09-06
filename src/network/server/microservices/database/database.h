#include <iostream>
#include <sqlite3.h>

class database{
    public:
        database();
        ~database();

        bool openDatabase();
        bool closeDatabase();

        bool createTable();
        bool insertData();
        bool updateData();
        bool deleteData();
        bool selectData();

    private:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        const char* data = "Callback function called";

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};