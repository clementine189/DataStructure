#include <iostream>
using namespace std;

//定义二叉搜索树的结点
template <typename E, typename K>
struct BSTNode 
{
    /* data */
    E data;//数据域
    BSTNode<E, K>*left, *right;
    BSTNode():left(nullptr), right(nullptr){}
    BSTNode(const E d, BSTNode<E,K> *L = nullptr, BSTNode<E, K> *R = nullptr):data(d),left(L),right(R){}
};
