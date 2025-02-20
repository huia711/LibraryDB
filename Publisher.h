#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QStandardItemModel>
#include "dboperator.h"

namespace Ui {
class Publisher;
}

class Publisher : public QDialog
{
    Q_OBJECT

public:
    explicit Publisher(QWidget *parent = nullptr);
    void setStyle();
    void show();
    void overdue();
    ~Publisher();

private:
    Ui::Publisher *ui;
    DBOperator DBO;
    QSqlTableModel *table;

private slots:
    void on_re_pushButton_clicked();

    void on_commandLinkButton_clicked();

};

#endif // PUBLISHER_H
