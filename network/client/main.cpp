#include "socket.cpp"
#include <cstring>
#define PORT 8080


int main(){

    //creates a socket on port 8080
    Socket *socket = new Socket(PORT, "127.0.0.1");

    if(socket->createSocket() == false){
        cout << "Error creating socket." << endl;
        return 1;
    }

for(int i = 0; i < 5; i++) {
        string s = "Hello from clien122222222222lskjdjkarekjbgfkhljiuadsgfb4qi79z132qgziahkldfhbaksndbfhkasdfbhashkbdfakhljdhkfuh2ih3rqhfkahjds222222222222222222t\n";
        socket->setDataPaketSend(s.c_str());
        bool sent = socket->sendData();

}
    

    delete socket;
        cout << "Socket deleted" << endl;

    return 0;
}