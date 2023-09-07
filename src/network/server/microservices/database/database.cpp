#include "database.h"

Database::Database(){
    this->db = NULL;
    this->query = NULL;
    this->zErrMsg = NULL;
    this->rc = 0;
    this->sql = NULL;
}




bool Database::createDatabase(string databaseName){
    int ret;
    if(SQLITE_OK != (ret = sqlite3_initialize())){
        cout << "Error: sqlite3_initialize failed! Errorcode: " << ret << endl;
        return false;
    }
    else{
        cout << "sqlite3_initialize successful!" << endl;
    }

    //only create database if it doesn't exist

    if(SQLITE_OK != (ret = sqlite3_open_v2(databaseName.c_str(), &this->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))){
        cout << "Error: sqlite3_open_v2 failed! Errorcode: " << ret << endl;
        return false;
    }
    else{
        cout << "Database " << databaseName << " successful created!" << endl;
    }

    return true;
}

bool Database::deleteDatabase(string databaseName){

    //string db = path + databaseName

    if(remove(databaseName.c_str()) != 0){
        cout << "Error: Unable to delete the database " << databaseName << endl;
        return false;
    }
    else{
        cout << "Database " << databaseName << " successful deleted!" << endl;
    }

    return true;
}





bool Database::openDatabase(string databaseName){

    //opens the db only if it exists

}

bool Database::closeDatabase(string databaseName){

    if(this->db){
        int code = sqlite3_close(this->db);

        if(code != SQLITE_OK){
            cout << "Error: Unable to close the database " << databaseName << ", Errorcode: " << code << endl;
            cout << "Error: " << sqlite3_errmsg(this->db) << endl;
            return false;
        }

        return true;
    }

    cout << "Error: Database error while closing the DB " << databaseName << ", Errorcode: " << sqlite3_errmsg(this->db) << endl;

    return false;
}





bool Database::executeStatement(string statement){

    if(this->db){
        this->rc = sqlite3_exec(this->db, statement.c_str(), NULL, NULL, &this->zErrMsg);

        if(this->rc != SQLITE_OK){
            cout << "Error: Unable to execute the statement " << statement << ", Errorcode: " << this->rc << endl;
            cout << "Error: " << this->zErrMsg << endl;
            return false;
        }

        return true;
    }

    cout << "Error: Database error while executing the statement " << statement << ", Errorcode: " << sqlite3_errmsg(this->db) << endl;

    return false;
}




Database::~Database(){
    if (this->query){
        sqlite3_finalize(this->query);
        this->query = nullptr;
    } 
    if (this->db){
        sqlite3_close(this->db);
        this->db = nullptr;
    }
    sqlite3_shutdown();
}