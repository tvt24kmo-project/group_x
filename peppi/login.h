#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnLogin_clicked();
    void loginSlot (QNetworkReply *reply);

private:
    Ui::Login *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // LOGIN_H
