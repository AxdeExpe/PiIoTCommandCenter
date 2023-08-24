#include "response.h"

Response::Response(int ret, char* clientIP){
    this->ret = ret;

    this->clientIP = new char[strlen(clientIP) + 1];
    strcpy(this->clientIP, clientIP);
}


void Response::createDataPacket(){
    this->dataPacket = new char[4];

    //irgendwas zurück schicken
    switch (ret)
    {
    case -1:
        //send response of wrong data packet

        break;
        
    case -2:
        //send response of server issue

        break;

    case -3:
        //send response of client already connected

         break;

    case -4:
        //send response of login failed

        break;
        
    default:
        break;
    }



}

int Response::send(){
    
    return 0;
}

Response::~Response(){
    delete this->clientIP;
    delete this->dataPacket;
}