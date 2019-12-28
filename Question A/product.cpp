#include "product.h"

product::product(QString nam, QString sor, double pric, int exp,int amoun=0,int batchnu=0)//创建时数量和批次为空
{
    name=nam;
    sort=sor;
    price=pric;
    amount=amoun;
    expirationDate=exp;
    batchNum=batchnu;
    head=new batch;
    head->next=nullptr;//空指针
}

void product::ChangeProduct(QString nam,QString sor,double pric,int exp)//除了数量都可供修改
{
    name=nam;
    sort=sor;
    price=pric;
    expirationDate=exp;
}

void product::AddBatch(QDate date, int amount)//增加批次
{
    batch* p =head;
    while(p->next!=nullptr){
        p=p->next;
    }
    batch* add=new batch;
    add->amount=amount;
    add->birthDate=date;
    add->next=nullptr;
    p->next=add;
}
