
#pragma once

struct Node
{
    int *p_item;

    Node *next;
};
class List
{
public:
    //List();
    //~List();
    int Remove(const int &it);
    Node *head_;

private:
};