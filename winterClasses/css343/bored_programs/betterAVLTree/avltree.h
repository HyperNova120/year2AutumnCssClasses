#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <functional>
using namespace std;

template <typename T, typename TComparison = less<T>>
class AVLTree
{
private:
    struct NodeData
    {
        T data_;
    };
    class Node
    {
    public:
        Node(T data, Node *parent);
        ~Node();

        Node *left_ = nullptr;
        Node *right_ = nullptr;
        Node *parent_ = nullptr;
        NodeData *nodeData = nullptr;
        int height_ = 0;
        int balanceFactor = 0;
        bool heightOnChange_ = false;
        bool balanceFactorOnChange_ = false;
    };

public:
    AVLTree();
    AVLTree(TComparison comp);
    AVLTree(const AVLTree &other);
    ~AVLTree();

    AVLTree<T, TComparison> &operator=(const AVLTree<T, TComparison> &other);
    bool operator==(const AVLTree<T, TComparison> &other) const;
    bool operator!=(const AVLTree<T, TComparison> &other) const;

    bool insert(T obj);
    bool contains(T obj) const;
    T retrieve(const T obj);
    bool remove(const T obj);
    bool isEmpty() const;
    int size() const;

private:

    Node *getNode(const T data) const;

    TComparison m_comp; // user defined comparison method
    bool TEqual(const T &A, const T &B) const;
    int size_ = 0;
    Node *root_ = nullptr;
};

template <typename T, typename TComparison>
class AVLTree<T *, TComparison>
{
};

#endif //_AVL_TREE_H_