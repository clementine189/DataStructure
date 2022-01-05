#include <iostream>
using namespace std;
template<typename T>
struct CircLinkNode
{
    T data;
    CircLinkNode<T> *link;
    CircLinkNode(CircLinkNode<T> * next = nullptr):link(next){}
    CircLinkNode(T d, CircLinkNode<T> *next = nullptr):data(d), link(next){}
};

template<typename T>
class CircList
{
public:
   // CircList(){first = new CircLinkNode<T>; last = nullptr; first -> link = first;}//默认构造函数会创建一个空表
   // CircList(const T& x);//构造函数，创建循环链表时，
    CircList(CircList<T>& L);//copy构造函数
    CircList(initializer_list<T>);//构造函数
    ~CircList(){makeEmpty();}
    int Length()const;//计算循环链表长度
    bool IsEmpty(){return first -> link == first ? true : false; }
    void makeEmpty();
    CircLinkNode<T> *getHead()const{return first;}//返回附加头结点位置
    CircLinkNode<T> *getLast()const{return last;}//返回尾结点位置
    bool setHead(CircLinkNode<T> *p);//设置附加头结点的位置,设置成功返回true，否则返回false
    CircLinkNode<T> *Search(T x);
    CircLinkNode<T> *Locate(int i);
    T *getData(int i);
    bool Insert(int i, T& x);//在第i个元素后插入x
    bool Remove(int i, T& x);//删除第i个元素，x返回该元素的值
    bool Remove(CircLinkNode<T> *p);//删除指针所指的结点，成功返回true
    void Print();
private:
    CircLinkNode<T> *first, *last;//first指针指向附加头结点，last指向循环链表的最后一个结点，
    //循环链表为空，说明只有一个附加头结点（first），first->link指向first，last = nullptr
    //循环链表中只有一个元素，假设p指针指向该结点，first指向附加头结点，first->link = p,last = p, p->link = p

};

//copy构造函数
template<typename T>
CircList<T>::CircList(CircList<T>& L)
{
    first = new CircLinkNode<T>;
    last = nullptr;
    if(L.IsEmpty() == false)
    {
       // cout << "not empty" << endl;
        CircLinkNode<T> *srcptr = L.getHead() -> link;
        CircLinkNode<T> *dstptr = first;
        while(srcptr != L.getLast())
        {
            //cout << srcptr -> data << endl;
            dstptr -> link = new CircLinkNode<T>(srcptr->data);
            dstptr = dstptr -> link;
            srcptr = srcptr -> link;
        }
        //last结点要特殊处理
        dstptr -> link = new CircLinkNode<T>(srcptr->data);
        dstptr = dstptr -> link;
        //cout << dstptr -> data << endl;
        last = dstptr;
       // cout << last->data << endl;
        dstptr -> link = first -> link;        
    }
    else
    {
        first -> link = first;
    }
  

}

template<typename T>
CircList<T>::CircList(initializer_list<T> lst)
{
    first = new CircLinkNode<T>; 
    last = nullptr;
  //  cout << lst.size() << endl;
    if(lst.size() > 0)
    {
        
        CircLinkNode<T> *pos = first;
        for(auto iter : lst)
        {
           // cout << iter << endl;
            pos -> link = new CircLinkNode<T>(iter);
            pos = pos -> link;
        }
        last = pos;
        pos -> link = first -> link;
        //cout << last -> data << endl;
    }
    else
    {
        first -> link = first;
    }

   //cout << "lst " << endl;
}

template<typename T>
void CircList<T>::makeEmpty()
{
    if(!IsEmpty())
    {
       // cout << "not empty" << endl;
        CircLinkNode<T>* pos;
        while (1)
        {       
            
            pos = first -> link;
            if(pos == last)
                break;
           // cout << pos->data << endl;
            first -> link = pos -> link;
            delete pos;                  
       }
     //  cout << pos -> data << endl;
       first -> link = first;
       delete pos;

    } 
    delete first;
    first = nullptr;
    last = nullptr;    
//   cout << "~" << endl;
}

template<typename T>
int CircList<T>::Length()const
{
    if(first -> link == first)
        return 0;

    int res = 0;
    CircLinkNode<T>* tmp = first;
    while(tmp != last)
    {
        tmp = tmp -> link;
     //   cout << tmp -> data << endl;
        res ++;
    }

    return res;
}

template<typename T>
bool CircList<T>::setHead(CircLinkNode<T> *p)
{
    bool res = false;
    //p是循环链表中的某个结点(不包括附加头结点)，设置附加头结点的link指向该结点，last指向该结点的前一个结点
    //先检查p是不是指向表中的结点
    int len = Length();
    if(len == 0)
    {
        return res;
    }
    CircLinkNode<T> *tmp = last;
    for(int i = 0; i < len; i++)
    {
        if(tmp -> link == p)
        {
            res = true;
            break;
        }
        tmp = tmp -> link;
    }
    if(res)
    {
        first -> link = p;    
        //记得修改last的指向
        last = tmp;       
    }
    return res;
}

// template<typename T>
// CircLinkNode<T> * CircList<T>::Search(T x)
// {
//     if(first -> link == first)
//         return nullptr;

//     CircLinkNode<T>* res, *tmp = first;
//     int flag = 0;
//     while(flag != 1 || tmp -> link != last)
//     {
//         if(tmp -> link -> data == x)
//         {
//             flag = 1;
//             res = tmp -> link;
//         }
//         tmp = tmp -> link;
//     }

//     if(flag)
//     {
//         return res;
//     }

//     if(tmp -> link == last && last -> data == x)
//     {
//         return last;
//     }

//     return nullptr;
// }



template<typename T>
CircLinkNode<T> * CircList<T>::Search(T x)
{
    CircLinkNode<T> *res = nullptr, *tmp = first -> link;
    int len = Length();
    for(int i = 0; i < len; i++)
    {
        if(tmp -> data == x)
        {
            res = tmp;
            break;
        }
        tmp = tmp -> link;
    }
    return res;
}

template<typename T>
CircLinkNode<T> *CircList<T>::Locate(int i)
{
    CircLinkNode<T> *res = nullptr, *tmp = first;
    int len = Length(), j = 0;
    if(len < i)
    {
        return res;
    }
    while(j < i)
    {
        tmp = tmp -> link;
        j++;
    }
    res = tmp;

    return res;
}

template<typename T>
T *CircList<T>::getData(int i)
{
    T *res = nullptr;
    CircLinkNode<T> *tmp = Locate(i);
    if(tmp)
    {
        res = &(tmp->data);
    }

    return res;
}

template<typename T>
bool CircList<T>::Insert(int i, T& x)//i>0,在第i个元素后插入x;i=0，作为第一个元素插入
{
    bool res = false;
    CircLinkNode<T> *newNode = new CircLinkNode<T>(x);
    if(i == 0)
    {
        //last如果为nullptr，是空表
        if(last)//非空
        {
            newNode -> link = first -> link;
            first -> link = newNode;
        }
        else//空
        {
            first -> link = newNode;
            newNode -> link = first;
            last = newNode;
        }
        res = true;
        return res;
    }
    CircLinkNode<T> *tmp = Locate(i);
    if(tmp)
    {        
        newNode -> link = tmp -> link;
        tmp -> link = newNode;
        if(last == tmp)
        {
            last = newNode;
        }
        res = true;
    }
    return res;
}
template<typename T>
bool CircList<T>::Remove(int i, T& x)//删除第i个元素（0 < i <= len），x返回该元素的值
{
   // cout << "Remove -> Remove i = " << i << endl;
    bool res = false;
    int len = Length();
    if(len <= 0 || i <= 0 || i > len)
        return res;
    CircLinkNode<T> *tmp = Locate(i);
    if(tmp)
    {
        if(len == 1)//仅有一个结点
        {
            //cout << "len = 1" << endl;
            if(i == 1)//验证i是否为1
            {
                first -> link = first;
                last = nullptr;
                x = tmp -> data;
                delete tmp;
                res = true;
            }

        }
        else if(first ->link == tmp)//结点数目大于1，删除第一个结点
        {
            //cout << "first" << endl;
            first -> link = tmp -> link;
            last -> link = tmp -> link;
            x = tmp -> data;
            delete tmp;
            res = true;
        }
        else if(last == tmp)//结点数目大于1，删除最后一个结点
        {
            CircLinkNode<T> *before_tmp = Locate(i - 1);
            before_tmp -> link = last -> link;
            last = before_tmp;
            x = tmp -> data;
            delete tmp;            
            res = true;
        }
        else//结点数目大于1，删除非头尾的结点
        {
            CircLinkNode<T> *before_tmp = Locate(i - 1);
            before_tmp -> link = tmp -> link;
            x = tmp -> data;
            delete tmp;
            res = true;
        }
    }
    //cout << "Remove:" << x << endl;
    return res;
}

template<typename T>
bool CircList<T>::Remove(CircLinkNode<T> *p)//p指向该链表中的某个结点
{
    int i = 1;
    T x;
    CircLinkNode<T> *tmp = first -> link;
    while(1)
    {
        
        if(tmp == p)
        {
           // cout << "Remove: i = " << i << "data = "<< tmp -> data << "len = " << Length()<< endl;
            break;
            
        }
        i++;
        tmp = tmp -> link;
        
    }
    //cout << "Remove i = " << i << endl;
    bool res = Remove(i, x);

    return res;
}

template<typename T>
void CircList<T>::Print()
{
    cout << "Print(): ";
    CircLinkNode<T> *tmp = first -> link;
    int len = Length();
    for(int i =0; i < len; i++)
    {
        cout << tmp -> data << " ";
        tmp = tmp -> link;
    }
    cout << endl;

}