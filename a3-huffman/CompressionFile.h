//
// Created by alex on 22.02.16.
//

#ifndef A3_HUFFMAN_COMPRESSIONFILE_H
#define A3_HUFFMAN_COMPRESSIONFILE_H

#pragma once /* Защита от двойного подключения заголовочного файла */
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include "Node.h"

using namespace std;

class CompressionFile {
public:
    void compressFile(string *filename);

private:

    map<char, int> createMapSymbolRate(string *filename);
    void createListOfNodesContainSymbolsAndFrequency(map<char, int> *pMap, list<Node *> *lNode);

    Node * createBinaryTreeHuffman(list<Node *> *pList);

    void print(Node *root, unsigned s);
    void createTableCodeCharacters(Node *root, vector<bool> &code,
                                   map<char, vector<bool> > &table);

    void printTableCodeCharacters(map<char, vector<bool> > &table);
};


#endif //A3_HUFFMAN_COMPRESSIONFILE_H
