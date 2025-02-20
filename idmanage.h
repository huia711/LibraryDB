#ifndef IDMANAGE_H
#define IDMANAGE_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QStandardItemModel>
#include "dboperator.h"

namespace Ui {
class idmanage;
}

class idmanage : public QDialog
{
    Q_OBJECT

public:
    explicit idmanage(QWidget *parent = nullptr);
    ~idmanage();
    void setStyle();
    void showmodel();
    void show(QString Type);
    void overdue();
    void remake();

private:
    Ui::idmanage *ui;
    DBOperator DBO;
    QSqlQueryModel *table;
    QSqlQueryModel *model;
    QStandardItemModel *modell;
    QStandardItemModel *modelr;

private slots:
    void on_re_pushButton_clicked();

    void on_commandLinkButton_clicked();
    void on_tableView_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // IDMANAGE_H
