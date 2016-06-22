//
// Created by alex on 18.04.16.
//

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "Node.h"
#include "CompressionProgram.h"


#define DEBUG true


void CompressionProgram::compressFile(string &ptrF) {

    /* Create a vector of characters ranking */
    vector<int> ratingOfSymbol(256);
    createRankingOfSymbols(ptrF, ratingOfSymbol);

    /* Create a list of nodes pointing to the symbols in ratingOfSymbol */
    list<Node *> listOfNodesRatingsSymbols = createListOfNodesWithRatingsSymbols(ratingOfSymbol);

    /* Create the root of the binary tree Huffman */
    Node *root = createHuffmanBinaryTree(listOfNodesRatingsSymbols);

    /* Create Table of symbols and their codes */
    vector<bool> code; // temporary vector to store codes
    vector<vector<bool> > table(256); // Table of symbols and their codes
    createTableOfEncodedSymbol(root, table, code);


    /* Debug */
    if (DEBUG)
        printBinaryTreeOfHuffman(root, 0); // Output to the console a binary tree Huffman.

    string codefile = ptrF + ".huff";
    createCompressedFile(codefile, ptrF, table, ratingOfSymbol);
    cout << "File compressed!" << endl;

}

void CompressionProgram::decompressionFile(string &ptrF) {
    string filename = renameF(ptrF);
    ifstream iFile(ptrF.c_str(), ios::binary); // Open the file for reading
    ofstream oFile(filename.c_str(), ios::binary); // Open the file for writing

    /* Create a vector of characters ranking */
    vector<int> symbolRating(256);

    int tableSize;
    iFile.read((char *) &tableSize, sizeof(tableSize));

    for (int i = 0; i < tableSize; i++) {
        iFile.read((char *) &symbolRating[i], sizeof(symbolRating[i]));
    }
    list<Node *> listNodesOfSymbolFrequencies = createListOfNodesWithRatingsSymbols(symbolRating);
    /* Create the root of the binary tree Huffman */
    Node *root = createHuffmanBinaryTree(listNodesOfSymbolFrequencies);
    Node *p = root;
    unsigned char byte;
    int count = 0;
    byte = iFile.get();

    while (!iFile.eof()) {

        bool b = byte & (1 << (7 - count));

        p = (b) ? p->right : p->left;

        if (p->symbol) {
            unsigned char k = p->symbol;
            oFile.put(k);
            p = root;
        }
        count++;
        if (count == 8) {
            count = 0;
            byte = iFile.get();
        }
    }

    iFile.close();
    oFile.close();
}

/* Create a vector of characters ranking  */
void CompressionProgram::createRankingOfSymbols(string &ptrF, vector<int> &symbolRating) {
    ifstream file(ptrF.c_str(), ios::binary);
    while (!file.eof()) {
        unsigned char ch = file.get();
        symbolRating[ch]++;
        if (DEBUG)
            cout << ch;
    }
    file.close();
    if (DEBUG) {
        separator();
        for (int i = 0; i < symbolRating.size(); ++i) {
            char a = i;
            cout << " " << symbolRating[i] << "-" << a << endl;
        }
    }
}

/* Create a list of nodes pointing to the symbols in vector */
list<Node *> CompressionProgram::createListOfNodesWithRatingsSymbols(vector<int> &symbolRating) {

    list<Node *> listNode;

    for (int i(0); i < symbolRating.size(); ++i) {
        Node *n = new Node;
        n->symbol = char(i);
        n->value = symbolRating[i];
        n->left = NULL;
        n->right = NULL;
        listNode.push_back(n);

    }
    if (DEBUG) {
        list<Node *>::iterator itr2 = listNode.begin();
        list<Node *>::iterator itr2_end = listNode.end();
        for (; itr2 != itr2_end; ++itr2) {
            Node *n = *itr2;
            cout << " " << n->symbol << "-" << n->value;
        }
        cout << endl;
    }
    return listNode;
}

/*
 *  Create the root of the binary tree Huffman
 *  @return - Node* root
 */
Node *CompressionProgram::createHuffmanBinaryTree(list<Node *> &ptrList) {
    while (ptrList.size() != 1) {
        ptrList.sort(Node::MyCompare()); // Sort the list of nodes, restart operators - MyCompare

        /* We get the first two Node sorted list */
        Node *sonL = ptrList.front();
        ptrList.pop_front();
        Node *sonR = ptrList.front();
        ptrList.pop_front();

        Node *parent = new Node(sonL, sonR); // Create a parent Node of the two youngest Nodes
        ptrList.push_back(parent); // We put in the list of the parent Node
    }
    if (DEBUG) {
        separator();
        cout << "root: " << ptrList.front()->symbol << " - " << ptrList.front()->value << endl;
    }
    return ptrList.front();
}

/* Create table of encoded symbol */
void CompressionProgram::createTableOfEncodedSymbol(Node *root, vector<vector<bool> > &ptrTable, vector<bool> &code) {
    if (root->left != NULL) {
        code.push_back(0);
        createTableOfEncodedSymbol(root->left, ptrTable, code);
    }
    if (root->right != NULL) {
        code.push_back(1);
        createTableOfEncodedSymbol(root->right, ptrTable, code);
    }
    if (root->symbol) {
        ptrTable[int(root->symbol)] = code; // put the symbol in vector and its code
    }
    code.pop_back(); // remove the last element of the deque and return to the parent Node
}

/* print in console Binary Tree Huffman */
void CompressionProgram::printBinaryTreeOfHuffman(Node *root, size_t s = 0) {
    if (root != NULL) {
        printBinaryTreeOfHuffman(root->left, s + 3);
        for (unsigned i = 0; i < s; i++) { //
            cout << "  ";
        }
        if ((root->symbol) != 0)
            cout << root->value << " (" << root->symbol << ")" << endl;
        else
            cout << root->value << endl;
        printBinaryTreeOfHuffman(root->right, s + 3);
    }
}

void CompressionProgram::createCompressedFile(string codefile, string &ptrF, vector<vector<bool> > table,
                                              vector<int> symbolRating) {
    ifstream iFile(ptrF.c_str(), ios::binary); // Open the file for reading

    ofstream oFile(codefile.c_str(), ios::binary); // Open the file for writing
    setlocale(LC_ALL, "Russian"); // understand the Cyrillic

    int tableSize = (int) symbolRating.size();
    oFile.write((char *) &tableSize, sizeof(tableSize));

    for (int j = 0; j < tableSize; ++j) {
        oFile.write((char *) &symbolRating[j], sizeof(symbolRating[j]));
    }
    int count = 0;
    unsigned char buf;

    while (!iFile.eof()) {
        unsigned char ch = iFile.get();
        vector<bool> tmp = table[ch]; // Put in a vector is considered a symbol code
        for (int i = 0; i < tmp.size(); i++) {
            buf = buf | tmp[i] << (7 - count);
            count++;
            if (count == 8) {
                count = 0;
                oFile << buf;
                buf = 0;
            }
        }
    }
    oFile.close(); // Close the file that is writing
    iFile.close(); // Close the file that is read
}

string CompressionProgram::renameF(string &basic_string) {
    string tmp;
    for (int i = 0; i < basic_string.size() - 5; ++i) {
        tmp += basic_string[i];
    }
    return tmp;
}

void CompressionProgram::separator() {
    cout << "-----------------------------------------------------------" << endl;
}

