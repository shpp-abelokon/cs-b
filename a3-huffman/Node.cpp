//
// Created by alex on 18.04.16.
//

#include <stddef.h>
#include "Node.h"

Node::Node() {

}

Node::Node(Node *L, Node *R) {
    left = L;
    right = R;
    symbol = NULL;

    value = L->value + R->value;


}