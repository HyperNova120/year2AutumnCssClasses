#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stack>
#include <queue>
#include <iostream>
#include <cmath>
#include <iterator>
#include <cstddef>
using namespace std;

/// @brief
/// @tparam T type to be stored
/// @tparam TComparison comparision function takes (T A, T B) that returns true only if A < B
template <typename T, typename TComparison = less<T>>
class AVLTree
{
private:
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
        Node *left_ = nullptr;               // left branch
        Node *right_ = nullptr;              // right branch
        Node *parent_ = nullptr;             // right branch
        int balanceFactor_ = 0;              // balance factor
        int height_ = 0;                     // height
        bool heightOnChange_ = false;        // change the height was last updated on
        bool BalanceFactorOnChange_ = false; // change the balance factor was last updated on
        T *data_ = nullptr;                  // pointer to stored data
    };

public:
    /// @brief default constructor
    AVLTree();

    /// @brief constructor
    /// @param comp custom comparision method to compare T
    AVLTree(TComparison comp);

    /// @brief copy constructor
    /// @param other AVLTree to create a deep copy of
    AVLTree(const AVLTree<T, TComparison> &other);

    /// @brief deconstructor
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
    int size() const;                   // returns size of AVLTree

private:
    TComparison m_comp;                                                                    // user defined comparison method
    bool TEqual(const T &A, const T &B) const;                                             // equality checker for T using the user define comparison method
    void sideways(Node *current, int level) const;                                         // prints tree sideways to cout
    void calculateBalanceFactors(Node *curNode);                                           // calculates and sets balancefactors for curNode and all nodes under curNode
    int getHeight(Node *curNode);                                                          // returns height of curNode
    void balanceTreeInsertion(Node *curNode);                                              // balances tree after insertion
    void balanceTreeRemove(Node *changedNode);                                             // balances tree after deletion
    T *remove(const T &data, bool original, Node *curNode);                                // performs remove operation
    int getRotationType(Node *gParent, Node *parent, Node *child);                         // returns rotation type needed
    void Rotate(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);   // rotates nodes based on rotation type
    void RotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs LL rotation
    void RotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs LR rotation
    void RotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs RR rotation
    void RotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // performs RL rotation

    Node *root_ = nullptr; // root of AVL Tree
    int size_ = 0;         // number of nodes in AVL Tree

public:
    /// @brief Custom Iterator for AVLTree, allows for in-order forward-only stepping
    struct Iterator
    {
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        struct IteratorNodeData
        {
            Node *node = nullptr;
            bool vistedRightBranch = false;
            bool firstVisit = true;
        };
        stack<IteratorNodeData> nodeStack;
        TComparison m_compare;

    public:
        Iterator(Node *ptr, TComparison compare)
        {
            m_compare = compare;
            if (ptr == nullptr)
            {
                return;
            }
            Node *reader = ptr;
            do
            {
                nodeStack.push({reader, false});
                reader = reader->left_;
            } while (reader != nullptr);
            nodeStack.top().firstVisit = false;
            nodeStack.top().vistedRightBranch = true;
        };

        reference operator*() const { return *nodeStack.top().node->data_; };
        pointer operator->() { return nodeStack.top().node->data_; };

        // prefix
        Iterator &operator++()
        {
            if (nodeStack.size() == 0)
            {
                return *this;
            }
            if (nodeStack.top().vistedRightBranch)
            {
                // fully explored children
                while (nodeStack.size() != 0 && (nodeStack.top().vistedRightBranch))
                {
                    nodeStack.pop();
                }
            }
            else
            {
                // need to visit right
                if (nodeStack.top().node->right_ == nullptr && nodeStack.top().firstVisit)
                {
                    // no right node on first visit
                    nodeStack.top().firstVisit = false;
                    nodeStack.top().vistedRightBranch = true;
                    while (nodeStack.size() != 0 && (nodeStack.top().vistedRightBranch))
                    {
                        nodeStack.pop();
                    }
                    return *this;
                }
                nodeStack.top().vistedRightBranch = true;
                // has right node
                nodeStack.push({nodeStack.top().node->right_, (nodeStack.top().node->right_->right_ == nullptr)});
                while (nodeStack.top().node->left_ != nullptr)
                {
                    nodeStack.push({nodeStack.top().node->left_, false});
                }
            }

            return *this;
        }

        // postfix
        Iterator &operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b)
        {
            if (a.nodeStack.size() == 0 && b.nodeStack.size() == 0)
            {
                return true;
            }
            if (a.nodeStack.size() != b.nodeStack.size())
            {
                return false;
            }
            bool equalPlace = (a.nodeStack.top().vistedRightBranch && b.nodeStack.top().vistedRightBranch);
            equalPlace &= a.nodeStack.top().firstVisit == b.nodeStack.top().firstVisit;
            // equalPlace = equalPlace && (*a.nodeStack.top().node->data_ == *b.nodeStack.top().node->data_);
            equalPlace &= (!a.m_compare(*a.nodeStack.top().node->data_, *b.nodeStack.top().node->data_) && !a.m_compare(*b.nodeStack.top().node->data_, *a.nodeStack.top().node->data_));

            return equalPlace;
        }
        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return !(a == b);
        }
    };

    /// @brief returns iterator placed at the start of AVLTree
    /// @return Iterator at beginning of AVLTree
    Iterator begin() { return Iterator(root_, m_comp); }

    /// @brief returns iterator placed at end of AVLTree
    /// @return Iterator at end of AVLTree
    Iterator end() { return Iterator(nullptr, m_comp); }
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
    size_ = 0;
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
        size_ = 1;
    }
    Node *reader = root_;
    // reader->BalanceFactorOnChange_ = false;
    // reader->heightOnChange_ = false;
    while (((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_) != nullptr)
    {
        if (TEqual(*reader->data_, obj))
        {
            return false;
        }
        reader = ((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_);
        // reader->BalanceFactorOnChange_ = false;
        // reader->heightOnChange_ = false;
    }
    if (TEqual(*reader->data_, obj))
    {
        return false;
    }

    Node *tmp = reader;
    while (tmp != nullptr)
    {
        tmp->BalanceFactorOnChange_ = false;
        tmp->heightOnChange_ = false;
        tmp = tmp->parent_;
    }

    ((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_) = new Node(obj);
    ((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_)->parent_ = reader;
    balanceTreeInsertion(((m_comp(obj, *reader->data_)) ? reader->left_ : reader->right_));
    size_++;
    return true;
}

/// @brief removes and returns T from AVLTree
/// @param data T to search for and remove
/// @return deep copy of the T that was stored in the AVLTree
template <typename T, typename TComparison>
inline T *AVLTree<T, TComparison>::remove(const T &data)
{
    return remove(data, true, nullptr);
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
inline T *AVLTree<T, TComparison>::remove(const T &data, bool original, Node *curNode)
{
    if (root_ == nullptr)
    {
        return nullptr;
    }
    Node *parent = nullptr;
    Node *reader = root_;
    bool lastSearchMoveLeft = false;
    if (original)
    {
        while (reader != nullptr && !TEqual(*reader->data_, data))
        {
            // reader->BalanceFactorOnChange_ = false;
            // reader->heightOnChange_ = false;
            parent = reader;
            lastSearchMoveLeft = m_comp(data, *reader->data_);
            reader = (lastSearchMoveLeft) ? reader->left_ : reader->right_;
        }
        if (reader != nullptr)
        {
            // reader->BalanceFactorOnChange_ = false;
            // reader->heightOnChange_ = false;
            curNode = reader;
        }
    }
    else
    {
        reader = curNode;
        curNode = curNode->parent_;
        parent = curNode;
        // nodeStack.pop();
        lastSearchMoveLeft = (TEqual(*parent->left_->data_, *reader->data_));
    }
    if (reader == nullptr)
    {
        return nullptr;
    }

    Node *tmp = reader;
    while (tmp != nullptr)
    {
        tmp->BalanceFactorOnChange_ = false;
        tmp->heightOnChange_ = false;
        tmp = tmp->parent_;
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
        W->BalanceFactorOnChange_ = false;
        W->heightOnChange_ = false;
        while (curNode != nullptr && curNode != W)
        {
            curNode = curNode->parent_;
        }
    }
    else if (reader->left_ == nullptr ^ reader->right_ == nullptr)
    {
        // single branch
        Node *replacement = ((reader->left_ != nullptr) ? reader->left_ : reader->right_);
        ((lastSearchMoveLeft) ? parent->left_ : parent->right_) = replacement;
        replacement->parent_ = parent;
        delete reader;
        W = replacement;
        if (original)
        {
            curNode = curNode->parent_;
        }
        curNode->BalanceFactorOnChange_ = false;
        curNode->heightOnChange_ = false;
        curNode = W;
    }
    else
    {
        // dual branch
        Node *replacement = reader->right_;
        curNode = replacement;
        while (replacement->left_ != nullptr)
        {
            replacement = replacement->left_;
        }
        T *replacementData = remove(*replacement->data_, false, replacement);
        delete reader->data_;
        reader->data_ = replacementData;
        W = reader;
        while (curNode != nullptr && curNode != W)
        {
            curNode->BalanceFactorOnChange_ = false;
            curNode->heightOnChange_ = false;
            curNode = curNode->parent_;
        }
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

    // updateCurrentChange();
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
    if (parent->right_ != nullptr)
        parent->right_->parent_ = gParent;

    parent->right_ = gParent;
    gParent->parent_ = parent;

    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = parent;
    parent->parent_ = ((isSmallTree) ? nullptr : root);

    root_->BalanceFactorOnChange_ = false;
    root_->heightOnChange_ = false;
    gParent->BalanceFactorOnChange_ = false;
    gParent->heightOnChange_ = false;
    parent->BalanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
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
    if (child->left_ != nullptr)
        child->left_->parent_ = parent;

    child->left_ = parent;
    parent->parent_ = child;

    gParent->left_ = child;
    child->parent_ = gParent;
    // rot2 parent=child, child=parent
    gParent->left_ = child->right_;
    if (child->right_ != nullptr)
        child->right_->parent_ = gParent;

    child->right_ = gParent;
    gParent->parent_ = child;
    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = child;
    child->parent_ = ((isSmallTree) ? nullptr : root);

    root_->BalanceFactorOnChange_ = false;
    root_->heightOnChange_ = false;
    gParent->BalanceFactorOnChange_ = false;
    gParent->heightOnChange_ = false;
    parent->BalanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
    child->BalanceFactorOnChange_ = false;
    child->heightOnChange_ = false;
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
    if (parent->left_ != nullptr)
        parent->left_->parent_ = gParent;

    parent->left_ = gParent;
    gParent->parent_ = parent;

    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = parent;
    parent->parent_ = ((isSmallTree) ? nullptr : root);

    root_->BalanceFactorOnChange_ = false;
    root_->heightOnChange_ = false;
    gParent->BalanceFactorOnChange_ = false;
    gParent->heightOnChange_ = false;
    parent->BalanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
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
    if (child->right_ != nullptr)
        child->right_->parent_ = parent;

    child->right_ = parent;
    parent->parent_ = child;

    gParent->right_ = child;
    child->parent_ = gParent;
    // rot 2
    gParent->right_ = child->left_;
    if (child->left_ != nullptr)
        child->left_->parent_ = gParent;

    child->left_ = gParent;
    gParent->parent_ = child;
    ((isSmallTree) ? root_ : ((leftToUpdate) ? root->left_ : root->right_)) = child;
    child->parent_ = ((isSmallTree) ? nullptr : root);

    root_->BalanceFactorOnChange_ = false;
    root_->heightOnChange_ = false;
    gParent->BalanceFactorOnChange_ = false;
    gParent->heightOnChange_ = false;
    parent->BalanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
    child->BalanceFactorOnChange_ = false;
    child->heightOnChange_ = false;
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
    sideways(root_, -1);
}

/// @brief returns if AVLTree is empty
/// @return true if AVLTree is empty, false if not
template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::isEmpty() const
{
    return root_ == nullptr;
}

/// @brief returns size of AVLTree
/// @return number of nodes in AVLTree
template <typename T, typename TComparison>
inline int AVLTree<T, TComparison>::size() const
{
    return size_;
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
    if (curNode->BalanceFactorOnChange_)
    {
        return;
    }
    curNode->balanceFactor_ = getHeight(curNode->right_) - getHeight(curNode->left_);
    curNode->BalanceFactorOnChange_ = true;
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
    else if (curNode->heightOnChange_)
    {
        return curNode->height_;
    }

    int left_height = getHeight(curNode->left_);
    int right_height = getHeight(curNode->right_);

    curNode->height_ = 1 + ((left_height > right_height) ? left_height : right_height);
    curNode->heightOnChange_ = true;
    return curNode->height_;
}

/// @brief balances the AVLTree after insertion
/// @param changedNode node that was inserted
/// @param nodeStack node stack trace from root to inserted node
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::balanceTreeInsertion(Node *curNode)
{
    if (root_ == nullptr)
    {
        return;
    }

    // find path to change
    /* stack<Node *> nodeStack = stack<Node *>();
    nodeStack.push(root_);
    while (!TEqual(*nodeStack.top()->data_, *changedNode->data_))
    {
        nodeStack.push(m_comp(*changedNode->data_, *(nodeStack.top()->data_)) ? nodeStack.top()->left_ : nodeStack.top()->right_);
    } */

    // rotate
    Node *gParent = curNode;
    curNode = curNode->parent_;
    Node *root = curNode;
    Node *parent = nullptr;
    Node *child = nullptr;
    curNode = curNode->parent_;
    calculateBalanceFactors(gParent);
    bool leftToUpdate = (root->left_ == gParent);
    while (curNode != nullptr && abs((*gParent).balanceFactor_) < 2)
    {
        child = parent;
        parent = gParent;
        gParent = root;
        root = curNode;
        leftToUpdate = (root->left_ == gParent);
        calculateBalanceFactors(gParent);
        curNode = curNode->parent_;
    }

    // check if we need to set root_
    bool isSmallTree = false;
    if (curNode == nullptr && abs((*gParent).balanceFactor_) < 2)
    {
        calculateBalanceFactors(root);
        if (abs((*root).balanceFactor_) > 1)
        {
            child = parent;
            parent = gParent;
            gParent = root;
            isSmallTree = true;
        }
    }

    if ((curNode == nullptr && abs((*gParent).balanceFactor_) < 2))
    {
        // balanced
        return;
    }
    Rotate(isSmallTree, root, gParent, parent, child);
}

/// @brief balances the AVLTree after remove
/// @param changedNode the node that replaced the deleted node, or the parent of the deleted node if the deleted node was a leaf
template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::balanceTreeRemove(Node *curNode)
{
    if (root_ == nullptr)
    {
        return;
    }

    // find path to change
    /* stack<Node *> nodeStack = stack<Node *>();
    nodeStack.push(root_);
    while (!nodeStack.empty() && !TEqual(*nodeStack.top()->data_, *changedNode->data_))
    {
        nodeStack.push(m_comp(*changedNode->data_, *(nodeStack.top()->data_)) ? nodeStack.top()->left_ : nodeStack.top()->right_);
    } */

    Node *root = nullptr;
    Node *gParent = nullptr;
    root = curNode;
    curNode = curNode->parent_;
    bool firstRun = true;
    // calculateBalanceFactors(root);
    while (curNode != nullptr || firstRun)
    {
        firstRun = false;
        if (curNode != nullptr)
        {
            gParent = root;
            root = curNode;
            curNode = curNode->parent_;
        }
        bool leftToUpdate = (root->left_ == gParent);
        bool isSmallTree = false;
        if (curNode == nullptr) // && abs((*root).balanceFactor_) > 1)
        {
            isSmallTree = true;
            gParent = root;
        }
        calculateBalanceFactors(gParent);
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
        for (int i = level; i > 0; i--)
        {
            cout << "    ";
        }

        cout << *current->data_ << endl; // display information of object
        // cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}

#endif // AVLTREE_H_