#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
    int data;
    int count;
    Node *leftChild, *rightChild;
    Node(int, int);
} Node, *BSTree;

void InOrderTraversal(BSTree);
BSTree AddData(BSTree, int);
