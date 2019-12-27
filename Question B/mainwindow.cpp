#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clearTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setChart(QChart * chart)
{
    ui->graphicsView->setChart(chart);
}

QChart* MainWindow::initChart()
{
    QBarSet *set0 = new QBarSet("Data");//数据集
    QList<int> keys=map.keys();
    for (int i=0;i<keys.length();i++){//写入概率数据
        *set0<<(map[keys[i]]/double(total));
    }
    QBarSeries *series = new QBarSeries();//数据列
    series->append(set0);
    QChart *chart = new QChart();//构建条形图
    chart->addSeries(series);
    chart->setTitle("Chart");//条形图名称
    chart->setAnimationOptions(QChart::SeriesAnimations);//设置动画
    QStringList categories;
    for (int i=0;i<keys.length();i++){//写入分类数据
        QString temp=QString::number(keys[i]);
        categories<<temp;
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);//x轴的标记
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,1);//设置y轴范围
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->setVisible(false);
    //chart->legend()->setAlignment(Qt::AlignBottom);
    return chart;//构建完成，返回指针
}

void MainWindow::on_pushButton_clicked()//点击按钮触发该函数
{
    QString text=ui->textEdit->toPlainText();//获取文本框数据
    text=text.simplified();//去除字符串前面、后面的空格，将字符串内部连续空格变为1个
    for (int i=0;i<text.length();i++){//遍历字符串
        if (!((text[i]>='0'&&text[i]<='9')||text[i]==' ')){//如果有数字、空格之外的字符
            QMessageBox *msgBox=new QMessageBox();
            msgBox->setWindowTitle("输入错误");
            msgBox->setText("请确认输入为纯数字后重试！");
            msgBox->show();
            return;
        }
    }
    if (text.length()==0){
        QMessageBox *msgBox=new QMessageBox();
        msgBox->setWindowTitle("输入错误");
        msgBox->setText("输入内容为空，请重新输入！");
        msgBox->show();
        ui->textEdit->clear();//清空文本框里面输入的多个空格
        return;
    }
    QStringList num=text.split(" ");//用split功能分割字符串获取每个子数据
    for (int i=0;i<num.size();i++){//将子数据转为int并插入到二叉排序树中
        insertTree(num.at(i).toInt());
    }
    setChart(initChart());//显示统计图
    clearTree();
}

void MainWindow::insertTree(int t)
{
    QList<int> list=map.keys();
    bool flag=true;
    for (int i=0;i<list.length();i++){//遍历key
        if(t==list[i]){//如果该key存在
            flag=false;
            break;
        }
    }
    if (flag){//不存在该key则写入树，出现次数记为1
        map[t]=1;
    }else{//存在该key则出现次数++
        map[t]++;
    }
    total++;//数据总量++
    return;
}

void MainWindow::clearTree()//清空树，数据总量和文本框
{
    map.clear();
    total=0;
    ui->textEdit->clear();
    return;
}

