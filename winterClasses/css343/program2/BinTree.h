#ifndef _BINTREE_H_
#define _BIN_TREE_H_

#include "nodedata.h"
#include <iostream>
using namespace std;
class BinTree
{ // you add class/method comments and assumptions
public:
    // constructor
    BinTree();

    // copy constructor
    BinTree(const BinTree &other);

    // destructor, calls deleteHelper
    ~BinTree();

    // true if tree is empty, otherwise false
    bool isEmpty() const;

    // make the tree empty so isEmpty returns true
    void makeEmpty();

    // assignment overload
    BinTree &operator=(const BinTree &other);

    // equality
    bool operator==(const BinTree &other) const;

    // not equality
    bool operator!=(const BinTree &other) const;

    // insert data into BSTree
    bool insert(NodeData *data);

    // return target Nodedata if exists
    bool retrieve(const NodeData &target, NodeData *&nodeData) const;

    // make BSTree into array
    void bstreeToArray(NodeData *arr[]);

    // make array into BSTree
    void arrayToBSTree(NodeData *arr[]);

    // ostream overload
    friend ostream &operator<<(ostream &os, BinTree obj);

    // return height of target node
    int getHeight(const NodeData &target) const;

    // provided below, displays the tree sideways
    void displaySideways() const;

private:
    int K_ARRAY_MAX_SIZE = 100; // predefined assumed size of array

    struct Node
    {
        NodeData *data = nullptr; // pointer to data object
        Node *left = nullptr;     // left subtree pointer
        Node *right = nullptr;    // right subtree pointer
    };
    Node *root = nullptr; // root of the tree

    // utility functions
    void inorderHelper(Node *curNode, ostream &output) const;

    // provided below, helper for displaySideways()
    void sideways(Node *current, int level) const;

    // recursivly delete starting from curNode
    void deleteHelper(Node *curNode);

    // recursivly check equivalency starting from curNode
    bool equivalencyHelper(const Node *curNode, const Node *otherCurNode) const;

    // get height of node
    int getHeightHelper(const Node *curNode) const;

    // returns Node with target data
    Node *getNode(const NodeData &target) const;

    // recursivly insert middle of low/high
    void arrayToBSTreeHelper(NodeData *arr[], int low, int high);

    // recursivly set arr[index] to nodeData via in-order traversal
    void bstreeToArrayHelper(Node *curNode, NodeData *arr[], int &index);

    // recursivly check each BST has equivalent nodes
    void assignmentHelper(Node *curNode);
};

#endif //_BIN_TREE_H_