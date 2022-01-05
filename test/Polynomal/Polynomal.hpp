#include <iostream>
#include <limits.h>
#include <map>
using namespace std;
//多项式结点的定义
struct Term
{
    //系数
    float coef;
    //指数
    int exp;

    Term *link;
    Term (float c, int e, Term *next = nullptr)
    {
        coef = c;
        exp = e;
        link = next;
    }

    Term *InsertAfter(float c, int e);
    friend ostream& operator<<(ostream&, const Term&);
};

class Polynomal
{
public:
    //构造函数
    Polynomal()
    {
        first = new Term(0, -1);
    }

    //copy构造函数
    Polynomal(Polynomal& R);
    //计算最大阶数
    int maxOrder();
    //取得多项式单链表的表头指针
    Term *getHead()const {return first;}

private:
    Term *first;
    friend ostream& operator<<(ostream&, const Polynomal&);
    friend istream& operator>>(istream&, Polynomal&);
    friend Polynomal operator+(Polynomal&, Polynomal&);
    friend Polynomal operator*(Polynomal&, Polynomal&);
};


//在当前由this指针指示的项(调用此函数的项)后面插入一个新项
Term *Term::InsertAfter(float c, int e)
{
    link = new Term(c, e, link);
    return link;
}

//Term的友元函数，输出一个项x的内容到输出流out中
ostream& operator<<(ostream& out, const Term& x)
{
    //零系数项不输出
    if(x.coef == 0.0)
        return out;
    //输出系数
    out << x.coef;
    //输出指数
    switch(x.exp)
    {
        case 0:break;
        case 1:out << "X";break;
        default:out << "X^" << x.exp; break;
    }

    return out;
}


Polynomal::Polynomal(Polynomal& R)
{
    first = new Term(0, -1);
    Term *desptr = first, *srcptr = R.getHead() -> link;
    while(srcptr != nullptr)
    {
        desptr->InsertAfter(srcptr->coef, srcptr->exp);
        srcptr = srcptr -> link;
        desptr = desptr -> link;
    }
}

//计算最大阶数，重要前置条件，多项式中的的阶数按升序还是降序未定,
int Polynomal::maxOrder()
{

    int res = INT_MIN;
    //如果为空表，则返回最小整数值
    if(first -> link == nullptr)
        return res;
    Term *pos = first -> link;
    while(pos != nullptr)
    {
        if(pos->exp > res)
        {
            res = pos->exp;
        }
        pos = pos -> link;
    }

    return res;
}


ostream& operator<<(ostream& out, const Polynomal& x)
{
    Term *current = x.getHead() -> link;
    cout << "The polynomal is:" << endl;
    bool h = true;
    while(current != nullptr)
    {
        if(h == false && current -> coef > 0.0)
        {
            out << "+";
        }
        h = false;
        out << *current;
        current = current -> link;
    }
    out << endl;
    return out;
}


istream& operator>>(istream& in, Polynomal& x)
{
    cout << "请输入多项式的项数： " << endl; 
    int num = 0;
    cin >> num;
    while(num < 0)
    {
        cout << "请输入正确的项数："  << endl;
        cin >> num;
    }
    Term *rear = x.getHead();
    int c, e;
    cout << "输入各项系数和指数：" << endl;  
    for(int i = 0; i < num; i++)
    {
        in >> c >> e;
        rear = rear->InsertAfter(c, e); 
    }
    
    return in;
}

//对两个带附加头结点的按升序排列的多项式链表进行加法运算，返回多项式链表
Polynomal operator+(Polynomal& A, Polynomal& B)
{
    Term *pa = A.getHead()->link, *pb = B.getHead()->link;
    Polynomal res;
    Term *current = res.getHead();
    while(pa || pb)
    {
        if(pa == nullptr && pb != nullptr)
        {
            while(pb)
            {
                current = current->InsertAfter(pb->coef, pb->exp);
                pb = pb->link;
            }
            break;
        }
        if(pb == nullptr && pa != nullptr)
        {
            while(pa)
            {
                current = current->InsertAfter(pa->coef, pa->exp);
                pa = pa -> link;
            }
            break;
        }
        if(pb == nullptr && pa == nullptr)
        {
            break;
        }
        if(pa->exp < pb->exp)
        {
            current = current->InsertAfter(pa->coef, pa->exp);
            pa = pa -> link;
        }else if(pa -> exp == pb -> exp)
        {
            current = current->InsertAfter(pa->coef + pb->coef, pa->exp);
            pa = pa -> link;
            pb = pb -> link;
        }
        else
        {
            current = current->InsertAfter(pb->coef, pb->exp);
            pb = pb -> link;
        }
    }
    return res;
}

//对两个带附加头结点的按升序排列的多项式链表进行乘法运算，返回多项式链表
Polynomal operator*(Polynomal& A, Polynomal& B)
{
    Polynomal res;
    map<int, float> m;
    Term *pa, *pb, *tmp;
    tmp = res.getHead();
    pa = A.getHead() -> link;
    while(pa)
    {
        pb = B.getHead() -> link;
        while(pb)
        {
            if(m.count(pa->exp + pb->exp) == 0)
            {
                m.insert(make_pair(pa->exp + pb->exp, pa->coef * pb->coef));
            }
            else
            {
                m[pa->exp + pb->exp] += (pa->coef * pb->coef);
            } 
            pb = pb -> link;
       }
       pa = pa -> link;
    }

    for(auto i : m)
    {
        tmp = tmp->InsertAfter(i.second, i.first);
    }
    return res;

}