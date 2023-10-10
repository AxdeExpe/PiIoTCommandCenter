#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string.h>
#include <vector>
#include <bitset>

using namespace std;
using namespace Json;

class Interpreter{

    public:

        Interpreter();
        void setData(char* dataPacket, char* clientIP);

        int InterpretData();

        ~Interpreter();

    private:
        int checkRights();
        bool checkLogin();
        
        void cleanup();

        bool logout();

        char* dataPacket;
        char* clientIP;

        vector<pair<string, bitset<3>>> IPs; //IP's and their rights (0 = send data, 1 = access to gpio, 2 = access to file system)
        
        Database *db;

};