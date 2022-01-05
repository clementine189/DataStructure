#include <iostream>
#include <cstdlib>
//#include "linearList.h"
using namespace std;

const int defaultSize = 100;

template <typename T>
class SeqList
{
protected:
    T *data;
    int maxSize;//最大可容纳的表项数目
    int last;//当前已存表项的最后位置从0开始
    void reSize(int newSize);

public:
    SeqList(int size = defaultSize);
    SeqList(SeqList<T>& L);
    ~SeqList(){delete[] data;}
    int Size()const{return maxSize;}
    int Length()const{return last + 1;}
    int Search(T& x)const;
    int Locate(int i)const;
    bool getData(int i, T& x)const
    {
        if(i > 0 && i <= last + 1)
        {
            x = data[i-1]; 
            return true;
        }
        else
        {
            return false;
        }    
    }
    void setData(int i, T& x)
    {
        if(i > 0 && i <= last+1)
        {
            data[i-1] = x; 
        }
    }
    bool Insert(int i, T& x);
    bool Remove(int i, T& x);
    bool IsEmpty()
    {
        return (last == -1) ? true : false; 
    }
    bool IsFull()
    {
        return (last == maxSize-1) ? true : false;
    }
    void input();
    void output();
    SeqList<T>& operator=(SeqList<T>& L);

};

//构造函数
template <typename T>
SeqList<T>::SeqList(int sz)
{
    if(sz > 0)
    {
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if(data == NULL)
        {
            cerr << "存储分配错误！" << endl;
            exit(1);
        }
    }
}

//复制构造函数
template <typename T>
SeqList<T>::SeqList(SeqList<T>& L)
{
    maxSize = L.Size();
    last = L.Length() - 1;
    T value;
    data = new T[maxSize];
    if(data == NULL)
    {
        cerr << "存储分配错误！"<< endl;
        exit(1);
    }
    for(int i = 0; i <= last + 1; i++)
    {
        L.getData(i, value);
        data[i-1] = value;
    }
}


//扩充顺序表
template <typename T>
void SeqList<T>::reSize(int newSize)
{
    if(newSize <= 0)
    {
        cerr << "无效的数组大小" << endl;
        return ;
    }
    if(newSize != maxSize)
    {
        T *newarray = new T[newSize];
        if(newarray == NULL)
        {
            cerr << "存储分配错误" << endl;
            exit(1);
        }
        int n = last + 1;
        T *srcptr = data;
        T *dstptr = newarray;
        while(n--)
        {
            *dstptr++ = *srcptr++; 
        }
        delete []data;
        data = newarray;
        maxSize = newSize;
    }
}

//搜索:如果返回0，表示搜索失败；否则返回该表项是第几个元素
template <typename T>
int SeqList<T>::Search(T& x)const
{
  //  cout << "Search传入的元素为：" << x <<endl;
    for(int i = 0; i <= last; i++)
    {
    //    cout << "   " << last << ":" << data[i] << endl;
        if(data[i] == x)
        {
            return i+1;
        }
    }
    return 0;
}

//定位：返回第i（1 <= i <= last + 1）个表项的位置，否则返回0，表示定位失败
template <typename T>
int SeqList<T>::Locate(int i)const
{
    if(i >= 1 && i <= last+1)
        return i;
    else
        return 0;
}

//插入:将x插入到表中第i（0 <= i <= last+1）个表项之后
template <typename T>
bool SeqList<T>::Insert(int i, T& x)
{
 //   cout << "传入的元素为：" << x <<endl;
    if(last == maxSize - 1)
        return false;
    if(i < 0 || i > last+1)
        return false;

    for(int j = last; j >= i; j--)
        data[j+1] = data[j];

    data[i] = x;
    last++;
    return true;
}

//删除：从表中删除第i（1 <= i <= last）个表项，通过x返回删除的元素值
template <typename T>
bool SeqList<T>::Remove(int i, T& x)
{
    if(last == -1)
        return false;
    if(i < 1 || i > last + 1)
        return false;
    x = data[i-1];
    for(int j = i; j <= last; j++)
    {
        data[j-1] = data[j];
    }
    last--;
    return true;
}

//输入
template <typename T>
void SeqList<T>::input()
{
    //从标准输入逐个输入，建立顺序表
    cout << "开始建立顺序表，请输入表中元素个数(从0开始)：" ;
    while(1)
    {
        cin >> last;
        if(last <= maxSize - 1)
            break;

        cout << "元素输入有误，范围不能超过" << maxSize - 1 << ":" ;

    }

    for(int i = 0; i <= last; i++)
    {
        cin >> data[i];
    }
}



//输出
template <typename T>
void SeqList<T>::output()
{
    cout << "顺序表当前的最后位置为：" << last << endl;
    for(int i = 0; i <= last; i++)
    {
        cout << "#" << i+1 << ":" << data[i] << endl;
    }
}

template <typename T>
SeqList<T>& SeqList<T>::operator=(SeqList<T>& L)
{
    
    maxSize = L.Size();
    last = L.Length() - 1;
    T *tmp = data;
    T value;
    data = new T[maxSize];
    if(data == NULL)
    {
        cerr << "存储分配错误！"<< endl;
        exit(1);
    }
    for(int i = 0; i <= last + 1; i++)
    {
        L.getData(i, value);
        data[i-1] = value;
    }
    if(tmp)
        delete tmp;
}