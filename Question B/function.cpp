#include "header.hpp"

Node::Node(int Data = 0, int Count = 1) //构造函数
{
    data = Data;
    count = Count;
    leftChild = NULL;
    rightChild = NULL;
}

void InOrderTraversal(BSTree root) //二叉排序树中序遍历
{
    if (root != NULL) {
        InOrderTraversal(root->leftChild);
        printf("data: %d , count: %d\n", root->data, root->count);
        InOrderTraversal(root->rightChild);
    }
}

BSTree AddData(BSTree root, int data) //二叉排序树插入数据
{
    if (root == NULL) {
        root = new Node(data);
    } else {
        if (root->data == data) {
            root->count++;
        } else if (root->data > data) {
            root->leftChild = AddData(root->leftChild, data);
        } else {
            root->rightChild = AddData(root->rightChild, data);
        }
    }
    return root;
}