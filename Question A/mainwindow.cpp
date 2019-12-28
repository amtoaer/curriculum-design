#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createproduct.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //给第一个table设置只允许单行选中且无法编辑
    ui->firstTableView->verticalHeader()->hide();//隐藏行号
    ui->firstTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->firstTableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->firstTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //第二个同理
    ui->SecondTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SecondTableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->SecondTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FirstTableSet(QStandardItemModel *t)
{
    ui->firstTableView->setModel(t);
    ui->firstTableView->setCurrentIndex(t->index(0,0));
    on_firstTableView_clicked(t->index(0,0));//默认选中第一行
}

void MainWindow::SecondTableSet(QStandardItemModel *t)
{
    ui->SecondTableView->setModel(t);
}

QStandardItemModel* MainWindow::getFirstModel()
{
    QStandardItemModel* model=new QStandardItemModel();
    QString label="编号,商品名,类别,库存,价格,保质期";
    QStringList labels=label.split(',');
    model->setHorizontalHeaderLabels(labels);//设置label
    for (int i=0;i<shop.size();i++){//顺序插入
        model->insertRow(i);
        model->setData(model->index(i, 0), i+1);
        model->setData(model->index(i, 1), shop[i].name);
        model->setData(model->index(i, 2), shop[i].sort);
        model->setData(model->index(i, 3), shop[i].amount);
        model->setData(model->index(i, 4), shop[i].price);
        model->setData(model->index(i, 5), shop[i].expirationDate);
    }
    return model;
}

QStandardItemModel* MainWindow::getSecondModel(const QModelIndex &index)
{
    QStandardItemModel* model=new QStandardItemModel();
    QString label="库存,生产日期";
    QStringList labels=label.split(',');
    model->setHorizontalHeaderLabels(labels);
    auto num=index.model()->index(index.row(),0);
    int position=num.data().toInt();//获取当前行的编号
    batch* p=shop[position-1].head->next;//用编号找到原始数据
    //原始用行号找到原始数据的方法在进行查询后无法使用，故修改为使用编号标记原始数据
    int flag=0;
    while(p!=nullptr){//顺序插入
        model->insertRow(flag);
        model->setData(model->index(flag,0),p->amount);
        model->setData(model->index(flag,1),p->birthDate);
        p=p->next;
        flag++;
    }
    return model;
}

QStandardItemModel* MainWindow::getSearchResult(QStandardItemModel * base, QString toSearch)
{
    QStandardItemModel* result=new QStandardItemModel();
    QString label="编号,商品名,类别,库存,价格,保质期";
    QStringList labels=label.split(',');
    result->setHorizontalHeaderLabels(labels);//result设置label
    auto items=base->findItems(toSearch,Qt::MatchContains,1);//模糊查找商品名
    for (int i=0;i<items.size();i++){
        int t = items[i]->index().row();//获取该行行号
        result->appendRow(base->takeRow(t));//在结果中插入该行内容
    }
    return result;
}

void MainWindow::on_firstTableView_clicked(const QModelIndex &index)
{
    SecondTableSet(getSecondModel(index));//基于第一个表中被选中的编号显示第二个表中的内容
}

void MainWindow::ReadFromFile()
{
    /*读取顺序为：商品名，类别，价格，库存，保质期，批次数，批次
     * 批次读取顺序为：年/月/日/库存 */
    QString path= "/home/jeasonlau/tttt";//路径需要自己手动修改（预计添加目录选择功能）
    QFile read(path);
    if (!(read.open(QIODevice::ReadOnly))){
        QMessageBox* warning=new QMessageBox();
        warning->setWindowTitle("读入错误");
        warning->setText("存档文件不存在！");
        warning->show();
    }
    //成功打开后
    shop.clear();
    QTextStream in(&read);
    while(!in.atEnd()){
        QString content=in.readLine();
        if (content==""){//读到最后的换行符
            break;
        }
        QStringList varible=content.simplified().split(' ');
        QString name=varible.at(0);
        QString sort=varible.at(1);
        double price=varible.at(2).toDouble();
        int amount=varible.at(3).toInt();
        int expdate=varible.at(4).toInt();
        int batchNum=varible.at(5).toInt();
        product temp(name,sort,price,amount,expdate,batchNum);//构造product对象
        int position=6;
        for (int i=batchNum;i>0;i--){//读入批次
            int year=varible.at(position++).toInt();
            int month=varible.at(position++).toInt();
            int day=varible.at(position++).toInt();
            int amount=varible.at(position++).toInt();
            QDate date(year,month,day);
            temp.AddBatch(date,amount);
        }
        shop.append(temp);//添加该商品
    }
    QMessageBox *msgbox=new QMessageBox();
    msgbox->setWindowTitle("导入成功");
    msgbox->setText("已成功导入数据!");
    msgbox->show();
    read.close();
    FirstTableSet(getFirstModel());
}

void MainWindow::WriteInFile()//导出文件
{
    QString path= "/home/jeasonlau/tttt";//路径需要自己手动修改（预计添加目录选择功能）
    QFile Write(path);
    Write.open(QIODevice::ReadWrite);//如果文件不存在会自动创建文件
    QTextStream out(&Write);
    QString writeIn;
    for (int i=0;i<shop.size();i++){//对商店商品进行遍历
        writeIn.clear();
        writeIn=shop[i].name+" "+\
                        shop[i].sort+" "+\
                        QString::number(shop[i].price)+' '+\
                        QString::number(shop[i].amount)+' '+\
                        QString::number(shop[i].expirationDate)+' '+\
                        QString::number(shop[i].batchNum)+' ';
        batch* p=shop[i].head;
        while(p->next!=nullptr){
            p=p->next;
            writeIn=writeIn+QString::number(p->birthDate.year())+' '+
                            QString::number(p->birthDate.month())+' '+
                            QString::number(p->birthDate.day())+' '+
                            QString::number(p->amount)+' ';
        }
        //成功读取完一件商品
        writeIn+='\n';
        out<<writeIn;//保存到文件
    }
    //文件保存结束后
    QMessageBox *msgbox=new QMessageBox();
    msgbox->setWindowTitle("导出成功");
    msgbox->setText("已成功导出数据！");
    msgbox->show();
    Write.close();
}

void MainWindow::on_importFrom_clicked()
{
    QMessageBox::StandardButton t=QMessageBox::question(
            nullptr,
            "警告",
            "从文件导入将会覆盖现有内容，是否继续？",
            QMessageBox::Yes|QMessageBox::No,
            QMessageBox::Yes);
    if (t==QMessageBox::Yes)
        ReadFromFile();
}

void MainWindow::on_exportTo_clicked()
{
    WriteInFile();
}

void MainWindow::on_search_clicked()
{
    QString test=ui->searchContent->text();
    FirstTableSet(getSearchResult(getFirstModel(),test));//将第一个table内容设置为搜索结果
}
