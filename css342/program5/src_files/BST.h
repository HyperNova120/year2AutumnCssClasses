#ifndef _SRC_BST_H_
#define _SRC_BST_H_

#include <iostream>
#include <sstream>
using namespace std;

template <typename T>
class BST
{
private:
    class Node
    {
    public:
        T *item_ = nullptr;
        Node *left_ = nullptr;
        Node *right_ = nullptr;
    };

public:
    BST();
    BST(const BST<T> &other);
    ~BST();

    bool Remove(const T &obj);
    bool Insert(const T &obj);
    bool Contains(const T &obj) const;

    bool operator==(const BST<T> &other);
    bool operator!=(const BST<T> &other);

    T &Get(const T &obj) const;

    void DeleteBST(BST<T>::Node *currentNode);

    template <typename U>
    friend ostream &operator<<(ostream &os, const BST<U> &obj);

private:
    BST<T>::Node *GetReplacementNode(const BST<T>::Node *current);
    string printMe(const BST<T>::Node *current) const;
    Node *head_ = nullptr;
};

template <typename T>
inline BST<T>::BST()
{
}

template <typename T>
inline BST<T>::BST(const BST<T> &other)
{
}

template <typename T>
inline BST<T>::~BST()
{
    DeleteBST(head_);
    head_ = nullptr;
}

template <typename T>
bool BST<T>::Remove(const T &obj)
{
    if (head_ == nullptr)
    {
        return false;
    }
    Node *currentNode = head_;
    Node *lastNode = nullptr;
    bool wasLastMoveLeft = false;
    while (currentNode != nullptr && *currentNode->item_ != obj)
    {
        lastNode = currentNode;
        if (obj < *currentNode->item_)
        {
            currentNode = currentNode->left_;
            wasLastMoveLeft = true;
        }
        else if (obj > *currentNode->item_)
        {
            currentNode = currentNode->right_;
            wasLastMoveLeft = false;
        }
    }
    if (currentNode == nullptr)
    {
        // element does not exist
        return false;
    }
    // element found
    Node *replacementNode = GetReplacementNode(currentNode);
    if (lastNode == nullptr)
    {
        // head
        delete head_->item_;
        delete head_;
        head_ = nullptr;
        return true;
    }
    replacementNode->left_ = currentNode->left_;
    replacementNode->right_ = currentNode->right_;

    if (wasLastMoveLeft)
    {
        // replace last->left_;
        lastNode->left_ = replacementNode;
    }
    else
    {
        lastNode->right_ = replacementNode;
    }

    delete currentNode->item_;
    delete currentNode;
}

template <typename T>
bool BST<T>::Insert(const T &obj)
{
    BST<T>::Node *tmp = new BST<T>::Node();
    tmp->item_ = new T(obj);
    if (head_ == nullptr)
    {
        head_ = tmp;
        return true;
    }
    Node *currentNode = head_;
    Node *lastNode = nullptr;
    bool wasLastMoveLeft = false;
    while (currentNode != nullptr)
    {
        lastNode = currentNode;
        if (*currentNode->item_ == obj)
        {
            return false;
        }
        else if (obj > *currentNode->item_)
        {
            currentNode = currentNode->right_;
            wasLastMoveLeft = false;
        }
        else
        {
            currentNode = currentNode->left_;
            wasLastMoveLeft = true;
        }
    }
    if (wasLastMoveLeft)
    {
        lastNode->left_ = tmp;
    }
    else
    {
        lastNode->right_ = tmp;
    }
    return true;
}

template <typename T>
inline bool BST<T>::Contains(const T &obj) const
{
    Node *currentNode = head_;
    while (currentNode != nullptr)
    {
        if (*currentNode->item_ == obj)
        {
            return true;
        }
        else if (obj > *currentNode->item_)
        {
            currentNode = currentNode->right_;
        }
        else
        {
            currentNode = currentNode->left_;
        }
    }
    return false;
}

template <typename T>
inline T &BST<T>::Get(const T &obj) const
{
    // assumes contains was true
    Node *currentNode = head_;
    while (currentNode != nullptr)
    {
        if (*currentNode->item_ == obj)
        {
            return *currentNode->item_;
        }
        else if (obj > *currentNode->item_)
        {
            currentNode = currentNode->right_;
        }
        else
        {
            currentNode = currentNode->left_;
        }
    }
    T tmp = T(0);
    return tmp;
}

template <typename T>
void BST<T>::DeleteBST(typename BST<T>::Node *currentNode)
{
    if (currentNode == nullptr)
    {
        return;
    }
    DeleteBST(currentNode->left_);
    DeleteBST(currentNode->right_);
    delete currentNode->item_;
    delete currentNode;
}

template <typename T>
typename BST<T>::Node *BST<T>::GetReplacementNode(const BST<T>::Node *current)
{
    Node *last = current;
    if (current->left_ != nullptr)
    {
        Node *tmp = current->left_;
        while (tmp->right_ != nullptr)
        {
            last = tmp;
            tmp = tmp->right_;
        }
        last->right_ = nullptr;
        return tmp;
    }
    else if (current->right_ != nullptr)
    {
        Node *tmp = current->right_;
        while (tmp->left_ != nullptr)
        {
            last = tmp;
            tmp = tmp->left_;
        }
        last->left_ = nullptr;
        return tmp;
    }
    // is leaf node already
    return nullptr;
}

template <typename T>
string BST<T>::printMe(const BST<T>::Node *current) const
{
    if (current == nullptr)
    {
        return "";
    }
    string returner;
    if (current->left_ != nullptr)
    {
        returner += printMe(current->left_);
        // returner += "\n";
    }
    stringstream ss = stringstream();
    ss << *current->item_;
    returner += ss.str();
    returner += "\n";

    if (current->right_ != nullptr)
    {
        returner += printMe(current->right_);
        // returner += "\n";
    }

    return returner;
}

template <typename U>
ostream &operator<<(ostream &os, const BST<U> &obj)
{
    os << obj.printMe(obj.head_);
    return os;
}

#endif //_SRC_BST_H_
