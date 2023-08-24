#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string.h>
#include <vector>

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
        void cleanup();

        char* dataPacket;
        char* clientIP;
        vector<string> IPs;

};