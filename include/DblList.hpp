//带附加头结点的双向循环链表
#include <iostream>
using namespace std;
template<typename T>
struct DblNode
{
    T data;
    DblNode<T> *lLink, *rLink;
    DblNode(DblNode<T> *left = nullptr, DblNode<T> *right = nullptr):lLink(left), rLink(right){}
    DblNode(T value, DblNode<T> *left = nullptr, DblNode<T> *right = nullptr):data(value), lLink(left), rLink(right){}
};

template<typename T>
class DblList
{
public:
    DblList(T uniqueVal);//构造函数：建立附加头结点
    DblList(initializer_list<T> lst);
    ~DblList();
    int Length()const;
    bool IsEmpty(){return first -> rLink == first;}
    DblNode<T> *getHead()const{return first;}
    void setHead(DblNode<T> *ptr){first = ptr;}
    DblNode<T>*Search(const T& x);//在链表中沿后记方向寻找等于给定值x的结点
    DblNode<T> *Locate(int i, int d);//在链表中定位序号为i（i >= 0）的结点，d = 0按前驱方向，d！=0按后继方向
    bool Insert(int i, const T& x, int d);//在第i个结点后插入一个包含值x的新结点，d = 0按前驱方向，d ！= 0按后继方向
    bool Remove(int i, T& x, int d);//删除第i个结点，x返回其值，d = 0按前驱方向，d！= 0按后继方向 
    void Print();//rLink打印循环双向链表
private:
    DblNode<T> *first;
};

template<typename T>
DblList<T>::DblList(T uniqueVal)//构造函数：建立附加头结点
{
    first = new DblNode<T>(uniqueVal);
    if(first == nullptr)
    {
        cerr << "存储分配出错！" << endl;
        exit(1);
    }

    first -> lLink = first -> rLink = first;
}

template<typename T>
DblList<T>::DblList(initializer_list<T> lst)
{
    T head;
    first = new DblNode<T>(head);
    if(first == nullptr)
    {
        cerr << "存储分配出错！" << endl;
        exit(1);
    }

    first -> lLink = first -> rLink = first;


    DblNode<T> *pos = first, *right_pos = pos -> rLink;

    for(auto iter : lst)
    {
        DblNode<T>* tmp = new DblNode<T>(iter);
        if(tmp == nullptr)
        {
            cerr << "存储分配出错！" << endl;
            exit(1);
        }
        tmp -> lLink = pos;
        tmp -> rLink = right_pos;
        pos -> rLink = tmp;
        right_pos -> lLink = tmp;

        pos = tmp;
        right_pos = tmp -> rLink;
    }

}
template<typename T>
DblList<T>::~DblList()//删除表中所有结点
{
    while(!IsEmpty())
    {
        cout << "~" << endl;
        DblNode<T> *pos = first->rLink;
        DblNode<T> *pos_after = pos -> rLink;
        first -> rLink = pos_after;
        pos_after -> lLink = first;
        delete pos;        
    }
    delete first;

}

template<typename T>
int DblList<T>::Length()const
{
    int res = 0;
    DblNode<T> * pos = first->rLink;
    while(pos != first)
    {
        pos = pos->rLink;
        res++;
    }
    return res;
}

template<typename T>
DblNode<T>* DblList<T>::Search(const T& x)//在链表中按后继方向寻找等于给定值x的结点
{
    DblNode<T> *res = nullptr, *pos = first -> rLink;
    while(pos != first)
    {
        if(pos -> data == x)
        {
            res = pos;
            break;
        }
        pos = pos->rLink;
    }

    return res;
}

template<typename T>
DblNode<T> * DblList<T>::Locate(int i, int d)//在链表中定位序号为i（0 <= i <= len, 0表示头结点）的结点，d = 0按前驱方向，d！=0按后继方向
{
    DblNode<T> *res = nullptr;
    if(i < 0 || i > Length())
        return res;
    int cnt = i;
    res = first;

    while(cnt)
    {
        if(d)//后继
        {
            res = res->rLink;
        }
        else//前驱
        {
            res = res->lLink;
        }
        cnt--;
    }

    return res;
}

template<typename T>
bool DblList<T>::Insert(int i, const T& x, int d)//在第i个结点后插入一个包含值x的新结点，d = 0按前驱方向，d ！= 0按后继方向
{
    bool res = false;
    DblNode<T> *pos = Locate(i, d);
    if(pos == nullptr)
    {
        return res;
    }

    DblNode<T> *newNode = new DblNode<T>(x);
    if(newNode == nullptr)
    {
        cerr << "存储分配出错！" << endl;
        exit(1);
    }
    
    if(d)//后继
    {
        DblNode<T> *pos_right = pos->rLink;
        newNode->rLink = pos_right;
        newNode->lLink = pos;
        pos->rLink = newNode;
        pos_right->lLink = newNode;
    }
    else//前驱
    {
        DblNode<T> *pos_left = pos->lLink;
        newNode->lLink = pos_left;
        newNode->rLink = pos;
        pos_left->rLink = newNode;
        pos->lLink = newNode;
    }

    res = true;

    return res;
}

template<typename T>
bool DblList<T>::Remove(int i, T& x, int d)//删除第i个结点，x返回其值，d = 0按前驱方向，d！= 0按后继方向 
{
    bool res = false;
    DblNode<T> *pos = Locate(i, d);
    if(pos == nullptr)
    {
        return res;
    }
    if(pos == first)
    {
        cout << "不允许删除头结点！" << endl;
        return res;
    }
    x = pos->data;
    DblNode<T> *pos_left = pos->lLink, *pos_right = pos->rLink;
    pos_left->rLink = pos_right;
    pos_right->lLink = pos_left;  
    delete pos;
    res = true; 

    return res;
}

template<typename T>
void DblList<T>::Print()
{
    cout << "Print()" ;
    DblNode<T>* pos = first->rLink;
    while(pos != first)
    {
        cout << pos -> data << " ";
        pos = pos -> rLink;
    }
    cout << endl;
}