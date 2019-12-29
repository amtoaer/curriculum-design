#include "in.h"
#include "ui_in.h"

in::in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::in)
{
    ui->setupUi(this);
}

in::~in()
{
    delete ui;
}

void in::batchIn(int position)
{
    int year,month,day,amount;
    amount=ui->amount->text().toInt();
    QStringList date=ui->birthdate->text().simplified().split('.');
    year=date.at(0).toInt();
    month=date.at(1).toInt();
    day=date.at(2).toInt();
    QDate temp(year,month,day);
    father->shop[position-1].AddBatch(temp,amount);
    father->shop[position-1].addAmount(amount);
    ui->birthdate->clear();
    ui->amount->clear();
    QMessageBox::information(nullptr,"入库成功","商品已入库成功");
}

void in::setFather(MainWindow * t)
{
    father=t;
}

void in::setInfo(QString t)
{
    ui->info->setText(t);
}
