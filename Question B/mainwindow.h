#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QMessageBox>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setChart(QChart*);
    QChart* initChart();
    QChart* initSimpleChart();
    void insertTree(int);
    void insertSimpleTree(int);
    void clearTree();
    void initSimpleTree();
private slots:
    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

private:
    Ui::MainWindow *ui;
    QMap<int,int> map;//二叉排序树
    int total;//数据总量
    QMap<QString,int> simplemap;//用于生成简单视图
};
#endif // MAINWINDOW_H
