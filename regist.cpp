#include "regist.h"
#include "ui_regist.h"
#include <Qchar>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{
    setStyle();
    DBO.DBOpen();

}

regist::~regist()
{
    delete ui;
}

//设置样式
void regist:: setStyle(){
    ui->setupUi(this);
    setWindowTitle(tr("管理员注册"));
    ui->pushButton->setStyleSheet(   //正常状态样式
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
    ui->lineEdit_position->setStyleSheet(
                        "border-radius:5px;"
                                    );

    //定义下拉框
    QStringList list;
    list<<"男"<<"女"<<"保密";
    ui->comboBox->addItems(list);
}

//注册
void regist::on_pushButton_clicked()
{
    QString ID = ui->lineEdit1->text().trimmed();                //lineEdit输入框，trimmed()去除开头结尾的空白
    QString Password = ui->lineEdit2->text().trimmed();
    QString Confirm = ui->lineEdit->text().trimmed();
    QString Name = ui->lineEdit_name->text().trimmed();
    QString Phone = ui->lineEdit_phone->text().trimmed();
    QString Position = ui->lineEdit_position->text().trimmed();
    int Sex = ui->comboBox->currentIndex();
    bool s = 1;

    //判断是否已注册
    QString sql = "SELECT AdminID FROM AdministratorInfo";
    QSqlQuery qq = DBO.DBGetData(sql);
    while(qq.next()){
        if(ID == qq.value("AdminID").toString()){
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
        QString sqlstr = "INSERT INTO AdministratorInfo VALUES("+ID+",'"+Password+"','"+Name+"',"+QString::number(Sex)+",'"+Phone+"','"+Position+"')";
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
void regist::on_showBox_stateChanged(int arg1)
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

//取消
void regist::on_commandLinkButton_clicked()
{
    close();
}




