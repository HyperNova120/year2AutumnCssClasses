#ifndef _BINTREE_H_
#define _BIN_TREE_H_

#include "nodedata.h"
#include <iostream>
using namespace std;
class BinTree
{ // you add class/method comments and assumptions
public:
    BinTree();                // constructor
    BinTree(const BinTree &); // copy constructor
    ~BinTree();               // destructor, calls makeEmpty
    bool isEmpty() const;     // true if tree is empty, otherwise false
    void makeEmpty();         // make the tree empty so isEmpty returns true
    BinTree &operator=(const BinTree &other);
    bool operator==(const BinTree &other) const;
    bool operator!=(const BinTree &other) const;
    bool insert(NodeData *data);
    bool retrieve(const NodeData &target, NodeData *&nodeData) const;
    void displaySideways() const; // provided below, displays the tree sideways
    friend ostream &operator<<(ostream &os, BinTree obj);

private:
    struct Node
    {
        NodeData *data = nullptr; // pointer to data object
        Node *left = nullptr;     // left subtree pointer
        Node *right = nullptr;    // right subtree pointer
    };
    Node *root = nullptr; // root of the tree

    // utility functions
    void inorderHelper(...) const;
    void sideways(Node *, int) const; // provided below, helper for displaySideways()
};

#endif //_BIN_TREE_H_