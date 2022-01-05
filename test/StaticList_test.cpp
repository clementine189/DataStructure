#include "../include/StaticList.hpp"

int main()
{
    // StaticList<int> slst1{1, 2, 3, 4, 5};
    // slst1.Print();

    // StaticList<int> slst2{};

    // for(int i = 0; i < 20; i++)
    // {
    //     slst2.Append(i + 9);
    // }
    // slst2.Print();

    StaticList<int> slst3{-1};

    for(int i = 0; i < 20; i++)
    {
        slst3.Insert(1, i);
    }
    slst3.Print();

    // for(int i = 20; i > 0; i--)
    // {
    //     slst3.Remove(i);
    //     slst3.Print();
    // }
    // slst3.Print();

    cout << "InsertSort:" << endl; 
    slst3.InsertSort();
    slst3.Print();
    

    return 0;
}