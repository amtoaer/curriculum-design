#include "product.h"

product::product(QString nam, QString sor, float pric, int amoun, int exp, int batchnu=0)
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

void product::ChangeProduct(QString nam,QString sor,float pric,int amoun,int exp,int batchnu)
{
    name=nam;
    sort=sor;
    price=pric;
    amount=amoun;
    expirationDate=exp;
    batchNum=batchnu;
}

void product::AddBatch(QDate date, int amount)
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
