#include "list.h"

int main()
{
    Node *tmp = new Node();
    int tmpInt = 5;
    tmp->p_item = new int(5);
    Node *tmp2 = new Node();
    int tmpInt2 = 7;
    tmp2->p_item = new int(7);
    Node *tmp3 = new Node();
    int tmpInt3 = 9;
    tmp3->p_item = new int(9);
    Node *tmp4 = new Node();
    int tmpInt4 = 10;
    tmp4->p_item =new int(10);

    tmp3->next = tmp4;
    tmp2->next = tmp3;
    tmp->next = tmp2;
    tmp4->next = nullptr;

    List tmpList;
    tmpList.head_ = tmp;
    tmp = nullptr;
    tmp2 = nullptr;
    tmp3 = nullptr; 
    tmp4 = nullptr;
    int debug = 0;
    tmpList.Remove(7);
    debug = 0;

}