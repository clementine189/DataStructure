#include "dataList.hpp"

//merge：L1.Vector[left:mid]与L1.Vector[mid+1:right]是两个有序表，将这两个表合并成L1.Vector[left:right]
//      L2是一个辅助数据表
template<typename T>
void merge(dataList<T>& L1, dataList<T>& L2, const int left, const int mid, const int right)
{
    L1.Print();
    //先复制L1到L2中
    for(int k = left; k <= right; k++)
    {
        L2[k] = L1[k];
    }

    int s1 = left, s2 =  mid + 1, t = left;
    while(s1 <= mid && s2 <= right)
    {
        if(L2[s1] <= L2[s2])
        {
            L1[t++] = L2[s1++];
        }
        else
        {
            L1[t++] = L2[s2++];
        }
    }
    while(s1 <= mid)
    {
        L1[t++] = L2[s1++];
    }
    while(s2 <= right)
    {
        L1[t++] = L2[s2++];
    }
}

//mergeSort:递归实现归并两路归并
template<typename T>
void mergeSort(dataList<T>& L, dataList<T>& L2, int left, int right)
{
    if(left >= right) return ;
    int mid = (left+right)/2;
    mergeSort(L, L2, left, mid);
    mergeSort(L, L2, mid+1, right);
    merge(L, L2, left, mid , right);
}


