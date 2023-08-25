#include "socket.cpp"
#include <cstring>
#define PORT 8080


int main(){

    //creates a socket on port 8080
    Socket *socket = new Socket(PORT, "127.0.0.1"); //get own ip address

    if(!socket->createSocket()){
        cout << "Error creating socket." << endl;
        return 1;
    }

        string s = "0000admin";
        socket->setDataPaketSend(s.c_str());
        bool sent = socket->sendData();
        delete socket;


        Socket *ss = new Socket(PORT, "127.0.0.1");

        if(!socket->createSocket()){
            cout << "Error creating socket." << endl;
            return 1;
        }

        string logout = "0100";
        socket->setDataPaketSend(logout.c_str());
        sent = ss->sendData();
        delete socket;

        cout << "Socket deleted" << endl;

    return 0;
}