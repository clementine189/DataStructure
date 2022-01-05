#ifndef DATALIST_HPP_
#define DATALIST_HPP_
#include <iostream>
using namespace std;

const int DefaultSize = 100;
template<typename T>
class Element
{
public:
    T key;
   // field otherdata;
    Element<T>& operator=(Element<T>& x){key = x.key;return *this;}
    bool operator==(Element<T>& x){return key == x.key;}
    bool operator<=(Element<T>& x){return key <= x.key;}
    bool operator>(Element<T>& x){return key > x.key;}
    bool operator<(Element<T>& x){return key < x.key;}
    void setKey(T x){key = x;}
    T getKey(){return key;}
};

template<typename T>
class dataList
{
public:
    dataList(int maxSz = DefaultSize):maxSize(maxSz), currentSize(0){Vector = new Element<T>[maxSize];}
    void setLength(int len){currentSize = len;}
    void Swap(Element<T>& x, Element<T>& y){Element<T> tmp = x; x = y; y = tmp;}
    int Length(){return currentSize;}
    Element<T>& operator[](int i){return Vector[i];}
    int Partition(const int low, const int high);//快速排序划分, 返回基准元素，假设基准元素为Element<T>[low]
    void Print();
private:
    Element<T>* Vector;
    int maxSize;
    int currentSize;
};

template<typename T>
void dataList<T>::Print()
{
    cout << "Print()" ;
    for(int i = 0; i < Length(); i++)
    {
        cout << Vector[i].getKey() <<" ";
    }
    cout << endl;
}

#endif
