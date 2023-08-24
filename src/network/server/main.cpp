#include "socket.cpp"
#include <csignal>

#define PORT 8080

Socket *sock = nullptr;

void signalHandler(int signum) {
   cout << "Interrupt signal (" << signum << ") received.\n";

   if(sock != nullptr){
       delete sock;
   }

   exit(signum);  
}

int main(){

    //doesnt block the port after closing the server
    signal(SIGINT, signalHandler);

    //creates a socket on port 8080
    sock = new Socket(PORT);

    if(sock->createSocket() == false){
        cout << "Error creating socket." << endl;
        return 1;
    }

    sock->listenAndReact();

    delete sock;

    return 0;
}