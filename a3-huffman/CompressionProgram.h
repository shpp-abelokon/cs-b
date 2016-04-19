//
// Created by alex on 18.04.16.
//

#ifndef A4_HUFF_COMPRESSIONPROGRAM_H
#define A4_HUFF_COMPRESSIONPROGRAM_H


#include <iostream>
#include <list>
#include <vector>
#include "myList.h"
#include "Node.h"

using namespace std;

class CompressionProgram {


public:
    CompressionProgram(){};

    ~CompressionProgram(){};

    void compressFile(string &ptrF);

    void decompressionFile(string &ptrF);

    void createSymbolsRating(string &ptrF, vector<int> &symbolRating);

    list<Node *> createListOfFrequenciesOfSymbolsNodes(vector<int> &symbolRating);

    Node *createBinaryTreeHuffman(list<Node *> &ptrList);

    void createTableOfEncodedSymbol(Node *root, vector<vector<bool> > &ptrTable, vector<bool> &code);

    void printBinaryTreeHuffman(Node *pNode, size_t s);

    void createCompressedFile(string codefile, string &ptrF, vector<vector<bool> > table, vector<int> symbolRating);

    string renameF(string &basic_string);
};

#endif //A4_HUFF_COMPRESSIONPROGRAM_H
