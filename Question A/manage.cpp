#include "header.hpp"

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

int Date::GetYear() { return year; }
int Date::GetMonth() { return month; }
int Date::GetDay() { return day; }

Product::Product(string n, string s, float p, int a, int e, int b = 0) //批次数量默认为0
{
    batchNum = 0;
    name = n;
    sort = s;
    amount = a;
    batchNum = b;
    expirationDate = e;
    head = new batch;
    head->next = NULL;
    price = p;
}

void Product::AddBatch(Date e, int a)
{
    batchNum++;
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
        batchNum--;
    }
    //当前批次足够出库数量
    p->amount -= a;
}

void Product::ChangeProduct()
//修改商品信息
{
    int i = 0, choice[4] = { 0 }, expirationDat;
    string nam, sor;
    float pric;
    char c;
    cout << "1、修改姓名\n2、修改商品类别\n3、修改商品价格\n4、修改商品保质期\n请输入你想修改的信息选项（可多选，以空格分隔）：" << endl;
    cin >> choice[i];
    while (1) {
        if (choice[i] < 1 || choice[i] > 4) {
            cout << "输入错误，请重新输入！" << endl;
            i = 0;
            cin >> choice[i];
        } else {
            i++;
            c = getchar();
            if (c == '\n')
                break;
            cin >> choice[i];
        }
    }
    for (int i = 0; choice[i] != 0; i++) {
        switch (choice[i]) {
        case 1:
            cout << "将该姓名修改为：";
            cin >> nam;
            name = nam;
            break;
        case 2:
            cout << "将商品类别修改为：";
            cin >> sor;
            sort = sor;
            break;
        case 3:
            cout << "将商品价格修改为：";
            cin >> pric;
            price = pric;
            break;
        case 4:
            cout << "将商品保质期修改为：";
            cin >> expirationDat;
            expirationDate = expirationDat;
            break;
        default:
            cout << "输入错误！\n";
            break;
        }
    }
}

void Product::SaveProduct(ofstream& save)
{
    //将该商品的所有信息输出到文件
    save << name << ' ' << sort << ' ' << price << ' '
         << amount << ' ' << expirationDate << ' ' << batchNum << ' ';
    batch* p = head;
    while (p->next != NULL) {
        p = p->next;
        save << p->birthDate.GetYear() << ' ' << p->birthDate.GetMonth() << ' ' << p->birthDate.GetDay() << ' '
             << p->amount << ' ';
    }
    save << p->birthDate.GetYear() << ' ' << p->birthDate.GetMonth() << ' ' << p->birthDate.GetDay() << ' '
         << p->amount << ' ';
    return;
}

string Product::GetName() { return name; }
string Product::GetSort() { return sort; }