#ifndef MARK

#define MARK

#include <bits/stdc++.h>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;

public:
    Date(int, int, int);
    void PrintDate();
    int GetYear();
    int GetMonth();
    int GetDay();
};

typedef struct batch {
    Date birthDate; //该批次生产日期
    int amount; //该批次数量
    batch* next; //指向下一个批次的指针
} batch;

class Product {
private:
    string name; //商品名
    string sort; //商品类别
    batch* head; //商品批次头结点
    int batchNum; //批次数量
    int amount; //商品总数
    float price; //商品价格
    int expirationDate; //商品保质期
public:
    Product(string, string, float, int, int, int); //商品名、类别、价格、数量、保质期、批次数
    void AddBatch(Date, int); //生产日期和数量（入库）
    void Removal(int); //移除特定数量的商品（出库）
    void PrintProduct(); //输出当前商品的详细信息
    void ChangeProduct(); //修改商品信息
    void SaveProduct(ofstream&); //把商品信息保存到文件
    //便于查询
    string GetSort();
    string GetName();
};

#endif