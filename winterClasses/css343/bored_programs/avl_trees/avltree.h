#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stack>
#include <queue>
#include <iostream>
#include <cmath>
using namespace std;

/// @brief
/// @tparam T type to be stored
/// @tparam TComparison comparision function takes (T A, T B) that returns true only if A < B
template <typename T, typename TComparison = less<T>>
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
    AVLTree(TComparison comp);
    AVLTree(const AVLTree<T, TComparison> &other);
    ~AVLTree();

    AVLTree<T, TComparison> &operator=(const AVLTree<T, TComparison> &other);
    bool operator==(const AVLTree<T, TComparison> &other) const;
    bool operator!=(const AVLTree<T, TComparison> &other) const;

    bool insert(const T &obj);          // inserts a copy of obj into tree
    T *remove(const T &data);           // removes node from tree and returns it, calls remove
    T *retrieve(const T &data);         // returns node if tree contains, else nullptr
    bool contains(const T &data) const; // returns if tree contains data
    void print();                       // calls sideways
    bool isEmpty() const;               // returns if tree is empty

private:
    TComparison m_comp;                                                                    // user defined comparison method
    bool TEqual(const T &A, const T &B) const;                                             // equality checker for T using the user define comparison method
    void sideways(Node *current, int level) const;                                         // prints tree sideways to cout
    void calculateBalanceFactors(Node *curNode);                                           // calculates and sets balancefactors for curNode and all nodes under curNode
    int getHeight(Node *curNode);                                                          // returns height of curNode
    void balanceTreeInsertion(Node *changedNode);                                          // balances tree after insertion
    void balanceTreeRemove(Node *changedNode);                                             // balances tree after deletion
    T *remove(const T &data, bool original);                                               // performs remove operation
    int getRotationType(Node *gParent, Node *parent, Node *child);                         // returns rotation type needed
    void Rotate(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);   // rotates nodes based on rotation type
    void RotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs LL rotation
    void RotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs LR rotation
    void RotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs RR rotation
    void RotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs RL rotation

    Node *root_ = nullptr;
};

/// @brief default constructor
template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::AVLTree() {}

template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::AVLTree(TComparison comp)
{
    m_comp = comp;
}

/// @brief copy constructor
/// @param other AVLTree to duplicate
template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::AVLTree(const AVLTree<T, TComparison> &other)
{
    m_comp = other.m_comp;
    *this = other;
}

/// @brief deconstructor
template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::~AVLTree()
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

/// @brief assignment operator for AVLTree, performs a deep copy of other
/// @param other AVLTree to copy
/// @return returns AVLTree
template <typename T, typename TComparison>
inline AVLTree<T, TComparison> &AVLTree<T, TComparison>::operator=(const AVLTree<T, TComparison> &other)
{
    // TODO: insert return statement here
    if (&other == this)
    {
        return *this;
    }
    this->~AVLTree();
    if (other.root_ == nullptr)
    {
        return *this;
    }
    queue<Node *> nodeQueue = queue<Node *>();
    nodeQueue.push(other.root_);
    while (!nodeQueue.empty())
    {
        insert(*(nodeQueue.front()->data_));
        if (nodeQueue.front()->left_ != nullptr)
        {
            nodeQueue.push(nodeQueue.front()->left_);
        }
        if (nodeQueue.front()->right_ != nullptr)
        {
            nodeQueue.push(nodeQueue.front()->right_);
        }
        nodeQueue.pop();
    }
    return *this;
}

/// @brief equivalency operator
/// @param other AVLTree to compare against
/// @return true if AVLTree is equal to other, false if not equal
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::operator==(const AVLTree<T, TComparison> &other) const
{
    if (&other == this)
    {
        return true;
    }
    queue<Node *> nodeQueue = queue<Node *>();
    nodeQueue.push(root_);
    queue<Node *> otherNodeQueue = queue<Node *>();
    otherNodeQueue.push(other.root_);
    while (!nodeQueue.empty() && !otherNodeQueue.empty())
    {
        if (nodeQueue.front() == nullptr && otherNodeQueue.front() == nullptr)
        {
            nodeQueue.pop();
            otherNodeQueue.pop();
            continue;
        }
        if (nodeQueue.front() == nullptr ^ otherNodeQueue.front() == nullptr)
        {
            return false;
        }
        else if (!TEqual(*(nodeQueue.front()->data_), *(otherNodeQueue.front()->data_)))
        {
            return false;
        }
        nodeQueue.push(nodeQueue.front()->left_);
        nodeQueue.push(nodeQueue.front()->right_);

        otherNodeQueue.push(otherNodeQueue.front()->left_);
        otherNodeQueue.push(otherNodeQueue.front()->right_);
        nodeQueue.pop();
        otherNodeQueue.pop();
    }
    return true;
}

/// @brief non-equivalence operator
/// @param other AVLTree to compare against
/// @return true if AVLTree is not equal to other, false if equal
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::operator!=(const AVLTree<T, TComparison> &other) const
{
    return !(*this == other);
}

/// @brief insert deep copy of obj into AVLTree.
/// @param obj object to insert
/// @return true if insertion succeeded, false if obj is a duplicate
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::insert(const T &obj)
{
    if (root_ == nullptr)
    {
        root_ = new Node(obj);
    }
    Node *reader = root_;
    while (((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_) != nullptr)
    {
        if (TEqual(*reader->data_, obj))
        {
            return false;
        }
        reader = ((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_);
    }
    if (TEqual(*reader->data_, obj))
    {
        return false;
    }
    ((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_) = new Node(obj);
    balanceTreeInsertion(((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_));
    return true;
}

/// @brief removes and returns T from AVLTree
/// @param data T to search for and remove
/// @return deep copy of the T that was stored in the AVLTree
template <typename T, typename TComparison>
inline T *AVLTree<T, TComparison>::remove(const T &data)
{
    return remove(data, true);
}

/// @brief returns a pointer to the T object stored in the AVLTree
/// @param data T to search for and return
/// @return a pointer to the T object stored in the AVLTree, returns nullptr if not found
template <typename T, typename TComparison>
inline T *AVLTree<T, TComparison>::retrieve(const T &data)
{
    Node *reader = root_;
    while (reader != nullptr && !TEqual(*reader->data_, data))
    {
        reader = (m_comp(data, *reader->data_)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return reader;
}

/// @brief recursively searches for and removes the node storing data
/// @param data the data to search for and remove
/// @param original if this call was the first and not a recursive call
/// @return pointer to a deep copy of the T object stored in the AVLTree
template <typename T, typename TComparison>
inline T *AVLTree<T, TComparison>::remove(const T &data, bool original)
{
    if (root_ == nullptr)
    {
        return nullptr;
    }
    Node *parent = nullptr;
    Node *reader = root_;
    bool lastSearchMoveLeft = false;
    while (reader != nullptr && !TEqual(*reader->data_, data))
    {
        parent = reader;
        lastSearchMoveLeft = m_comp(data, *reader->data_);
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
        balanceTreeRemove(W);
    }

    return returner;
}

/// @brief returns the rotation required for the given nodes
/// @param gParent grandparent node
/// @param parent parent node
/// @param child child node
/// @return roation type for balancing, 1=LL, 2=LR, 3=RL, 4=RR, 0=WTF
template <typename T, typename TComparison>
inline int AVLTree<T, TComparison>::getRotationType(Node *gParent, Node *parent, Node *child)
{
    if (gParent->left_ == parent && parent->left_ == child)
    {
        // LL
        return 1;
    }
    else if (gParent->left_ == parent && parent->right_ == child)
    {
        // LR
        return 2;
    }
    else if (gParent->right_ == parent && parent->left_ == child)
    {
        // RL
        return 3;
    }
    else if (gParent->right_ == parent && parent->right_ == child)
    {
        // RR
        return 4;
    }
    // how tf
    return 0;
}

/// @brief performs a rotation on the given nodes
/// @param isSmallTree if root_ must be set
/// @param root parent of the grandparent node
/// @param gParent grandparent node
/// @param parent parent node
/// @param child child node
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::Rotate(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool leftToUpdate = (root->left_ == gParent);
    switch (getRotationType(gParent, parent, child))
    {
    case 1:
        // LL
        RotateLL(isSmallTree, root, gParent, parent, child);
        break;
    case 2:
        // LR
        RotateLR(isSmallTree, root, gParent, parent, child);
        break;
    case 3:
        // RL
        RotateRL(isSmallTree, root, gParent, parent, child);
        break;
    case 4:
        // RR
        RotateRR(isSmallTree, root, gParent, parent, child);
        break;
    default:
        cout << "HOW TF ARE WE HERE" << endl;
        break;
    }
}

/// @brief performs an LL rotation on the given nodes
/// @param isSmallTree if root_ must be set
/// @param root parent of grandparent node
/// @param gParent grandparent node
/// @param parent parent node
/// @param child child node
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::RotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool leftToUpdate = (root->left_ == gParent);
    gParent->left_ = parent->right_;
    parent->right_ = gParent;
    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = parent;
}

/// @brief performs an LR rotation on the given nodes
/// @param isSmallTree if root_ must be set
/// @param root parent of grandparent node
/// @param gParent grandparent node
/// @param parent parent node
/// @param child child node
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::RotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool leftToUpdate = (root->left_ == gParent);
    // rot 1
    parent->right_ = child->left_;
    child->left_ = parent;
    gParent->left_ = child;
    // rot2 parent=child, child=parent
    gParent->left_ = child->right_;
    child->right_ = gParent;
    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = child;
}

/// @brief performs an RR rotation on the given nodes
/// @param isSmallTree if root_ must be set
/// @param root parent of grandparent node
/// @param gParent grandparent node
/// @param parent parent node
/// @param child child node
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::RotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool leftToUpdate = (root->left_ == gParent);
    gParent->right_ = parent->left_;
    parent->left_ = gParent;
    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = parent;
}

/// @brief performs an RL rotation on the given nodes
/// @param isSmallTree if root_ must be set
/// @param root parent of grandparent node
/// @param gParent grandparent node
/// @param parent parent node
/// @param child child node
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::RotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool leftToUpdate = (root->left_ == gParent);
    // rot 1
    parent->left_ = child->right_;
    child->right_ = parent;
    gParent->right_ = child;
    // rot 2
    gParent->right_ = child->left_;
    child->left_ = gParent;
    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = child;
}

/// @brief returns if AVLTree contains data
/// @param data T Object to search for
/// @return true if AVLTree contains data, false if not
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::contains(const T &data) const
{
    Node *reader = root_;
    while (reader != nullptr && !TEqual(*reader->data_, data))
    {
        reader = (m_comp(*reader->data_, data)) ? reader->left : reader->right;
    }
    return reader != nullptr && TEqual(*reader->data_, data);
}

/// @brief prints AVLTree to cout
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::print()
{
    sideways(root_, 0);
}

/// @brief returns if AVLTree is empty
/// @return true if AVLTree is empty, false if not
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::isEmpty() const
{
    return root_ == nullptr;
}

/// @brief recursively calculates the balance factor (rightHeight - leftHeight) for curNode
/// @param curNode node to calculate the balance factor for
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::calculateBalanceFactors(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    curNode->balanceFactor_ = getHeight(curNode->right_) - getHeight(curNode->left_);
    calculateBalanceFactors(curNode->left_);
    calculateBalanceFactors(curNode->right_);
}

/// @brief calculates and returns height of given node
/// @param curNode node to get the height of
/// @return height of curNode
template <typename T, typename TComparison>
inline int AVLTree<T, TComparison>::getHeight(Node *curNode)
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

/// @brief balances the AVLTree after insertion
/// @param changedNode node that was inserted
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::balanceTreeInsertion(Node *changedNode)
{
    if (root_ == nullptr)
    {
        return;
    }
    calculateBalanceFactors(root_);

    // find path to change
    stack<Node *> nodeStack = stack<Node *>();
    nodeStack.push(root_);
    while (!nodeStack.empty() && !TEqual(*nodeStack.top()->data_, *changedNode->data_))
    {

        nodeStack.push(m_comp(*changedNode->data_, *(nodeStack.top()->data_)) ? nodeStack.top()->left_ : nodeStack.top()->right_);
    }

    // rotate
    Node *gParent = nodeStack.top();
    nodeStack.pop();
    Node *root = nodeStack.top();
    Node *parent = nullptr;
    Node *child = nullptr;
    nodeStack.pop();
    bool leftToUpdate = (root->left_ == gParent);
    while (!nodeStack.empty() && abs((*gParent).balanceFactor_) < 2)
    {
        child = parent;
        parent = gParent;
        gParent = root;
        root = nodeStack.top();
        leftToUpdate = (root->left_ == gParent);
        nodeStack.pop();
    }

    // check if we need to set root_
    bool isSmallTree = false;
    if (nodeStack.empty() && abs((*gParent).balanceFactor_) < 2 && abs((*root).balanceFactor_) > 1)
    {
        child = parent;
        parent = gParent;
        gParent = root;
        isSmallTree = true;
    }

    if ((nodeStack.empty() && abs((*gParent).balanceFactor_) < 2))
    {
        // balanced
        return;
    }
    Rotate(isSmallTree, root, gParent, parent, child);
}

/// @brief balances the AVLTree after remove
/// @param changedNode the node that replaced the deleted node, or the parent of the deleted node if the deleted node was a leaf
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::balanceTreeRemove(Node *changedNode)
{
    if (root_ == nullptr)
    {
        return;
    }
    calculateBalanceFactors(root_);

    // find path to change
    stack<Node *> nodeStack = stack<Node *>();
    nodeStack.push(root_);
    while (!nodeStack.empty() && !TEqual(*nodeStack.top()->data_, *changedNode->data_))
    {
        nodeStack.push(m_comp(*changedNode->data_, *(nodeStack.top()->data_)) ? nodeStack.top()->left_ : nodeStack.top()->right_);
    }

    Node *root = nullptr;
    Node *gParent = nullptr;
    root = nodeStack.top();
    nodeStack.pop();
    bool firstRun = true;
    while (!nodeStack.empty() || firstRun)
    {
        firstRun = false;
        if (!nodeStack.empty())
        {
            gParent = root;
            root = nodeStack.top();
            nodeStack.pop();
        }
        calculateBalanceFactors(root_);
        bool leftToUpdate = (root->left_ == gParent);
        bool isSmallTree = false;
        if (nodeStack.empty() && abs((*root).balanceFactor_) > 1)
        {
            isSmallTree = true;
            gParent = root;
        }
        if (abs((*gParent).balanceFactor_) > 1)
        {
            Node *parent = nullptr;
            Node *child = nullptr;
            if ((*gParent).balanceFactor_ < -1)
            {
                if ((*gParent->left_).balanceFactor_ <= 0)
                {
                    parent = gParent->left_;
                    child = parent->left_;
                    // LL
                    RotateLL(isSmallTree, root, gParent, parent, child);
                }
                else
                {
                    parent = gParent->left_;
                    child = parent->right_;
                    // LR
                    RotateLR(isSmallTree, root, gParent, parent, child);
                }
            }
            else
            {
                if ((*gParent->right_).balanceFactor_ >= 0)
                {
                    parent = gParent->right_;
                    child = parent->right_;
                    // RR
                    RotateRR(isSmallTree, root, gParent, parent, child);
                }
                else
                {
                    parent = gParent->right_;
                    child = parent->left_;
                    // RL
                    RotateRL(isSmallTree, root, gParent, parent, child);
                }
            }
        }
    }
}

/// @brief retuns if A and B are equal using to the set TComparison
/// @param A object ot compare against
/// @param B object to compare against
/// @return true if A equals B, false otherwise
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::TEqual(const T &A, const T &B) const
{
    return !m_comp(A, B) && !m_comp(B, A);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::sideways(Node *current, int level) const
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