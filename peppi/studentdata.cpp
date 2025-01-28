#include "environment.h"
#include "studentdata.h"
#include "ui_studentdata.h"

StudentData::StudentData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentData)
{
    ui->setupUi(this);
}

StudentData::~StudentData()
{
    delete ui;
}

void StudentData::setUsername(const QString &newUsername)
{
    username = newUsername;
}

void StudentData::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void StudentData::on_btnShowData_clicked()
{
    qDebug()<<"show data button";
    QString site_url=Environment::base_url()+"/student/"+username;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    dataManager = new QNetworkAccessManager(this);

    //connect(dataManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(showDataSlot(QNetworkReply*)));
    //korvataan uudella versiolla
    connect(dataManager,&QNetworkAccessManager::finished,this,&StudentData::showDataSlot);
    reply = dataManager->get(request);
}

void StudentData::showDataSlot(QNetworkReply *reply)
{
    qDebug()<<"show data SLOT";
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    /*QString myData;
    myData+=json_obj["username"].toString()+ " "+json_obj["fname"].toString()+" "+json_obj["lname"].toString();
    ui->labelData->setText(myData);*/
    ui->labelFname->setText(json_obj["fname"].toString());
    ui->labelLname->setText(json_obj["lname"].toString());
    ui->labelAddress->setText(json_obj["address"].toString());

    reply->deleteLater();
    dataManager->deleteLater();
}

