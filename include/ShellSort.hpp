#include "dataList.hpp"
template<typename T>
void ShellSort(dataList<T>& L, const int left, const int right)
{
    int i, j, gap = right - left + 1;
    Element<T> temp;
    do{
        gap = gap/3 + 1;
        for(i = left + gap; i <= right; i++)
        {
            if(L[i] < L[i - gap])
            {
                temp = L[i];
                j = i - gap;
                do{
                    L[j+gap] = L[j];//后移元素
                    j = j - gap;//再比较前一元素
                }while(j >= left && temp < L[j]);
                L[j+gap] = temp;
            }
        }
    }while(gap > 1);
}