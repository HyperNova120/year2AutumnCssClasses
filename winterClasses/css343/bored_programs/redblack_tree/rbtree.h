#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <functional>
#include <iostream>
using namespace std;

namespace RBTree_Internals
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
    class RBTreeBase
    {
    protected:
        class Node
        {
        public:
            Node(T data, Node *parent)
            {
                nodeData_ = new NodeData<T>{data};
                parent_ = parent;
            };
            Node(NodeData<T> *data, Node *parent)
            {
                nodeData_ = data;
                parent_ = parent;
            };
            ~Node()
            {
                if (nodeData_ != nullptr)
                {
                    delete nodeData_;
                }
            };

            Node *left_ = nullptr;
            Node *right_ = nullptr;
            Node *parent_ = nullptr;
            NodeData<T> *nodeData_ = nullptr;
            bool color_ = true;
        };

    public:
        RBTreeBase();
        RBTreeBase(TComparison comp);
        RBTreeBase(const RBTreeBase &other);
        ~RBTreeBase();

        RBTreeBase<T, TComparison> &operator=(const RBTreeBase<T, TComparison> &other);
        bool operator==(const RBTreeBase<T, TComparison> &other) const;
        bool operator!=(const RBTreeBase<T, TComparison> &other) const
        {
            return !(*this == other);
        };

        bool insert(const T obj);
        bool contains(const T obj) const;
        void clear()
        {
            this->~RBTreeBase();
        };
        // virtual T *retrieve(const T obj) = 0;
        bool remove(const T obj);
        bool isEmpty() const
        {
            return root_ == nullptr;
        };
        int size() const
        {
            return size_;
        };
        void print()
        {
            sideways(root_, -1);
        }; // calls sideways

    protected:
        void removeHelper(Node *curNode);
        void deleteHelper(Node *curNode);

        void balanceInsert(Node *curNode);
        void balanceRemove(Node *parent, bool color, bool lastMoveLeft);

        void rotate(bool isInsert, bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
        void rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
        void rotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
        void rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);
        void rotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child);

        virtual void sideways(Node *current, int level) const = 0; // prints tree sideways to cout

        TComparison m_comp; // user defined comparison method
        bool TEqual(const NodeData<T> &A, const NodeData<T> &B) const
        {
            return !TCompare(A, B) && !TCompare(B, A);
        };
        virtual bool TCompare(const NodeData<T> &A, const NodeData<T> &B) const = 0;
        int size_ = 0;
        Node *root_ = nullptr;
    }; // RBTreeBase

    template <typename T, typename TComparison>
    inline RBTreeBase<T, TComparison>::RBTreeBase() {}

    template <typename T, typename TComparison>
    inline RBTreeBase<T, TComparison>::RBTreeBase(TComparison comp)
    {
        m_comp = comp;
    }

    template <typename T, typename TComparison>
    inline RBTreeBase<T, TComparison>::RBTreeBase(const RBTreeBase &other)
    {
        *this = other;
    }

    template <typename T, typename TComparison>
    inline RBTreeBase<T, TComparison>::~RBTreeBase()
    {
        deleteHelper(root_);
        root_ = nullptr;
    }

    template <typename T, typename TComparison>
    inline bool RBTreeBase<T, TComparison>::insert(const T obj)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(obj, nullptr);
            root_->color_ = false;
            size_ = 1;
            return true;
        }
        Node *reader = root_;
        NodeData<T> objData = {obj};
        bool insertLeft = TCompare(objData, *reader->nodeData_);
        while (((insertLeft) ? reader->left_ : reader->right_) != nullptr && !TEqual(objData, *reader->nodeData_))
        {
            reader = ((insertLeft) ? reader->left_ : reader->right_);
            insertLeft = TCompare(objData, *reader->nodeData_);
        }

        if (TEqual(objData, *reader->nodeData_))
        {
            // duplicate
            return false;
        }

        Node *tmp = new Node(obj, reader);
        ((insertLeft) ? reader->left_ : reader->right_) = tmp;
        size_++;
        balanceInsert(tmp);
    }

    template <typename T, typename TComparison>
    inline bool RBTreeBase<T, TComparison>::contains(const T obj) const
    {
        if (root_ == nullptr)
        {
            return false;
        }
        Node *reader = root_;
        bool insertLeft = TCompare(obj, reader->nodeData_->data_);
        while (((insertLeft) ? reader->left_ : reader->right_) != nullptr && !TEqual(obj, reader->nodeData_->data_))
        {
            reader = ((insertLeft) ? reader->left_ : reader->right_);
            insertLeft = TCompare(obj, reader->nodeData_->data_);
        }
        if (TEqual(obj, reader->nodeData_->data_))
        {
            return true;
        }
        return false;
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::balanceInsert(Node *curNode)
    {
        if (root_ != nullptr)
        {
            root_->color_ = false;
        }
        if (root_ == curNode)
        {
            root_->color_ = false;
            return;
        }
        if (!curNode->parent_->color_)
        {
            // parent is black
            return;
        }
        Node *parent = curNode->parent_;
        Node *gParent = parent->parent_;
        bool isParentLeft = parent == gParent->left_;
        Node *uncle = ((isParentLeft) ? gParent->right_ : gParent->left_);
        if (uncle == nullptr || !uncle->color_)
        {
            // uncle is black
            rotate(true, root_ == gParent, gParent->parent_, gParent, parent, curNode);
            return;
        }

        // uncle red
        uncle->color_ = false;
        parent->color_ = false;
        gParent->color_ = true;
        balanceInsert(gParent);
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::rotate(bool isInsert, bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
    {
        if (isInsert)
        {

            if (parent == gParent->left_)
            {
                // L
                if (child == parent->left_)
                {
                    // LL
                    rotateLL(isSmallTree, root, gParent, parent, child);
                    parent->color_ = false;
                    child->color_ = true;
                    gParent->color_ = true;
                }
                else
                {
                    // LR
                    rotateLR(isSmallTree, root, gParent, parent, child);
                    child->color_ = false;
                    parent->color_ = true;
                    gParent->color_ = true;
                }
            }
            else
            {
                // R
                if (child == parent->left_)
                {
                    // RL
                    rotateRL(isSmallTree, root, gParent, parent, child);
                    child->color_ = false;
                    parent->color_ = true;
                    gParent->color_ = true;
                }
                else
                {
                    // RR
                    rotateRR(isSmallTree, root, gParent, parent, child);
                    parent->color_ = false;
                    child->color_ = true;
                    gParent->color_ = true;
                }
            }
        }
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::rotateLL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::rotateLR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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
        rotateLL(isSmallTree, root, gParent, child, parent);
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::rotateRL(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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
        rotateRR(isSmallTree, root, gParent, child, parent);
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::rotateRR(bool isSmallTree, Node *root, Node *gParent, Node *parent, Node *child)
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
    }

    template <typename T, typename TComparison>
    inline bool RBTreeBase<T, TComparison>::remove(const T obj)
    {
        Node *reader = root_;
        while (reader != nullptr && !TEqual(obj, reader->nodeData_->data_))
        {
            reader = ((TCompare(obj, reader->nodeData_->data_)) ? reader->left_ : reader->right_);
        }
        if (reader == nullptr)
        {
            return false;
        }
        removeHelper(reader);
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::removeHelper(Node *curNode)
    {
        Node *parent = nullptr;
        bool lastMoveLeft = true;
        bool color = false;
        if (curNode->left_ == nullptr && curNode->right_ == nullptr)
        {
            // leaf
            parent = curNode->parent_;
            color = curNode->color_;
            lastMoveLeft = (parent->left_ == curNode);

            ((lastMoveLeft) ? parent->left_ : parent->right_) = nullptr;
            delete curNode;
            curNode = nullptr;
        }
        else if (curNode->left_ == nullptr ^ curNode->right_ == nullptr)
        {
            // single branch
            parent = curNode->parent_;
            color = curNode->color_;
            lastMoveLeft = (parent->left_ == curNode);

            Node *replacementBranch = ((curNode->left_ != nullptr) ? curNode->left_ : curNode->right_);

            replacementBranch->parent_ = parent;
            ((lastMoveLeft) ? parent->left_ : parent->right_) = replacementBranch;
        }
        else
        {
            // dual branch
            Node *reader = curNode->right_;
            while (reader->left_ != nullptr)
            {
                reader = reader->left_;
            }

            // get replacement data
            NodeData<T> *replacementData = reader->nodeData_;
            reader->nodeData_ = nullptr;

            // node to remove is reader
            parent = reader->parent_;
            color = reader->color_;
            lastMoveLeft = (parent->left_ == curNode);

            // replace data
            delete curNode->nodeData_;
            curNode->nodeData_ = replacementData;

            // delete node
            ((lastMoveLeft) ? parent->left_ : parent->right_) = nullptr;
            delete reader;
        }

        balanceRemove(parent, color, lastMoveLeft);
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::balanceRemove(Node *parent, bool color, bool lastMoveLeft)
    {
        Node *replacedNode = ((lastMoveLeft) ? parent->left_ : parent->right_);
        if (color || (replacedNode != nullptr && replacedNode->color_))
        {
            // deleted or replacement red
            if (replacedNode != nullptr)
            {
                replacedNode->color_ = false;
            }
            return;
        }
        else if (!color && (replacedNode != nullptr && !replacedNode->color_))
        {
            // both deleted node and replacement is black
            Node *u = replacedNode;
        }

        Node *sibling = ((lastMoveLeft) ? parent->right_ : parent->left_);
        if (sibling != nullptr && sibling->color_)
        {
            // sibling is red
        }
        else
        {
            // sibling is black
            if (sibling != nullptr)
            {
                if ((sibling->left_ != nullptr && !sibling->left_->color_) && (sibling->right_ != nullptr && !sibling->right_->color_))
                {
                    // both children black
                    sibling->color_ = true;
                    parent->color_ = false;
                }
                else
                {
                    // at least one child red
                }
            }
        }
    }

    template <typename T, typename TComparison>
    inline void RBTreeBase<T, TComparison>::deleteHelper(Node *curNode)
    {
        if (curNode == nullptr)
        {
            return;
        }
        deleteHelper(curNode->left_);
        deleteHelper(curNode->right_);
        delete curNode;
    }

} // RBTree_Internals

//====================================
//          PUBLIC TEMPLATES
//====================================

template <typename T, typename TComparison = typename RBTree_Internals::DefaultComparator<T>::Comparator>
class RBTree : public RBTree_Internals::RBTreeBase<T, TComparison>
{
    using typename RBTree_Internals::RBTreeBase<T, TComparison>::Node;

protected:
    void sideways(Node *current, int level) const override; // prints tree sideways to cout
    bool TCompare(const RBTree_Internals::NodeData<T> &A, const RBTree_Internals::NodeData<T> &B) const override
    {
        return this->m_comp(A.data_, B.data_);
    };
};

template <typename T, typename TComparison>
inline void RBTree<T, TComparison>::sideways(Node *current, int level) const
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

        cout << current->nodeData_->data_; // display information of object
        if (current->color_)
        {
            cout << "(R)";
        }
        cout << endl;
        // cout << (*current).balanceFactor_ << endl; // display information of object
        sideways(current->left_, level);
    }
}

#endif //_RB_TREE_H_
