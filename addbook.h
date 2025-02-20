#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include "dboperator.h"

namespace Ui {
class addbook;
}

class addbook : public QDialog
{
    Q_OBJECT

public:
    explicit addbook(QWidget *parent = nullptr);
    void setStyle();
    ~addbook();

private slots:

    void on_pushButton2_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::addbook *ui;
    DBOperator DBO;
};

#endif // ADDBOOK_H
