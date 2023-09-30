#include "socket.cpp"
#include <cstring>
#include<unistd.h>

#define PORT 8080

//predefined data packets
#define LOGIN "0000admin" //packet + password
#define LOGOUT "0010"
#define GETDATA "0022../data.txt" //packet + path to file

using namespace std;

int main(){

    //creates a socket on port 8080
    Socket *socket = new Socket(PORT, "127.0.0.1"); //get own ip address

    if(!socket->createSocket()){
        cout << "Error creating socket." << endl;
        return 1;
    }

    string login = LOGIN;
    socket->setDataPaketSend(login);
    bool sent = socket->sendData();

    sleep(3);

    string logout = LOGOUT;
    socket->setDataPaketSend(logout);
    cout << "hello" << endl;
    sent = socket->sendData();
    delete socket;

 

/*
    Socket *ss = new Socket(PORT, "127.0.0.1");

    if(!ss->createSocket()){
        cout << "Error creating socket." << endl;
        return 1;
    }

    string logout = LOGOUT;
    ss->setDataPaketSend(logout);
    bool sent1 = ss->sendData();
    delete ss;

*/


    Socket *s = new Socket(PORT, "127.0.0.1");

    if(!s->createSocket()){
        cout << "Error creating socket." << endl;
        return 1;
    }

    string data = GETDATA;
    s->setDataPaketSend(data);
    bool sent2 = s->sendData();
    delete s;

    cout << "Socket deleted" << endl;

    return 0;


}
