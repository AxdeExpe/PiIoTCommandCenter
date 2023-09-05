#include <iostream>
#include <string.h>
#include <vector>
#include <bitset>

using namespace std;

struct PinInfo{
    string IP;
    short pin;
    bitset<1> mode;
    bitset<1> value;
};

class GPIO{

    public:
        GPIO();
        ~GPIO();

    private:
        
        int pin;
        int mode;
        int value;

        vector<PinInfo> PINS; //1. IP, 2. Pin, 3. IN / OUT, 4. HIGH / LOW

};