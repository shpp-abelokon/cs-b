//
// Created by alex on 22.02.16.
// 

#include "CompressionFile.h"


using namespace std;


void CompressionFile::compressFile(string *filename) {

    map<char, int> mapChar = createMapSymbolRate(filename);
    list<Node *> listNode;
    createListOfNodesContainSymbolsAndFrequency(&mapChar, &listNode);
    Node *root = createBinaryTreeHuffman(&listNode);
    vector<bool> code;
    map<char, vector<bool> > table;

    createTableCodeCharacters(root, code, table);

    printTableCodeCharacters(table);
}

map<char, int> CompressionFile::createMapSymbolRate(string *filename) {

    map<char, int> mapChar;
    ifstream file(*filename);
    string fileStr;
    if (file.is_open()) {
        while (file.good()) {
            getline(file, fileStr);
            for (int i = 0; i < fileStr.length(); ++i) {
                char n = fileStr[i];
                mapChar[n]++;
            }
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    map<char, int>::iterator j;
    for (j = mapChar.begin(); j != mapChar.end(); ++j) {
        cout << j->first << " " << j->second << endl;
    }
    return mapChar;
};


void CompressionFile::createListOfNodesContainSymbolsAndFrequency(map<char, int> *pMap, list<Node *> *lNode) {
    map<char, int>::iterator i;
    for (i = pMap->begin(); i != pMap->end(); ++i) {
        Node *p = new Node;
        p->symbol = i->first;
        p->value = i->second;
        p->left = NULL;
        p->right = NULL;
        lNode->push_back(p);
    }
}

Node *CompressionFile::createBinaryTreeHuffman(list<Node *> *pList) {

    //Building a binary tree until there is 1 item
    while (pList->size() != 1) {

        pList->sort(Node::MyCompare());

        Node *sonLeft = pList->front();
        pList->pop_front();
        Node *sonRight = pList->front();
        pList->pop_front();

        Node *parent = new Node(sonRight, sonLeft); // Call the constructor that creates the parent left and right node
        pList->push_back(parent);
    }
    print(pList->front(), 0);
    return pList->front();
}

void CompressionFile::print(Node *root, unsigned s = 0) {

    if (root != 0) {
        print(root->left, s + 2);
        for (unsigned i = 0; i < s; i++) {
            cout << "  ";
        }
        if ((root->symbol)) {
            cout << root->value << " [" << root->symbol << "]" << endl;

        } else {
            cout << root->value << endl;
        }
        print(root->right, s + 2);
    }

}

void CompressionFile::createTableCodeCharacters(Node *root, vector<bool> &code,
                                                map<char, vector<bool> > &table) {
    if (root->left != NULL) {
        code.push_back(0);
        createTableCodeCharacters(root->left, code, table);
    }
    if (root->right != NULL) {
        code.push_back(1);
        createTableCodeCharacters(root->right, code, table);
    }
    if (root->symbol) {
        table[root->symbol] = code;
    }
    code.pop_back();
}

void CompressionFile::printTableCodeCharacters(map<char, vector<bool> > &table) {
    map<char, vector<bool> >::iterator itr;
    for (itr = table.begin(); itr != table.end(); ++itr) {
        cout << itr->first << " - ";
        vector<bool> code = itr->second;
        for (int i = 0; i < code.size(); i++) {
            cout << code[i];
        }
        cout << endl;
    }
}
