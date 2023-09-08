#include <string>
#include <iostream>

using namespace std;

class file{

    public:

        file(string filename);

        bool createFile();
        bool deleteFile();

        bool executeFile();
        bool writeFile(string content, string mode);
        string readFile();

        ~file();

    private:
        bool searchFile();
        string filename;
};