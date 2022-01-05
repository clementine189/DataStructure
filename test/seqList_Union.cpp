//有顺序表LA和LB，实现合并运算，结果存于LA,重复元素只保留一个
#include "../include/seqList.hpp"
void Union(SeqList<int>& LA, SeqList<int>& LB)
{
    int n = LA.Length(), m = LB.Length();
    int tmp=666;
    for(int i = 0; i < m; i++)
    {
        LB.getData(i+1, tmp);
        int k = LA.Search(tmp);
        if(k == 0)
       {
            LA.Insert(n, tmp);
            n++;
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
    Union(LA, LB);
    LA.output();
    return 0;
}