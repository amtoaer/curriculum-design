#include "header.h"

Date::Date(int y = 0, int m = 0, int d = 0)
{
    year = y;
    month = m;
    day = d;
}

void Date::PrintDate()
{
    cout << year << "," << month << "," << day << endl;
}

Product::Product(string n, string s, float p, Date e)
    : expirationDate(e)
{
    name = n;
    sort = s;
    head = new batch;
    head->next = NULL;
    price = p;
}

void Product::AddBatch(Date e, int a)
{
    amount = amount + a;
    batch* p = head;
    while (!p->next)
        p = p->next;
    batch* newp = new batch;
    newp->amount = a;
    newp->birthDate = e;
    newp->next = NULL;
    p->next = newp;
}

void Product::Removal(int a)
{
    if (amount < a) {
        cout << "出库数量大于库存数量！" << endl;
        return;
    }
    batch* p = head->next;
    while (a > p->amount) { //当前批次不够出库数量
        a -= p->amount; //该批次商品全部出库，需出库数量减少
        //删除该批次
        head->next = p->next;
        delete p;
        p = head->next;
    }
    //当前批次足够出库数量
    p->amount -= a;
}