#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItemModel>
#include <QMainWindow>
#include <product.h>
#include <QVector>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVector<product> shop;
    friend class operateproduct;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel* getFirstModel();
    QStandardItemModel* getSecondModel(const QModelIndex &index);//基于第一个model的位置显示第二个model的数据
    QStandardItemModel* getSearchResult(QStandardItemModel*,QString);//基于第一个model进行查找构造查找结果
    void FirstTableSet(QStandardItemModel*);
    void SecondTableSet(QStandardItemModel*);
    void ReadFromFile();
    void WriteInFile();
private slots:
    void on_firstTableView_clicked(const QModelIndex &index);

    void on_importFrom_clicked();

    void on_exportTo_clicked();

    void on_search_clicked();

    void on_create_clicked();

    void on_change_clicked();

    void on_in_clicked();

    void on_out_clicked();

    void on_stat_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
