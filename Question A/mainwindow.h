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
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel* getFirstModel();
    QStandardItemModel* getSecondModel(const QModelIndex &index);//基于第一个model的位置显示第二个model的数据
    void FirstTableSet(QStandardItemModel*);
    void SecondTableSet(QStandardItemModel*);
    void ReadFromFile();
private slots:
    void on_firstTableView_clicked(const QModelIndex &index);

    void on_importFrom_clicked();

private:
    Ui::MainWindow *ui;
    QVector<product> shop;
};
#endif // MAINWINDOW_H
