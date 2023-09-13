#include <string.h>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class File{

    public:

        File(string filename);

        bool createFile();
        bool deleteFile();

        bool executeFile(bool waitForChild = false);

        //mode: r+,w,w+,a,a+
        bool writeFile(string content, string mode);
        string readFile();

        ~File();

    private:
        //it's nearly the same funrion like in database.cpp
        bool searchFile();
        string filename;
};