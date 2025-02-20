#ifndef REGIST_READER_H
#define REGIST_READER_H

#include <QDialog>
#include "dboperator.h"

namespace Ui {
class regist_reader;
}

class regist_reader : public QDialog
{
    Q_OBJECT

public:
    explicit regist_reader(QWidget *parent = nullptr);
    ~regist_reader();
    void setStyle();

private slots:

    void on_showBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::regist_reader *ui;
    DBOperator DBO;
};

#endif // REGIST_READER_H
