#include "header.h"
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