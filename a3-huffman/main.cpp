#include <iostream>
#include "CompressionProgram.h"

#define DEBUG true

#define CODED_FILE "test1.txt"
#define DECODED_FILE "test1.txt.huff"

void displayGreeting();

string &requestFile(string filename);

using namespace std;

int main() {
    while (true) {
        displayGreeting();
        string task;
        getline(cin, task);
        if (task == "exit")
            break;
        string filename;
        CompressionProgram *file = new CompressionProgram();
        if (task == "encode")
            file->compressFile(requestFile(CODED_FILE));
        else if (task == "decode")
            file->decompressionFile(requestFile(DECODED_FILE));
        else
            cout << "Unknown commando please try again!" << endl;
    }
    return 0;
}

string &requestFile(string filename) {
    if (!DEBUG) {
        cout << "Enter filename: ";
        getline(cin, filename);
    }
    return filename;
}

void displayGreeting() {
    cout << endl;
    cout <<
    "File Compression, enter \"encode\", enter \"decode\" to decrypt the file, close the program enter \"exit\"." <<
    endl;
    cout << ">> ";
}