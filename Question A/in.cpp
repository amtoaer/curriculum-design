#include "in.h"
#include "ui_in.h"
#include <QIntValidator>

in::in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::in)
{
    ui->setupUi(this);
    ui->amount->setValidator(new QIntValidator(nullptr));//设置只能输入int
}

in::~in()
{
    delete ui;
}

void in::batchIn(int position)
{
    int year,month,day,amount;
    amount=ui->amount->text().toInt();
    QStringList date=ui->birthdate->text().simplified().split('/');
    if (date.size()!=3){
        QMessageBox::information(nullptr,"入库失败","请检查日期格式后重试！\n(正确格式为year/month/day)");
        return;
    }
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
