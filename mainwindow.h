#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include "dboperator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setStyle();
    void Menu();
    void Mainshow(QString Type);
    void manage();
    void Addad();
    void Deletead();
    void Addbook();
    void Deletebook();
    void Changebook();
    void PublisherInfo();
    void ReaderState();
    void cancellation();
    void Updatebook();
    void warning();
    void advise();
    ~MainWindow();

private slots:
    void on_exit_pushButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_borrow_pushButton_clicked();

    void on_search_pushButton_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

    void on_textEdit_2_selectionChanged();

private:
    Ui::MainWindow *ui;
    DBOperator DBO;
    QAction *openAction;
    QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
