#include "dataList.hpp"

//默认无重复元素
//直接插入排序,升序排序
template<typename T>
void InsertSort(dataList<T>& L, const int left, const int right)
{
    Element<T> temp;
    int i, j;
    for(i = left + 1; i <= right; i++)
    {
        if(L[i] < L[i-1])
        {
            temp = L[i];
            j = i - 1;
            do{
                L[j+1] = L[j];
                j--;
            }while(j >= left && temp < L[j]);
            L[j+1] = temp;

            L.Print();
        }
        
    }
}

//折半插入排序，升序
template<typename T>
void BinaryInsertSort(dataList<T>& L, const int left, const int right)
{
    Element<T> temp;
    int i, j, k, low, high, mid;

    for(i = left+1; i <= high; i++)
    {
        temp = L[i];
        low = left;
        high = i - 1;
        while(low <= high)
        {
            mid = (low + high)/2;
            if(temp < L[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for(k = i - 1; k >= low; k--)
        {
            L[k+1] = L[k];
        }
        L[low] = temp;
    }
}