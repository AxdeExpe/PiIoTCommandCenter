#include "interpreter.h"

Interpreter::Interpreter(char* dataPacket, char* clientIP){
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
    4. Byte: 0x00 = No Data, 0x01 = Commands, 0x02 = File
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
    ret val:
    -1: unable to interpret the data packet
    -2: unable to open the json file
    -3: client is already connected
    -4: login failed
    -5:
*/

int Interpreter::InterpretData(){
    if(!this->dataPacket){
        return -1; //data packet is empty
    }

    cout << this->dataPacket << endl;

    //check the data packet
    //request
    if(this->dataPacket[0] == '0'){
        cout << "sdf" << endl;

        //check the response
        if(this->dataPacket[1] == '0'){
            //None response
            if(this->dataPacket[2] == '0'){
                //for login only
                if(this->dataPacket[3] == '0'){

                    //check if the client is already connected
                    for(int i = 0; i < IPs.size(); i++){
                        if(this->IPs[i] == this->clientIP){
                            cout << "Client is already connected! IP: " << this->clientIP << endl;
                            return -3;
                        }
                    }

                    //add the client to the list if he is not already connected
                    IPs.push_back(this->clientIP);

                    ifstream data("../../microservices/data.json", ifstream::binary);

                    if (!data.is_open()) {
                        cout << "Error opening file" << endl;
                        return -1;
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
                                return 0;
                            }
                        }
                    }

                    //send response that the login failed
                    this->IPs.pop_back();

                    cout << "Login failed" << endl;
                    return -1;

                }
                else{
                    return -1; //unable to interpret the data packet
                }

            }
            else{
                return -1; //unable to interpret the data packet

            }
        }
        else if(this->dataPacket[1] == 0x01){

        }
        else if(this->dataPacket[1] == 0x02){

        }
        else{
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

    return 0;
}



Interpreter::~Interpreter(){
    delete[] this->dataPacket;
    delete[] this->clientIP;
}