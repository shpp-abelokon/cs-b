//
// Created by alex on 18.04.16.
//

#ifndef A4_HUFF_COMPRESSIONPROGRAM_H
#define A4_HUFF_COMPRESSIONPROGRAM_H


#include <iostream>
#include <list>
#include <vector>
#include "MyList.h"
#include "Node.h"

using namespace std;

class CompressionProgram {


public:
    CompressionProgram(){};

    ~CompressionProgram(){};

    void compressFile(string &ptrF);

    void decompressionFile(string &ptrF);

    void createRankingOfSymbols(string &ptrF, vector<int> &symbolRating);

    list<Node *> createListOfNodesWithRatingsSymbols(vector<int> &symbolRating);

    Node *createHuffmanBinaryTree(list<Node *> &ptrList);

    void createTableOfEncodedSymbol(Node *root, vector<vector<bool> > &ptrTable, vector<bool> &code);

    void printBinaryTreeOfHuffman(Node *pNode, size_t s);

    void createCompressedFile(string codefile, string &ptrF, vector<vector<bool> > table, vector<int> symbolRating);

    string renameF(string &basic_string);

    void separator();
};

#endif //A4_HUFF_COMPRESSIONPROGRAM_H
