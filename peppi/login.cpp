#include "environment.h"
#include "login.h"
#include "studentinfo.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("username",ui->textUsername->text());
    jsonObj.insert("password",ui->textPassword->text());

    QString site_url=Environment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    postManager = new QNetworkAccessManager(this);
    //connect(postManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));
    //korvataan uudella versiolla
    connect(postManager, &QNetworkAccessManager::finished, this, &Login::loginSlot);
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Login::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    if(response_data.length()<2){
        qDebug()<<"Palvelin ei vastaa";
        ui->labelInfo->setText("Palvelin ei vastaa!");
    }
    else {
        if(response_data=="-11"){
            ui->labelInfo->setText("Tietokanta virhe!");
        }
        else {
            if(response_data!="false" && response_data.length()>20) {
               ui->labelInfo->setText("Kirjautuminen OK");
               QByteArray myToken="Bearer "+response_data;
               StudentInfo *objStudentInfo=new StudentInfo(this);
               objStudentInfo->setUsername(ui->textUsername->text());
               objStudentInfo->setMyToken(myToken);
               objStudentInfo->open();
            }
            else {
               ui->labelInfo->setText("Väärä tunnus/salasana");
            }

        }

    }

    reply->deleteLater();
    postManager->deleteLater();
}

