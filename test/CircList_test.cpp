#include "../include/CircList.hpp"

int main()
{
//     CircList<int> c1{1, 2, 3, 4, 5, 6, 7, 8, 9};
//     CircList<int> c2(c1);
//   //  cout << c2.Length() << endl;
//     c1.Print();
//     c2.Print();
//     CircLinkNode<int>* p1 = c1.Search(7);
//     if(p1)
//         cout << p1->data<< endl;
//     p1 = c1.Locate(9);
//     if(p1)
//         cout << p1->data << endl;
//     int t1 = 100, t2 = 999;
//     int t3 = 0;
//     c1.Insert(1, t1);
//     c1.Print();
//     c2.Insert(9, t2);
//     c2.Print();

    int t3 = 0;
    CircList<int>c3{666};
    c3.Remove(1, t3);
    cout << t3 << endl;

    CircList<int>c4{11, 22, 33};
    c4.Remove(1, t3);
    //cout << t3 << endl;
    c4.Print();
    c4.Remove(1, t3);
    //cout << t3 << endl; 
    c4.Print();   
    c4.Remove(1, t3);
    //cout << t3 << endl;
    c4.Print();
    CircList<int>c5{11, 22, 33};
    c5.Remove(3, t3);
    //cout << t3 << endl;
    c5.Print();
    return 0;   
}