#include "interpreter.h"

Interpreter::Interpreter(){

}

void Interpreter::setData(char* dataPacket, char* clientIP){
    this->dataPacket = new char[strlen(dataPacket) + 1];
    strcpy(this->dataPacket, dataPacket);

    this->clientIP = new char[strlen(clientIP) + 1];
    strcpy(this->clientIP, clientIP);
}

/*
    Datastructure in the dataPacket

    1. Byte: 0x00 = Request, 0x01 = Response
    2. Byte: 0x00 = None, 0x01 = Success, 0x02 = Failure -> response from the previous data packet
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
     0: login successful
    -1: unable to interpret the data packet
    -2: unable to open the file
    -3: client is already connected
    -4: login failed
    -5: logout failed
*/

int Interpreter::InterpretData(){
    if(!this->dataPacket){
        return -1; //data packet is empty
    }

    cout << this->dataPacket << endl;

    //check the data packet
    //request 
    if(this->dataPacket[0] == '0'){

        //check the request
        if(this->dataPacket[1] == '0'){
            //None response
            if(this->dataPacket[2] == '0'){
                //for login only
                if(this->dataPacket[3] == '0'){

                    //check if the client is already connected
                    for(int i = 0; i < IPs.size(); i++){
                        cout << this->IPs[i] << endl;
                        if(this->IPs[i] == this->clientIP){
                            cout << "Client is already connected! IP: " << this->clientIP << endl;
                            cleanup();

                            return -3;
                        }
                    }

                    //add the client to the list if he is not already connected
                    IPs.push_back(this->clientIP);

                    ifstream data("../../microservices/data.json", ifstream::binary);

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

                    //check if the ip and password does match<<
                    for(int i = 0; i < root["worker"].size(); i++){
                        if(strcmp(this->clientIP, root["worker"][i]["ip"].asCString()) == 0){
                            if(strcmp(buffer, root["worker"][i]["pwd"].asCString()) == 0){
                                cout << "Login successful" << endl;
                                cleanup();

                                return 0;
                            }
                        }
                    }

                    //send response that the login failed
                    this->IPs.pop_back();

                    cout << "Login failed" << endl;

                    cleanup();

                    return -4;

                }
                else{
                    cleanup();
                    return -1; //unable to interpret the data packet
                }

            }
            //logout
            else if(this->dataPacket[2] == '1'){
                if(this->dataPacket[3] == '0'){
                    
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
                else{
                    cleanup();
                    return -1; //unable to interpret the data packet
                }

            }
            //Get data
            else if(this->dataPacket[2] == '2'){
                if(this->dataPacket[3] == '1'){
                    //interpret the commands
                }
                else if(this->dataPacket[3] == '2'){
                    //get the file
                    string dataPacket(this->dataPacket); //data packet as string
                    string fileName = dataPacket.substr(4, dataPacket.size() - 4); //get the path of the file
                    cout << fileName << endl;

                    ifstream file(fileName, ifstream::binary | ios::ate);

                    if(!file.is_open()){
                        cout << "Error opening file" << endl;
                        cleanup();

                        return -2;
                    }

                    streampos fileSize = file.tellg();
                    char* buffer = new char[fileSize];

                    file.seekg(0, ios::beg); // Go back to the beginning of the file
                    file.read(buffer, fileSize);
    
                    file.close();

                    //send the file to the client
                    cout << buffer << endl;

                    delete[] buffer;
                }
                else if(this->dataPacket[3] == '3'){
                    //interpret the sql query
                }
                else{
                    cleanup();
                    return -1; //unable to interpret the data packet

                }
            }
            else{
                cleanup();
                return -1; //unable to interpret the data packet

            }
        }
        else if(this->dataPacket[1] == 0x01){

        }
        else if(this->dataPacket[1] == 0x02){

        }
        else{
            cleanup();
            return -1; //unable to interpret the data packet
        }

    }
    
    //response
    if(this->dataPacket[0] == 0x01){

    }

    //success
    if(this->dataPacket[1] == 0x00){


    }

    //failure
    if(this->dataPacket[1] == 0x01){

    }

    //Login
    if(this->dataPacket[2] == 0x00){

    }

    //Logout
    if(this->dataPacket[2] == 0x01){

    }

    //Get Data
    if(this->dataPacket[2] == 0x02){

    }

    //Set Data
    if(this->dataPacket[2] == 0x03){

    }

    //No Data
    if(this->dataPacket[3] == 0x00){

    }

    //Commands
    if(this->dataPacket[3] == 0x01){

    }

    //File
    if(this->dataPacket[3] == 0x02){

    }

    cleanup();
    return 0;
}

bool Interpreter::checkLogin(){

    for(int i = 0; i < this->IPs.size(); i++){
        if(this->IPs[i] == this->clientIP){
            return true;
        }
    }

    return false;
}

bool Interpreter::logout(){
    for(int i = 0; i < this->IPs.size(); i++){
        if(this->IPs[i] == this->clientIP){
            this->IPs.erase(this->IPs.begin() + i);
            cout << "Client logged out! IP: " << this->clientIP << endl;
            return true;
        }
    }

    return false;
}

void Interpreter::cleanup(){

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