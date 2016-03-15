//
// Created by alex on 22.02.16.
//

#ifndef A3_HUFFMAN_COMPRESSIONFILE_H
#define A3_HUFFMAN_COMPRESSIONFILE_H

#include <map>
#include <list>
#include <vector>
#include "Node.h"

using namespace std;

class CompressionProgram {

public:

    int sizeInBitsEncodedContent = 0;

    void compressFile(string *filename);

    void decompressionFile(string *fileHuff);


private:
    map<char, int> createMapSymbolsRating(string *pString);

    list<Node *> createListOfFrequenciesOfSymbolsNodes(map<char, int> *pMap);

    Node *createBinaryTreeHuffman(list<Node *> *listOfNodes);

    void createTableOfEncodedSymbol(Node *root, map<char, vector<bool> > &table,
                                    vector<bool> &code);

    void printBinaryTreeHuffman(Node *root, unsigned s);

    void createCompressedFile(string &codedFile, string filename, map<char, vector<bool> > &table);

    vector<bool> *createAnEncodedFileContent(string filename, map<char, vector<bool> > &table);

    string renamefile(string pString);

public:
    ~CompressionProgram() {
    }
};


#endif //A3_HUFFMAN_COMPRESSIONFILE_H
