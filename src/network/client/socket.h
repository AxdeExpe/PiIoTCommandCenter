#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

class Socket{

    public:
        Socket(int port, string ip);

        bool createSocket();

        void receive();
        bool sendData();

        void setDataPaketSend(string data){

            if (this->DataPaketSend) {
                delete[] this->DataPaketSend;
            }
            this->DataPaketSend = new char[strlen(data.c_str()) + 1];
            strcpy(this->DataPaketSend, data.c_str());
        }


        ~Socket();


    private:

        char* DataPaketSend;
        char* DataPaketReceive;

        int status, valread, client_fd;
        struct sockaddr_in serv_addr;

        int port;
        string ip;
};