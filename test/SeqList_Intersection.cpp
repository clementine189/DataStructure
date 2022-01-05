//求顺序表LA与LB中的共有元素，结果存于LA
#include "../include/seqList.hpp"

void Intersection(SeqList<int>& LA, SeqList<int>& LB)
{
    int tmp = 666, k = 0, i = 0;
    int m = LA.Length();
    while(i < m)
    {
   //     cout << "i = " << i << "; tmp = " << tmp << endl; 
        LA.getData(i+1, tmp);
    //    cout << "i = " << i << "; tmp = " << tmp << endl; 
        k = LB.Search(tmp);
   //     cout << "k = " << k << endl;
        if(k == 0)
        {
            LA.Remove(i+1, tmp);
            m--;
        }
        else
        {
            i++;
        }
    }
}

int main()
{
    SeqList<int> LA;
    SeqList<int> LB;
    LA.input();
    LB.input();
    LA.output();
    LB.output();

    Intersection(LA, LB);

    LA.output();

    return 0;
}