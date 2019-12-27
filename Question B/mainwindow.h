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
    void insertTree(int);
    void clearTree();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QMap<int,int> map;//二叉排序树
    int total;//数据总量
};
#endif // MAINWINDOW_H
