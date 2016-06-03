#include <iostream>
#include "CompressionProgram.h"

#define DEBUG true

#define CODED_FILE "/home/lex/ClionProjects/cs-b/a3-huffman/test1.txt"
#define DECODED_FILE "/home/lex/ClionProjects/cs-b/a3-huffman/test1.txt.huff"

void displayGreeting();

string &fileRequest(string filename);

using namespace std;

int main() {
    while (true) {
        displayGreeting();
        string task;
        getline(cin, task);
        if (task == "exit") break;
        string filename;
        CompressionProgram *file = new CompressionProgram();
        if (task == "encode") file->compressFile(fileRequest(CODED_FILE));
        else if (task == "decode") file->decompressionFile(fileRequest(DECODED_FILE));
        else cout << "Unknown commando please try again!" << endl;
        delete (file);
    }
    return 0;
}

string &fileRequest(string filename) {
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