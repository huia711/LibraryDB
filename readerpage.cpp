#include "readerpage.h"
#include "qdatetime.h"
#include "ui_readerpage.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QScrollBar>
#include <QStandardItemModel>

#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

extern QString ID;
extern QString Password;

bool Edit = 0;

readerpage::readerpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readerpage)
{
    //设置样式
    setStyle();
    DBO.DBOpen();
    show();
}

readerpage::~readerpage()
{
    delete ui;
}

//设置样式
void readerpage::setStyle(){
    ui->setupUi(this);
    setWindowTitle("用户"+ID);
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
    ui->edit_pushButton->setStyleSheet(   //正常状态样式
                        "QPushButton{"
                        "border-radius:5px;"//设置圆角半径
                        "background-color:#4861fb;;"
                        "color:white;"
                        "font:bold;"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:#8293fd;"//设置按钮背景色
                        "color:#5282bc;"//设置按钮字体颜色
                        "}");
    ui->can_pushButton->setStyleSheet(   //正常状态样式
                        "QPushButton{"
                        "border-radius:5px;"//设置圆角半径
                        "background-color:#8293fd;;"
                        "color:white;"
                        "font:bold;"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:#4861fb;"//设置按钮背景色
                        "color:#5282bc;"//设置按钮字体颜色
                        "}");
    ui->borrow_pushButton->setStyleSheet(   //正常状态样式
                        "QPushButton{"
                        "border-radius:5px;"//设置圆角半径
                        "background-color:#8293fd;;"
                        "color:white;"
                        "font:bold;"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:#4861fb;"//设置按钮背景色
                        "color:#5282bc;"//设置按钮字体颜色
                        "}");
    ui->tableView->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                                    );
    ui->name_lineEdit->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                                   );
    ui->id_lineEdit->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                                    );
    ui->pass_lineEdit->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                                    );
    ui->phone_lineEdit->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                                    );
    ui->lineEdit->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                                    );

    //设置时间显示样式
    ui->lcdNumber->setDigitCount(2);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setStyleSheet("border: white; color: red;");
    ui->lcdNumber_2->setDigitCount(2);
    ui->lcdNumber_2->setMode(QLCDNumber::Dec);
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_2->setStyleSheet("border: white; color: red;");
    ui->lcdNumber_4->setDigitCount(2);
    ui->lcdNumber_4->setMode(QLCDNumber::Dec);
    ui->lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_4->setStyleSheet("border: white; color: red;");

    //设置滑块
    ui->tableView->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView->horizontalHeader()->setMinimumHeight(25);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置滑块2
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView_2->setStyleSheet("border:0px");                //设置隐藏网格线
    ui->tableView_2->horizontalHeader()->setMinimumHeight(25);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置滑块3
    ui->tableView_3->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView_3->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView_3->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
    //设置滑块4
    ui->tableView_4->verticalHeader()->setVisible(false);        //不要行标题
    ui->tableView_4->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView_4->setStyleSheet("border:0px");                //设置隐藏网格线
    ui->tableView_4->horizontalHeader()->setMinimumHeight(25);   //设置标题高度
    ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑
    ui->tableView_4->setSelectionMode(QAbstractItemView::NoSelection);    //设置不可选中
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //定义下拉框
    QStringList list;
    list<<"男"<<"女"<<"保密";
    ui->comboBox->addItems(list);

    //信誉条
    Color_progressBar();
}

//显示
void readerpage::show(){
    //访问数据库
    QString str = "SELECT ReaderName,ReaderPhone,ReaderSex,ReaderCategoryName,BorrowNum,TotalBorrowNum,ViolationNum,RegistrationDate FROM ReaderInfo,ReaderCategory WHERE ReaderInfo.ReaderCategoryID=ReaderCategory.ReaderCategoryID AND ReaderID = "+ID+"";
    QSqlQuery qs = DBO.DBGetData(str);
    qs.next();

    QString Name = qs.value("ReaderName").toString();
    QString Phone = qs.value("ReaderPhone").toString();
    int Sex = qs.value("ReaderSex").toInt();
    QString Category = qs.value("ReaderCategoryName").toString();
    QDate RegistrationDate = qs.value("RegistrationDate").toDate();
    int BorrowNum = qs.value("BorrowNum").toInt();
    int TotalBorrowNum = qs.value("TotalBorrowNum").toInt();
    int ViolationNum = qs.value("ViolationNum").toInt();

    //显示
    ui->id_lineEdit->setText(ID);
    ui->pass_lineEdit->setText(Password);
    ui->name_lineEdit->setText(Name);
    ui->phone_lineEdit->setText(Phone);
    ui->comboBox->setCurrentIndex(Sex);

    ui->textBrowser->setText(Category);
    ui->dateEdit->setDate(RegistrationDate);
    ui->lcdNumber->display(BorrowNum);
    ui->lcdNumber_2->display(TotalBorrowNum);
    ui->lcdNumber_4->display(ViolationNum);

    ui->name_lineEdit->setReadOnly(1);  //只读
    ui->pass_lineEdit->setReadOnly(1);
    ui->id_lineEdit->setReadOnly(1);
    ui->comboBox->setDisabled(1);
    ui->phone_lineEdit->setReadOnly(1);

    ui->textBrowser->setReadOnly(1);
    ui->dateEdit->setReadOnly(1);

    //信誉分
    ui->progressBar->setValue(100 - (10 * ViolationNum));
    Color_progressBar(); //更新颜色


    //借书表
    QString sqlstr;
    sqlstr = "SELECT br.BookID as BookID,Title,AdminName,BorrowDate,DueDate,br.BorrowingID,b.ISBN as ISBN FROM Borrowing br,LibraryItem l,BookInfo b,AdministratorInfo a WHERE br.BookID=l.BookID AND l.ISBN=b.ISBN AND br.AdminID=a.AdminID AND br.ReaderID="+ID+"";
    table = new QSqlQueryModel(this);
    table->setQuery(sqlstr, DBO.dbcon);
    table->setHeaderData(0, Qt::Horizontal, "馆藏编号");
    table->setHeaderData(1, Qt::Horizontal, "书名");
    table->setHeaderData(2, Qt::Horizontal, "业务办理人员");
    table->setHeaderData(3, Qt::Horizontal, "借出日期");
    table->setHeaderData(4, Qt::Horizontal, "归还日期");
    ui->tableView->setModel(table);                     //设置tablevie组件
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);

    //借书状态框
    overdue();


    //预约表
    QString sqlstr2;
    sqlstr2 = "SELECT br.BookID as BookID,Title,BorrowDate,DueDate,b.ISBN as ISBN FROM Borrowing br,LibraryItem l,BookInfo b WHERE br.BookID=l.BookID AND l.ISBN=b.ISBN AND RenewalNum=-1 AND br.ReaderID="+ID+"";
    table2 = new QSqlQueryModel(this);
    table2->setQuery(sqlstr2, DBO.dbcon);
    table2->setHeaderData(0, Qt::Horizontal, "馆藏编号");
    table2->setHeaderData(1, Qt::Horizontal, "书名");
    table2->setHeaderData(2, Qt::Horizontal, "预约日期");
    table2->setHeaderData(3, Qt::Horizontal, "到期日期");
    ui->tableView_3->setModel(table2);                     //设置tablevie组件
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    ui->tableView_3->hideColumn(4);

    //预约状态框
    ifborrow();
}

//是否逾期框
void readerpage::overdue(){
    m = new QStandardItemModel(this);
    m->setColumnCount(1);
    m->setHeaderData(0, Qt::Horizontal, tr("状态"));
    ui->tableView_2->setModel(m);

    QString checkstr = "CALL CheckOverdue()";
    QSqlQuery check = DBO.DBGetData(checkstr);
    check.next();

    int row = 0;
    //数据库查询
    QString sqlstr;
    sqlstr = "SELECT FineID,RenewalNum FROM Borrowing LEFT JOIN OverdueFine ON Borrowing.BorrowingID = OverdueFine.FineID WHERE Borrowing.ReaderID = '"+ID+"' ";
    QSqlQuery qs = DBO.DBGetData(sqlstr);

    while(qs.next()){
        if(qs.value("FineID").toInt() != 0){
            QList<QStandardItem *> itemrow{new QStandardItem("已逾期")};
            m->appendRow(itemrow);
            m->item(row, 0)->setBackground(QColor(Qt::red));
        }
        else if(qs.value("RenewalNum").toInt() == -1){
            QList<QStandardItem *> itemrow{new QStandardItem("预约中")};
            m->appendRow(itemrow);
            m->item(row, 0)->setBackground(QColor(Qt::white));
        }
        else if(qs.value("FineID").toInt() == 0){
            QList<QStandardItem *> itemrow{new QStandardItem("未逾期")};
            m->appendRow(itemrow);
            m->item(row, 0)->setBackground(QColor(Qt::green));
        }
        row++;
    }
}

//预约状态框
void readerpage::ifborrow(){
    m = new QStandardItemModel(this);
    m->setColumnCount(1);
    m->setHeaderData(0, Qt::Horizontal, tr("状态"));
    ui->tableView_4->setModel(m);

    QString checkstr = "CALL CheckOverdue()";
    QSqlQuery check = DBO.DBGetData(checkstr);
    check.next();

    int row = 0;
    //数据库查询
    QString sqlstr;
    sqlstr = "SELECT CurrentStock FROM Borrowing,LibraryItem,BookInfo WHERE Borrowing.BookID=LibraryItem.BookID AND LibraryItem.ISBN=BookInfo.ISBN AND Borrowing.ReaderID = '"+ID+"' AND RenewalNum=-1";
    QSqlQuery qs = DBO.DBGetData(sqlstr);

    while(qs.next()){
        if(qs.value("CurrentStock").toInt() > 0){
            QList<QStandardItem *> itemrow{new QStandardItem("可租借")};
            m->appendRow(itemrow);
            m->item(row, 0)->setBackground(QColor(Qt::green));
        }
        else{
            QList<QStandardItem *> itemrow{new QStandardItem("无库存")};
            m->appendRow(itemrow);
            m->item(row, 0)->setBackground(QColor(Qt::white));
        }
        row++;
    }
}


//编辑-完成
void readerpage::on_edit_pushButton_clicked()
{
    if(Edit) {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否保存编辑");
        if(result == QMessageBox::Yes)
        {
            QString name = ui->name_lineEdit->text().trimmed();
            QString phone = ui->phone_lineEdit->text().trimmed();
            QString id = ui->id_lineEdit->text().trimmed();
            QString password = ui->pass_lineEdit->text().trimmed();
            QString Confirm = ui->lineEdit->text().trimmed();

            //判断是否已注册
            QString sql = "SELECT ReaderID FROM ReaderInfo";
            QSqlQuery qq = DBO.DBGetData(sql);
            while(qq.next()){
                if(id == qq.value("ReaderID").toString() && id != ID){
                    QMessageBox::warning(this, "警告", "用户名已使用");
                    break;
                }
            }
            //判断密码
            if(password == "") {
                QMessageBox::warning(this, "警告", "密码不能为空");
            }
            if(Confirm != password) {
                QMessageBox::warning(this, "警告", "密码与确认密码不相同");
            }

            //数据库更改
            QString sqlstr = "UPDATE ReaderInfo SET ReaderID="+id+",ReaderPWD='"+password+"',ReaderName='"+name+"',ReaderPhone="+phone+" WHERE ReaderID='"+ID+"'";
            qDebug() << sqlstr;
            QSqlQuery qs = DBO.DBGetData(sqlstr);
            if(qs.numRowsAffected() >=1 ){
                //全局变量更新
                ID = id;
                Password = password;
                QMessageBox::information(this, "成功","修改成功");
            }
            else{
                QMessageBox::warning(this, "警告", "修改失败");
            }

            //更新显示
            show();
            Edit = 0;
            ui->unlock_pushButton->setEnabled(1);
            ui->re_pushButton->setEnabled(1);
        }
    }
}

//编辑-开始
void readerpage::on_unlock_pushButton_clicked()
{
    if(!Edit){
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否编辑信息");
        if(result == QMessageBox::Yes)
        {
            ui->unlock_pushButton->setEnabled(0);
            ui->re_pushButton->setEnabled(0);

            ui->name_lineEdit->setReadOnly(0);
            ui->pass_lineEdit->setReadOnly(0);
            ui->id_lineEdit->setReadOnly(0);
            ui->comboBox->setDisabled(0);
            ui->phone_lineEdit->setReadOnly(0);

            Edit = 1;
        }
    }
}

//还书
void readerpage::on_re_pushButton_clicked()
{
    //获取该行记录
    int row = ui->tableView->currentIndex().row();
    QSqlRecord record = table->record(row);
    if(row >= 0)
    {
        //已逾期，需要交罚款
        //获取当前日期
        QDate currentDate = QDate::currentDate();
        if( currentDate > record.value("DueDate").toDate() ){
             QMessageBox::warning(this, "警告", "该图书已逾期，请联系管理员归还并罚款!");
        }

        //未逾期
        else{
            QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否归还"+record.value("Title").toString());
            if(result == QMessageBox::Yes)
            {
                QString sql = "INSERT INTO ReturnBook values(null, "+ID+","+record.value(0).toString()+",1,CURDATE(),IsOverdue("+record.value(0).toString()+"),0)";
                qDebug() << sql;
                QSqlQuery qq = DBO.DBGetData(sql);
                if(qq.numRowsAffected() >=1 ){
                    QMessageBox::information(this, "成功","归还成功");
                }
                else{
                    QMessageBox::warning(this, "警告", "归还失败");
                }

                //更新
                show();
                overdue();
            }
        }
    }

    else
        QMessageBox::warning(this, "警告", "请选中需要归还的书籍!");
}


//信誉分颜色
void readerpage::Color_progressBar(){
    if(ui->progressBar->value() < 80) {
        ui->progressBar->setStyleSheet(
                    "QProgressBar::chunk {"
                    "background: red"
                    "}");
    }
}


//取消预约
void readerpage::on_can_pushButton_clicked()
{
    int row = ui->tableView_3->currentIndex().row();
    if(row >= 0)
    {
        QSqlRecord record = table2->record(row);
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否取消预约"+record.value("Title").toString());
        if(result == QMessageBox::Yes)
        {
            //数据库访问
            QString s = "DELETE FROM Borrowing WHERE ReaderID='"+ID+"' AND BookID="+record.value("BookID").toString()+"";
            QSqlQuery q = DBO.DBGetData(s);

            show();
        }
    }

    else
        QMessageBox::warning(this, "警告", "请选中需要归还的书籍!");
}

//借
void readerpage::on_borrow_pushButton_clicked()
{
    int row = ui->tableView_3->currentIndex().row();
    QSqlRecord record = table2->record(row);

    QString ISBN = record.value("ISBN").toString();
    QString BookID = "";
    QString OrderID = "";

    QString sqlstr = "SELECT ViolationNum,CurrentStock,BorrowNum,MaxBorrowNum FROM BookInfo,ReaderInfo,ReaderCategory WHERE ReaderID='"+ID+"' AND ReaderInfo.ReaderCategoryID=ReaderCategory.ReaderCategoryID AND ISBN='"+ISBN+"' ";  //SQL数据库语言
    qDebug() << sqlstr;
    QSqlQuery qq = DBO.DBGetData(sqlstr);
    qq.first();

    //判断是否还有库存，且用户借书数量是否达到上限，违规次数是否达到上限
    if(qq.value("CurrentStock").toInt() > 0 && qq.value("BorrowNum").toInt() <= qq.value("MaxBorrowNum").toInt() && qq.value("ViolationNum").toInt() <= 3){
        //数据库访问
        QString s = "SELECT LibraryItem.BookID as BookID,RenewalNum,ReaderID FROM LibraryItem LEFT JOIN Borrowing ON LibraryItem.BookID=Borrowing.BookID WHERE LibraryItem.ISBN='"+ISBN+"'";
        qDebug() << s;
        QSqlQuery q = DBO.DBGetData(s);
        int check = 1;

        while(q.next()){
            //记录可借馆藏
            if(q.value("RenewalNum").toInt() == 0 || q.value("RenewalNum").toInt()==-1){
                BookID = q.value("BookID").toString();
            }

            //如果已经借过
            if(q.value("ReaderID").toString() == ID && q.value("RenewalNum").toInt()!=-1){
                QMessageBox::warning(this, "警告", "已经借过此书");
                check = 0;
                break;
            }

            //记录预约馆藏
            if(q.value("ReaderID").toString() == ID && q.value("RenewalNum").toInt()==-1){
                OrderID = q.value("BookID").toString();
            }
        }

        if(check){
            //数据库访问
            QString sql = "UPDATE Borrowing SET BookID="+BookID+", BorrowDate=CURDATE(), DueDate=DueDate("+ID+"), RenewalNum=1 WHERE ReaderID="+ID+" AND RenewalNum=-1 AND BookID="+OrderID+"";
            qDebug() << sql;
            QSqlQuery qs = DBO.DBGetData(sql);
            if(qs.numRowsAffected() >=1 ){
                QMessageBox::information(this, "成功","预约租借成功");
            }
            else{
                QMessageBox::warning(this, "警告", "预约租借失败");
            }
        }
    }

    //无库存
    else if(qq.value("CurrentStock").toInt() <= 0){
        QMessageBox::warning(this, "警告", "未有库存");
    }

    //达到借书上限
    else if(qq.value("BorrowNum").toInt() > qq.value("MaxBorrowNum").toInt()){
        QMessageBox::warning(this, "警告", "您已达到借书上限");
    }

    //达到违规上限
    else if(qq.value("ViolationNum").toInt() > 3) {
        QMessageBox::warning(this, "警告", "信誉分低于80，无法借书!请联系管理员");
    }

    show();
}


void readerpage::on_commandLinkButton_clicked()
{
    close();
}
