#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <functional>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

namespace AVLTreeInternals
{
    template <typename T>
    struct DefaultComparator
    {
        typedef std::less<T> Comparator;
    };

    template <typename T>
    struct DefaultComparator<T *>
    {
        typedef std::less<T> Comparator;
    };

    template <typename T>
    struct NodeData
    {
        T data_;
    };
    template <typename T>
    struct NodeData<T *>
    {
        T *data_;
    };

    template <typename T, typename TComparison = typename DefaultComparator<T>::Comparator>
    class AVLTreeBase
    {
    protected:
        class Node
        {
        public:
            Node(T data, Node *parent)
            {
                nodeData = new NodeData<T>{data};
                parent_ = parent;
            };
            ~Node()
            {
                delete nodeData;
            };

            Node *left_ = nullptr;
            Node *right_ = nullptr;
            Node *parent_ = nullptr;
            NodeData<T> *nodeData = nullptr;
            int height_ = 0;
            int balanceFactor = 0;
            bool heightOnChange_ = false;
            bool balanceFactorOnChange_ = false;
        };

    public:
        AVLTreeBase();
        AVLTreeBase(TComparison comp);
        AVLTreeBase(const AVLTreeBase &other);
        ~AVLTreeBase();

        AVLTreeBase<T, TComparison> &operator=(const AVLTreeBase<T, TComparison> &other);
        bool operator==(const AVLTreeBase<T, TComparison> &other) const;
        bool operator!=(const AVLTreeBase<T, TComparison> &other) const;

        bool insert(const T obj);
        bool contains(const T obj) const;
        void clear()
        {
            this->~AVLTreeBase();
        };
        // virtual T *retrieve(const T obj) = 0;
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

        virtual void sideways(Node *current, int level) const = 0; // prints tree sideways to cout

        TComparison m_comp; // user defined comparison method
        bool TEqual(const T &A, const T &B) const;
        virtual bool TCompare(const NodeData<T> &A, const NodeData<T> &B) const = 0;
        int size_ = 0;
        Node *root_ = nullptr;
    }; // AVLTreeBase

    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::AVLTreeBase() {}

    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::AVLTreeBase(TComparison comp)
    {
        m_comp = comp;
    }

    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::AVLTreeBase(const AVLTreeBase &other)
    {
        *this = other;
    }

    template <typename T, typename TComparison>
    inline AVLTreeBase<T, TComparison>::~AVLTreeBase()
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
    inline AVLTreeBase<T, TComparison> &AVLTreeBase<T, TComparison>::operator=(const AVLTreeBase<T, TComparison> &other)
    {
        this->~AVLTreeBase();
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
        // wtf(root_);
        return true;
    }

    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::contains(const T obj) const
    {
        Node *reader = root_;
        while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
        {
            reader = (TCompare(NodeData<T>{obj}, *reader->nodeData)) ? reader->left_ : reader->right_;
        }
        return reader != nullptr;
    }

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
                if (TCompare(*curNode->nodeData, *curNode->parent_->nodeData))
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

    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::isEmpty() const
    {
        return root_ == nullptr;
    }

    template <typename T, typename TComparison>
    inline int AVLTreeBase<T, TComparison>::size() const
    {
        return size_;
    }

    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::print()
    {
        sideways(root_, -1);
    }

    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::balanceInsert(Node *curNode)
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
    inline void AVLTreeBase<T, TComparison>::balanceRemove(Node *curNode)
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

    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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

        parent->balanceFactorOnChange_ = false;
        parent->heightOnChange_ = false;
        rotateLL(isSmallTree, root, gParent, child, parent);
    }

    template <typename T, typename TComparison>
    inline void AVLTreeBase<T, TComparison>::rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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

        gParent->balanceFactorOnChange_ = false;
        gParent->heightOnChange_ = false;
        parent->balanceFactorOnChange_ = false;
        parent->heightOnChange_ = false;
    }

    template <typename T, typename TComparison>
    inline bool AVLTreeBase<T, TComparison>::TEqual(const T &A, const T &B) const
    {
        // NodeData<T> ADat = {A};
        // NodeData<T> BDat = {B};
        return !(TCompare({A}, {B})) && !(TCompare({B}, {A}));
    }
} // AVLTreeInternals

//============================================
// PUBLIC TEMPLATES
//============================================

template <typename T, typename TComparison = typename AVLTreeInternals::DefaultComparator<T>::Comparator>
class AVLTree : public AVLTreeInternals::AVLTreeBase<T, TComparison>
{
public:
    ~AVLTree()
    {
        this->clear();
    };
    using typename AVLTreeInternals::AVLTreeBase<T, TComparison>::Node;
    T *retrieve(const T obj);

protected:
    void sideways(Node *current, int level) const override; // prints tree sideways to cout
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
            // equalPlace = equalPlace && (*a.nodeStack.top().node->data_ == *b.nodeStack.top().node->data_);
            equalPlace &= (!a.m_compare(a.nodeStack.top().node->nodeData->data_, b.nodeStack.top().node->nodeData->data_) &&
                           !a.m_compare(b.nodeStack.top().node->nodeData->data_, a.nodeStack.top().node->nodeData->data_));
            // equalPlace(equals(a.nodeStack.top()->nodeData->data_, b.nodeStack.top()->nodeData->data_));

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
}; // AVLTree<T>

template <typename T, typename TComparison>
T *AVLTree<T, TComparison>::retrieve(const T obj)
{
    Node *reader = this->root_;
    while (reader != nullptr && !this->TEqual(reader->nodeData->data_, obj))
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
        // sidewaysHelper(current, is_pointer<T>());
        //  cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}

template <typename T, typename TComparison>
class AVLTree<T *, TComparison> : public AVLTreeInternals::AVLTreeBase<T *, TComparison>
{
public:
    ~AVLTree()
    {
        this->clear();
    };
    using typename AVLTreeInternals::AVLTreeBase<T *, TComparison>::Node;
    T *retrieve(const T obj);
    T *retrieve(const T *obj);

protected:
    void sideways(Node *current, int level) const override; // prints tree sideways to cout
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
            // equalPlace = equalPlace && (*a.nodeStack.top().node->data_ == *b.nodeStack.top().node->data_);
            equalPlace &= (!a.m_compare(*a.nodeStack.top().node->nodeData->data_, *b.nodeStack.top().node->nodeData->data_) &&
                           !a.m_compare(*b.nodeStack.top().node->nodeData->data_, *a.nodeStack.top().node->nodeData->data_));
            // equalPlace(equals(a.nodeStack.top()->nodeData->data_, b.nodeStack.top()->nodeData->data_));

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
}; // AVLTree<T*>

template <typename T, typename TComparison>
T *AVLTree<T *, TComparison>::retrieve(const T obj)
{
    Node *reader = this->root_;
    while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(obj, reader->nodeData->data_)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return reader->nodeData->data_;
}

template <typename T, typename TComparison>
T *AVLTree<T *, TComparison>::retrieve(const T *obj)
{
    Node *reader = this->root_;
    while (reader != nullptr && !TEqual(reader->nodeData->data_, obj))
    {
        reader = (TCompare(*obj, reader->nodeData->data_)) ? reader->left_ : reader->right_;
    }
    if (reader == nullptr)
    {
        return nullptr;
    }
    return reader->nodeData->data_;
}

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

        cout << *current->nodeData->data_ << endl; // display information of object
        // sidewaysHelper(current, is_pointer<T>());
        //  cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}
#endif //_AVL_TREE_H_
