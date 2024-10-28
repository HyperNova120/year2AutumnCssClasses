#ifndef LIST342_H_
#define LIST342_H_
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

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
    bool Peek(T target, T &result);
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
        T *data = nullptr;
        Node *next = nullptr;
    };

    Node *head_ = nullptr;

public:
    Node *head() const;
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
    ifstream ifs(file_name);
    if (!ifs)
    {
        ifs.close();
        return false;
    }
    while (ifs)
    {
        T tmp;
        Insert(ifs >> tmp);
    }
    ifs.close();
    return true;
}

template <typename T>
bool List342<T>::Insert(T *obj)
{
    Node *tmp = new Node();
    tmp->data = new T(*obj);

    Node *buffer = new Node();
    buffer->next = head_;
    Node *current = buffer;
    while (current->next != nullptr)
    {
        if (*(current->next->data) >= *obj)
        {
            break;
        }
        current = current->next;
    }

    if (current->next == nullptr)
    {
        current->next = tmp;
        head_ = buffer->next;
        delete buffer;
        tmp = nullptr;
        return true;
    }
    else if (*(current->next->data) > *obj)
    {
        tmp->next = current->next;
        current->next = tmp;
        head_ = buffer->next;
        delete buffer;
        tmp = nullptr;
        return true;
    }
    
    delete buffer;
    delete tmp;
    return false;
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
            current->next->data = nullptr;
            Node *tmp = current->next;
            current->next = current->next->next;
            delete tmp;
            head_ = buffer->next;
            delete buffer;
            return true;
        }
        current = current->next;
    }
    delete buffer;
    return false;
}

template <typename T>
bool List342<T>::Peek(T target, T &result)
{
    Node *buffer = new Node();
    buffer->next = head_;
    Node *current = buffer;
    while (current->next != nullptr)
    {
        if (*(current->next->data) == target)
        {
            result = *(current->next->data);
            delete buffer;
            return true;
        }
        current = current->next;
    }
    delete buffer;
    return false;
}

template <typename T>
void List342<T>::DeleteList()
{
    while (head_ != nullptr)
    {
        Node *tmp = head_->next;
        delete head_->data;
        delete head_;
        head_ = tmp;
    }
}

template <typename T>
bool List342<T>::Merge(List342<T> &list1)
{
    if (*this == list1)
    {
        return false;
    }

    while (list1.head_ != nullptr)
    {
        T *target = list1.head_->data;
        T tmp;
        list1.Remove(*target, tmp);
        Insert(target);
    }
    return true;
}

template <typename T>
List342<T> List342<T>::operator+(const List342<T> &other) const
{
    List342<T> tmp = List342(*this);
    tmp += other;
    return tmp;
}

template <typename T>
List342<T> &List342<T>::operator+=(const List342<T> &other)
{
    Node *current = other.head_;
    while (current != nullptr)
    {
        Insert(current->data);
        current = current->next;
    }
    return *this;
}

template <typename T>
List342<T> &List342<T>::operator=(const List342<T> &other)
{
    DeleteList();
    Node *current = other.head_;
    while (current != nullptr)
    {
        Insert(current->data);
        current = current->next;
    }
    return *this;
}

template <typename T>
bool List342<T>::operator==(const List342<T> &other) const
{
    Node *this_current = head_;
    Node *other_current = other.head_;
    while (this_current != nullptr && other_current != nullptr)
    {
        if ((this_current->data == nullptr) != (other_current->data == nullptr))
        {
            return false;
        }
        else if (*(this_current->data) != *(other_current->data))
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

template <typename T>
ostream &operator<<(ostream &os, const List342<T> &obj)
{
    auto current_node = obj.head_; //auto works but if i manually declare current_node as the same type that auto makes it when you look at it in debug, gcc suddenly doesnt know wtf im talking about.... WTF
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
    Node *current = head_;
    int size = 0;
    while (current != nullptr)
    {
        size++;
        current = current->next;
    }
    return size;
}

#endif // LIST342_H_