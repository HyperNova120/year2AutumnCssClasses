#ifndef LIST342_H_
#define LIST342_H_
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// a templatized sorted linked list
template <typename T>
class List342
{
public:
    List342();
    List342(const List342<T> &other);
    ~List342();

    bool BuildList(string file_name);
    bool Insert(T *obj);
    bool Remove(T target, T &result);
    bool Peek(T target, T &result) const;
    void DeleteList();
    bool Merge(List342<T> &list1);

    List342<T> operator+(const List342<T> &other) const;
    List342<T> &operator+=(const List342<T> &other);

    List342<T> &operator=(const List342<T> &other);

    bool operator==(const List342<T> &other) const;
    bool operator!=(const List342<T> &other) const;

    template <typename U>
    friend ostream &operator<<(ostream &os, const List342<U> &obj);

    int Size() const;

private:
    struct Node
    {
        ~Node();
        T *data = nullptr;
        Node *next = nullptr;
    };
    Node *head_ = nullptr;
    int size_ = 0;
};

template <typename T>
List342<T>::List342() {}

template <typename T>
List342<T>::List342(const List342<T> &other)
{
    *this = other;
}

template <typename T>
List342<T>::~List342()
{
    DeleteList();
}

template <typename T>
bool List342<T>::BuildList(string file_name)
{
    ifstream ifs;
    ifs.open(file_name);
    if (!ifs.is_open())
    {
        ifs.close();
        return false;
    }

    try
    {
        T obj;
        while (ifs >> obj)
        {
            Insert(&obj);
        }
    }
    catch (exception &e)
    {
        DeleteList();
        ifs.close();
        return false;
    }
    ifs.close();
    return true;
}

template <typename T>
bool List342<T>::Insert(T *obj)
{
    Node *buffer = new Node();
    buffer->next = head_;

    Node *current = buffer;

    // step forward until current->next >= obj
    while (current->next != nullptr && *(current->next->data) < *obj)
    {
        current = current->next;
    }

    if (current->next != nullptr && *(current->next->data) == *obj)
    {
        // not unique
        delete buffer;
        return false;
    }

    Node *tmp = new Node;
    tmp->data = new T(*obj);
    tmp->next = current->next;

    current->next = tmp;
    head_ = buffer->next;

    size_++;

    delete buffer;
    return true;
}

template <typename T>
bool List342<T>::Remove(T target, T &result)
{
    Node *buffer = new Node();
    buffer->next = head_;
    Node *current = buffer;
    while (current->next != nullptr)
    {
        if (*(current->next->data) == target)
        {
            result = *(current->next->data);
            Node *node_to_remove = current->next;
            current->next = current->next->next;
            head_ = buffer->next;

            delete node_to_remove;
            delete buffer;
            size_--;
            return true;
        }
        current = current->next;
    }
    delete buffer;
    return false;
}

template <typename T>
bool List342<T>::Peek(T target, T &result) const
{
    Node *current = head_;
    while (current != nullptr)
    {
        if (*(current->data) == target)
        {
            result = T(*(current->data));
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
void List342<T>::DeleteList()
{
    while (head_ != nullptr)
    {
        Node *tmp = head_->next;
        delete head_;
        head_ = tmp;
    }
    size_ = 0;
}

template <typename T>
bool List342<T>::Merge(List342<T> &list1)
{
    if (this == &list1)
    {
        return false;
    }

    Node *buffer = new Node();
    buffer->next = head_;
    Node *current = buffer;

    while (current->next != nullptr && list1.head_ != nullptr)
    {
        while (list1.head_ != nullptr && *(list1.head_->data) < *(current->next->data))
        {
            Node *tmp = list1.head_;
            list1.head_ = tmp->next;
            tmp->next = current->next;
            current->next = tmp;
            size_++;
            list1.size_--;
        }
        while (list1.head_ != nullptr && *(list1.head_->data) == *(current->next->data))
        {
            Node *tmp = list1.head_;
            list1.head_ = list1.head_->next;
            list1.size_--;
            delete tmp;
        }
        current = current->next;
    }
    if (list1.head_ != nullptr)
    {
        current->next = list1.head_;
        list1.head_ = nullptr;
    }
    head_ = buffer->next;
    size_ += list1.size_;
    list1.size_ = 0;
    delete buffer;

    return true;
}

template <typename T>
List342<T> List342<T>::operator+(const List342<T> &other) const
{
    List342<T> tmp = *this;
    tmp += other;
    return tmp;
}

template <typename T>
List342<T> &List342<T>::operator+=(const List342<T> &other)
{
    Node *buffer = new Node();
    buffer->next = head_;
    Node *current = buffer;

    Node *other_current = other.head_;

    while (current->next != nullptr && other_current != nullptr)
    {
        while (other_current != nullptr && *(other_current->data) < *(current->next->data))
        {
            Node *tmp = new Node();
            tmp->data = new T(*(other_current->data));
            tmp->next = current->next;
            current->next = tmp;
            current = current->next;
            other_current = other_current->next;
            size_++;
        }
        while (other_current != nullptr && *(other_current->data) == *(current->next->data))
        {
            other_current = other_current->next;
        }
        current = current->next;
    }
    while (other_current != nullptr)
    {
        Node *tmp = new Node();
        tmp->data = new T(*(other_current->data));
        tmp->next = current->next;
        current->next = tmp;
        current = current->next;
        other_current = other_current->next;
        size_++;
    }
    head_ = buffer->next;
    delete buffer;
    return *this;
}

template <typename T>
List342<T> &List342<T>::operator=(const List342<T> &other)
{
    if (this == &other)
    {
        return *this;
    }
    DeleteList();

    size_ = other.size_;

    Node *other_current = other.head_;
    Node *buffer = new Node();
    Node *current = buffer;
    while (other_current != nullptr)
    {
        Node *tmp = new Node();
        tmp->data = new T(*(other_current->data));
        current->next = tmp;

        other_current = other_current->next;
        current = current->next;
    }
    head_ = buffer->next;
    delete buffer;
    return *this;
}

template <typename T>
bool List342<T>::operator==(const List342<T> &other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    Node *this_current = head_;
    Node *other_current = other.head_;
    while (this_current != nullptr && other_current != nullptr)
    {
        if ((this_current->data == nullptr) != (other_current->data == nullptr) || *(this_current->data) != *(other_current->data))
        {
            return false;
        }

        this_current = this_current->next;
        other_current = other_current->next;
    }
    return (this_current == nullptr) && (other_current == nullptr);
}

template <typename T>
inline bool List342<T>::operator!=(const List342<T> &other) const
{
    return !(*this == other);
}

template <typename U>
ostream &operator<<(ostream &os, const List342<U> &obj)
{
    typename List342<U>::Node *current_node = obj.head_;
    while (current_node != nullptr)
    {
        if (current_node->data != nullptr)
        {
            os << *(current_node->data);
        }
        current_node = current_node->next;
    }
    return os;
}

template <typename T>
int List342<T>::Size() const
{
    return size_;
}

template <typename T>
inline List342<T>::Node::~Node()
{
    // next node deletion is handled externally
    // deletion of node is not intented to chain
    delete data;
}

#endif // LIST342_H_
