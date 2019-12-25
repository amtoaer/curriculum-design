#include "header.hpp"

int main()
{
    BSTree root;
    int data;
    while (cin >> data) {
        root = AddData(root, data);
    }
    InOrderTraversal(root);
    return 0;
}