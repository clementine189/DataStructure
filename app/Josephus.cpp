#include "../include/CircList.hpp"
//len为长度，数到第d个人删除
void Josephus(CircList<int> &L, int len, int d)
{
    CircLinkNode<int> *tmp = L.getHead() -> link;
    CircLinkNode<int> *after_tmp = tmp;
    while(len > 1)
    {
        tmp = after_tmp;        
        for(int i = 1; i < d; i++)
        {
            tmp = tmp -> link;            
            //cout << "i = " <<  i << " data = " << tmp->data << " after_tmp = " << after_tmp->data << endl;
            
        }
        after_tmp = tmp -> link;
        L.Remove(tmp);
        L.Print();
        len --;
    }
}

int main()
{
    CircList<int> L{32, 11, 78, 21, 90, 42, 89, 100, 667, 789};
    Josephus(L, 10, 3);
    //L.Print();
    return 0;
}