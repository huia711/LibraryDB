#include "idmanage.h"
#include "ui_idmanage.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#include <QScrollBar>
#include <QStandardItemModel>

#include <QSqlQuery>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

extern QString ID;
static QString i = " ";
extern QString Password;

idmanage::idmanage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::idmanage)
{
    //设置样式
    setStyle();
    DBO.DBOpen();
    showmodel();
    show(" ");
}

idmanage::~idmanage()
{
    delete ui;
}

//设置样式
void idmanage::setStyle(){
    ui->setupUi(this);
    setWindowTitle("账号管理");
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
    ui->pushButton->setStyleSheet(   //正常状态样式
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
    ui->pushButton_2->setStyleSheet(   //正常状态样式
                        "QPushButton{"
                        "border-radius:5px;"//设置圆角半径
                        "background-color:#5f9ae6;"
                        "color:white;"
                        "font:bold;"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:#5282bc;"//设置按钮背景色
                        "color:#bbc6d3;"//设置按钮字体颜色
                        "}");
    //设置滑块
    ui->tableView->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"                    //设置头样式
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置滑块2
    ui->tableView_2->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section {"                    //设置头样式
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView_2->setStyleSheet("border:0px");                //设置隐藏网格线
    ui->tableView_2->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
    ui->tableView_2->setSelectionMode(QAbstractItemView::NoSelection);    //设置不可选中
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    //设置滑块3
    ui->tableView_3->verticalHeader()->setVisible(false);
    ui->tableView_3->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView_3->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置滑块4
    ui->tableView_4->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView_4->horizontalHeader()->setStyleSheet("QHeaderView::section {"                    //设置头样式
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView_4->setStyleSheet("border:0px");                //设置隐藏网格线
    ui->tableView_4->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
    ui->tableView_4->setSelectionMode(QAbstractItemView::NoSelection);    //设置不可选中
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


//显示
//账号表
void idmanage::showmodel(){
    QString sqlstr = "SELECT ReaderID,ReaderCategoryName,ReaderName,ReaderSex,ReaderPhone,BorrowNum,TotalBorrowNum,ViolationNum,IsSuspended FROM ReaderInfo,ReaderCategory WHERE ReaderInfo.ReaderCategoryID=ReaderCategory.ReaderCategoryID";
    //建立一个model
    model=new QSqlQueryModel(this);
    model->setQuery(sqlstr, DBO.dbcon);
    model->setHeaderData(0, Qt::Horizontal, "账号");
    model->setHeaderData(1, Qt::Horizontal, "读者类别");
    model->setHeaderData(2, Qt::Horizontal, "读者名");
    model->setHeaderData(3, Qt::Horizontal, "性别");
    model->setHeaderData(4, Qt::Horizontal, "手机号码");
    model->setHeaderData(5, Qt::Horizontal, "已借书数");
    model->setHeaderData(6, Qt::Horizontal, "总借书数");
    model->setHeaderData(7, Qt::Horizontal, "违规次数");
    ui->tableView_3->setModel(model);                     //设置tablevie组件
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    ui->tableView_3->hideColumn(8);

    //是否重置框
    remake();
}

//更新id
void idmanage::on_tableView_3_clicked()
{
    int r = ui->tableView_3->currentIndex().row();
    QSqlRecord record = model->record(r);
    i = record.value(0).toString();
    show(i);
}

//是否重置框
void idmanage::remake(){
    modell = new QStandardItemModel(this);
    modell->setColumnCount(1);
    modell->setHeaderData(0, Qt::Horizontal, tr("是否挂失"));
    ui->tableView_4->setModel(modell);

    int row = 0;
    //数据库查询
    QString sqlstr;
    sqlstr = "SELECT r2.ReaderID AS ReaderID FROM ReaderInfo r1 LEFT JOIN ReaderInfo r2 ON r1.ReaderID = r2.ReaderID AND r2.IsSuspended = 1";
    QSqlQuery qs = DBO.DBGetData(sqlstr);
    while(qs.next()){
        if(qs.value("ReaderID").toString().toInt() != 0){
            QList<QStandardItem *> itemrow{new QStandardItem("请求重置")};
            modell->appendRow(itemrow);
            modell->item(row, 0)->setBackground(QColor(Qt::green));
        }
        else{
            QList<QStandardItem *> itemrow{new QStandardItem("未请求")};
            modell->appendRow(itemrow);
            modell->item(row, 0)->setBackground(QColor(Qt::white));
        }
        row++;
    }
}


//借书表
void idmanage::show(QString id){
    QString sqlstr;
    if(id == " ") sqlstr = "SELECT ReaderName,br.BookID,Title,AdminName,BorrowDate,DueDate,br.BorrowingID,br.ReaderID,b.Price FROM Borrowing br,ReaderInfo r,LibraryItem l,BookInfo b,AdministratorInfo a WHERE br.ReaderID=r.ReaderID AND br.BookID=l.BookID AND l.ISBN=b.ISBN AND br.AdminID=a.AdminID";
    else sqlstr = "SELECT ReaderName,br.BookID,Title,AdminName,BorrowDate,DueDate,BorrowingID,br.ReaderID,b.Price FROM Borrowing br,ReaderInfo r,LibraryItem l,BookInfo b,AdministratorInfo a WHERE br.ReaderID=r.ReaderID AND br.BookID=l.BookID AND l.ISBN=b.ISBN AND br.AdminID=a.AdminID AND br.ReaderID='"+id+"'";
    qDebug() << sqlstr;
    //建立一个model
    table=new QSqlQueryModel(this);
    table->setQuery(sqlstr, DBO.dbcon);
    table->setHeaderData(0, Qt::Horizontal, "读者名");
    table->setHeaderData(1, Qt::Horizontal, "馆藏编号");
    table->setHeaderData(2, Qt::Horizontal, "书名");
    table->setHeaderData(3, Qt::Horizontal, "业务办理人员");
    table->setHeaderData(4, Qt::Horizontal, "借出日期");
    table->setHeaderData(5, Qt::Horizontal, "归还日期");
    ui->tableView->setModel(table);                     //设置tablevie组件
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);

    //借书状态框
    overdue();
}

//借书状态框
void idmanage::overdue(){
    modelr = new QStandardItemModel(this);
    modelr->setColumnCount(1);
    modelr->setHeaderData(0, Qt::Horizontal, tr("状态"));
    ui->tableView_2->setModel(modelr);

    QString checkstr = "CALL CheckOverdue()";
    QSqlQuery check = DBO.DBGetData(checkstr);
    check.next();

    int row = 0;
    //数据库查询
    QString sqlstr;
    if(i == " ") sqlstr = "SELECT FineID,RenewalNum FROM Borrowing LEFT JOIN OverdueFine ON Borrowing.BorrowingID = OverdueFine.FineID";
    else sqlstr = "SELECT FineID,RenewalNum FROM Borrowing LEFT JOIN OverdueFine ON Borrowing.BorrowingID = OverdueFine.FineID WHERE Borrowing.ReaderID = '"+i+"' ";
    QSqlQuery qs = DBO.DBGetData(sqlstr);

    while(qs.next()){
        if(qs.value("FineID").toInt() != 0){
            QList<QStandardItem *> itemrow{new QStandardItem("已逾期")};
            modelr->appendRow(itemrow);
            modelr->item(row, 0)->setBackground(QColor(Qt::red));
        }
        else if(qs.value("RenewalNum").toInt() == -1){
            QList<QStandardItem *> itemrow{new QStandardItem("预约中")};
            modelr->appendRow(itemrow);
            modelr->item(row, 0)->setBackground(QColor(Qt::white));
        }
        else if(qs.value("FineID").toInt() == 0){
            QList<QStandardItem *> itemrow{new QStandardItem("未逾期")};
            modelr->appendRow(itemrow);
            modelr->item(row, 0)->setBackground(QColor(Qt::green));
        }
        row++;
    }
}


//还书
void idmanage::on_re_pushButton_clicked()
{
    //获取该行记录
    int row = ui->tableView->currentIndex().row();
    QSqlRecord record = table->record(row);
    if(row >= 0)
    {
        //确认
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否归还"+record.value(0).toString()+"的"+record.value(2).toString());
        if(result == QMessageBox::Yes)
        {
            float Fine = 0;

            //1.是否损坏
            QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "图书是否损坏");
            //1.损坏
            if(result == QMessageBox::Yes)
            {
                QString sql = "INSERT INTO ReturnBook values(null, "+record.value(7).toString()+", "+record.value(1).toString()+", 1, CURDATE(), IsOverdue("+record.value(1).toString()+"), 1)";
                qDebug() << sql;
                QSqlQuery qq = DBO.DBGetData(sql);
                if(qq.numRowsAffected() >=1 ){
                    //是否逾期
                    QString sqlstr = "SELECT FineAmount FROM ReturnBook,OverdueFine WHERE ReturnBook.ReturnID = OverdueFine.ReturnID AND BookID="+record.value(1).toString()+"";
                    QSqlQuery qs = DBO.DBGetData(sqlstr);
                    //1.1.逾期
                    if(qs.numRowsAffected() >=1 ){
                        qs.first();
                        Fine = qs.value("FineAmount").toFloat() + record.value(8).toFloat();
                        qDebug() << Fine;
                        QMessageBox::information(this, "成功","归还成功,读者需缴纳罚款"+QString::number(Fine, 'f', 2)+"元");
                    }
                    //1.2.未逾期
                    else{
                        Fine = record.value(8).toFloat();
                        qDebug() << Fine;
                        QMessageBox::information(this, "成功","归还成功,读者需缴纳罚款"+QString::number(Fine, 'f', 2)+"元");
                    }
                }
                else{
                    QMessageBox::warning(this, "警告", "归还失败");
                }
            }

            //2.无损坏
            else {
                //数据库访问
                QString sql = "INSERT INTO ReturnBook values(null, "+record.value(7).toString()+", "+record.value(1).toString()+", 1, CURDATE(), IsOverdue("+record.value(1).toString()+"), 0)";

                QSqlQuery qq = DBO.DBGetData(sql);
                if(qq.numRowsAffected() >=1 ){
                    //是否逾期
                    QString sqlstr = "SELECT FineAmount FROM ReturnBook,OverdueFine WHERE ReturnBook.ReturnID = OverdueFine.ReturnID AND BookID="+record.value(1).toString()+"";
                    QSqlQuery qs = DBO.DBGetData(sqlstr);
                    //2.1.逾期
                    if(qs.numRowsAffected() >=1 ){
                        qs.first();
                        Fine = qs.value("FineAmount").toInt();
                        qDebug() << Fine;
                        QMessageBox::information(this, "成功","归还成功,读者需缴纳罚款"+QString::number(Fine, 'f', 2)+"元");
                    }
                    //2.2.未逾期
                    else{
                        QMessageBox::information(this, "成功","归还成功");
                    }
                }
                else{
                    QMessageBox::warning(this, "警告", "归还失败");
                }
            }
            //更新
            showmodel();
            show(i);
            overdue();
        }
    }
    else
        QMessageBox::warning(this, "警告", "请选中需要归还的书籍!");
}



//重置密码
void idmanage::on_pushButton_clicked()
{
    if(i!=" "){
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否重置"+i);
        if(result == QMessageBox::Yes)
        {
            //数据库更改
            QString sqlstr = "UPDATE ReaderInfo SET ReaderPWD = '0000',IsSuspended = 0 WHERE ReaderID='"+i+"'";
            QSqlQuery qs = DBO.DBGetData(sqlstr);
            if(qs.numRowsAffected() >=1 ){
                QMessageBox::information(this, "成功","重置成功");
                showmodel();
                show(" ");
            }
            else{
                QMessageBox::warning(this, "警告", "重置失败");
            }
        }
    }
    else QMessageBox::warning(this, "警告", "请选中需要重置的用户!");
}

//删除账号
void idmanage::on_pushButton_2_clicked()
{
    if(i!=" "){
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否删除"+i);
        if(result == QMessageBox::Yes)
        {
            //数据库更改
            QString sqlstr = "DELETE FROM ReaderInfo WHERE ReaderID = '"+i+"' ";
            QSqlQuery qs = DBO.DBGetData(sqlstr);
            if(qs.numRowsAffected() >=1 ){
                QMessageBox::information(this, "成功","删除成功");
                showmodel();
                show(" ");
            }
            else{
                QMessageBox::warning(this, "警告", "删除失败");
            }
        }
    }
    else QMessageBox::warning(this, "警告", "请选中需要删除的用户!");
}


//返回
void idmanage::on_commandLinkButton_clicked()
{
    close();
}
