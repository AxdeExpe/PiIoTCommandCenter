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




bool file::executeFile(){

    if(!this->searchFile()){
        return false;
    }

    //execute the file
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