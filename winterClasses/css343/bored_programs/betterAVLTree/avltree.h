#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <functional>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

namespace AVLTreeInternals
{
    /// @brief template for compare
    template <typename T>
    struct DefaultComparator
    {
        typedef std::less<T> Comparator;
    };

    /// @brief specialized template for compare
    template <typename T>
    struct DefaultComparator<T *>
    {
        typedef std::less<T> Comparator;
    };

    /// @brief template for storing T
    template <typename T>
    struct NodeData
    {
        T data_;
    };

    /// @brief specialized template for storing T*
    template <typename T>
    struct NodeData<T *>
    {
        T *data_;
    };

    /// @brief internal base class for AVLTree
    /// @tparam T type to store
    /// @tparam TComparison comparison method to use for <
    template <typename T, typename TComparison = typename DefaultComparator<T>::Comparator>
    class AVLTreeBase
    {
    protected:
        /// @brief internal node class
        class Node
        {
        public:
            /// @brief constructor
            /// @param data T to store
            /// @param parent parent of node
            Node(T data, Node *parent)
            {
                nodeData = new NodeData<T>{data};
                parent_ = parent;
            };

            /// @brief deconstructor
            ~Node()
            {
                if (nodeData != nullptr)
                {
                    delete nodeData;
                }
            };

            /// @brief set node to recalculate height and balancefactor
            void updated()
            {
                heightOnChange_ = false;
                balanceFactorOnChange_ = false;
            }

            Node *left_ = nullptr;               // left branch
            Node *right_ = nullptr;              // right branch
            Node *parent_ = nullptr;             // parent
            NodeData<T> *nodeData = nullptr;     // data storing T
            int height_ = 0;                     // calculated height
            int balanceFactor = 0;               // calculated balanceFactor
            bool heightOnChange_ = false;        // if height has changed
            bool balanceFactorOnChange_ = false; // if balanceFactor has changed
        };

    public:
        AVLTreeBase();                         // constructor
        AVLTreeBase(TComparison comp);         // constructor for custom comparison method
        AVLTreeBase(const AVLTreeBase &other); // copy constructor
        ~AVLTreeBase();                        // deconstructor

        AVLTreeBase<T, TComparison> &operator=(const AVLTreeBase<T, TComparison> &other); // assignment operator
        bool operator==(const AVLTreeBase<T, TComparison> &other) const;                  // equivalency overload
        bool operator!=(const AVLTreeBase<T, TComparison> &other) const;                  // non-equivalency overload

        bool insert(const T obj);         // add obj to tree
        bool contains(const T obj) const; // check if tree contanis obj

        /// @brief clear tree to empty
        void clear();

        bool remove(const T obj); // remove obj from tree
        bool isEmpty() const;     // return if tree is empty
        int size() const;         // return size of tree
        void print();             // calls sideways

    protected:
        void remove(Node *curNode, bool original); // recursive helper

        void calculateBalanceFactor(Node *curNode); // calculate balanceFactor for node
        int getHeight(Node *curNode);               // calculate height of node

        void balanceInsert(Node *curNode); // perform balance after successful insertion
        void balanceRemove(Node *curNode); // perform balance after successful removal

        void rotate(bool isInsert, bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child); // rotate sub tree
        void rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);              // LL subtree rotation
        void rotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);              // LR subtree rotation
        void rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);              // RL subtree rotation
        void rotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);              // RR subtree rotation

        virtual void sideways(Node *current, int level) const = 0; // prints tree sideways to cout

        bool TEqual(const T &A, const T &B) const;                                   // return if A and B equal based on m_comp
        virtual bool TCompare(const NodeData<T> &A, const NodeData<T> &B) const = 0; // return if A < B

        TComparison m_comp;    // user defined comparison method
        int size_ = 0;         // size of tree
        Node *root_ = nullptr; // root of tree
    }; // AVLTreeBase

    /// @brief default constructor
    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::AVLTreeBase() {}

    /// @brief constructor for custom compare method
    /// @param comp bool method to use to compare
    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::AVLTreeBase(TComparison comp)
    {
        m_comp = comp;
    }

    /// @brief copy constructor
    /// @param other tree to copy
    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::AVLTreeBase(const AVLTreeBase &other)
    {
        *this = other;
    }

    /// @brief deconstructor
    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::~AVLTreeBase()
    {
        clear();
    }

    /// @brief clear AVLTree
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::clear()
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

    /// @brief assignment overload
    /// @param other tree to copy
    /// @return AVLTree as copy
    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison> &AVLTreeBase<T, TComparison>::operator=(const AVLTreeBase<T, TComparison> &other)
    {
        this->clear();
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

    /// @brief insert into tree
    /// @param obj T to insert
    /// @return if successful tree
    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::insert(const T obj)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(obj, nullptr);
            size_ = 1;
            return true;
        }
        Node *reader = root_;
        NodeData<T> objDat{obj};
        bool moveLeft = TCompare(objDat, *reader->nodeData);
        while (!TEqual(reader->nodeData->data_, obj) && ((moveLeft) ? reader->left_ : reader->right_) != nullptr)
        {
            reader = ((moveLeft) ? reader->left_ : reader->right_);
            moveLeft = TCompare(objDat, *reader->nodeData);
        }
        if (TEqual(reader->nodeData->data_, obj))
        {
            // duplicate
            return false;
        }
        ((moveLeft) ? reader->left_ : reader->right_) = new Node(obj, reader);
        balanceInsert(((moveLeft) ? reader->left_ : reader->right_));
        size_++;
        return true;
    }

    /// @brief checks if AVLTree contains obj
    /// @param obj T to search for
    /// @return if AVLTree contains obj
    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::contains(const T obj) const
    {
        Node *reader = root_;
        NodeData<T> test{obj};
        while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
        {
            reader = (TCompare(test, *reader->nodeData)) ? reader->left_ : reader->right_;
        }
        return reader != nullptr;
    }

    /// @brief remove obj from AVLTree
    /// @param obj obj to remove
    /// @return if successful remove
    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::remove(const T obj)
    {
        Node *reader = root_;
        NodeData<T> objDat{obj};
        while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
        {
            reader = (TCompare(objDat, *reader->nodeData)) ? reader->left_ : reader->right_;
        }
        if (reader == nullptr)
        {
            return false;
        }
        remove(reader, true);
        size_--;
        return true;
    }

    /// @brief remove node from AVLTree
    /// @param curNode node to remove
    /// @param original if original remove call
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::remove(Node *curNode, bool original)
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
                ((TCompare(*curNode->nodeData, *curNode->parent_->nodeData)) ? curNode->parent_->left_ : curNode->parent_->right_) = nullptr;
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
                // is root
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
            Node *replacement = curNode->left_;
            replacement->updated();
            while (replacement->right_ != nullptr)
            {
                replacement = replacement->right_;
                replacement->updated();
            }

            T replacementData = replacement->nodeData->data_;
            remove(replacement, false);
            curNode->nodeData->data_ = replacementData;

            curNode->updated();
            W = curNode;
        }
        if (W != nullptr && original)
        {
            balanceRemove(W);
        }
    }

    /// @brief calculate balance factor for curNode
    /// @param curNode node to calculate balanceFactor for
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::calculateBalanceFactor(Node *curNode)
    {
        if (curNode == nullptr)
        {
            return;
        }
        else if (curNode->balanceFactorOnChange_)
        {
            return;
        }
        curNode->balanceFactor = getHeight(curNode->right_) - getHeight(curNode->left_);
        curNode->balanceFactorOnChange_ = true;
    }

    /// @brief calculate height of curNode
    /// @param curNode node to calculate height of
    /// @return height of curNode
    template <typename T, typename TComparison>
    inline int AVLTreeBase<T, TComparison>::getHeight(Node *curNode)
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

    /// @brief check if AVLTree is empty
    /// @return if AVLTree is empty
    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::isEmpty() const
    {
        return root_ == nullptr;
    }

    /// @brief return size of AVLTree
    /// @return size of AVLTree
    template <typename T, typename TComparison>
    inline int AVLTreeBase<T, TComparison>::size() const
    {
        return size_;
    }

    /// @brief print AVLTree sideways to cout
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::print()
    {
        sideways(root_, -1);
    }

    /// @brief balance AVLTree after successful insert
    /// @param curNode inserted node
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::balanceInsert(Node *curNode)
    {
        Node *gParent = curNode;
        gParent->updated();
        Node *root = curNode->parent_;
        if (root != nullptr)
        {
            root->updated();
        }
        Node *parent = nullptr;
        Node *child = nullptr;
        calculateBalanceFactor(gParent);
        while (root != nullptr && abs(gParent->balanceFactor) < 2)
        {
            child = parent;
            parent = gParent;
            gParent = root;
            root = root->parent_;
            if (root != nullptr)
            {
                root->updated();
            }
            calculateBalanceFactor(gParent);
        }
        Node *reader = root;
        while (reader != nullptr)
        {
            reader->updated();
            reader = reader->parent_;
        }
        if (root == nullptr && abs(gParent->balanceFactor) < 2)
        {
            // balanced
            return;
        }
        rotate(true, (root_ == gParent), root, gParent, parent, child);
    }

    /// @brief balance AVLTree after successful removal
    /// @param curNode node removed
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::balanceRemove(Node *curNode)
    {
        Node *root = nullptr;
        Node *gParent = curNode;
        while (gParent != nullptr)
        {
            gParent->updated();
            root = gParent->parent_;
            calculateBalanceFactor(gParent);
            if (abs(gParent->balanceFactor) > 1)
            {
                rotate(false, (root == nullptr), root, gParent, nullptr, nullptr);
            }
            gParent = root;
        }
    }

    /// @brief perform needed rotation after insert or remove
    /// @param isInsert if caller is insert
    /// @param isSmallTree if gParent is root
    /// @param root parent of gParent
    /// @param gParent grandparent node
    /// @param parent parent node
    /// @param child child node
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotate(bool isInsert, bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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

    /// @brief perform a LL rotation
    /// @param isSmallTree if gParent is root
    /// @param root parent of gParent
    /// @param gParent grandparent node
    /// @param parent parent node
    /// @param child child node
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
    {
        bool isLeft = false;
        if (!isSmallTree)
        {
            isLeft = (root->left_ == gParent);
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

        gParent->updated();
        parent->updated();
    }

    /// @brief perform a LR rotation
    /// @param isSmallTree if gParent is root
    /// @param root parent of gParent
    /// @param gParent grandparent node
    /// @param parent parent node
    /// @param child child node
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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

        parent->updated();
        rotateLL(isSmallTree, root, gParent, child, parent);
    }

    /// @brief perform a RL rotation
    /// @param isSmallTree if gParent is root
    /// @param root parent of gParent
    /// @param gParent grandparent node
    /// @param parent parent node
    /// @param child child node
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
    {
        parent->left_ = child->right_;
        if (parent->left_ != nullptr)
        {
            parent->left_->parent_ = parent;
        }

        child->right_ = parent;
        parent->parent_ = child;
        child->parent_ = gParent;
        gParent->right_ = child;

        parent->updated();
        rotateRR(isSmallTree, root, gParent, child, parent);
    }

    /// @brief perform a RR rotation
    /// @param isSmallTree if gParent is root
    /// @param root parent of gParent
    /// @param gParent grandparent node
    /// @param parent parent node
    /// @param child child node
    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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

        gParent->updated();
        parent->updated();
    }

    /// @brief check if A equals B
    /// @param A T to compare with
    /// @param B T to compare against
    /// @return if A equals B
    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::TEqual(const T &A, const T &B) const
    {
        /* return A == B; */
        return !(TCompare({A}, {B})) && !(TCompare({B}, {A}));
    }
} // AVLTreeInternals

//============================================
// PUBLIC TEMPLATES
//============================================

/// @brief AVLTree
/// @tparam T type to store
/// @tparam TComparison bool method to use for <
template <typename T, typename TComparison = typename AVLTreeInternals::DefaultComparator<T>::Comparator>
class AVLTree : public AVLTreeInternals::AVLTreeBase<T, TComparison>
{
public:
    /// @brief deconstructor
    ~AVLTree()
    {
        this->clear();
    };
    AVLTree() {}
    AVLTree(const AVLTree<T, TComparison> &other)
    {
        *this = other;
    }
    using typename AVLTreeInternals::AVLTreeBase<T, TComparison>::Node;
    T *retrieve(const T obj); // return pointer to T in AVLTree

protected:
    void sideways(Node *current, int level) const override; // prints tree sideways to cout

    /// @brief compare overload
    /// @param A NodeData to compare with
    /// @param B NodeData to compare against
    /// @return if A < B
    bool TCompare(const AVLTreeInternals::NodeData<T> &A, const AVLTreeInternals::NodeData<T> &B) const override
    {
        return this->m_comp(A.data_, B.data_);
    };

public:
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
        Iterator(Node *ptr, TComparison comp)
        {
            m_compare = comp;
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

        reference operator*() const { return nodeStack.top().node->nodeData->data_; };
        pointer operator->() { return &nodeStack.top().node->nodeData->data_; };

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
        Iterator operator++(int)
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
            equalPlace &= (!a.m_compare(a.nodeStack.top().node->nodeData->data_, b.nodeStack.top().node->nodeData->data_) &&
                           !a.m_compare(b.nodeStack.top().node->nodeData->data_, a.nodeStack.top().node->nodeData->data_));

            return equalPlace;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return !(a == b);
        }
    };

    /// @brief returns iterator placed at the start of AVLTree
    /// @return Iterator at beginning of AVLTree
    Iterator begin() { return Iterator(this->root_, this->m_comp); }

    /// @brief returns iterator placed at end of AVLTree
    /// @return Iterator at end of AVLTree
    Iterator end() { return Iterator(nullptr, this->m_comp); }

    /// @brief returns the last element of AVLTree
    /// @return the last element of AVLTree
    T *last()
    {
        Node *reader = this->root_;
        while (reader->right_ != nullptr)
        {
            reader = reader->right_;
        }
        return &reader->nodeData->data_;
    }
}; // AVLTree<T>

/// @brief return read/write ponter to obj in AVLTree
/// @param obj obj to search for
/// @return pointer to T in AVLtree, nullptr if not found
template <typename T, typename TComparison>
T *AVLTree<T, TComparison>::retrieve(const T obj)
{
    Node *reader = this->root_;
    AVLTreeInternals::NodeData<T> objData = AVLTreeInternals::NodeData<T>{obj};
    while (reader != nullptr && !this->TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(objData, *reader->nodeData)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return &reader->nodeData->data_;
}

/// @brief print AVLTree to cout
/// @param current node to print
/// @param level depth of current
template <typename T, typename TComparison>
void AVLTree<T, TComparison>::sideways(Node *current, int level) const
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
        sideways(current->left_, level);
    }
}

/// @brief specialized AVLTree for pointers
/// @tparam T type of pointer
/// @tparam TComparison custom method to use for <
template <typename T, typename TComparison>
class AVLTree<T *, TComparison> : public AVLTreeInternals::AVLTreeBase<T *, TComparison>
{
public:
    /// @brief deconstructor
    ~AVLTree()
    {
        this->clear();
    };
    AVLTree() {}
    AVLTree(const AVLTree<T *, TComparison> &other)
    {
        *this = other;
    }
    using typename AVLTreeInternals::AVLTreeBase<T *, TComparison>::Node;
    T *retrieve(T obj);  // get pointer to obj in AVLTree
    T *retrieve(T *obj); // get pointer to obj in AVLTree

protected:
    void sideways(Node *current, int level) const override; // prints tree sideways to cout

    /// @brief compare overload
    /// @param A NodeData to compare with
    /// @param B NodeData to compare against
    /// @return if A < B
    bool TCompare(const AVLTreeInternals::NodeData<T *> &A, const AVLTreeInternals::NodeData<T *> &B) const override
    {
        return this->m_comp(*A.data_, *B.data_);
    };

public:
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
        Iterator(Node *ptr, TComparison comp)
        {
            m_compare = comp;
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

        reference operator*() const { return *nodeStack.top().node->nodeData->data_; };
        pointer operator->() { return nodeStack.top().node->nodeData->data_; };

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
        Iterator operator++(int)
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
            equalPlace &= (!a.m_compare(*a.nodeStack.top().node->nodeData->data_, *b.nodeStack.top().node->nodeData->data_) &&
                           !a.m_compare(*b.nodeStack.top().node->nodeData->data_, *a.nodeStack.top().node->nodeData->data_));

            return equalPlace;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return !(a == b);
        }
    };

    /// @brief returns iterator placed at the start of AVLTree
    /// @return Iterator at beginning of AVLTree
    Iterator begin() { return Iterator(this->root_, this->m_comp); }

    /// @brief returns iterator placed at end of AVLTree
    /// @return Iterator at end of AVLTree
    Iterator end() { return Iterator(nullptr, this->m_comp); }

    /// @brief returns the last element of AVLTree
    /// @return the last element of AVLTree
    T *last()
    {
        Node *reader = this->root_;
        while (reader->right_ != nullptr)
        {
            reader = reader->right_;
        }
        return reader->nodeData->data_;
    }
}; // AVLTree<T*>

/// @brief get read/write pointer to obj in AVLTree
/// @param obj obj to search for
/// @return pointer to obj in AVLTree, nullptr if not found
template <typename T, typename TComparison>
T *AVLTree<T *, TComparison>::retrieve(T obj)
{
    Node *reader = this->root_;
    AVLTreeInternals::NodeData<T> objData = AVLTreeInternals::NodeData<T>{obj};
    while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(objData, *reader->nodeData)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return reader->nodeData->data_;
}

/// @brief get read/write pointer to obj in AVLTree
/// @param obj obj to search for
/// @return pointer to obj in AVLTree, nullptr if not found
template <typename T, typename TComparison>
T *AVLTree<T *, TComparison>::retrieve(T *obj)
{
    Node *reader = this->root_;
    AVLTreeInternals::NodeData<T *> objData = AVLTreeInternals::NodeData<T *>{obj};

    while (reader != nullptr && !AVLTreeInternals::AVLTreeBase<T *, TComparison>::TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(objData, *reader->nodeData)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return reader->nodeData->data_;
}

/// @brief print AVLTree to cout
/// @param current node to print
/// @param level depth of current
template <typename T, typename TComparison>
void AVLTree<T *, TComparison>::sideways(Node *current, int level) const
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

        cout << *current->nodeData->data_ << endl;
        sideways(current->left_, level);
    }
}
#endif //_AVL_TREE_H_