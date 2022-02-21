#ifndef SINGUP_H
#define SINGUP_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

namespace Ui {
class SingUp;
}

class SingUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingUp(QWidget *parent = nullptr);
    ~SingUp();

private slots:
    void on_userNameLineEdit_textEdited(const QString &arg1);

    void on_emailLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_confirmPasswordLineEdit_textEdited(const QString &arg1);

    void on_registerPushButton_clicked();

    void on_loginRedirectionPushButton_clicked();

    void showOrHideLoginRedirectionWidgets(bool is_show);

    void on_returnFromSignUpButton_clicked();

private:
    Ui::SingUp *ui;

public:
    QString username;
    QString email;
    QString password;
    QString confirmPassword;
};

#endif // SINGUP_H
