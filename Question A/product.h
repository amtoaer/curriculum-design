#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>
#include <QDate>
#include <iostream>
using namespace std;

typedef struct batch {
    QDate birthDate; //该批次生产日期
    int amount; //该批次数量
    batch* next; //指向下一个批次的指针
} batch;

class product
{
public:
    friend class MainWindow;//使窗口部件可以操作该类
    product(QString, QString, float, int, int, int); //商品名、类别、价格、数量、保质期、批次数
    void AddBatch(QDate, int); //入库（为了与文件读取复用，删除了增加amount和batchnum的功能，槽要记得写！）
    void Removal(int); //移除特定数量的商品（出库）
    void ChangeProduct(QString,QString,float,int,int,int); //修改商品信息(覆盖写入）
private:
    QString name; //商品名
    QString sort; //商品类别
    batch* head; //商品批次头结点
    int batchNum; //批次数量
    int amount; //商品库存
    float price; //商品价格
    int expirationDate; //商品保质期
};

#endif // PRODUCT_H
