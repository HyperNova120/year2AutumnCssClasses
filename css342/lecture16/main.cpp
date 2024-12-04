#include <iostream>

using namespace std;

bool List::MoveToEnd(Item item)
{
    Node buffer = *head;
    buffer.next = head;
    Node *current = &buffer;
    while (current->next != nullptr && *current->next->pItem != item)
    {
        current = current->next;
    }
    if (current->next == nullptr)
    {
        //no item found
        return false;
    }
    //item found
    Node *element = current->next;
    current->next = element->next;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = element;
    head = buffer.next;
    return true;
}
