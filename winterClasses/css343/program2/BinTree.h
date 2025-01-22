#ifndef _BINTREE_H_
#define _BIN_TREE_H_

#include "nodedata.h"
#include <iostream>
using namespace std;
class BinTree
{ // you add class/method comments and assumptions
public:
    BinTree();                     // constructor
    BinTree(const BinTree &other); // copy constructor
    ~BinTree();                    // destructor, calls makeEmpty
    bool isEmpty() const;          // true if tree is empty, otherwise false
    void makeEmpty();              // make the tree empty so isEmpty returns true

    BinTree &operator=(const BinTree &other);    // assignment overload
    bool operator==(const BinTree &other) const; // equality
    bool operator!=(const BinTree &other) const; // not equality

    bool insert(NodeData *data);                                      // insert data into BSTree
    NodeData *remove(NodeData *target);                               // removes and returns nodeData if found
    bool retrieve(const NodeData &target, NodeData *&nodeData) const; // return target Nodedata if exists

    void bstreeToArray(NodeData *arr[]); // make BSTree into array
    void arrayToBSTree(NodeData *arr[]); // make array into BSTree

    friend ostream &operator<<(ostream &os, BinTree obj); //<< overload

    int getHeight(const NodeData &target) const; // return height of target node

    void displaySideways() const; // provided below, displays the tree sideways

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

    void recursiveDelete(Node *curNode);                                            // recursivly delete starting from curNode
    bool recursiveEqualsCheck(const Node *curNode, const Node *otherCurNode) const; // recursivly check equivalency starting from curNode
    int getHeight(const Node *curNode) const;                                       // get height of node
    Node *getNode(const NodeData &target) const;                                    // returns Node with target data
};

#endif //_BIN_TREE_H_