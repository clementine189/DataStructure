#include <iostream>
using namespace std;
template <typename T>
struct LinkNode
{
    T data;//数据域
    LinkNode<T> *link;//指针域
    LinkNode(LinkNode<T> *ptr = nullptr){link = ptr;}//仅初始化指针成员的构造函数
    LinkNode(const T& item, LinkNode<T> *ptr = nullptr)
    {data = item; link = ptr;}//初始化数据和指针的构造函数
};

template <typename T>
class List
{
public:
    List(){first = new LinkNode<T>;}
  //  List(const T& x){first = new LinkNode<T>(x);}
    List(List<T>& L);
    List(initializer_list<T>);
    ~List(){makeEmpty();}

    void makeEmpty();
    int Length()const;
    LinkNode<T> *getHead()const{return first;}
    LinkNode<T> *Search(T x);
    LinkNode<T> *Locate(int i);
    bool getData(int i, T& x) const;
    void setData(int i, T& x);
    bool Insert(int i, T& x);
    bool Remove(int i, T& x);
    bool IsEmpty()const
    {return first->link == nullptr ? true : false;}
    bool IsFull()const{return false;}
    void Sort();
    void inputFront(T);
    void inputRear(T);
    void output();
    List<T>& operator=(List<T>& L);

protected:
    LinkNode<T> *first;//链表的头指针
};


//复制构造函数
template<typename T>
List<T>::List(List<T>& L)
{
    T value;
    LinkNode<T> *srcptr = L.getHead();
    LinkNode<T> *dstptr = first = new LinkNode<T>;//头节点的data部分不复制
    while (srcptr -> link != nullptr)
    {
        value = srcptr -> link -> data;
        dstptr -> link = new LinkNode<T>(value);
        srcptr = srcptr -> link;
        dstptr = dstptr -> link;        
    }

    dstptr -> link = nullptr;
}

template<typename T>
List<T>::List(initializer_list<T> lst)
{
    first = new LinkNode<T>;
    LinkNode<T> *pos = first;
    for(auto iter : lst)
    {
        //cout << "~" << iter << endl;
        pos -> link = new LinkNode<T>(iter);
        pos = pos -> link;
    }
}
//清空链表
template <typename T>
void List<T>::makeEmpty()
{
    LinkNode<T> *p;   
    while(first -> link != nullptr)
    {
        p = first -> link;
        first -> link = p -> link;
        delete p;
    }
}

//计算带附加头结点的单链表的长度
template <typename T>
int List<T>::Length()const
{
    int count = 0;
    LinkNode<T> *p = first -> link;
    while(p)
    {
        count ++;
        p = p -> link;
    }

    return count;
} 

//搜索单链表中第一次含x的结点，索引成功时返回该结点的位置，否则返回nullptr值
template <typename T>
LinkNode<T>* List<T>::Search(T x)
{
    LinkNode<T> *p = first -> link;
    while(p)
    {
        if(p -> data == x)
        {
            break;
        }
        p = p -> link;
    }

    return p;
}

//定位函数，返回表中第i个元素的地址（第0个表示头节点）。若i<0或i超出表中结点个数，则返回nullptr
template <typename T>
LinkNode<T>* List<T>::Locate(int i)
{
    if(i < 0)
        return nullptr;
    LinkNode<T> *p = first;
    int count = 0;
    while(p != nullptr && count < i)
    {
        p = p -> link;
        count ++;
    }

    return p;
}

//取出链表中的第i个元素的值
template <typename T>
bool List<T>::getData(int i, T& x) const
{
    if(i <= 0)
        return false;
    // int count = 0;
    // LinkNode<T> *p = first;
    // while(p != nullptr && count < i)
    // {
    //     p = p -> link;
    //     count ++;
    // }
    // if(count == i && p != nullptr)
    // {
    //     x = p -> data;
    //     return true;
    // }
    // return false;
    
    LinkNode<T> *p = Locate(i);
    if(p == nullptr)
        return false;
    else
    {
        x = p -> data;
        return true;
    }
}

//给表中第i个元素赋值
template <typename T>
void List<T>::setData(int i, T& x)
{
    if(i <= 0)
        return ;
    LinkNode<T> *p = Locate(i);
    if(p == nullptr)
        return ;
    else
        p -> data = x;
}

//将新元素x插入到链表中的第i个结点之后，插入成功后返回true
template <typename T>
bool List<T>::Insert(int i, T& x)
{
    LinkNode<T> *p = Locate(i);
    if(p == nullptr)
        return false;
    LinkNode<T> *newNode = new LinkNode<T> (x);

    if(newNode == nullptr)
    {
        cerr << "存储分配错误！" << endl;
        exit(1);
    } 
    newNode -> link = p -> link;
    p -> link = newNode;
    
    return true;
}


//删除表中的第i个元素，通过引用型参数x返回该元素的值
template<typename T>
bool List<T>::Remove(int i, T& x)
{
    LinkNode<T> *current = Locate(i - 1);
    if(current == nullptr || current -> link == nullptr)
    {
        return false;
    }

    LinkNode<T> *del = current->link;
    current -> link = del -> link;
    x = del -> data;
    delete del;

    return true;
}

///建立单链表的规定：T endTag
///endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag是0或负数；如果输入序列是字符，
///endTag可以是字符集中不会出现的字符，如'\0'
//前插法建立单链表
template<typename T>
void List<T>::inputFront(T endTag)
{
    LinkNode<T> *newNode;
    T val;
    makeEmpty();
    cin >> val;
    while(val != endTag)
    {
        newNode = new LinkNode<T>(val);
        if(newNode == nullptr)
        {
            cerr<<"存储分配错误！" << endl;
            exit(1);
        }

        newNode -> link = first -> link;
        first -> link = newNode;
        cin >> val;
    }
} 
//后插法建立单链表
template<typename T>
void List<T>::inputRear(T endTag)
{
    LinkNode<T> *newNode, *last;
    last = first;
    T val;
    makeEmpty();
    cin >> val;
    while(val != endTag)
    {
        newNode = new LinkNode<T>(val);
        if(newNode == nullptr)
        {
            cerr << "存储分配错误！" << endl;
            exit(1);
        }
        last -> link = newNode;
        last = last -> link;
        cin >> val;
    } 
}


//单链表的输出函数：将单链表中所有数据按逻辑顺序输出到屏幕上
template<typename T>
void List<T>::output()
{
    LinkNode<T> *current = first -> link;
    while(current != nullptr)
    {
        cout << current->data << endl;
        current = current -> link;
    }
}

//重载operator=，形如A = B,其中A是调用此操作的List对象，B是与参数表中的引用型参数L结合的实参。
template<typename T>
List<T>& List<T>::operator=(List<T>& L)
{
    T value;
    LinkNode<T> *srcptr = L.getHead();
    LinkNode<T> *desptr = first = new LinkNode<T>;

    while(srcptr -> link != nullptr)
    {
        value = srcptr -> link -> date;
        desptr -> link = new LinkNode<T>(value);
        desptr = desptr -> link;
        srcptr = srcptr -> link;
    }

    desptr -> link = nullptr;

    return *this;
}

