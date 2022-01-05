#include "dataList.hpp"
template<typename T>
void SelectSort(dataList<T>& L, const int left, const int right)
{
    for(int i = left; i < right; i++)
    {
        int k = i;
        for(int j = i+1; j <= right; j++)
        {
            if(L[j] < L[k])
            {
                k = j;
            }
        }
        if(k != i)
        {
            L.Swap(L[i], L[k]);
        }
        L.Print();
    }
    
}
