#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(){

    // fstream std("filename.ext", mode);
    /*
    Mode	      Description
    ios::in	    File open for reading. If file does not exists, the open operation fails.
    ios::out	File open for writing: the internal stream buffer supports output operations.
    ios::binary	Operations are performed in binary mode rather than text.
    ios::ate	The output position starts at the end of the file.
    ios::app	All output operations happen at the end of the file, appending to its existing contents.
    ios::trunc	Any contents that existed in the file before it is open are discarded.
    */
    fstream file("mydummyfile", ios::in | ios::out);

    // ifstream: Stands for input file stream. It is equivalent to open fstream in ios::in mode.
    // ofstream: Stands for output file stream. It is equivalent to opening fstream in ios::out mode.

    ofstream fileout("mydummyfile");
    fileout << "welcome to my darkness!";
    fileout.close();

    ifstream filein("mydummyfile");
    if(filein.is_open()){
        string s;
        while(getline(filein, s)){
            cout << s << endl;
        }
        if(filein.eof()){
            cout << "reached end of file.\n"; 
        }
        else
            cerr << "Error: file reading failed!" << endl;
    }
    else{
        cerr << "Error: Unable to open file!" << endl;
        filein.close();
        return 1;
    }

    // writing data to binary file
    string msg = "Welcome to binary world.";

    ofstream binfile("binaryfile.bin", ios::binary);

    if(!binfile){
        cerr << "error opening the file for writing.";
        return 1;
    }
    
    size_t msgLength = msg.length();
    binfile.write(reinterpret_cast<const char *>(&msgLength), sizeof(msgLength));

    binfile.write(msg.c_str(), msgLength);

    binfile.close();

    // reading from binary file

    fstream readfile("binaryfile.bin", ios::in | ios::binary);

    if(!readfile){
        cerr << "Error opening the binary file!";
        return 1;
    }

    size_t strLength;
    readfile.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));

    
    string str(strLength, '\0');
    readfile.read(&str[0], strLength);

    cout << "file data: " << str;
    readfile.close();

    return 0;
}