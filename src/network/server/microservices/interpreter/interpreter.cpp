#include "interpreter.h"

Interpreter::Interpreter(char* dataPacket){
    strcpy(this->dataPacket, dataPacket);
}


/*
    Datastructure in the dataPacket

    1. Byte: 0x00 = Request, 0x01 = Response
    2. Byte: 0x00 = Success, 0x01 = Failure -> response from the previous data packet
    3. Byte: 0x00 = Login, 0x01 = Logout, 0x02 = Get Data, 0x03 = Set Data
    4. Byte: 0x00 = No Data, 0x01 = Commands, 0x02 = File
    5 - n. Byte: Data
*/

int Interpreter::InterpretData(){
    if(!this->dataPacket){
        return -1;
    }

    //check the data packet
    //request
    if(this->dataPacket[0] == 0x00){

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
}