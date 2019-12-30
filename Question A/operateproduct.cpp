#include "operateproduct.h"
#include "ui_operateproduct.h"
#include "product.h"
#include "QValidator"

operateProduct::operateProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operateProduct)
{
    ui->setupUi(this);
    ui->price->setValidator(new QDoubleValidator(nullptr));//价格只能输入double
    ui->expdate->setValidator(new QIntValidator(nullptr));//保质期只能输入int
}

operateProduct::~operateProduct()
{
    delete ui;
}

void operateProduct::setFather(MainWindow *t)
{
    father=t;
}

void operateProduct::creat()
{
    //姓名和类别不能存在空格，否则将污染存档导致读取失败（存档基于空格分割）
    //str.remove(QRegExp("\\s"))表示去除该字符串所有空白字符
    product t(ui->name->text().remove(QRegExp("\\s")),
              ui->sort->text().remove(QRegExp("\\s")),
              ui->price->text().toDouble(),
              ui->expdate->text().toInt(),0,0);
    father->shop.append(t);//插入新数据
    father->FirstTableSet(father->getFirstModel());//刷新first table
    ui->name->clear();
    ui->sort->clear();
    ui->price->clear();
    ui->expdate->clear();
    QMessageBox::information(nullptr,"创建成功","商品已创建成功");
}

void operateProduct::chang(int num)//参数为编号
{
    //获取原始数据
    auto name=father->shop[num-1].name;
    auto sort=father->shop[num-1].sort;
    auto price=father->shop[num-1].price;
    auto expdate=father->shop[num-1].expirationDate;
    //表示如果留空则使用原始数据，即留空则不修改
    if (ui->name->text().remove(QRegExp("\\s"))==""){
        ui->name->setText(name);
    }
    if (ui->sort->text().remove(QRegExp("\\s"))==""){
        ui->sort->setText(sort);
    }
    if (ui->price->text().remove(QRegExp("\\s"))==""){
        ui->price->setText(QString::number(price));
    }
    if (ui->expdate->text().remove(QRegExp("\\s"))==""){
        ui->expdate->setText(QString::number(expdate));
    }
    father->shop[num-1].ChangeProduct(ui->name->text().remove(QRegExp("\\s")),
                                    ui->sort->text().remove(QRegExp("\\s")),
                                    ui->price->text().toDouble(),
                                    ui->expdate->text().toInt());
    father->FirstTableSet(father->getFirstModel());//刷新first table
    ui->name->clear();
    ui->sort->clear();
    ui->price->clear();
    ui->expdate->clear();
    QMessageBox::information(nullptr,"修改成功","商品已修改成功");
}

void operateProduct::setInfoContent(QString a)
{
    ui->info->setText(a);
}
