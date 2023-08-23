#include "socket.h"
#include "../../microservices/interpreter/interpreter.cpp"

Socket::Socket(int port){
    
    this->port = port;
}

bool Socket::createSocket(){

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Error creating socket." << endl;
        return false;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        cout << "Error setting socket options." << endl;
        return false;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port); //big endian

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cout << "Error binding socket to port " << port << endl;
        return false;
    }

    if (listen(server_fd, 10) < 0) { //10 clients
        cout << "Error listening on port " << port << endl;
        return false;
    }
    
    
    while(true){

        if (( this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            cout << "Error accepting client connection." << endl;
            return false;
        }

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(address.sin_addr), clientIP, INET_ADDRSTRLEN);
        
        cout << "New client connected! IP: " << clientIP << endl;

        if (this->new_socket == -1) {
            cout << "Error accepting client connection." << endl;
            continue;
        }

        cout << "Client accepted" << endl;

        //receive data
        receive();

        //interpret data and do something with it
        Interpreter *interpreter = new Interpreter(this->DataPaketReceive, clientIP);
        interpreter->InterpretData();

        delete this->DataPaketReceive;
        delete interpreter;


        //send response

        close(this->new_socket);
    }
}

void Socket::receive(){

    int bufferSize = 0;
    this->DataPaketReceive = nullptr;

    while (true) {
        char chunk[10]; // Buffer for Datachunks
        int bytesRead = recv(this->new_socket, chunk, sizeof(chunk), 0);

        if (bytesRead <= 0) {
            cout << "Connection closed" << endl;
            break; // No Data or Error -> Stop receiving
        }

        // Expand the buffer and copy the received chunk
        char *newBuffer = new char[bufferSize + bytesRead];

        if (this->DataPaketReceive) {
            memcpy(newBuffer, this->DataPaketReceive, bufferSize);
            delete this->DataPaketReceive; // Alten Puffer freigeben
        }
        memcpy(newBuffer + bufferSize, chunk, bytesRead);

        this->DataPaketReceive = newBuffer;
        bufferSize += bytesRead;
    }

    // Null-terminate the received data
    if (this->DataPaketReceive) {
        this->DataPaketReceive[bufferSize] = '\0';
    }
}

bool Socket::send(char *data){

    return true;
}





Socket::~Socket(){
    if(this->DataPaketSend){
        delete[] this->DataPaketSend;
    }
    
    close(server_fd);
}