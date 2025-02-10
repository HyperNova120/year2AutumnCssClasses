#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
#include <functional>
using namespace std;

template <typename T, typename TComparison = less<T>>
class RBTree
{
private:
    const bool RED = true;
    const bool BLACK = false;
    struct Node
    {
        T *data_ = nullptr;
        Node *left_ = nullptr;
        Node *right_ = nullptr;
        Node _parent_ = nullptr;
        bool color = RED;
    };

public:
    RBTree();
    RBTree(TComparison compare);
    RBTree(const RBTree &other);
    ~RBTree();

    RBTree &operator=(const RBTree &other);

    bool insert(const T &obj);
    T *remove(const T &obj);
    bool contains(const T &obj) const;
    T *retrieve(const T &obj) const;
    void print() const;
    bool isEmpty() const;
    int size() const;

private:
    TComparison m_comp;                                                                   // user defined comparison method
    bool TEqual(const T &A, const T &B) const { return !m_comp(A, B) && !m_comp(B, A); }; // equality checker for T using the user define comparison method
    void sideways(Node *current, int level) const;                                        // prints tree sideways to cout
    void balanceInsertion(Node *curNode);

    Node *root_ = nullptr;
    int size_ = 0;

};

#endif //_RED_BLACK_TREE_H_