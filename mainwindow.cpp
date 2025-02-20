#include "mainwindow.h"
#include "qdatetime.h"
#include "ui_mainwindow.h"
#include "idmanage.h"
#include "homepage.h"
#include "regist.h"
#include "addbook.h"
#include "Publisher.h"
#include "readerpage.h"

#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <ctime>

#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QScrollBar>

#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QInputDialog>

extern bool IfAd;
extern QString ID;

bool up = 0;
QString ISBN;
QString Title;
QString Author;
QString PublisherName;
QDate PublishDate;
QString Type;
float Price;
int Stock;
int CurrentStock;

bool warn = 0;
int ViolationNum = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //设置样式
    setStyle();
    Menu();
    DBO.DBOpen();
    Mainshow("全部");
    Updatebook();
    warning();
    advise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置样式
void MainWindow:: setStyle(){
    ui->setupUi(this);
    setWindowTitle(tr("图书管理系统"));
    ui->exit_pushButton->setStyleSheet(   //正常状态样式
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
    ui->search_pushButton->setStyleSheet(   //正常状态样式
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
    ui->borrow_pushButton->setStyleSheet(   //正常状态样式
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
    ui->lineEdit->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                            );
    ui->comboBox->setStyleSheet(   //正常状态样式
                         "QComboBox:drop-down{"
                         "width:40px;  "
                         "height:50px; "
                         "border:none;  "
                         "subcontrol-position:right center; "
                         "subcontrol-origin:padding;"
                         "}");
    ui->textEdit->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                           );
    ui->listView->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                           );
    ui->listView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"
                                                     "background:#FFFFFF;"
                                                     "padding-top:20px;"
                                                     "padding-bottom:20px;"
                                                     "padding-left:3px;"
                                                     "padding-right:3px;"
                                                     "border-left:1px solid #d7d7d7;"
                                                     "}"
                                                     "QScrollBar::handle:vertical{"
                                                     "background:#dbdbdb;"
                                                     "border-radius:5px;"
                                                     "min-height:80px;"
                                                     "}"
                                                     "QScrollBar::handle:vertical:hover{"
                                                     "background:#d0d0d0;"
                                                     "}"
                                                     "QScrollBar::sub-line:vertical{"  // 设置上箭头
                                                     "height:0px;width:0px;"
                                                     "}"
                                                     "QScrollBar::add-line:vertical{"
                                                     "height:0px;width:0px;"
                                                     "}");
    ui->tableView->setStyleSheet(   //正常状态样式
                        "border-radius:5px;"//设置圆角半径
                           );
    ui->tableView->verticalHeader()->setVisible(false);                                //不要行标题
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"          //设置头样式
                                                     "background-color:#d4e1e7; "
                                                     "color:#CD2626;"
                                                     "padding-left:1px;"
                                                     "}");
    ui->tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"           //垂直滑块整体
                                                     "background:#FFFFFF;"  //背景色
                                                     "padding-top:20px;"    //上预留位置（放置向上箭头）
                                                     "padding-bottom:20px;" //下预留位置（放置向下箭头）
                                                     "padding-left:3px;"    //左预留位置（美观）
                                                     "padding-right:3px;"   //右预留位置（美观）
                                                     "border-left:1px solid #d7d7d7;"//左分割线
                                                     "}"
                                                     "QScrollBar::handle:vertical{"  //滑块样式
                                                     "background:#dbdbdb;"  //滑块颜色
                                                     "border-radius:5px;"   //边角圆润
                                                     "min-height:80px;"    //滑块最小高度
                                                     "}"
                                                     "QScrollBar::handle:vertical:hover{"//鼠标触及滑块样式
                                                     "background:#d0d0d0;" //滑块颜色
                                                     "}"
                                                     "QScrollBar::sub-line:vertical{"  // 设置上箭头
                                                     "height:0px;width:0px;"
                                                     "border-image:url(:/arrow_top.png);"
                                                     "subcontrol-position:top;"
                                                     "}"
                                                     "QScrollBar::add-line:vertical{"
                                                     "height:0px;width:0px;"
                                                     "}");
    ui->tableView->horizontalHeader()->setMinimumHeight(25); //设置标题高度
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可手动编辑

    //左侧滑动组件
    //QStringList 它提供了快速的基于索引的访问，以及快速插入和删除。将字符串列表作为值参数传递是快速和安全的。append增加元素
    QStringList type;
    type.append("全部");          type.append("B哲学、宗教");      type.append("D政治、法律"); type.append("E军事");       type.append("F经济");
    type.append("H语言");         type.append("I文学");           type.append("J艺术");      type.append("K历史、地理");  type.append("N自然科学总论");
    type.append("O数理科学和化学"); type.append("F天文学、地球科学"); type.append("Q生物科学");   type.append("R医药、卫生");  type.append("S农业科学");
    type.append("T工业技术");      type.append("U交通运输");       type.append("V航空航天");   type.append("X环境科学");    type.append("Z综合性图书");
    //QStringListModel 用于处理字符串列表的数据模型
    QStringListModel *sfListMode = new QStringListModel(type);             //输入字符串
    ui->listView->setModel(sfListMode);                                    //填充到listview
    ui->listView->setSpacing(3);                                           //表示各个控件之间的上下间距
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //设置item内容不可编辑

    //时间组件
    //设置时间显示样式
    ui->time_LCD->setDigitCount(19);
    ui->time_LCD->setMode(QLCDNumber::Dec);
    //显示外观
    ui->time_LCD->setSegmentStyle(QLCDNumber::Flat);
    //样式
    ui->time_LCD->setStyleSheet("border: white; color: red; background-color: rgb(180, 190, 247);");
    //启动定时器
    QTimer *CurrentTime = new QTimer(this);
    CurrentTime->start(0);
    //使用定时器信号槽，尽快更新时间的显示
    connect(CurrentTime,&QTimer::timeout,[=](){
    QDateTime now = QDateTime::currentDateTime();
    QString strTime = now.toString("yyyy-MM-dd hh:mm:ss");
    ui->time_LCD->display(strTime);
    });
}


//菜单栏
void MainWindow::Menu(){
        //下面的menuBar()和statusBar()三个是QMainWindow的函数，用于创建并返回菜单栏和状态栏
        if(IfAd == 1){
            //创造一个Administrator菜单
            QMenu *IDmanage = menuBar()->addMenu(tr("&账号管理"));

            openAction = new QAction(("&管理账号..."), this);
            openAction->setStatusTip(tr("管理账号"));
            connect(openAction, &QAction::triggered, this, &MainWindow::manage);
            IDmanage->addAction(openAction);

            openAction = new QAction(("&添加管理员..."), this);  //创建了openAction对象；使用了QIcon，对应Qt资源文件中的一段路径；第二个参数中，文本值前面有一个&，意味着这将成为一个快捷键
            openAction->setShortcuts(QKeySequence::New);                                      //用于说明这个QAction的快捷键
            openAction->setStatusTip(tr("添加管理员"));                                         //实现了当用户鼠标滑过这个 action 时，会在主窗口下方的状态栏显示相应的提示。
            connect(openAction, &QAction::triggered, this, &MainWindow::Addad);               //用户点击了这个QAction时，会自动触发MainWindow的Add()函数
            IDmanage->addAction(openAction);

            openAction = new QAction(("&注销账号..."), this);
            openAction->setStatusTip(tr("注销账号"));
            connect(openAction, &QAction::triggered, this, &MainWindow::cancellation);
            IDmanage->addAction(openAction);

            QMenu *Bookmanage = menuBar()->addMenu(tr("&图书管理"));

            openAction = new QAction(("&添加图书..."), this);
            openAction->setShortcuts(QKeySequence::Save);
            openAction->setStatusTip(tr("添加图书"));
            connect(openAction, &QAction::triggered, this, &MainWindow::Addbook);
            Bookmanage->addAction(openAction);

            openAction = new QAction(("&出版社信息..."), this);
            openAction->setStatusTip(tr("出版社信息"));
            connect(openAction, &QAction::triggered, this, &MainWindow::PublisherInfo);
            Bookmanage->addAction(openAction);

            openAction = new QAction(("&删除图书..."), this);
            openAction->setShortcuts(QKeySequence::Delete);
            openAction->setStatusTip(tr("删除图书"));
            connect(openAction, &QAction::triggered, this, &MainWindow::Deletebook);
            Bookmanage->addAction(openAction);

            //按钮设置
            ui->borrow_pushButton->setText("调整");
            ui->exit_pushButton->setText("删除");
        }

        else if(IfAd == 0){
            //创造一个Reader菜单
            QMenu *Reader = menuBar()->addMenu(tr("&读者"));
            openAction = new QAction(("&读者信息..."), this);
            openAction->setShortcuts(QKeySequence::Open);
            openAction->setStatusTip(tr("读者信息"));
            connect(openAction, &QAction::triggered, this, &MainWindow::ReaderState);
            Reader->addAction(openAction);

            openAction = new QAction(("&注销账号..."), this);
            openAction->setStatusTip(tr("注销账号"));
            connect(openAction, &QAction::triggered, this, &MainWindow::cancellation);
            Reader->addAction(openAction);

            //按钮设置
            ui->borrow_pushButton->setText("借出");
            ui->exit_pushButton->setText("退出");
        }

        //状态栏
        statusBar() ;
}


//主显示界面
void MainWindow::Mainshow(QString Type){
    //数据库访问
    QString sqlstr;
    if(Type == "全部") sqlstr = "SELECT Title,Type,Author,PublisherName,PublishDate,Price,CurrentStock,TotalStock,ISBN FROM BookInfo,PublisherInfo WHERE BookInfo.PublisherID=PublisherInfo.PublisherID";
    else sqlstr = "SELECT Title,Type,Author,PublisherName,PublishDate,Price,CurrentStock,TotalStock,ISBN FROM BookInfo,PublisherInfo WHERE PublisherInfo.PublisherID=BookInfo.PublisherID AND BookInfo.Type='"+Type+"' ";  //SQL数据库语言

    qDebug() << sqlstr;
    QSqlQuery qq = DBO.DBGetData(sqlstr);
    ui->textEdit->setReadOnly(1);  //只读
    ui->textEdit_2->setReadOnly(1);  //只读

    //计数
    int count = 0;
    while(qq.next()){
        count++;
    }
    if(count != 0)
        ui->textEdit->setText(" "+Type+"\n 共"+QString::number(count)+"种");
    else
        ui->textEdit->setText(" 无此类书籍！");

    //主界面
    //建立一个model
    model=new QSqlQueryModel(this);  //QSqlQueryModel封装了执行SELECT语句从数据库查询数据的功能，但是QSqlQueryModel只能作为只读数据源使用，不可以编辑数据
    model->setQuery(sqlstr, DBO.dbcon);
    model->setHeaderData(0, Qt::Horizontal, "书名");
    model->setHeaderData(1, Qt::Horizontal, "类型");
    model->setHeaderData(2, Qt::Horizontal, "作者");
    model->setHeaderData(3, Qt::Horizontal, "出版社");
    model->setHeaderData(4, Qt::Horizontal, "出版时间");
    model->setHeaderData(5, Qt::Horizontal, "价格");
    model->setHeaderData(6, Qt::Horizontal, "库存数量");
    model->setHeaderData(7, Qt::Horizontal, "总数量");

    //设置tablevie组件
    ui->tableView->setModel(model);                            //将以前设置的任何模型替换为model(标准的条目模型), model设置的内容都将显示在tableview上
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);    //根据列内容来定列宽
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    ui->tableView->hideColumn(8);
}

//左侧滑动组件
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString Type = index.data().toString().trimmed();
    Mainshow(Type);
}


//所有账号管理
void MainWindow::manage(){
    idmanage win(this);//对象
    win.exec();

    Mainshow("全部");
    Updatebook();
}

//管理员——增加
void MainWindow::Addad(){
    regist win(this);//对象
    win.exec();

    Mainshow("全部");
    Updatebook();
}


//图书——增加
void MainWindow::Addbook(){
    up = 0;
    addbook win(this);//对象
    win.exec();

    Mainshow("全部");
    Updatebook();
}

//图书——删除
void MainWindow::Deletebook(){
    //获取行数据
    int r = ui->tableView->currentIndex().row();
    if(r >= 0)
    {
        QSqlRecord record = model->record(r);

        //判断是否有书在借出
        bool check = 1;
        QString s = "SELECT ISBN FROM BookInfo WHERE CurrentStock!=TotalStock";
        QSqlQuery q = DBO.DBGetData(s);
        while(q.next()){
            if(record.value("ISBN").toString() == q.value("ISBN").toString()){
                QMessageBox::warning(this, "警告", "该书已被借出!");
                check = 0;
            }
        }

        //删除操作
        if(check){
            QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否删除"+record.value("Title").toString());
            if(result == QMessageBox::Yes)
            {
                QString str = "DELETE FROM BookInfo WHERE ISBN='"+record.value("ISBN").toString()+"'";
                QSqlQuery qq = DBO.DBGetData(str);
                if(qq.numRowsAffected() >=1 ){
                    QMessageBox::information(this, "成功","删除成功");
                }
                else{
                    QMessageBox::warning(this, "警告", "删除失败");
                }
            }

            Mainshow("全部");
            Updatebook();
        }
    }

    else
        QMessageBox::warning(this, "警告", "请选中需要删除的书籍!");
}

//图书——调整图书信息
void MainWindow::Changebook(){
    //获取行数据
    int r = ui->tableView->currentIndex().row();
    if(r >= 0)
    {
        QSqlRecord record = model->record(r);

        //删除操作
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否修改"+record.value("Title").toString());
        if(result == QMessageBox::Yes)
        {
            up = 1;
            ISBN = record.value("ISBN").toString();
            Title = record.value("Title").toString();
            Author = record.value("Author").toString();
            PublisherName = record.value("PublisherName").toString();
            PublishDate = record.value("PublishDate").toDate();
            Type = record.value("Type").toString();
            Price = record.value("Price").toFloat();
            Stock = record.value("TotalStock").toInt();
            CurrentStock = record.value("CurrentStock").toInt();

            addbook win(this);//对象
            win.exec();

            Mainshow("全部");
            Updatebook();
        }
    }

    else
        QMessageBox::warning(this, "警告", "请选中需要修改的书籍!");
}

//图书——借阅情况
void MainWindow::PublisherInfo(){
    Publisher win(this);//对象
    win.exec();

    Mainshow("全部");
    Updatebook();
}


//读者信息
void MainWindow::ReaderState(){
    readerpage win(this);//对象
    win.exec();

    Mainshow("全部");
    Updatebook();
}


//注销
void MainWindow::cancellation(){
    QString sqlstr;
    QMessageBox::StandardButton result;
    //管理员
    if (IfAd == 1) {
        sqlstr = "DELETE FROM AdministratorInfo WHERE AdminID = '"+ID+"' ";
        result = QMessageBox::question(this, "确认", "是否注销管理员账号"+ID);
    }
    //读者
    if (IfAd == 0) {
        sqlstr = "DELETE FROM ReaderInfo WHERE ReaderID = '"+ID+"' ";
        result = QMessageBox::question(this, "确认", "是否注销读者帐号"+ID);
    }

    if(result == QMessageBox::Yes)
    {
        QSqlQuery qq = DBO.DBGetData(sqlstr);
        close();
        homepage win(this);//对象
        win.exec();
    }

}


//调整or借书button
void MainWindow::on_borrow_pushButton_clicked()
{
    //调整
    if(IfAd == 1){
        //调整图书信息函数
        Changebook();
    }

    //借书
    else if(IfAd == 0){
        QString ISBN = "";
        QString Title = "";
        QString BookID = "";
        QString OrderID = "";

        //数据库访问
        int row = ui->tableView->currentIndex().row();
        QSqlRecord record = model->record(row);
        if(row >= 0)
        {
            Title = record.value(0).toString();
            ISBN = record.value(8).toString();

            QString sqlstr = "SELECT ViolationNum,CurrentStock,BorrowNum,MaxBorrowNum FROM BookInfo,ReaderInfo,ReaderCategory WHERE ReaderID='"+ID+"' AND ReaderInfo.ReaderCategoryID=ReaderCategory.ReaderCategoryID AND Title='"+Title+"' ";  //SQL数据库语言
            QSqlQuery qq = DBO.DBGetData(sqlstr);
            qq.first();

            //判断是否还有库存，且用户借书数量是否达到上限，违规次数是否达到上限
            if(qq.value("CurrentStock").toInt() > 0 && qq.value("BorrowNum").toInt() <= qq.value("MaxBorrowNum").toInt() && qq.value("ViolationNum").toInt() <= 3){
                int check = 1;
                int num = 0;

                //数据库访问
                QString s = "SELECT LibraryItem.BookID BookID,RenewalNum,ReaderID FROM LibraryItem LEFT JOIN Borrowing ON LibraryItem.BookID=Borrowing.BookID WHERE LibraryItem.ISBN='"+ISBN+"'";
                QSqlQuery q = DBO.DBGetData(s);
                while(q.next()){
                    //判断预约了多少本
                    if(q.value("RenewalNum").toInt() == -1){
                        num++;
                    }

                    //2.已经预约过
                    if(q.value("ReaderID").toString() == ID && q.value("RenewalNum").toInt() == -1){
                        OrderID = q.value("LibraryItem.BookID").toString();
                        check = 2;
                        break;
                    }

                    //记录可借馆藏
                    if(q.value("RenewalNum").toInt() == 0){
                        BookID = q.value("BookID").toString();
                    }

                    //如果已经借过
                    if(q.value("ReaderID").toString() == ID){
                        QMessageBox::warning(this, "警告", "已经借过此书");
                        check = 0;
                        break;
                    }
                }

                //0.如果都被预约了
                if(num >= qq.value("CurrentStock").toInt()){
                    QMessageBox::warning(this, "警告", "该书已被预约,请等待更多图书归还");
                    check = 0;
                }

                //1.有库存且未预约完，2.之前预约过
                if(check){ 
                    //1.有库存且未预约完
                    if(check==1){
                        //数据库访问
                        QString sql = "INSERT INTO Borrowing values(null, "+ID+", '"+BookID+"', 1, CURDATE(), DueDate("+ID+"), 1)";
                        qDebug() << sql;
                        QSqlQuery qq = DBO.DBGetData(sql);
                        if(qq.numRowsAffected() >=1 ){
                            QMessageBox::information(this, "成功","租借成功");
                        }
                        else{
                            QMessageBox::warning(this, "警告", "租借失败");
                        }
                    }

                    //2.之前预约过
                    if(check==2){
                        //数据库访问
                        QString sql = "UPDATE Borrowing SET BookID="+BookID+", BorrowDate=CURDATE(), DueDate=DueDate("+ID+"), RenewalNum=1 WHERE BookID="+OrderID+"";
                        QSqlQuery qq = DBO.DBGetData(sql);
                        if(qq.numRowsAffected() >=1 ){
                            QMessageBox::information(this, "成功","预约租借成功");
                        }
                        else{
                            QMessageBox::warning(this, "警告", "预约租借失败");
                        }
                    }
                }
            }

            //3.无库存，可预约
            else if(record.value("CurrentStock").toInt() <= 0) {
                int check = 1;

                //3.1.判断之前是否预约过
                QString s = "SELECT DueDate FROM Borrowing,LibraryItem WHERE Borrowing.BookID=LibraryItem.BookID AND ISBN='"+ISBN+"' AND RenewalNum=-1 AND ReaderID="+ID+"";
                QSqlQuery q = DBO.DBGetData(s);
                while(q.next()){
                    //已经预约过
                    QMessageBox::warning(this, "警告", "已经预约过该书,预约到期时间为"+q.value("DueDate").toString()+"");
                    check = 0;
                    break;
                }

                //3.2.未预约过，询问是否预约
                if(check){
                    QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "已无剩余图书，是否预约"+Title);
                    if(result == QMessageBox::Yes)
                    {
                        //找到可用BookID
                        QString s = "SELECT BookID FROM LibraryItem WHERE ISBN='"+ISBN+"' AND BookID NOT IN (SELECT BookID FROM Borrowing WHERE ISBN='"+ISBN+"' AND RenewalNum=-1)";
                        QSqlQuery q = DBO.DBGetData(s);
                        q.next();
                        BookID = q.value("BookID").toString();
                        //插入
                        QString sql = "INSERT INTO Borrowing values(null, "+ID+", '"+BookID+"', 1, CURDATE(), ADDDATE(CURDATE(),15), -1)";
                        qDebug() << sql;
                        QSqlQuery qq = DBO.DBGetData(sql);
                        if(qq.numRowsAffected() >=1 ){
                            QMessageBox::information(this, "成功","预约成功");
                        }
                        else{
                            QMessageBox::warning(this, "警告", "预约失败");
                        }
                    }
                }
            }

            //达到借书上限
            else if(qq.value("BorrowNum").toInt() > qq.value("MaxBorrowNum").toInt()){
                QMessageBox::warning(this, "警告", "您已达到借书上限");
            }

            //达到违规上限
            else if(qq.value("ViolationNum").toInt() > 3) {
                QMessageBox::warning(this, "警告", "信誉分低于80，无法借书!请向管理员提交罚款!");
            }
        }


        else
            QMessageBox::warning(this, "警告", "请选中需要租借的书籍!");
    }

    Mainshow("全部");
    Updatebook();
}

//删除or退出button
void MainWindow::on_exit_pushButton_clicked()
{
    if(IfAd){
        //删除图书函数
        Deletebook();
    }

    else if(IfAd == 0){
        close();
        homepage win(this);//对象
        win.exec();
    }
}


//模糊搜索
void MainWindow::on_search_pushButton_clicked()
{
    QString t = ui->comboBox->currentText();
    QString search = ui->lineEdit->text().trimmed();
    QString strSearch;

    if(t == "书名")
    {
        strSearch = "SELECT Title,Type,Author,PublisherName,PublishDate,Price,CurrentStock,TotalStock,ISBN FROM BookInfo,PublisherInfo WHERE BookInfo.PublisherID=PublisherInfo.PublisherID AND Title like '%"+search+"%'";
        model->setQuery(strSearch, DBO.dbcon);
    }

    else if(t == "作者")
    {
        strSearch = "SELECT Title,Type,Author,PublisherName,PublishDate,Price,CurrentStock,TotalStock,ISBN FROM BookInfo,PublisherInfo WHERE BookInfo.PublisherID=PublisherInfo.PublisherID AND Author like '%"+search+"%'";
        model->setQuery(strSearch, DBO.dbcon);
    }

    else if (t == "出版社")
    {
        strSearch = "SELECT Title,Type,Author,PublisherName,PublishDate,Price,CurrentStock,TotalStock,ISBN FROM BookInfo,PublisherInfo WHERE BookInfo.PublisherID=PublisherInfo.PublisherID AND PublisherName like '%"+search+"%'";
        model->setQuery(strSearch, DBO.dbcon);
    }
}

//提醒预约过的书可租借
void MainWindow::Updatebook(){
    warn = 0;
    //有预约的书可借
    if(IfAd == 0){
        QString sqlstr = "SELECT ISBN FROM Borrowing,LibraryItem WHERE Borrowing.BookID=LibraryItem.BookID AND ReaderID='"+ID+"'and RenewalNum=-1 ";
        QSqlQuery qs = DBO.DBGetData(sqlstr);
        while(qs.next()){
            QString s = "SELECT CurrentStock FROM BookInfo where ISBN = '"+qs.value("ISBN").toString()+"' ";
            QSqlQuery q = DBO.DBGetData(s);
            q.first();
            if(q.value("CurrentStock").toInt() > 0){
                warn = 1;
                break;
            }
        }
    }
}

//提醒
void MainWindow::warning(){
    //可租借提醒
    if(warn){
        QMessageBox::information(this, "通知", "您有预约的书可租借");
    }
    //逾期提醒
    if(ViolationNum > 0 && ViolationNum <= 3){
        QMessageBox::warning(this, "警告", "有图书逾期未归还!");
    }
    else if(ViolationNum > 3){
        QMessageBox::warning(this, "警告", "信誉分低于70，无法借书!");
    }
}


//推荐
void MainWindow::advise(){
    QString sqlstr = "SELECT Title FROM BookInfo";
    QSqlQuery qs = DBO.DBGetData(sqlstr);
    int num = 1;
    while(qs.next()){
        num++;
    }
    //生成一个随机数
    srand((int)time(0));
    int random = arc4random()%num;
    //随机选择
    qs.first();
    for(int i=1;i<random;i++){
       qs.next();
    }
    ui->textEdit_2->setText(qs.value("Title").toString());
    ui->textEdit_2->setAlignment(Qt::AlignCenter);   //居中
}

//切换推荐按钮
void MainWindow::on_pushButton_clicked()
{
    advise();
}

//将推荐的图书填入搜索框
void MainWindow::on_textEdit_2_selectionChanged()
{
    ui->lineEdit->setText(ui->textEdit_2->toPlainText());
}


//返回
void MainWindow::on_commandLinkButton_clicked()
{
    close();
    homepage win(this);//对象
    win.exec();
}




