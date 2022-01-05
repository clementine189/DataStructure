#include "../include/QuickSort.hpp"
#include "../include/SelectSort.hpp"
#include "../include/mergeSort.hpp"
#include <cstdlib>
#include <ctime>

void Createlst(dataList<int>& L)
{
    srand((int)time(0));  // 产生随机种子
    for (int i = 0; i < L.Length(); i++)
    {
        L[i].setKey(rand() % 100);
    }
}

int main()
{
    dataList<int> lst3, lst4, lst5, lst6, lst7, lst72;
    // cout << "lst3:" << endl;
    // lst3.setLength(30);
    // Createlst(lst3);
    // lst3.Print();
    // HybirdSort_3(lst3, 0, 29);
    
    // cout<<"lst4:"<<endl;
    // lst4.setLength(30);
    // Createlst(lst4);
    // lst4.Print();
    // HybirdSort_4(lst4, 0, 29);
    
    // cout <<"lst5:" <<endl;
    // lst5.setLength(30);
    // Createlst(lst5);
    // lst5.Print();
    // QuickSort_5(lst5, 0, 29);
    
    // cout << "lst6:"<< endl;
    // lst6.setLength(30);
    // Createlst(lst6);
    // lst6.Print();
    // SelectSort(lst6, 0, 29);

    cout << "lst7:"<< endl;
    lst7.setLength(6);
    lst72.setLength(6);
    Createlst(lst7);
    lst7.Print();
    mergeSort(lst7, lst72, 0, 5);
    lst7.Print();
    return 0;
}