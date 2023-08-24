#include <cstring>

class Response{

    public:

        Response(int ret, char* clientIP);

        ~Response();

    private:

        char* clientIP;
        char* dataPacket;

        int ret;

        void createDataPacket();
        int send();
};