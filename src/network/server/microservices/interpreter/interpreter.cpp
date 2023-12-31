#include "interpreter.h"
#include "../GPIO/GPIO.cpp"
#include "../database/database.cpp"
#include "../file/file.cpp"



Interpreter::Interpreter(){

}

void Interpreter::setData(char* dataPacket, char* clientIP){
    this->dataPacket = new char[strlen(dataPacket) + 1];
    strcpy(this->dataPacket, dataPacket);

    this->clientIP = new char[strlen(clientIP) + 1];
    strcpy(this->clientIP, clientIP);

    this->db = new Database();
}

/*
    Datastructure in the dataPacket

    1. Byte: 0x00 = Request, 0x01 = Response
    2. Byte: 0x00 = None, (0x01 = Success, 0x02 = Failure) -> response from the previous data packet
    3. Byte: 0x00 = Login, 0x01 = Logout, 0x02 = Get Data, 0x03 = Set Data
    4. Byte: 0x00 = No Data, 0x01 = Commands, 0x02 = File, 0x03 = Database -> data from database
    5 - n. Byte: Data
*/

/*
    Login:
    1. Byte: 0x00 = Request
    2. Byte: 0x00 = None
    3. Byte: 0x00 = Login
    4. Byte: 0x00 = No Data
    5 - n. Bytes: pwd
*/

/*
    Logout:
    1. Byte: 0x00 = Request
    2. Byte: 0x00 = None
    3. Byte: 0x01 = Logout
    4. Byte: 0x00 = No Data
*/

/*
    Get Data:
    1. Byte: 0x00 = Request
    2. Byte: 0x00 | 0x01 | 0x02 = None | Success | Failure
    3. Byte: 0x02 = Get Data
    4. Byte: 0x01 | 0x02 | 0x03 = Commands | File | Database
*/

/*
    Response:
    1. Byte: 0x01 = Response
    2. Byte: 0x01 = Success, 0x02 = Failure
    3. 
*/

/*
    ret val:
    2: sql statement sucessfull executed
    1: File sent
    0: login successful
    -1: unable to interpret the data packet
    -2: unable to open the file
    -3: client is already connected
    -4: login failed
    -5: logout failed
    -6: client is not logged in
    -7: no rights for the command
    -8: sql statement not executed
    -9: database not found
*/

int Interpreter::InterpretData(){
    if(!this->dataPacket){
        return -1; //data packet is empty
    }

    cout << this->dataPacket << endl;

    bool connected = false;
    int IPIndex = -1; //place in the IPs vector

    //check if the client is not already connected
    for(int i = 0; i < IPs.size(); i++){
        cout << this->IPs[i].first << endl;
        if(this->IPs[i].first != this->clientIP){
            cout << "Client is not already connected! IP: " << this->clientIP << endl;
            connected = false;
        }
        if(this->IPs[i].first == this->clientIP){
            cout << "Client is already connected! IP: " << this->clientIP << endl;
            connected = true;
            IPIndex = i;
        }
    }

    //login
    if(this->dataPacket[0] == '0' && this->dataPacket[1] == '0'  && this->dataPacket[2] == '0' && this->dataPacket[3] == '0' && !connected){

        ifstream data("./microservices/clients.json", ifstream::binary);

        if (!data.is_open()) {
            cout << "Error opening file" << endl;
            cleanup();

            return -2;
        }

        //read the json file
        Value root;
        data >> root;

        data.close();

        char buffer[strlen(this->dataPacket) - 4];
        int j = 0;

        //extract the password
        for(int i = 4; i <= strlen(this->dataPacket); i++){
            buffer[j] = this->dataPacket[i];
            j++;
        }

        //check if the ip and password does match
        for(int i = 0; i < root["worker"].size(); i++){
            if(strcmp(this->clientIP, root["worker"][i]["ip"].asCString()) == 0){
                if(strcmp(buffer, root["worker"][i]["pwd"].asCString()) == 0){
                    cout << "Login successful" << endl;
                                
                    //add the client to the list if he is not already connected
                    IPs.push_back(make_pair(this->clientIP, bitset<3>(root["worker"][i]["rights"].asCString())));
                                
                    cout << "Client logged in! IP: " << this->IPs[0].first << " " << this->IPs[0].second << endl;

                    cleanup();

                    return 0;
                }
            }
        }

        cout << "Login failed" << endl;

        cleanup();

        return -4;
    }

    //logout
    else if(this->dataPacket[0] == '0' && this->dataPacket[1] == '0'  && this->dataPacket[2] == '1' && this->dataPacket[3] == '0' && connected && IPIndex > -1){
        if(this->logout()){
            cout << "Logout successful" << endl;
            cleanup();

            return 0;
        }
        else{
            cout << "Logout failed" << endl;
            cleanup();

            return -5; //logout failed
        }
    }

    //get data
    else if(this->dataPacket[0] == '0' && this->dataPacket[1] == '0' && this->dataPacket[2] == '2' && connected && (this->IPs[IPIndex].second[0] == 1 || this->IPs[IPIndex].second[2] == 1) && IPIndex > -1){
        
        if(this->dataPacket[3] == '1' && this->IPs[IPIndex].second[0] == 1){
            //interpret the commands -> GPIO



        }
        else if(this->dataPacket[3] == '2' && this->IPs[IPIndex].second[1] == 1){
            //get the file
            cout << "Get file" << endl;
            string dataPacket(this->dataPacket); //data packet as string
            string fileName = dataPacket.substr(4, dataPacket.size() - 4); //get the path of the file
            cout << fileName << endl;

            File* file = new File(fileName);
            string ret = file->readFile();

            delete file;
            
            //send the file to the client
            cout << ret << endl;
            cleanup();

            return 1;
        }
        else if(this->dataPacket[3] == '3' && this->IPs[IPIndex].second[1] == 1){
            
            //get database name
            //needs a wildcard for context intervals
            //0023 + "/" + DB-name + "/" + statement
            //get the position of the second "/" char and calculate the length of the databasename 
            short length;

            for(int i = 5; i < strlen(this->dataPacket); i++){
                if(this->dataPacket[i] == '/'){
                    length = i - 5;
                    break;
                }
            }
            
            string dP = this->dataPacket;

            string database = dP.substr(5, length);

            //open database+
            if(!this->db->searchDB(database)){
                return -9;
            }

            this->db->openDatabase(database);


            //get the sql statement
            string statement = dP.substr(length+2, strlen(dP));
            
            //send sql statement to database microservice
            bool ret = this->db->executeStatement(statement);

            this->db->closeDatabase(database);

            if(!ret){
                return -8;
            }

            return 2;
        }
        return -7;
    }

    else if(!connected){
        cleanup();
        return -6; //client is not logged in
    }

    else{
        cleanup();
        return -1; //unable to interpret the data packet
    }
}

bool Interpreter::checkLogin(){

    for(int i = 0; i < this->IPs.size(); i++){
        if(this->IPs[i].first == this->clientIP){
            return true;
        }
    }

    return false;
}

bool Interpreter::logout(){
    for(int i = 0; i < this->IPs.size(); i++){
        if(this->IPs[i].first == this->clientIP){
            this->IPs.erase(this->IPs.begin() + i);
            cout << "Client logged out! IP: " << this->clientIP << endl;
            return true;
        }
    }

    return false;
}

void Interpreter::cleanup(){

    if(this->db){
        delete this->db;
        this->db = nullptr;
    }

    if(this->dataPacket){
        delete[] this->dataPacket;
        this->dataPacket = nullptr;
    }

    if(this->clientIP){
        delete[] this->clientIP;
        this->clientIP = nullptr;
    }
}

Interpreter::~Interpreter(){
    cleanup();
}