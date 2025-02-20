#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include "dboperator.h"

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    void setStyle();
    ~regist();

private slots:

    void on_showBox_stateChanged(int arg1);

    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::regist *ui;
    DBOperator DBO;
};

#endif // REGIST_H
