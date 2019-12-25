#include "header.h"

//输出商品详细信息
void Product::PrintProduct()
{
    cout << "商品名称：	" << name << endl;
    cout << "类型： " << sort << endl;
    cout << "价格： " << price << endl;
    cout << "总数量： " << amount << endl;
    cout << "保质期： "
         << "  天" << endl; //待更改（expiration已改为int型)
    cout << "批次总数： " << endl
         << endl; //待补充
}

//搜索函数（共三种搜索方式）

void SearchBySort(string key, vector<Product> v)
{ //按类查找某类商品
    int size = v.size(); //读取向量大小
    int flag = 0; //用于判断搜索是否成功
    int i;
    string::size_type idx;
    for (i = 0; i != size; i++) { //遍历向量，打印与关键词符合的商品信息
        idx = v[i].GetSort().find(key); //在所有商品的 种类 里模糊搜索关键词
        if (idx != string::npos) { //如果搜索成功
            v[i].PrintProduct(); //则打印该商品信息
        } else
            flag++;
    }
    if (flag == size) //如果查找失败
        cout << endl
             << "没有找到相关项 ToT " << endl;
}

void SearchByName(string key, vector<Product> v)
{ //按商品名字搜索
    int size = v.size(); //读取向量大小
    int flag = 0; //用于判断搜索是否成功
    int i;
    string::size_type idx;
    for (i = 0; i != size; i++) { //遍历向量，打印与关键词符合的商品信息
        idx = v[i].GetName().find(key); //在所有商品的 名字 里模糊搜索关键词
        if (idx != string::npos) { //如果搜索成功
            v[i].PrintProduct(); //则打印该商品信息
        } else
            flag++;
    }
    if (flag == size) //如果查找失败
        cout << endl
             << "没有找到相关项 ToT " << endl;
}

void Search(string key, vector<Product> v)
{ //不筛选搜索:在商品名字和种类里同时搜索
    int size = v.size(); //读取向量大小
    int flag = 0; //用于判断搜索是否成功
    int i;
    string::size_type idx1; //用于判断关键词是否与商品信息匹配
    string::size_type idx2;
    for (i = 0; i != size; i++) { //遍历向量，打印与关键词符合的商品信息
        idx1 = v[i].GetSort().find(key); //在所有商品的 种类和名字 里模糊搜索关键词
        idx2 = v[i].GetName().find(key);
        if (idx1 != string::npos || idx2 != string::npos) { //如果搜索成功
            v[i].PrintProduct(); //则打印该商品信息
        } else
            flag++;
    }
    if (flag == size) //如果查找失败
        cout << endl
             << "没有找到相关项 ToT " << endl;
}
