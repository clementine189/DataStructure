#include "dataList.hpp"
#include "InsertSort.hpp"

template<typename T>
int dataList<T>::Partition(const int low, const int high)
{
    if(low < 0 || high > currentSize)
        return -1;
    int pivotpos = low;
    Element<T> pivot = Vector[low];
    for(int i = low + 1; i <= high; i++)
    {
        if(Vector[i] < pivot)
        {
            pivotpos++;
            if(pivotpos != i)
                Swap(Vector[i], Vector[pivotpos]);
        }
    }
    Vector[low] = Vector[pivotpos];
    Vector[pivotpos] = pivot;

    return pivotpos;
}

///版本1
//基础版本的快速排序
template<typename T>
void QuickSort(dataList<T>& L, const int left, const int right)
{
    if(left < right)
    {
        int pivotpos = L.Partition(left, right);//L.Print();
        QuickSort(L, left, pivotpos-1);
        QuickSort(L, pivotpos+1, right);
    }
    
}


///版本2
//快速-直接插入混合算法，研究表明，序列长度M取值为5~25时，直接插入排序要比快速排序至少快10%
//对小规模的子序列调用插入排序算法进行排序
const int M2 = 20;
template<typename T>
void QuickSort_insert(dataList<T>& L, const int left, const int right)
{
    if(right - left <= M2)
    {
        InsertSort(L, left, right);
    }
    else
    {
        int pivotpos = L.Partition(left, right);L.Print();
        QuickSort(L, left, pivotpos-1);
        QuickSort(L, pivotpos+1, right);
    }
}


///版本3
//另一种改进的快速-直接插入混合排序算法
//QuickSort_3:对小规模的序列不排序，直接返回，版本3的快速排序实现
//HybridSort_3:先进行快速排序，最后对基本有序的序列进行一遍插入排序
const int M3 = 10;
template<typename T>
void QuickSort_3(dataList<T>& L, const int left, const int right)
{
    if(right - left <= M3)
        return ;

    int pivotpos = L.Partition(left, right);L.Print();
    QuickSort_3(L, left, pivotpos - 1);
    QuickSort_3(L, pivotpos + 1, right);
}

template<typename T>
void HybirdSort_3(dataList<T>& L, const int left, const int right)
{
    QuickSort_3(L, left, right);
    InsertSort(L, left, right);
}

///版本4
//基于版本3，对pivot的选取做一些改动，避免遇到最坏情况
//median3：三者取中的算法，得到在left、right、mid三个位置上中间的那个元素值，通过swap，将中间值交换到right位置
//PartitionOnce:一趟划分算法的一种实现，此处不再是成员函数
//QuickSort_4:版本4的快速排序实现
//HybirdSort:版本4的最顶层函数
const int M4 = 10;
template<typename T>
Element<T>& median3(dataList<T>& L, const int left, const int right)
{
    int mid = (left+right)/2;
    int k = left;
    if(L[mid] < L[k])
    {
        k = mid;
    }
    if(L[right] < L[k])
    {
        k = right;
    }

    if(k != left)
    {
        L.Swap(L[k], L[left]);//把最小的值交换到left位置上
    }
    if(mid != right && L[mid]<L[right])//把中间值交换到right
    {
        L.Swap(L[mid], L[right]);
    }

    return L[right];
}

template<typename T>
int PartitionOnce(dataList<T>& L, const int left, const int right)
{
    
    int i = left, j = right - 1;
    if(left < right)
    {
        Element<T> pivot = median3(L, left, right);//以L[right]为基准
        for(;;)
        {
            while(i < j&&L[i] < pivot)
            {
                i++;
            }
            while(i < j&&pivot<L[j])
            {
                j--;
            }
            if(i < j)
            {
                L.Swap(L[i], L[j]);
                i++;
                j--;
            }
            else
            {
                break;
            }
        }

        if(L[i] > pivot)
        {
            L[right] = L[i];
            L[i] = pivot;
        }     
    }

    return i;
}


template<typename T>
void QuickSort_4(dataList<T>& L, const int left, const int right)
{
    if(left - right <= M4)
    {
        return ;
    }

    int pivotpos = PartitionOnce(L, left, right);L.Print();
    QuickSort_4(L, left, pivotpos-1);
    QuickSort_4(L, pivotpos+1, right);
}

template<typename T>
void HybirdSort_4(dataList<T>& L, const int left, const int right)
{
    QuickSort_4(L, left, right);
    InsertSort(L, left, right);
}

///版本5
//三路划分的快速排序算法
//将文件划分成三个部分：比基准小的，与基准相等的，比基准大的
//在算法中，先把左右指针遇到的与基准相等的放到左右两侧，比基准大的放到右侧，比基准小的放到左侧；最后把两侧相等的值转移到中间来
template<typename T>
void QuickSort_5(dataList<T>& L, const int left, const int right)
{
    int i, j, k, p, q;
    Element<T> pivot = L[right];//设置pivot
    if(right <= left)
        return ;
    i = left-1;
    j = right;
    p = left-1;
    q = right;

    while(1)
    {
        while(L[++i] < pivot)
        {
             if(i == j)
             {
                 break;
             }
        }
        while(pivot < L[--j])
        {
            if(i == j)
            {
                break;
            }
        }
        if(i >= j)
        {
            break;
        }
        L.Swap(L[i],L[j]);
        if(L[i] == pivot)
        {
            p++;
            L.Swap(L[p], L[i]);
        }
        if(pivot == L[j])
        {
            q--;
            L.Swap(L[j],L[q]);
        }
    }
    
    if(L[i] > L[right])
    {
        L.Swap(L[i], L[right]);
        k = right - 1;
    }
    else
    {
        k = right;
    }
    j--;
    i++;
    while(k >= q)
    {
        L.Swap(L[k], L[q]);
        k--;
        q++;
    }
    L.Print();
    QuickSort_5(L, left, j);
    QuickSort_5(L, i, right);
}