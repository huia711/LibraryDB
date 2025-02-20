#include "regist_reader.h"
#include "ui_regist_reader.h"
#include "homepage.h"
#include <Qchar>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

extern QString ID;
extern QString Password;

regist_reader::regist_reader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist_reader)
{
    setStyle();
    DBO.DBOpen();
}

regist_reader::~regist_reader()
{
    delete ui;
}

//设置样式
void regist_reader:: setStyle(){
    ui->setupUi(this);
    setWindowTitle(tr("读者注册"));
    ui->pushButton->setStyleSheet(   //正常状态样式
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
    ui->lineEdit1->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                                    );
    ui->lineEdit2->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                                    );
    ui->lineEdit2->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setStyleSheet(   //正常状态样式
                         "border-radius:5px;"//设置圆角半径
                                    );
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_name->setStyleSheet(
                        "border-radius:5px;"
                        );
    ui->lineEdit_phone->setStyleSheet(
                        "border-radius:5px;"
                        );
    ui->comboBox->setStyleSheet(
                        "border-radius:5px;"
                        );

    //定义下拉框
    QStringList list;
    list<<"男"<<"女"<<"保密";
    ui->comboBox->addItems(list);
}

//注册
void regist_reader::on_pushButton_clicked()
{
    ID = ui->lineEdit1->text().trimmed();
    Password = ui->lineEdit2->text().trimmed();
    QString Confirm = ui->lineEdit->text().trimmed();
    QString Name = ui->lineEdit_name->text().trimmed();
    QString Phone = ui->lineEdit_phone->text().trimmed();
    int Sex = ui->comboBox->currentIndex();
    bool s = 1;

    //判断是否已注册
    QString sql = "SELECT ReaderID FROM ReaderInfo";
    QSqlQuery qq = DBO.DBGetData(sql);
    while(qq.next()){
        if(ID == qq.value("ReaderID").toString()){
            QMessageBox::warning(this, "警告", "用户名已使用");
            s = 0;
            break;
        }
    }
    //判断密码
    if(Password == "") {
        QMessageBox::warning(this, "警告", "密码不能为空");
        s = 0;
    }
    if(Confirm != Password) {
        QMessageBox::warning(this, "警告", "密码与确认密码不相同");
        s = 0;
    }
    //SQL数据库语言
    if(s){
        QString sqlstr = "INSERT INTO ReaderInfo VALUES("+ID+",'"+Password+"',ReaderCategory("+ID+"),'"+Name+"',curdate(),"+QString::number(Sex)+",'"+Phone+"', null, 0, 0, 0, 0, null)";
        QSqlQuery qs = DBO.DBGetData(sqlstr);
        if(qs.numRowsAffected() >=1 ){
            QMessageBox::information(this, "成功","注册成功");
            //转到主界面
            close();
        }
        else{
            QMessageBox::warning(this, "警告", "注册失败");
        }
    }
}

//显示密码
void regist_reader::on_showBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        ui->lineEdit2->setEchoMode(QLineEdit::Normal);
        ui->lineEdit->setEchoMode(QLineEdit::Normal);
    }
    if(arg1 == 0){
        ui->lineEdit2->setEchoMode(QLineEdit::Password);
        ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
}
