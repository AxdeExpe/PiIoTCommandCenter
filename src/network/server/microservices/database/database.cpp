#include "database.h"
#define PATH "../database/"

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
    if(this->searchDB(databaseName)){
        cout << "Error: Database " << databaseName << " already exists!" << endl;
        return false;
    }

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

    string db = PATH + databaseName;

    if(remove(db.c_str()) != 0){
        cout << "Error: Unable to delete the database " << db << endl;
        return false;
    }
    else{
        cout << "Database " << db << " successful deleted!" << endl;
    }

    return true;
}





bool Database::openDatabase(string databaseName){

    //opens the db only if it exists
    if(this->searchDB(databaseName)){
        string db = PATH + databaseName;
        this->rc = sqlite3_open(db.c_str(), &this->db);

        if(this->rc != SQLITE_OK){
            cout << "Error: Unable to open the database " << databaseName << ", Errorcode: " << this->rc << endl;
            cout << "Error: " << sqlite3_errmsg(this->db) << endl;
            return false;
        }

        return true;
    }

    return false;
}

bool Database::closeDatabase(string databaseName){

    if(this->db){
        this->rc = sqlite3_close(this->db);

        if(this->rc != SQLITE_OK){
            cout << "Error: Unable to close the database " << databaseName << ", Errorcode: " << this->rc << endl;
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
            cout << "Error: " <<  sqlite3_errmsg(this->db) << endl;
            return false;
        }

        return true;
    }
    else{
        cout << "Database is not open!" << endl;    
    }

    return false;
}

bool Database::searchDB(string databaseName){

    //searches the database in the path

    //if found -> return true
    //if not found -> return false

    DIR *dir = opendir(PATH);

    if(dir){
        struct dirent *entry;

        while(entry = readdir(dir)){
            
            if(strcmp(entry->d_name, databaseName.c_str()) == 0){
                closedir(dir);
                return true;
            }
        }
        closedir(dir);
    }
    else{
        cout << "Error: Unable to open the directory " << PATH << endl;
        return false;
    }

    cout << "Error: Unable to find the database " << databaseName << endl;

    return false;
}

vector <string> Database::getAllDatabases(){

    vector <string> databases;

    //get all databases from the database directory

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