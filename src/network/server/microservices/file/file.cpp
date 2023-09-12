#include "file.h"

file::file(string filename){
    this->filename = filename;
}




bool file::createFile(){

    ofstream file(this->filename.c_str());

    if(!file){
        cout << "Error: Unable to create the file " << this->filename << endl;
        return false;
    }

    file.close();

    return true;
}

bool file::deleteFile(){

    if(!this->searchFile()){
        return false;
    }

    if(remove(this->filename.c_str()) != 0){
        cout << "Error: Unable to delete the file " << this->filename << endl;
        return false;
    }

    return true;
}




bool file::executeFile(bool waitForChild){

    //true -> child executes the file
    //false -> child doesn't execute the file
    //and nothing more -> The troubleshooting will come later or needs to be resolved by the programmer themselves

    if(!this->searchFile()){
        return false;
    }

    //check if the file is executable
    struct stat file_execl;
    if(stat(this->filename.c_str(), &file_execl) == 0){
        //check if the file is executable
        if(!(file_execl.st_mode & S_IXUSR) && !(file_execl.st_mode & S_IXGRP) && !(file_execl.st_mode & S_IXOTH)){
            cout << "Error: The file " << this->filename << " is not executable" << endl;
            return false;
        }
    }
    else{
        cout << "Warning: Unable to get the file status of " << this->filename << endl;
    }

    
    //execute the file
    //create childprocess for the file
    pid_t child;
    if((child = fork()) == 0){
        //child process
        execl(this->filename.c_str(), NULL);
        cout << "Error: File " << this->filename << " could not be executed, PID: " << child << endl;
        exit(0);
    }
    else if(child == -1){
        //error
        cout << "Error: Unable to create a child process for the file " << this->filename << endl;
        return false;
    }
    else{
        //parent process
        if(waitForChild){
            //wait for the child process to finish
            int status;
            if (waitpid(child, &status, 0) > 0) {
             
                if (WIFEXITED(status) && !WEXITSTATUS(status)){
                    cout << "Program execution successful" << endl;
                    return true;
                }
                else
                    cout << "Warning: program didn't terminate normally!" << endl;
                    return true;      
                }
            else {
                // waitpid() failed
                cout << "Warning: waiting for child process failed" << endl;
                return true;
            }
        }
        else{
            //don't wait for the child process to finish
            return true;
        }
    }
}

bool file::writeFile(string content, string mode){

    if(!this->searchFile()){
        return false;
    }

    if(mode != "ate" || mode != "app" || mode != "trunc"){
        cout << "Error: Invalid mode " << mode << endl;
        return false;
    }

    ofstream file(this->filename.c_str(), mode);

    file << content;

    cout << "Successfully wrote to the file " << this->filename << endl;

    file.close();

    return true;
}

string file::readFile(){

    if(!this->searchFile()){
        return false;
    }

    else{
        ifstream file(this->filename, ifstream::binary | ios::ate);
    }

    if(!file.is_open()){
            cout << "Error opening file " << this->filename << endl;
            cleanup();

            return -2;
    }

    streampos fileSize = file.tellg();
    char* buffer = new char[fileSize];

    file.seekg(0, ios::beg); // Go back to the beginning of the file
    file.read(buffer, fileSize);
    
    file.close();

    string bufferString(buffer);
    delete[] buffer;

    return buferString;
}




bool file::searchFile(){

    //searches the file in the path

    //if found -> return true
    //if not found -> return false

    DIR *dir = opendir(this->filename.c_str());

    if(dir){
        struct dirent *entry;

        while(entry = readdir(dir)){
            
            if(strcmp(entry->d_name, this->filename.c_str()) == 0){
                closedir(dir);
                return true;
            }
        }
        closedir(dir);
    }
    else{
        cout << "Error: Unable to open the directory with the file " << this->filename << endl;
        return false;
    }

    cout << "Error: Unable to find the file " << this->filename << endl;

    return false;
}





file::~file(){

}