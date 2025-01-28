#include "environment.h"
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


void StudentInfo::on_btnGrade_clicked()
{
    qDebug()<<"show data button";
    QString site_url=Environment::base_url()+"/grade/"+username;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    gradeManager = new QNetworkAccessManager(this);
    //connect(gradeManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(gradeSlot(QNetworkReply*)));
    //korvataan uudella versiolla
    connect(gradeManager, &QNetworkAccessManager::finished, this, &StudentInfo::gradeSlot);

    reply = gradeManager->get(request);
}

void StudentInfo::gradeSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString grades;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        grades+=json_obj["name"].toString()+","+QString::number(json_obj["ects"].toInt())+","+json_obj["grade_date"].toString()+"\r";
    }
    ui->textGrades->setText(grades);


    reply->deleteLater();
    gradeManager->deleteLater();
}

