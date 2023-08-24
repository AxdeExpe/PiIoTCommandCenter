#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../../microservices/interpreter/interpreter.cpp"
#include "../../microservices/response/response.cpp"

using namespace std;

class Socket{

    public:
        Socket(int port);

        bool createSocket();
        bool listenAndReact();

        void receive();
        bool send(char *data);

        ~Socket();


    private:
    
        const int chunkSize = 10;

        char* DataPaketSend;
        char* DataPaketReceive;

        int server_fd, new_socket, valread;
        int opt = 1;
        struct sockaddr_in address;
        int addrlen = sizeof(address);

        int port;
        int ip;

        Interpreter *interpreter;
};