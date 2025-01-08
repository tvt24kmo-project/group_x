#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class StudentInfo;
}

class StudentInfo : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInfo(QWidget *parent = nullptr);
    ~StudentInfo();

    void setUsername(const QString &newUsername);

    void setMyToken(const QByteArray &newMyToken);

private slots:
    void on_btnData_clicked();

    void on_btnGrade_clicked();

     void gradeSlot (QNetworkReply *reply);

private:
    Ui::StudentInfo *ui;
    QString username;
    QByteArray myToken;
    QNetworkAccessManager *gradeManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // STUDENTINFO_H
