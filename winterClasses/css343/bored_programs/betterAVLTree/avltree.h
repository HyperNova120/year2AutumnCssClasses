#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <functional>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template <typename T, typename TComparison = less<T>>
class AVLTree
{
protected:
    struct NodeData
    {
        T data_;
    };
    class Node
    {
    public:
        Node(T data, Node *parent)
        {
            nodeData = new NodeData{data};
            parent_ = parent;
        };
        ~Node()
        {
            delete nodeData;
        };

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
    T *retrieve(const T obj);
    bool remove(const T obj);
    bool isEmpty() const;
    int size() const;
    void print(); // calls sideways

protected:
    void remove(Node *curNode, bool original);

    void calculateBalanceFactor(Node *curNode);
    int getHeight(Node *curNode);

    void balanceInsert(Node *curNode);
    void balanceRemove(Node *curNode);

    void rotate(bool isInsert, bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
    void rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
    void rotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
    void rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
    void rotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);

    void sideways(Node *current, int level) const; // prints tree sideways to cout

    TComparison m_comp; // user defined comparison method
    bool TEqual(const T &A, const T &B) const;
    bool TCompare(const T &A, const T &B) const;
    int size_ = 0;
    Node *root_ = nullptr;

    void wtf(Node *curNode);
};

template <typename T, typename TComparison>
class AVLTree<T *, TComparison> : public AVLTree<T>
{
private:
    using typename AVLTree<T>::Node;
    bool TCompare(const T &A, const T &B) const;
    void sideways(Node *current, int level) const; // prints tree sideways to cout
};

template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::AVLTree() {}

template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::AVLTree(TComparison comp)
{
    m_comp = comp;
}

template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::AVLTree(const AVLTree &other)
{
    *this = other;
}

template <typename T, typename TComparison>
inline AVLTree<T, TComparison>::~AVLTree()
{
    if (root_ == nullptr)
    {
        return;
    }
    stack<Node *> deleteStack;
    deleteStack.push(root_);
    while (!deleteStack.empty())
    {
        Node *tmp = deleteStack.top();
        deleteStack.pop();
        if (tmp->left_ != nullptr)
        {
            deleteStack.push(tmp->left_);
        }
        if (tmp->right_ != nullptr)
        {
            deleteStack.push(tmp->right_);
        }
        delete tmp;
    }
    root_ = nullptr;
}

template <typename T, typename TComparison>
inline AVLTree<T, TComparison> &AVLTree<T, TComparison>::operator=(const AVLTree<T, TComparison> &other)
{
    this->~AVLTree();
    if (other.root_ == nullptr)
    {
        return *this;
    }
    queue<Node *> buffer;
    buffer.push(other.root_);
    while (!buffer.empty())
    {
        Node *tmp = buffer.front();
        buffer.pop();
        if (tmp->left_ != nullptr)
        {
            buffer.push(tmp->left_);
        }
        if (tmp->right_ != nullptr)
        {
            buffer.push(tmp->right_);
        }
        insert(tmp->nodeData->data_);
    }
    return *this;
}

template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::insert(T obj)
{
    if (root_ == nullptr)
    {
        root_ = new Node(obj, nullptr);
        size_ = 1;
        return true;
    }
    Node *reader = root_;
    bool moveLeft = TCompare(obj, reader->nodeData->data_);
    while (!TEqual(reader->nodeData->data_, obj) && ((moveLeft) ? reader->left_ : reader->right_) != nullptr)
    {
        reader = ((moveLeft) ? reader->left_ : reader->right_);
        moveLeft = TCompare(obj, reader->nodeData->data_);
    }
    if (TEqual(reader->nodeData->data_, obj))
    {
        // duplicate
        return false;
    }

    Node *tmp = new Node(obj, reader);
    ((moveLeft) ? reader->left_ : reader->right_) = tmp;
    size_++;
    while (reader != nullptr)
    {
        reader->balanceFactorOnChange_ = false;
        reader->heightOnChange_ = false;
        reader = reader->parent_;
    }
    balanceInsert(tmp);
    //wtf(root_);
    return true;
}

template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::contains(T obj) const
{
    Node *reader = root_;
    while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(obj, reader->nodeData->data_)) ? reader->left_ : reader->right_;
    }
    return reader != nullptr;
}

template <typename T, typename TComparison>
inline T *AVLTree<T, TComparison>::retrieve(const T obj)
{
    Node *reader = root_;
    while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(obj, reader->nodeData->data_)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return &reader->nodeData->data_;
}

template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::remove(const T obj)
{
    Node *reader = root_;
    while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(obj, reader->nodeData->data_)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return false;
    }

    Node *tmp = reader->parent_;
    while (tmp != nullptr)
    {
        tmp->balanceFactorOnChange_ = false;
        tmp->heightOnChange_ = false;
        tmp = tmp->parent_;
    }

    // Node *curNode = reader->parent_;
    remove(reader, true);

    // balanceRemove(curNode);

    return true;
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::remove(Node *curNode, bool original)
{
    Node *W = nullptr;
    if (curNode->left_ == nullptr && curNode->right_ == nullptr)
    {
        // leaf
        if (curNode->parent_ == nullptr)
        {
            // is root
            root_ = nullptr;
        }
        else
        {
            if (TCompare(curNode->nodeData->data_, curNode->parent_->nodeData->data_))
            {
                // left
                curNode->parent_->left_ = nullptr;
            }
            else
            {
                // right
                curNode->parent_->right_ = nullptr;
            }
            W = curNode->parent_;
        }
        delete curNode;
        // return;
    }
    else if (curNode->left_ == nullptr ^ curNode->right_ == nullptr)
    {
        // single branch
        Node *branch = ((curNode->left_ == nullptr) ? curNode->right_ : curNode->left_);
        if (curNode->parent_ == nullptr)
        {
            root_ = branch;
            branch->parent_ = nullptr;
            W = branch;
        }
        else
        {
            branch->parent_ = curNode->parent_;
            if (curNode->parent_->left_ == curNode)
            {
                // replace left branch
                curNode->parent_->left_ = branch;
            }
            else
            {
                // replace right branch
                curNode->parent_->right_ = branch;
            }
            W = curNode->parent_;
        }
        delete curNode;
    }
    else
    {
        // dual branch
        Node *replacement = curNode->right_;
        replacement->balanceFactorOnChange_ = false;
        replacement->heightOnChange_ = false;
        while (replacement->left_ != nullptr)
        {
            replacement = replacement->left_;
            replacement->balanceFactorOnChange_ = false;
            replacement->heightOnChange_ = false;
        }
        T replacementData = replacement->nodeData->data_;
        remove(replacement, false);
        curNode->nodeData->data_ = replacementData;
        curNode->balanceFactorOnChange_ = false;
        curNode->heightOnChange_ = false;
        W = curNode;
    }
    if (W != nullptr && original)
    {
        balanceRemove(W);
    }
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::calculateBalanceFactor(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    else if (curNode->balanceFactorOnChange_)
    {
        return;
    }
    int leftHeight = getHeight(curNode->left_);
    int rightHeight = getHeight(curNode->right_);
    curNode->balanceFactor = rightHeight - leftHeight;
    curNode->balanceFactorOnChange_ = true;
}
template <typename T, typename TComparison>
inline int AVLTree<T, TComparison>::getHeight(Node *curNode)
{
    if (curNode == nullptr)
    {
        return 0;
    }
    else if (curNode->left_ == nullptr && curNode->right_ == nullptr)
    {
        return 1;
    }
    else if (curNode->heightOnChange_)
    {
        return curNode->height_;
    }
    int leftHeight = getHeight(curNode->left_);
    int rightHeight = getHeight(curNode->right_);
    curNode->height_ = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    curNode->heightOnChange_ = true;
    return curNode->height_;
}

template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::isEmpty() const
{
    return root_ == nullptr;
}

template <typename T, typename TComparison>
inline int AVLTree<T, TComparison>::size() const
{
    return size_;
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::print()
{
    sideways(root_, -1);
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::balanceInsert(Node *curNode)
{
    Node *gParent = curNode;
    Node *root = curNode->parent_;
    Node *parent = nullptr;
    Node *child = nullptr;
    calculateBalanceFactor(gParent);
    while (root != nullptr && abs(gParent->balanceFactor) < 2)
    {
        child = parent;
        parent = gParent;
        gParent = root;
        root = root->parent_;
        calculateBalanceFactor(gParent);
    }
    if (root == nullptr && abs(gParent->balanceFactor) < 2)
    {
        // balanced
        return;
    }
    if (root_ == gParent)
    {
        // smallTree
        rotate(true, true, nullptr, gParent, parent, child);
    }
    else
    {
        // not smallTree
        rotate(true, false, root, gParent, parent, child);
    }
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::balanceRemove(Node *curNode)
{
    Node *root = nullptr;
    Node *gParent = curNode;
    Node *parent = nullptr;
    Node *child = nullptr;
    while (gParent != nullptr)
    {
        bool isSmallTree = true;
        root = gParent->parent_;
        if (root != nullptr)
        {
            isSmallTree = false;
            root->balanceFactorOnChange_ = false;
            root->heightOnChange_ = false;
        }
        calculateBalanceFactor(gParent);
        if (abs(gParent->balanceFactor) > 1)
        {
            rotate(false, isSmallTree, root, gParent, parent, child);
        }
        gParent = root;
    }
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::rotate(bool isInsert, bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    if (isInsert)
    {
        // rotate insert
        if (gParent->left_ == parent)
        {
            // L
            if (parent->left_ == child)
            {
                // LL
                rotateLL(isSmallTree, root, gParent, parent, child);
            }
            else
            {
                // LR
                rotateLR(isSmallTree, root, gParent, parent, child);
            }
        }
        else
        {
            // R
            if (parent->left_ == child)
            {
                // RL
                rotateRL(isSmallTree, root, gParent, parent, child);
            }
            else
            {
                // RR
                rotateRR(isSmallTree, root, gParent, parent, child);
            }
        }
    }
    else
    {
        // rotate remove
        if (gParent->balanceFactor < -1)
        {
            // L
            parent = gParent->left_;
            calculateBalanceFactor(parent);
            if (parent->balanceFactor <= 0)
            {
                // LL
                child = parent->left_;
                rotateLL(isSmallTree, root, gParent, parent, child);
            }
            else
            {
                // LR
                child = parent->right_;
                rotateLR(isSmallTree, root, gParent, parent, child);
            }
        }
        else
        {
            // R
            parent = gParent->right_;
            calculateBalanceFactor(parent);
            if (parent->balanceFactor >= 0)
            {
                // RR
                child = parent->right_;
                rotateRR(isSmallTree, root, gParent, parent, child);
            }
            else
            {
                // RL
                child = parent->left_;
                rotateRL(isSmallTree, root, gParent, parent, child);
            }
        }
    }
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool isLeft = false;
    if (!isSmallTree)
    {
        isLeft = (root->left_ == gParent);
        /* root_->balanceFactorOnChange_ = false;
        root_->heightOnChange_ = false; */
    }
    gParent->left_ = parent->right_;
    gParent->parent_ = parent;
    if (gParent->left_ != nullptr)
    {
        gParent->left_->parent_ = gParent;
    }

    parent->right_ = gParent;
    gParent->parent_ = parent;
    ((isSmallTree) ? root_ : ((isLeft) ? root->left_ : root->right_)) = parent;
    parent->parent_ = (isSmallTree) ? nullptr : root;

    gParent->balanceFactorOnChange_ = false;
    gParent->heightOnChange_ = false;
    parent->balanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::rotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    parent->right_ = child->left_;
    if (parent->right_ != nullptr)
    {
        parent->right_->parent_ = parent;
    }

    child->left_ = parent;
    parent->parent_ = child;
    child->parent_ = gParent;
    gParent->left_ = child;

    parent->balanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
    rotateLL(isSmallTree, root, gParent, child, parent);
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    parent->left_ = child->right_;
    if (parent->left_ != nullptr)
    {
        parent->left_->parent_ = parent;
        /* root_->balanceFactorOnChange_ = false;
        root_->heightOnChange_ = false; */
    }

    child->right_ = parent;
    parent->parent_ = child;
    child->parent_ = gParent;
    gParent->right_ = child;

    parent->balanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
    rotateRR(isSmallTree, root, gParent, child, parent);
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::rotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
{
    bool isLeft = false;
    if (!isSmallTree)
    {
        isLeft = (root->left_ == gParent);
    }
    gParent->right_ = parent->left_;
    gParent->parent_ = parent;
    if (gParent->right_ != nullptr)
    {
        gParent->right_->parent_ = gParent;
    }

    parent->left_ = gParent;
    gParent->parent_ = parent;
    ((isSmallTree) ? root_ : ((isLeft) ? root->left_ : root->right_)) = parent;
    parent->parent_ = (isSmallTree) ? nullptr : root;

    gParent->balanceFactorOnChange_ = false;
    gParent->heightOnChange_ = false;
    parent->balanceFactorOnChange_ = false;
    parent->heightOnChange_ = false;
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

        cout << current->nodeData->data_ << endl; // display information of object
        // sidewaysHelper(current, is_pointer<T>());
        //  cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
template <typename T, typename TComparison>
inline void AVLTree<T *, TComparison>::sideways(Node *current, int level) const
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

        cout << *(current->nodeData->data_) << endl; // display information of object
        // sidewaysHelper(current, is_pointer<T>());
        //  cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}

template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::TCompare(const T &A, const T &B) const
{
    return m_comp(A, B);
}

template <typename T, typename TComparison>
inline void AVLTree<T, TComparison>::wtf(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    calculateBalanceFactor(curNode);
    if (abs(curNode->balanceFactor) > 1)
    {
        cout << "==========WTF==========" << endl;
        print();
        cout << "=======================" << endl;
        throw runtime_error("HOW TF");
    }
}

template <typename T, typename TComparison>
inline bool AVLTree<T, TComparison>::TEqual(const T &A, const T &B) const
{
    return !(TCompare(A, B)) && !(TCompare(B, A));
}

template <typename T, typename TComparison>
inline bool AVLTree<T *, TComparison>::TCompare(const T &A, const T &B) const
{
    return m_comp(*A, *B);
}

#endif //_AVL_TREE_H_