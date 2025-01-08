#include "studentdata.h"
#include "studentinfo.h"
#include "ui_studentinfo.h"

StudentInfo::StudentInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentInfo)
{
    ui->setupUi(this);
}

StudentInfo::~StudentInfo()
{
    delete ui;
}

void StudentInfo::setUsername(const QString &newUsername)
{
    username = newUsername;
    ui->labelUsername->setText(username);

}

void StudentInfo::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
    qDebug()<<"StudentInfo";
    qDebug()<<myToken;
}

void StudentInfo::on_btnData_clicked()
{
    StudentData *objStudentData=new StudentData(this);
    objStudentData->setUsername(username);
    objStudentData->setMyToken(myToken);
    objStudentData->open();
}

