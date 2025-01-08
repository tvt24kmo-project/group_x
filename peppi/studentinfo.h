#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>

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

private:
    Ui::StudentInfo *ui;
    QString username;
    QByteArray myToken;
};

#endif // STUDENTINFO_H
