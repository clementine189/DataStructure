//多项式加法、乘法，使用stl容器forward_list实现
#include <forward_list>
#include <map>
#include <iostream>
#include <iterator>
using namespace std;

struct Term
{
    //系数
    float coef;
    //指数
    int exp;
    Term (float c, int e)
    {
        coef = c;
        exp = e;
    }

};


forward_list<Term> operator+(forward_list<Term>& LA, forward_list<Term>& LB)
{
    forward_list<Term> res;
    Term tmp(0, -1);
    auto posA = LA.begin();
    auto posB = LB.begin();
    while((posA != LA.end())&&(posB != LB.end()))
    {
        if(posA->exp < posB->exp)
        {
            tmp = *posA;
            posA++;
        }
        else if(posA->exp == posB->exp)
        {
            tmp = Term(posA->coef + posB->coef, posA->exp);     
            posA++;
            posB++;       
        }
        else
        {
            tmp = *posB;
            posB++;
        }
        res.insert_after(res.before_begin(), tmp);
       
    }
    if(posA != LA.end())
    {
        res.insert_after(res.before_begin(), posA, LA.end());
        posA = LA.end();
    }
    if(posB != LB.end())
    {
        res.insert_after(res.before_begin(), posB, LB.end());
        posB = LB.end();
    }
    res.reverse();
 
    return res;
}

forward_list<Term> operator*(forward_list<Term>& LA, forward_list<Term>& LB)
{
    forward_list<Term> res;
    map<int, float> m;
    auto posA = LA.begin();
    auto posB = LB.begin();
    Term tmp(0, -1);
    while(posA != LA.end())
    {
        posB = LB.begin();
        while(posB != LB.end())
        {
            if(m.count(posA->exp + posB->exp) == 0)
            {
                m[posA->exp + posB->exp] = posA->coef * posB->coef;
            }
            else
            {
                m[posA->exp + posB->exp] += posA->coef * posB->coef;;
            }

            posB++;
        }
        posA++;
    }
    for(auto iter : m)
    {
        res.emplace_front(iter.second, iter.first);
    }
    res.reverse();
    return res;
}
void display(forward_list<Term>& l)
{
    for(auto iter : l)
    {
        cout << "(" << iter.coef << ", " << iter.exp << ")   ";  
    }
    cout << endl;
}
int main()
{
    forward_list<Term> lst1{{1.0, 1}, {2.0, 2}, {3.0, 3}};
    display(lst1);
    forward_list<Term> lst2{{2.0, 1}, {2.3, 2}, {3.0, 3}};
    display(lst2);
    forward_list<Term> lst3 = lst1 + lst2;
    display(lst3);
    forward_list<Term> lst4 = lst1 * lst2;
    display(lst4);

    return 0;
}