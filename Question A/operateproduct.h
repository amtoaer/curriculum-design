#ifndef OPERATEPRODUCT_H
#define OPERATEPRODUCT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class operateProduct;
}

class operateProduct : public QDialog
{
    Q_OBJECT

public:
    explicit operateProduct(QWidget *parent = nullptr);
    ~operateProduct();
    void setFather(MainWindow*);
    void creat();
    void chang(int);
    void setInfoContent(QString);

private:
    Ui::operateProduct *ui;
    MainWindow* father;
};

#endif // OPERATEPRODUCT_H
