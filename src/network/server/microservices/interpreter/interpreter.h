#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string.h>

using namespace std;
using namespace Json;

class Interpreter{

    public:

        Interpreter(char* dataPacket);

        int InterpretData();

        ~Interpreter();

    private:

        char* dataPacket;

};