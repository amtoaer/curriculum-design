#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //给第一个table设置只允许单行选中且无法编辑
    ui->firstTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->firstTableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->firstTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //给第二个table设置
    ui->SecondTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SecondTableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->SecondTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    FirstTableSet(getFirstModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FirstTableSet(QStandardItemModel *t)
{
    ui->firstTableView->setModel(t);
}

void MainWindow::SecondTableSet(QStandardItemModel *t)
{
    ui->SecondTableView->setModel(t);
}

QStandardItemModel* MainWindow::getFirstModel()
{
    QStandardItemModel* model=new QStandardItemModel();
    QString label="商品名,类别,库存,价格,保质期";
    QStringList labels=label.split(',');
    model->setHorizontalHeaderLabels(labels);//设置label
    for (int i=0;i<shop.size();i++){//顺序插入
        model->insertRow(i);
        model->setData(model->index(i, 0), shop[i].name);
        model->setData(model->index(i, 1), shop[i].sort);
        model->setData(model->index(i, 2), shop[i].amount);
        model->setData(model->index(i, 3), shop[i].price);
        model->setData(model->index(i, 4), shop[i].expirationDate);
    }
    return model;
}

QStandardItemModel* MainWindow::getSecondModel(const QModelIndex &index)
{
    QStandardItemModel* model=new QStandardItemModel();
    QString label="库存,生产日期";
    QStringList labels=label.split(',');
    model->setHorizontalHeaderLabels(labels);
    int position=index.row();
    batch* p=shop[position].head->next;
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

void MainWindow::on_firstTableView_clicked(const QModelIndex &index)
{
    SecondTableSet(getSecondModel(index));//基于第一个表中被选中的行数显示第二个表中的内容
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
    QTextStream in(&read);
    while(!in.atEnd()){
        QString content=in.readLine();
        if (content==""){//读到最后的换行符
            break;
        }
        QStringList varible=content.simplified().split(' ');
        QString name=varible.at(0);
        QString sort=varible.at(1);
        float price=varible.at(2).toFloat();
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
    msgbox->setWindowTitle("读取成功");
    msgbox->setText("已成功读取数据!");
    msgbox->show();
    read.close();
    FirstTableSet(getFirstModel());
}

void MainWindow::on_importFrom_clicked()
{
    ReadFromFile();
}
