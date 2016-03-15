//
// Created by alex on 22.02.16.
//


#include "CompressionProgram.h"

using namespace std;
bool debug = true;

void CompressionProgram::compressFile(string *filename) {

    /* Create a map of characters ranking */
    map<char, int> mapChar = createMapSymbolsRating(filename);

    /* Create a list of nodes pointing to the symbols in mapChar */
    list<Node *> listNodesOfSymbolFrequencies =
            createListOfFrequenciesOfSymbolsNodes(&mapChar);

    /* Create the root of the binary tree Huffman */
    Node *root = createBinaryTreeHuffman(&listNodesOfSymbolFrequencies);

    /* Create Table of symbols and their codes */
    vector<bool> code; // temporary vector to store codes
    map<char, vector<bool> > table; // Table of symbols and their codes
    createTableOfEncodedSymbol(root, table, code);

    /* Debug */
    if (debug) {
        printBinaryTreeHuffman(root, 0); // Output to the console a binary tree Huffman.
    }

    //write in file our coded map - "table" and coded file, in char representation
    string codefiles = *filename + ".huff";
    createCompressedFile(codefiles, *filename, table);
    cout << "File compressed!" << endl;
}

map<char, int> CompressionProgram::createMapSymbolsRating(string *pString) {

    char n;
    ifstream str((*pString).c_str(), ios::binary); // Open the file for reading
    map<char, int> mapChar;

    /* We push symbol in Map and consider it a rating */
    while (str.get(n)) {
        mapChar[n]++; // Put in a Map symbol and calculate its rating
    }
    str.close(); // Close the file that is read

    /* Debug */
    if (debug) {
        map<char, int>::iterator itr;
        for (itr = mapChar.begin(); itr != mapChar.end(); itr++) { // The output to the console, the rating symbol
            cout << itr->first << " - " << itr->second << endl;
        }
    }
    return mapChar;
}

list<Node *> CompressionProgram::createListOfFrequenciesOfSymbolsNodes(map<char, int> *pMap) {

    list<Node *> listNode;
    map<char, int>::iterator itr;

    for (itr = pMap->begin(); itr != pMap->end(); ++itr) {
        Node *p = new Node;
        p->symbol = itr->first; // Is placed into a symbol of nodes pMap
        p->value = itr->second; // Is placed into a value of nodes pMap
        p->left = NULL;
        p->right = NULL;
        listNode.push_back(p); // Put node in the list of Nods
    }
    return listNode;
}

Node *CompressionProgram::createBinaryTreeHuffman(list<Node *> *listOfNodes) {
    while (listOfNodes->size() != 1) {

        listOfNodes->sort(Node::MyCompare()); // Sort the list of nodes, restart operators - MyCompare

        /* We get the first two Node sorted list */
        Node *sonL = listOfNodes->front();
        listOfNodes->pop_front();
        Node *sonR = listOfNodes->front();
        listOfNodes->pop_front();

        Node *parent = new Node(sonL, sonR); // Create a parent Node of the two youngest Nodes
        listOfNodes->push_back(parent);     // We put in the list of the parent Node
    }
    return listOfNodes->front();
}

void CompressionProgram::createTableOfEncodedSymbol(Node *root, map<char, vector<bool> > &table,
                                                    vector<bool> &code) {
    if (root->left != NULL) {
        code.push_back(0);
        createTableOfEncodedSymbol(root->left, table, code);
    }
    if (root->right != NULL) {
        code.push_back(1);
        createTableOfEncodedSymbol(root->right, table, code);
    }
    if (root->symbol) {
        table[root->symbol] = code; // put the symbol in MAP and its code
    }
    code.pop_back(); // remove the last element of the vector and return to the parent Node

}

void CompressionProgram::printBinaryTreeHuffman(Node *root, unsigned s = 0) {
    if (root != NULL) {
        printBinaryTreeHuffman(root->left, s + 3);
        for (unsigned i = 0; i < s; i++) { //
            cout << "  ";
        }
        if ((root->symbol) != 0) {
            cout << root->value << " (" << root->symbol << ")" << endl;
        } else {
            cout << root->value << endl;
        }
        printBinaryTreeHuffman(root->right, s + 3);
    }
}

void CompressionProgram::createCompressedFile(string &codedFile, string filename,
                                              map<char, vector<bool> > &table) {

    /* The encoded contents of the file as a reference to the symbol codes*/
    vector<bool> *codedContents = createAnEncodedFileContent(filename, table);
    int sizeInBitsEncodedContent = CompressionProgram::sizeInBitsEncodedContent;
    char sizeOfTableMap = table.size();
    ofstream fileCompressed(codedFile.c_str(), ios::binary); // Open the file for writing
    char buf = 0;
    /* Write the symbol table and the code in a compressed file */
    fileCompressed.put(sizeOfTableMap); // write to the file size of the table
    /*Debug*/
    if (debug) {
        cout << "Write to file size of the table :" << (int) sizeOfTableMap << endl;
    }
    /* Write to file all of the characters and the codes of the table in turn. */
    map<char, vector<bool> >::iterator itr;
    for (itr = table.begin(); itr != table.end(); ++itr) {
        char symbol = itr->first;
        /* Debug */
        if (debug) {
            cout << "Write to file symbol [ " << symbol;
        }
        fileCompressed.put(symbol); // write a symbol in the file

        vector<bool> tmp = itr->second;
        /* Debug */
        if (debug) {
            cout << " ] size [ " << tmp.size() << " ] code: ";
        }
        fileCompressed.put((char) tmp.size()); // write size of tmp vector

        /* Debug */
        if (debug) {
            for (int i = 0; i < tmp.size(); ++i) {
                cout << tmp[i];
            }
            cout << endl;
        }
        int vecbool = 0;
        for (int j = 0; j < tmp.size(); ++j) {
            vecbool = (vecbool << 1) | tmp[j]; // pushes the symbol code in an int, making the bitwise shift
        }
        fileCompressed.write((char *) &vecbool, sizeof(vecbool)); // write a symbol code in the file size of 4 bytes
    }

    /* Write to file length code the content in a byte 4 */
    fileCompressed.write((char *) &sizeInBitsEncodedContent, sizeof(sizeInBitsEncodedContent));

    /* Write in file coded content */
    int count = 0;
    buf = 0;
    for (int i = 0; i < codedContents->size(); i++) {
        buf = buf | (codedContents->at(i)) << (7 - count);
        count++;
        if (count == 8) {
            count = 0;
            fileCompressed << buf; // Write 1 byte coded content
            buf = 0;
        }
    }
    fileCompressed.close(); // Close file
}

vector<bool> *CompressionProgram::createAnEncodedFileContent(string filename, map<char, vector<bool> > &table) {

    /* The encoded contents of the file as a reference to the symbol codes */
    vector<bool> *codedContents = new vector<bool>();
    ifstream str(filename.c_str(), ios::binary); // Open the file for reading
    setlocale(LC_ALL, "Russian"); // understand the Cyrillic
    char ch;

    while (str.get(ch)) {
        vector<bool> tmp = table[ch]; // Put in a vector is considered a symbol code
        for (int i = 0; i < tmp.size(); i++) {
            codedContents->push_back(tmp[i]);
        }
    }
    str.close(); // Close the file that is read
    CompressionProgram::sizeInBitsEncodedContent = (int) codedContents->size();
    /*Debug*/
    if (debug) {
        cout << "Size in bits encoded content: " << codedContents->size() << endl;
    }

    /* Check whether the last byte is filled with bits? */
    if (codedContents->size() % 8 != 0) {
        while ((codedContents->size()) % 8 != 0) {
            codedContents->push_back(NULL); // Fill byte Null bits.
            /*Debug*/
            if (debug) {
                cout << "Size in bits encoded content: " << codedContents->size() << endl;
            }
        }
        /*Debug*/
        if (debug) {
            cout << "Size in bytes of the encoded content: " << "[ " << codedContents->size() / 8 << " ]" << endl;
        }
    }
    return codedContents;
}

void CompressionProgram::decompressionFile(string *fileHuff) {
    ifstream fileCompressed(*fileHuff, ios::binary); // Open the file for reading

    string fileNew = renamefile(*fileHuff);
    ofstream fileDecompressed(fileNew, ios::binary); // Open the file for writing

    char tabsize = 0;
    fileCompressed.get(tabsize); // read the size of the symbol table

    /* Fill Map characters and their codes */
    map<vector<bool>, char> tab;
    for (int i = 0; i < tabsize; i++) {
        char symbol;
        fileCompressed.get(symbol); // reading a symbol file
        char size;
        fileCompressed.get(size); // reading from the file size of the code bits
        int num = 0;
        fileCompressed.read((char *) &num, sizeof(int)); // reading a file with 4 bytes of code symbol
        vector<bool> keyCode;
        num = num << (sizeof(num) * 8 - size);
        for (char u = 0; u < size; u++) {
            keyCode.push_back(num < 0); // put the last bit in the vector
            num = num << 1; // to shift by 1 bit
        }
        tab[keyCode] = symbol; // put in the Map symbol and its code
    }

    /* Read the length of the coded content */
    int sizeInBitsEncodedContent = 0;
    fileCompressed.read((char *) &sizeInBitsEncodedContent, sizeof(sizeInBitsEncodedContent));

    /* Read the content code */
    vector<bool> codedContents;
    int counter = 0;
    int counterForByte = 0;
    while (!fileCompressed.eof()) {
        char ch = 0;
        fileCompressed.get(ch);// Read the 1 byte code
        while (counterForByte != 8) {
            codedContents.push_back(ch < 0); // put 1 bit code in the vector
            ch = ch << 1; // shift by 1 bit
            counterForByte++;
        }
        counterForByte = 0;
        counter = counter + 8;
    }
    vector<bool> res;
    for (int i = 0; i < (codedContents.size() - (codedContents.size() - sizeInBitsEncodedContent)); i++) {
        res.push_back(codedContents[i]);
        if (tab[res]) {
            fileDecompressed << tab[res];
            res.clear();
        }
    }
    cout << "File decoded!" << endl;
    fileCompressed.close(); // Close file
    fileDecompressed.close(); // Close file

}

string CompressionProgram::renamefile(string pString) {
    string temp;
    for (int i = 0; i < pString.length() - 4; ++i) {
        temp += pString[i];
    }
    temp += "copy";
    return temp;
}