#include "product.h"

product::product(QString nam, QString sor, double pric, int exp,int amoun,int batchnu)
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

void product::addAmount(int t)
{
    amount+=t;
    batchNum++;
}

void product::Removal(int a)//因为在对话框里规定了数值范围，所以a必然比amount小
{
    amount-=a;//总库存减少
    batch* p = head->next;
    while (a >= p->amount) { //当前批次不够出库数量
        a -= p->amount; //该批次商品全部出库，需出库数量减少
        //删除该批次
        head->next = p->next;
        delete p;
        p = head->next;
        batchNum--;
        if (a==0)
            return;
    }
    //当前批次足够出库数量
    p->amount -= a;
}
