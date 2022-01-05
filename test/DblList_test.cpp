#include "../include/DblList.hpp"

int main()
{
    DblList<int> dlst1{1, 2, 3, 4, 5};
    int tmp = 0;
    dlst1.Print();

    cout << dlst1.Locate(2, 1)->data<<endl;

    cout << dlst1.Locate(3, 0)->data<< endl;

    dlst1.Insert(0, 0, 1);

    dlst1.Print();

    dlst1.Insert(0,-1,0);

    dlst1.Print();

    dlst1.Remove(0, tmp, 0);
    dlst1.Print();
    dlst1.Remove(1, tmp, 0);
    dlst1.Print();
    dlst1.Remove(1, tmp, 1);
    dlst1.Print();

    DblList<int> dlst2{};

    dlst2.Print();

    cout << dlst2.Length()<<endl;

    return 0;
}