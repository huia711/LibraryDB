#include "addbook.h"
#include "ui_addbook.h"
#include <Qchar>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

extern bool up;
extern QString ISBN;
extern QString Title;
extern QString Author;
extern QString PublisherName;
extern QDate PublishDate;
extern QString Type;
extern float Price;
extern int Stock;
extern int CurrentStock;

addbook::addbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbook)
{
    setStyle();
    DBO.DBOpen();
}

addbook::~addbook()
{
    delete ui;
}

//设置样式
void addbook:: setStyle(){
    ui->setupUi(this);
    setWindowTitle(tr("添加图书"));
    ui->pushButton2->setStyleSheet(   //正常状态样式
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
    ui->name_lineEdit->setStyleSheet(
                         "border-radius:5px;"
                                    );
    ui->author_lineEdit->setStyleSheet(
                         "border-radius:5px;"
                                    );
    ui->ISBN_lineEdit->setStyleSheet(
        "border-radius:5px;"
        );
    ui->dateEdit->setStyleSheet(
        "border-radius:5px;"
        );
    ui->price_lineEdit->setStyleSheet(
        "border-radius:5px;"
        );
    ui->price_lineEdit->setValidator(new QDoubleValidator(0.0, 10000.0, 2, ui->price_lineEdit));  //只能输入小数
    ui->publishing_lineEdit->setStyleSheet(
        "border-radius:5px;"
        );
    ui->publishing_lineEdit->setStyleSheet(
                         "border-radius:5px;"
                                    );
    ui->comboBox->setStyleSheet(
                         "border-radius:5px;"
                                    );
    ui->comboBox_2->setStyleSheet(
                         "border-radius:5px;"
                                    );
    //定义下拉框
    QStringList list;
    list<<"B哲学、宗教"<<"D政治、法律"<<"E军事"<<"F经济"<<"H语言"<<"I文学"<<"J艺术"<<"K历史、地理"<<"N自然科学总论"<<"O数理科学和化学";
    list<<"F天文学、地球科学"<<"Q生物科学"<<"R医药、卫生"<<"S农业科学"<<"T工业技术"<<"U交通运输"<<"V航空航天"<<"X环境科学"<<"Z综合性图书";
    ui->comboBox->addItems(list);

    QStringList list2;
    for(int i=1;i<21;i++){
        list2<<QString::number(i);
    }
    ui->comboBox_2->addItems(list2);

    //如果是修改，将原数据放入
    if(up){
        ui->ISBN_lineEdit->setText(ISBN);
        ui->name_lineEdit->setText(Title);
        ui->author_lineEdit->setText(Author);
        ui->publishing_lineEdit->setText(PublisherName);
        ui->price_lineEdit->setText(QString::number(Price, 'f', 2));
        ui->dateEdit->setDate(PublishDate);
        ui->comboBox->setCurrentText(Type);
        ui->comboBox_2->setCurrentText(QString::number(Stock));
    }
}

//完成
void addbook::on_pushButton2_clicked()
{
    QString ISBNset = ui->ISBN_lineEdit->text().trimmed();
    QString title = ui->name_lineEdit->text().trimmed();
    QString author = ui->author_lineEdit->text().trimmed();
    QString publishing = ui->publishing_lineEdit->text().trimmed();
    QString price = ui->price_lineEdit->text().trimmed();
    QDate PublishDate = ui->dateEdit->date();
    QString type = ui->comboBox->currentText();
    QString num = ui->comboBox_2->currentText();
    //SQL数据库语言
    //判断是否为空
    if(ISBNset.isEmpty() || title.isEmpty() || type.isEmpty() || num.isEmpty()){
        QMessageBox::warning(this, "警告", "输入值不能为空");
    }
    else{
        //如果是添加图书
        if(!up){
            QString sqlstr = "INSERT INTO BookInfo (ISBN,PublisherID,Title,Type,Author,PublishDate,Price,CurrentStock,TotalStock) VALUES "
                             "('"+ISBNset+"',Publisher('"+publishing+"'),'"+title+"','"+type+"','"+author+"','"+PublishDate.toString(("yyyy-MM-dd"))+"',"+price+","+num+","+num+")";
            QSqlQuery qs = DBO.DBGetData(sqlstr);
            if(qs.numRowsAffected() >=1 ){
                QMessageBox::information(this, "成功","添加成功");
                //转到主界面
                close();
            }
            else{
                QMessageBox::warning(this, "警告", "添加失败");
            }
        }

        //如果是修改图书
        if(up){
            QString sqlstr = "UPDATE BookInfo SET ISBN='"+ISBNset+"',PublisherID=Publisher('"+publishing+"'),Title='"+title+"',Type='"+type+"',Author='"+author+"',PublishDate='"+PublishDate.toString(("yyyy-MM-dd"))+"',Price="+price+",CurrentStock="+QString::number(CurrentStock+(num.toInt()-Stock))+",TotalStock="+num+" where ISBN='"+ISBN+"'";
            QSqlQuery qs = DBO.DBGetData(sqlstr);
            //库存不能少于借出的
            if(num.toInt() < (Stock - CurrentStock)){
                QMessageBox::warning(this, "警告", "库存不能少于借出本数");
            }
            else if(qs.numRowsAffected() >= 1){
                QMessageBox::information(this, "成功","修改成功");
                //转到主界面
                close();
            }
            else{
                QMessageBox::warning(this, "警告", "修改失败");
            }
        }

    }
}


//取消
void addbook::on_commandLinkButton_clicked()
{
    close();
}

