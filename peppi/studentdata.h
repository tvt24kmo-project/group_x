#ifndef STUDENTDATA_H
#define STUDENTDATA_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class StudentData;
}

class StudentData : public QDialog
{
    Q_OBJECT

public:
    explicit StudentData(QWidget *parent = nullptr);
    ~StudentData();

    void setUsername(const QString &newUsername);

    void setMyToken(const QByteArray &newMyToken);

private slots:
    void on_btnShowData_clicked();
    void showDataSlot(QNetworkReply *reply);

private:
    Ui::StudentData *ui;
    QString username;
    QByteArray myToken;

    QNetworkAccessManager *dataManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // STUDENTDATA_H
