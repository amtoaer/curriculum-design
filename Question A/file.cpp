#include "header.h"

/* 商品文件保存｜读取路径，可自行修改 */
string path = "/home/jeasonlau/.shop";

void ReadFromFile(vector<Product> v)
{
    ifstream readFile;
    readFile.open(path, ios::in);
    string name, sort;
    float price;
    int amount, batchNum, expirationDate;
    //首先读入初始化Product初始化所需数据
    while (readFile >> name >> sort >> price >> amount >> expirationDate >> batchNum) {
        Product tempProduct(name, sort, price, amount, expirationDate, batchNum);
        int year, month, day, batchAmount;
        //读入该Product各批次数据
        for (int count = batchNum; count > 0; count--) {
            cin >> year >> month >> day >> batchAmount;
            Date tempDate(year, month, day);
            //调用AddBatch函数
            tempProduct.AddBatch(tempDate, batchAmount);
        }
        v.push_back(tempProduct);
    }
    readFile.close();
}

void SaveToFile(vector<Product> v)
{
    ofstream saveFile;
    saveFile.open(path, ios::out);
    //遍历vector,输出其中每个元素的全部信息
    for (int i = 0; i < v.size(); i++) {
        v[i].SaveProduct(saveFile);
    }
    saveFile.close();
}