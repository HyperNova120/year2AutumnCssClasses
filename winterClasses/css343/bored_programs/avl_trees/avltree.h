#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stack>
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class AVLTree
{
private:
public:
    class Node
    {
    public:
        Node(const T &data)
        {
            data_ = new T(data);
        }
        ~Node()
        {
            delete data_;
        }
        Node *left_ = nullptr;
        Node *right_ = nullptr;
        int balanceFactor_ = 0;
        T *data_ = nullptr;
    };
    AVLTree();
    AVLTree(const AVLTree<T> &other);
    ~AVLTree();

    bool insert(const T &obj);
    T *remove(const T &data);
    bool contains(const T &data) const;
    void print();

private:
    void deleteHelper();
    void sideways(Node *current, int level) const;
    void calculateBalanceFactors(Node *curNode);
    int getHeight(Node *curNode);
    void balanceTree(Node *changedNode);
    void removeNode(const T &data);
    T *remove(const T &data, bool original);
    int getRotationType(Node *GParent, Node *Parent, Node *child);

    Node *root_ = nullptr;
};


template <typename T>
inline AVLTree<T>::AVLTree() {}

template <typename T>
inline AVLTree<T>::AVLTree(const AVLTree<T> &other)
{
}

template <typename T>
inline AVLTree<T>::~AVLTree()
{
    deleteHelper();
}

template <typename T>
inline bool AVLTree<T>::insert(const T &obj)
{
    if (root_ == nullptr)
    {
        root_ = new Node(obj);
    }
    Node *reader = root_;
    while (((obj < *reader->data_) ? reader->left_ : reader->right_) != nullptr)
    {
        if (*reader->data_ == obj)
        {
            return false;
        }
        reader = ((obj < *reader->data_) ? reader->left_ : reader->right_);
    }
    if (*reader->data_ == obj)
    {
        return false;
    }
    ((obj < *reader->data_) ? reader->left_ : reader->right_) = new Node(obj);
    calculateBalanceFactors(root_);
    balanceTree(((obj < *reader->data_) ? reader->left_ : reader->right_));
    return true;
}

template <typename T>
inline T *AVLTree<T>::remove(const T &data)
{
    return remove(data, true);
}

template <typename T>
inline T *AVLTree<T>::remove(const T &data, bool original)
{
    if (root_ == nullptr)
    {
        return nullptr;
    }
    Node *parent = nullptr;
    Node *reader = root_;
    bool lastSearchMoveLeft = false;
    while (reader != nullptr && *reader->data_ != data)
    {
        parent = reader;
        lastSearchMoveLeft = data < *reader->data_;
        reader = (lastSearchMoveLeft) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    // found node to delete, now to find replacement node
    T *returner = new T(*reader->data_);
    Node *W = nullptr;

    if (reader->left_ == nullptr && reader->right_ == nullptr)
    {
        // leaf
        delete reader;
        ((lastSearchMoveLeft) ? parent->left_ : parent->right_) = nullptr;
        W = parent;
    }
    else if (reader->left_ == nullptr ^ reader->right_ == nullptr)
    {
        // single branch
        Node *replacement = ((reader->left_ != nullptr) ? reader->left_ : reader->right_);
        delete reader;
        ((lastSearchMoveLeft) ? parent->left_ : parent->right_) = replacement;
        W = replacement;
    }
    else
    {
        // dual branch
        Node *replacement = reader->right_;
        while (replacement->left_ != nullptr)
        {
            replacement = replacement->left_;
        }
        T *replacementData = remove(*replacement->data_, false);
        delete reader->data_;
        reader->data_ = replacementData;
        W = reader;
    }
    if (original)
    {
        calculateBalanceFactors(root_);
        balanceTree(W);
    }

    return returner;
}

// returns roation type for balancing, 1=LL, 2=LR, 3=RL, 4=RR, 0=WTF
template <typename T>
inline int AVLTree<T>::getRotationType(Node *GParent, Node *Parent, Node *child)
{
    if (GParent->left_ == Parent && Parent->left_ == child)
    {
        // LL
        return 1;
    }
    else if (GParent->left_ == Parent && Parent->right_ == child)
    {
        // LR
        return 2;
    }
    else if (GParent->right_ == Parent && Parent->left_ == child)
    {
        // RL
        return 3;
    }
    else if (GParent->right_ == Parent && Parent->right_ == child)
    {
        // RR
        return 4;
    }
    // how tf
    return 0;
}

template <typename T>
inline bool AVLTree<T>::contains(const T &data) const
{
    Node *reader = root_;
    while (reader != nullptr && *reader->data_ != data)
    {
        reader = (*reader->data_ < data) ? reader->left : reader->right;
    }
    return reader != nullptr && *reader->data_ == data;
}

template <typename T>
inline void AVLTree<T>::print()
{
    sideways(root_, 0);
}

template <typename T>
inline void AVLTree<T>::calculateBalanceFactors(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    curNode->balanceFactor_ = getHeight(curNode->right_) - getHeight(curNode->left_);
    calculateBalanceFactors(curNode->left_);
    calculateBalanceFactors(curNode->right_);
}

template <typename T>
inline int AVLTree<T>::getHeight(Node *curNode)
{
    if (curNode == nullptr)
    {
        return 0;
    }
    else if ((curNode->left_ == nullptr && curNode->right_ == nullptr))
    {
        return 1;
    }
    int left_height = getHeight(curNode->left_);
    int right_height = getHeight(curNode->right_);
    return 1 + ((left_height > right_height) ? left_height : right_height);
}

template <typename T>
inline void AVLTree<T>::balanceTree(Node *changedNode)
{
    if (root_ == nullptr)
    {
        return;
    }
    struct stackData
    {
        stackData(Node *nNode, bool l, bool r)
        {
            node = nNode;
            checkedLeft = l;
            checkedRight = r;
        }
        Node *node;
        bool checkedLeft = false;
        bool checkedRight = false;
    };

    // find path to change
    stack<stackData> nodeStack = stack<stackData>();
    nodeStack.push(stackData(root_, false, false));
    while (!nodeStack.empty() && *nodeStack.top().node->data_ != *changedNode->data_)
    {
        if (nodeStack.top().checkedLeft && nodeStack.top().checkedRight)
        {
            // checked both
            nodeStack.pop();
        }
        else if (nodeStack.top().checkedLeft && !nodeStack.top().checkedRight)
        {
            // need to check right
            nodeStack.top().checkedRight = true;
            if (nodeStack.top().node->right_ != nullptr)
            {
                nodeStack.push(stackData(nodeStack.top().node->right_, false, false));
            }
        }
        else
        {
            // need to check left
            nodeStack.top().checkedLeft = true;
            if (nodeStack.top().node->left_ != nullptr)
            {
                nodeStack.push(stackData(nodeStack.top().node->left_, false, false));
            }
        }
    }

    // rotate
    Node *root = nodeStack.top().node;
    Node *gParent = root;
    nodeStack.pop();
    root = nodeStack.top().node;
    Node *parent = nullptr;
    Node *child = nullptr;
    nodeStack.pop();
    bool leftToUpdate = (root->left_ == gParent) ? true : false;
    while (!nodeStack.empty() && abs((*gParent).balanceFactor_) < 2)
    {
        child = parent;
        parent = gParent;
        gParent = root;
        root = nodeStack.top().node;
        // gParent = nodeStack.top().node;
        leftToUpdate = (root->left_ == gParent) ? true : false;
        nodeStack.pop();
    }

    bool isSmallTree = false;
    if (nodeStack.empty() && abs((*gParent).balanceFactor_) < 2 && abs((*root).balanceFactor_) > 1)
    {
        cout << "isSmallTree" << endl;
        child = parent;
        parent = gParent;
        gParent = root;
        isSmallTree = true;
    }

    if ((nodeStack.empty() && abs((*gParent).balanceFactor_) < 2))
    {
        // balanced
        cout << "balanced" << endl;
        return;
    }
    int rotationType = getRotationType(gParent, parent, child);
    cout << "not balanced" << endl;
    cout << "GParent:" << *(gParent->data_) << " Parent:" << *(parent->data_) << " Child:" << *(child->data_) << " RoationType:" << rotationType << endl;
    switch (rotationType)
    {
    case 1:
        // LL
        gParent->left_ = parent->right_;
        parent->right_ = gParent;
        if (isSmallTree)
        {
            root_ = parent;
        }
        else
        {
            ((leftToUpdate) ? root->left_ : root->right_) = parent;
        }
        break;
    case 2:
        // LR
        // rot 1
        parent->right_ = child->left_;
        child->left_ = parent;
        gParent->left_ = child;
        // rot2 parent=child, child=parent
        gParent->left_ = child->right_;
        child->right_ = gParent;
        if (isSmallTree)
        {
            root_ = child;
        }
        else
        {
            ((leftToUpdate) ? root->left_ : root->right_) = child;
        }
        break;
    case 3:
        // RL
        // rot 1
        parent->left_ = child->right_;
        child->right_ = parent;
        gParent->right_ = child;
        // rot 2
        gParent->right_ = child->left_;
        child->left_ = gParent;
        if (isSmallTree)
        {
            root_ = child;
        }
        else
        {
            ((leftToUpdate) ? root->left_ : root->right_) = child;
        }
        break;
    case 4:
        // RR
        gParent->right_ = parent->left_;
        parent->left_ = gParent;
        if (isSmallTree)
        {
            root_ = parent;
        }
        else
        {
            ((leftToUpdate) ? root->left_ : root->right_) = parent;
        }
        break;
    default:
        cout << "HOW TF ARE WE HERE" << endl;
        break;
    }
}

template <typename T>
inline void AVLTree<T>::removeNode(const T &data)
{
    Node *parent = nullptr;
    Node *reader = root_;
    bool lastMoveLeft = false;
    while (reader != nullptr && *reader->data_ != data)
    {
        parent = reader;
        lastMoveLeft = (data < *reader->data_);
        reader = (lastMoveLeft) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        // node not found
        return;
    }

    // get replacement data
    if (reader->left_ == nullptr && reader->right_ == nullptr)
    {
        // leaf
        delete reader;
        ((lastMoveLeft) ? parent->left_ : parent->right_) = nullptr;
    }
    // walk down branch
    if (parent->left_ != nullptr)
    {
        // left branch
        Node *branchReader = parent->left_;
        while (branchReader->right_ != nullptr)
        {
            branchReader = branchReader->right_;
        }
        remove(*branchReader->data_);
    }
    else
    {
        // right branch
        Node *branchReader = parent->right_;
        while (branchReader->left_ != nullptr)
        {
            branchReader = branchReader->left_;
        }
        remove(*branchReader->data_);
    }
}

template <typename T>
inline void AVLTree<T>::deleteHelper()
{
    if (root_ == nullptr)
    {
        return;
    }
    stack<Node *> nodeStack;
    nodeStack.push(root_);
    while (!nodeStack.empty())
    {
        Node *curNode = nodeStack.top();
        nodeStack.pop();
        if (curNode == nullptr)
        {
            continue;
        }
        nodeStack.push(curNode->left_);
        nodeStack.push(curNode->right_);
        delete curNode;
    }
    root_ = nullptr;
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
template <typename T>
inline void AVLTree<T>::sideways(Node *current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right_, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }

        cout << *current->data_ << endl; // display information of object
        // cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}


#endif // AVLTREE_H_
