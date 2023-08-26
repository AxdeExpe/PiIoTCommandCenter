#include "socket.h"

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
    return true;
}


bool Socket::listenAndReact() {
    if (listen(server_fd, 1) < 0) { // 1 client
        cout << "Error listening on port " << port << endl;
        return false;
    }

    this->interpreter = new Interpreter();

    while (true) {
        if ((this->new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            cout << "Error accepting client connection." << endl;
            return false;
        }

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(address.sin_addr), clientIP, INET_ADDRSTRLEN);

        cout << "New client connected! IP: " << clientIP << endl;
        cout << "Client accepted" << endl;

        // Receive data
        receive();

        // Interpret data and do something with it
        this->interpreter->setData(this->DataPaketReceive, clientIP);
        
        delete[] this->DataPaketReceive;
        this->DataPaketReceive = nullptr;

        Response *response = new Response(this->interpreter->InterpretData(), clientIP);

        // Send response

        delete response;

        close(this->new_socket);
    }

    // Cleanup
    delete this->interpreter;
    return true;
}


void Socket::receive(){
    vector<char> dataBuffer; // Use vector for dynamic array

    while (true) {
        char chunk[chunkSize];
        int bytesRead = recv(this->new_socket, chunk, sizeof(chunk), 0);

        if (bytesRead <= 0) {
            std::cout << "Not more Data" << std::endl;
            break;
        }

        dataBuffer.insert(dataBuffer.end(), chunk, chunk + bytesRead);
    }

    dataBuffer.push_back('\0'); // Null-terminate the received data

    // Convert vector<char> to char*
    this->DataPaketReceive = new char[dataBuffer.size()];
    copy(dataBuffer.begin(), dataBuffer.end(), this->DataPaketReceive);
    this->DataPaketReceive[dataBuffer.size()] = '\0'; // Null-terminate the received data
}


bool Socket::send(char *data){

    return true;
}


Socket::~Socket(){
    if(this->DataPaketSend){
        delete[] this->DataPaketSend;
    }
    if(this->interpreter){
        delete interpreter;
    }
    
    close(server_fd);
}