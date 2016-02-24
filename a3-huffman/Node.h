//
// Created by alex on 22.02.16.
//

#ifndef A3_HUFFMAN_NODE_H
#define A3_HUFFMAN_NODE_H

#include <stddef.h>

class Node {
public:
    int value;
    char symbol;
    Node *left, *right;

    Node();

    Node(Node *L, Node *R);

    struct MyCompare {
        bool operator()(Node *l, Node *r) const {
            return l->value < r->value;
        }
    };
};

#endif //A3_HUFFMAN_NODE_H
