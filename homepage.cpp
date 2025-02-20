#include "homepage.h"
#include "ui_homepage.h"
#include "mainwindow.h"
#include "regist_reader.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
using namespace std;

QString ID;
QString Password;
bool IfAd = 0;

homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{
    //设置样式
    setStyle();
    DBO.DBOpen();
    IfAd = 0;
}

homepage::~homepage()
{
    delete ui;
}

//设置样式
void homepage::setStyle(){
    ui->setupUi(this);
    setWindowTitle(tr("图书管理系统"));
    //按钮-忘记密码
    ui->btn_forget->setStyleSheet(
                "QPushButton{"
                "border:none;"
                "color:#e83737;"
                "}"
                "QPushButton:hover{"
                "border:none;"
                "color:#e83737;"
                "}");
    //按钮-登录
    ui->pushButton2->setStyleSheet(   //正常状态样式
                        "QPushButton{"
                        "border-radius:5px;"//设置圆角半径
                        "background-color:#8293fd;"
                        "color:white;"
                        "font:bold;"
                        "border: none;"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:#4861fb;"//设置按钮背景色
                        "color:#bbc6d3;"//设置按钮字体颜色
                        "border: none;"
                        "}");
    //输入框
    ui->lineEdit1->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                            );
    ui->lineEdit2->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                            );
    ui->lineEdit2->setEchoMode(QLineEdit::Password);
    ui->showBox->setStyleSheet(   //正常状态样式
                                  "font: bold;"
                            );
    ui->AdBox->setStyleSheet(   //正常状态样式
        "font: bold;"
        );
    ui->lineEdit1->setFocus(Qt::ActiveWindowFocusReason);//应用程序窗口切换为活动状态时更改焦点为此部件
}


//是否为管理员
void homepage::on_AdBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        IfAd = 1;
    }
    if(arg1 == 0){
        IfAd = 0;
    }
}


//登录
void homepage::on_pushButton2_clicked()
{
    bool check = 0;
    ID = ui->lineEdit1->text().trimmed();                //lineEdit输入框，trimmed()去除开头结尾的空白
    Password = ui->lineEdit2->text().trimmed();          //lineEdit输入框，trimmed()去除开头结尾的空白

    //判断管理员-是
    if(IfAd == 1){
        //SQL数据库语言
        QString sqlstr = "SELECT AdminID,AdminPWD,AdminName FROM AdministratorInfo";
        QSqlQuery qs = DBO.DBGetData(sqlstr);
        while(qs.next()){
            // 密码正确
            if(ID == qs.value("AdminID").toString() && Password == qs.value("AdminPWD").toString()){
                QMessageBox::information(this, "登录成功", "登录成功，欢迎管理员"+qs.value("AdminName").toString()+"    ");
                //转到主界面
                close();
                MainWindow *mainwin = new MainWindow;
                mainwin->show();
                check = 1;
                break;
            }
            // 密码错误
            if(ID == qs.value("AdminID").toString() && Password != qs.value("AdminPWD").toString()){
                QMessageBox::warning(this, "警告", "密码错误");
                check = 1;
                break;
            }
        }
    }

    //判断管理员-否
    if(IfAd == 0){
        //SQL数据库语言
        QString sqlstr = "SELECT ReaderID,ReaderPWD,ReaderName FROM ReaderInfo";
        QSqlQuery qs = DBO.DBGetData(sqlstr);
        while(qs.next()){
            // 密码正确
            if(ID == qs.value("ReaderID").toString() && Password == qs.value("ReaderPWD").toString()){
                QMessageBox::information(this, "登录成功", "登录成功，欢迎读者"+qs.value("ReaderName").toString()+"    ");
                //转到主界面
                close();
                MainWindow *mainwin = new MainWindow;
                mainwin->show();
                check = 1;
                break;
            }
            // 密码错误
            if(ID == qs.value("ReaderID").toString() && Password != qs.value("ReaderPWD").toString()){
                QMessageBox::warning(this, "警告", "密码错误");
                check = 1;
                break;
            }
        }
    }

    if(!check) QMessageBox::warning(this, "警告", "未找到此用户");
}

//显示密码
void homepage::on_showBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        ui->lineEdit2->setEchoMode(QLineEdit::Normal);
    }
    if(arg1 == 0){
        ui->lineEdit2->setEchoMode(QLineEdit::Password);
    }
}


//注册
void homepage::on_pushButton1_clicked()
{
    regist_reader win(this);//对象
    win.exec();
    ui->lineEdit1->setText(ID);
    ui->lineEdit2->setText(Password);
}


//忘记密码
void homepage::on_btn_forget_clicked()
{
    bool check = 0;
    ID = ui->lineEdit1->text().trimmed();

    //判断管理员-是
    if(IfAd == 1){
        QMessageBox::warning(this, "警告", "管理员无法使用");
        check = 1;
    }

    //判断管理员-否
    if(IfAd == 0){
        //SQL数据库语言
        QString sqlstr = "SELECT ReaderID FROM ReaderInfo";
        QSqlQuery qs = DBO.DBGetData(sqlstr);
        while(qs.next()){
            if(ID == qs.value("ReaderID").toString()){
                QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否通知管理员重置密码");
                if(result == QMessageBox::Yes)
                {
                    //数据库更改
                    QString sql = "UPDATE ReaderInfo SET IsSuspended = 1 WHERE ReaderID='"+ID+"'";
                    QSqlQuery qq = DBO.DBGetData(sql);
                    if(qq.numRowsAffected() >=1 ){
                        QMessageBox::information(this, "已通知", "已通知管理员，请向管理员出示相关证件");
                    }
                    else{
                        QMessageBox::warning(this, "警告", "通知出错");
                    }
                }
                check = 1;
                break;
            }
        }
    }

    if(!check) QMessageBox::warning(this, "警告", "未找到此用户");
}

