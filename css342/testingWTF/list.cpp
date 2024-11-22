#include "list.h"

int List::Remove(const int &it)
{
   Node *buffer = new Node();
   buffer->next = head_;
   Node *current = buffer;

   while (current->next != nullptr && *(current->next->p_item) < it)
   {
      current = current->next;
   }

   int numItemsAfter = 0;

   if (current->next != nullptr && *(current->next->p_item) == it)
   {
      //found item
      Node *tmp = current->next;
      current->next = tmp->next;
      delete tmp->p_item;
      delete tmp;

      //count # elements > it
      while (current->next != nullptr)
      {
         numItemsAfter++;
         current = current->next;
      }
   }

   head_ = buffer->next;
   delete buffer;
   return numItemsAfter;
}