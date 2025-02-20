#include "Publisher.h"
#include "ui_Publisher.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#include <QScrollBar>
#include <QStandardItemModel>

#include <QSqlQuery>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

extern QString ID;
bool Si = 0;

Publisher::Publisher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Publisher)
{
    //设置样式
    setStyle();
    DBO.DBOpen();
    show();
}

Publisher::~Publisher()
{
    delete ui;
}

//设置样式
void Publisher::setStyle(){
    ui->setupUi(this);
    setWindowTitle("出版社信息");
    ui->re_pushButton->setStyleSheet(   //正常状态样式
                        "QPushButton{"
                        "border-radius:5px;"//设置圆角半径
                        "background-color:#8293fd;"
                        "color:white;"
                        "font:bold;"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:#4861fb;"//设置按钮背景色
                        "color:#bbc6d3;"//设置按钮字体颜色
                        "}");
    ui->tableView->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                                    );
    ui->tableView->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"                    //设置头样式
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
}

//显示
//出版社表
void Publisher::show(){
    //设置QSqlTableModel
    table = new QSqlTableModel(this,DBO.dbcon);
    table->setTable("PublisherInfo");
    table->select();
    table->setEditStrategy(QSqlTableModel::OnManualSubmit); // 表格数据更新数据库，要手工提交
    table->setHeaderData(table->fieldIndex("PublisherID"),Qt::Horizontal,"出版社号");
    table->setHeaderData(table->fieldIndex("PublisherName"),Qt::Horizontal,"出版社名称");
    table->setHeaderData(table->fieldIndex("ContactPerson"),Qt::Horizontal,"所有人");
    table->setHeaderData(table->fieldIndex("ContactPhone"),Qt::Horizontal,"所有人电话");
    table->setHeaderData(table->fieldIndex("Fax"),Qt::Horizontal,"传真");
    table->setHeaderData(table->fieldIndex("Province"),Qt::Horizontal,"省");
    table->setHeaderData(table->fieldIndex("City"),Qt::Horizontal,"市");
    table->setHeaderData(table->fieldIndex("Region"),Qt::Horizontal,"区");
    table->setHeaderData(table->fieldIndex("SpecificAddress"),Qt::Horizontal,"具体地址");
    //设置tablevie组件
    ui->tableView->setModel(table);                            //将以前设置的任何模型替换为model(标准的条目模型), model设置的内容都将显示在tableview上
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(8,QHeaderView::ResizeToContents);    //根据列内容来定列宽
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
}


//编辑
void Publisher::on_re_pushButton_clicked()
{
    //编辑
    if(!Si){
        QMessageBox::information(this, "调整模式","成功切换为调整模式     ");
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //设置可手动编辑
        ui->re_pushButton->setText("完成");
        Si = 1;
    }

    //完成
    else {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否保存");
        if(result == QMessageBox::Yes)
        {   table->submitAll();
            show();
            //恢复
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
            ui->re_pushButton->setText("编辑");
            Si = 0;
        }

        else{
            QMessageBox::warning(this, "警告", "保存失败!");
            //恢复
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
            ui->re_pushButton->setText("编辑");
            Si = 0;
        }
    }

}


void Publisher::on_commandLinkButton_clicked()
{
    close();
}
