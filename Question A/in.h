#ifndef IN_H
#define IN_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class in;
}

class in : public QDialog
{
    Q_OBJECT

public:
    explicit in(QWidget *parent = nullptr);
    ~in();
    void batchIn(int);
    void setInfo(QString);
    void setFather(MainWindow*);

private:
    Ui::in *ui;
    MainWindow* father;
};

#endif // IN_H
