#include "socket.h"
#include <string.h>

Socket::Socket(int port, string ip){
    this->port = port;
    this->ip = ip;
    cout << this->ip << endl;
}

bool Socket::createSocket(){
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Socket creation error" << endl;
        return false;
    }

    cout << "Socket created" << endl;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(this->port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, this->ip.c_str(), &serv_addr.sin_addr) <= 0) {
        cout << "Invalid address/ Address not supported" << endl;
        return false;
    }

    cout << "Address set" << endl;


    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        cout << "Connection Failed" << endl;
        return false;
    }

    cout << "Connected" << endl;

    return true;
}   

bool Socket::sendData(){
     if (this->DataPaketSend) {
            int sentBytes = send(client_fd, this->DataPaketSend, strlen(this->DataPaketSend), 0);
            if (sentBytes == -1) {
                cout << "Error sending data" << endl;
                delete[] this->DataPaketSend;
                return false;
            }
            cout << "Data sent" << endl;
            delete[] this->DataPaketSend;
            this->DataPaketSend = nullptr; // Set the pointer to nullptr after deletion
            return true;
        }
        return false; // No data to send
}

void Socket::receive(){
    char buffer[1024] = {0};
    valread = read(client_fd, buffer, 1024);
    cout << buffer << endl;
}

Socket::~Socket(){

    if(this->DataPaketReceive){
        delete[] this->DataPaketReceive;
    }

    if(this->DataPaketSend){
        delete[] this->DataPaketSend;
    }

    close(client_fd);
}