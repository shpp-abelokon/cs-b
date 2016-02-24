//
// Created by alex on 22.02.16.
//
#include <iostream>
#include "CompressionFile.h"

#define CODED_FILE "test.txt"

using namespace std;

int main() {

    while (true) {
        cout << "File Compression, enter \"1\", enter \"2\" to decrypt the file, close the program enter \"exit\"." <<
        endl;
        string task;
        getline(cin, task);
        if (task == "exit") {
            break;
        }
        if (task == "1") {
            string filename;
//            cout<<"Enter filename: ";
//            getline(cin,filename);
            filename = CODED_FILE;
            CompressionFile *file = new CompressionFile();
            file->compressFile(&filename);
        } else if (task == "2") {

        } else {
            cout << "Unknown commando please try again!" << endl;
        }
    }
    return 0;
}
