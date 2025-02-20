#ifndef READERPAGE_H
#define READERPAGE_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QStandardItemModel>
#include "dboperator.h"

namespace Ui {
class readerpage;
}

class readerpage : public QDialog
{
    Q_OBJECT

public:
    readerpage(QWidget *parent = nullptr);
    void setStyle();
    void show();
    void Color_progressBar();
    void overdue();
    void ifborrow();
    ~readerpage();

private slots:

    void on_unlock_pushButton_clicked();

    void on_edit_pushButton_clicked();

    void on_re_pushButton_clicked();

    void on_commandLinkButton_clicked();

    void on_can_pushButton_clicked();

    void on_borrow_pushButton_clicked();

private:
    Ui::readerpage *ui;
    DBOperator DBO;
    QSqlQueryModel *table;
    QSqlQueryModel *table2;
    QSqlQueryModel *model;
    QStandardItemModel *m;
};

#endif // READERPAGE_H
