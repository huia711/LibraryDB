#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>
#include "dboperator.h"

extern QString ID;
extern QString Password;

namespace Ui {
class homepage;
}

class homepage : public QDialog
{
    Q_OBJECT
public:
    homepage(QWidget *parent = nullptr);
    ~homepage();
    void setStyle();

private:
    Ui::homepage *ui;
    DBOperator DBO;

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_showBox_stateChanged(int arg1);
    void on_btn_forget_clicked();
    void on_AdBox_stateChanged(int arg1);
};

#endif // HOMEPAGE_H

