#include "operateproduct.h"
#include "ui_operateproduct.h"
#include "product.h"

operateProduct::operateProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operateProduct)
{
    ui->setupUi(this);
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
    product t(ui->name->text(),
              ui->sort->text(),
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
    if (ui->name->text().remove(' ')==""){
        ui->name->setText(name);
    }
    if (ui->sort->text().remove(' ')==""){
        ui->sort->setText(sort);
    }
    if (ui->price->text().remove(' ')==""){
        ui->price->setText(QString::number(price));
    }
    if (ui->expdate->text().remove(' ')==""){
        ui->expdate->setText(QString::number(expdate));
    }
    father->shop[num-1].ChangeProduct(ui->name->text(),
                                    ui->sort->text(),
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
