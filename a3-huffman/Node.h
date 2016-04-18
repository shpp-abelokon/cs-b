//
// Created by alex on 18.04.16.
//

#ifndef A4_HUFF_NODE_H
#define A4_HUFF_NODE_H


class Node {
public:
    int value;
    unsigned char symbol;
    Node *left, *right;

    Node();

    Node(Node *L, Node *R);

    struct MyCompare {
        bool operator()(Node *l, Node *r) const {
            return l->value < r->value;
        }
    };
};


#endif //A4_HUFF_NODE_H
