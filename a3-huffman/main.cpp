//
// Created by alex on 22.02.16.
//
#include <iostream>
#include "CompressionProgram.h"

#define CODED_FILE "test2.txt"
#define DECODED_FILE "test2.txt.huff"
#define DEBUG true

using namespace std;

int main() {
    while (true) {
        cout << endl;
        cout << "File Compression, enter \"1\", enter \"2\" to decrypt the file, close the program enter \"exit\"." <<
        endl;
        string task;
        getline(cin, task);
        if (task == "exit") {
            break;
        }
        string filename;
        if (task == "1") {
            if (DEBUG) {
                filename = CODED_FILE;
            } else {
                cout << "Enter filename: ";
                getline(cin, filename);
            }
            CompressionProgram *file = new CompressionProgram();
            file->compressFile(&filename);
            delete (file);
        } else if (task == "2") {
            if (DEBUG) {
                filename = DECODED_FILE;;
            } else {
                cout << "Enter filename: ";
                getline(cin, filename);
            }
            CompressionProgram *file = new CompressionProgram();
            file->decompressionFile(&filename);
            delete (file);
        } else {
            cout << "Unknown commando please try again!" << endl;
        }
    }
    return 0;
}