#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string.h>
#include <vector>

using namespace std;
using namespace Json;

class Interpreter{

    public:

        Interpreter(char* dataPacket, char* clientIP);

        int InterpretData();

        ~Interpreter();

    private:
        int checkRights();

        char* dataPacket;
        char* clientIP;
        vector<string> logins;

};