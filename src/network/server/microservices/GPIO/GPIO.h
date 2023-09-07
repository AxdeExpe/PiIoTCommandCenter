#include <iostream>
#include <string.h>
#include <vector>
#include <bitset>
//#include <wiringPi.h>

using namespace std;

//Is an information about a single pin of the server (dynamically)
struct PinInfo{
    string IP;
    short pin;
    bitset<1> mode;
    bitset<1> value;
};


//Is an information about all pins of the server before the initialization (static)
struct standardPins{
    short pin;
    bitset<1> mode;
    bitset<1> value;
};

class GPIO{

    public:
        GPIO();
        ~GPIO();

        bool setPin(short pin, int mode, short value);
        short getPin(short pin, int mode, short value);
        
        int getPinMode(short pin);
        short getPinValue(short pin);

        vector <vector<int>> getAllPins(); //get all pins of the server as tupel, e.g. (1, 10, 1) -> (pin, mode, value)

    private:
        
        int pin;
        int mode;
        int value;

        vector<PinInfo> PINS; //1. IP, 2. Pin, 3. IN / OUT, 4. HIGH / LOW
        vector<standardPins> standardPinsList; //1. Pin, 2. IN / OUT, 3. HIGH / LOW
};