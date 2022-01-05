#include <iostream>
using namespace std;

const int maxSize = 100;

template<typename T>
struct SLinkNode
{
    T data;
    int link;
};

template<typename T>
class StaticList
{
private:
    SLinkNode<T> elem[maxSize];
    int avil;//当前可分配首地址
public:
    void InitList();
    StaticList(initializer_list<T> lst);
    int Length();//计算静态链表的长度
    int Locate(int i);//在静态链表中查找第i个结点
    int Search(T x);//在静态链表中查找具有给定值的结点
    bool Append(T x);//在静态链表的表尾追加一个新结点
    bool Insert(int i, T x);//在静态链表的第i个结点后插入新结点
    bool Remove(int i); //在静态链表中释放第i个结点
    bool IsEmpty();
    void Print();//打印静态链表
    void InsertSort();//使用插入排序算法
};

template<typename T>
void StaticList<T>::InitList()
{
    elem[0].link = -1;
    avil = 1;//空闲链表的开头
    for(int i = 1; i < maxSize; i++)
    {
        elem[i].link = i+1;//空闲链表
    }
    elem[maxSize - 1].link = -1;
}

template<typename T>
StaticList<T>::StaticList(initializer_list<T> lst)
{
    InitList();
    int pos = 0;
    for(auto iter : lst)
    {
        //从空闲链表头取出一个结点
        int newNode = avil;
        if(newNode == -1)
        {
            cout << "静态链表空闲空间不足" << endl;
            exit(1);
        }     
        avil = elem[avil].link;

        //将结点插入现有链表的末尾
        elem[newNode].data = iter;
        elem[newNode].link = -1;
        elem[pos].link = newNode;
        pos = newNode;
    }
}

template<typename T>
int StaticList<T>::Length()
{
    int cnt = 0, pos = 0;
    while(elem[pos].link!=-1)
    {
        cnt++;
        pos = elem[pos].link;
    }

    return cnt;
}

template<typename T>
bool StaticList<T>::IsEmpty()
{
    if(elem[0].link == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
int StaticList<T>::Search(T x)
{
    int res = 0;//如果找不到，返回头结点
    if(IsEmpty())
        return res;

    int pos = 0;
    while(elem[pos].link != -1)
    {
        pos = elem[pos].link;
        if(elem[pos].data == x)
        {
            res = pos;
            break;
        }        
    }

    return res;
}

template<typename T>
int StaticList<T>::Locate(int i)
{
    if(i < 0)
        return -1;
    if(i == 0)
        return 0;
    
    int pos = 0;
    int j = 0;
    while(pos != -1 && j < i)
    {
        pos = elem[pos].link;
        j++;
    }

    return pos;
}

template<typename T>
bool StaticList<T>::Append(T x)
{
    bool res = false;
    if(avil == -1)
    {
        return res;
    }
    int len = Length();
    int pos = Locate(len);
    int newNode = avil;
    avil = elem[avil].link;

    elem[pos].link = newNode;
    elem[newNode].data = x;
    elem[newNode].link = -1;
    res = true;
    return res;
}

template<typename T>
bool StaticList<T>::Insert(int i, T x)
{
    bool res = false;
    if(avil == -1)
    {
        return res;
    }
    int pos = Locate(i);
    int newNode = avil;
    avil = elem[avil].link;

    int pos_after = elem[pos].link;
    elem[pos].link = newNode;
    elem[newNode].data = x;
    elem[newNode].link = pos_after;
    res = true;
    return res;
}

template<typename T>
bool StaticList<T>::Remove(int i)
{
    bool res = false;
    int pos = Locate(i);
    if(i > 0)
    {
        int before_pos = Locate(i-1);
        int after_pos = elem[pos].link;
        elem[pos].link = avil;
        avil = pos;
        elem[before_pos].link = after_pos;
        res = true;
    }
    return res;
}
template<typename T>
void StaticList<T>::Print()
{
    cout << "Print() ";
    int pos = elem[0].link;
    while(pos != -1)
    {
        cout << elem[pos].data << " ";
        pos = elem[pos].link;
    }
    cout << endl;

    cout << "avil = " << avil << endl;
}

template<typename T>
void StaticList<T>::InsertSort()
{
   // cout << Length() << endl;
   int len = Length();
    if(len <= 1)
        return ;
    //记录第二个结点位置
    int pos = elem[0].link;
    int pos1 = elem[pos].link; 
    elem[pos].link = -1;

    for(int i = 2; i <= len; i++)
    {
        pos = pos1;
        T data = elem[pos].data;
        // cout << "data = " << data << endl;
        // cout << "pos  = " << pos << endl;
        int pre_tmp = 0;
        int tmp = elem[0].link;
        while(tmp != -1 && data >= elem[tmp].data)
        {
            // cout << "pre_tmp = " << pre_tmp << endl;
            // cout << "tmp =     " << tmp << endl;
            pre_tmp = tmp;
            tmp = elem[tmp].link;
            // cout << "   pre_tmp = " << pre_tmp << endl;
            // cout << "   tmp =     " << tmp << endl;
        }
        pos1 = elem[pos].link;

        elem[pre_tmp].link = pos;
        elem[pos].link = tmp;
        //Print();
    }
}

