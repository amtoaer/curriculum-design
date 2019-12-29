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
