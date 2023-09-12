#include <string.h>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <cstdlib.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class file{

    public:

        file(string filename);

        bool createFile();
        bool deleteFile();

        bool executeFile(bool waitForChild = false);

        //mode: r+,w,w+,a,a+
        bool writeFile(string content, string mode);
        string readFile();

        ~file();

    private:
        //it's nearly the same funrion like in database.cpp
        bool searchFile();
        string filename;
};