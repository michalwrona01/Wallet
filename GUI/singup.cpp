#include "singup.h"
#include "ui_singup.h"
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include "gui.h"

using json = nlohmann::json;


SingUp::SingUp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingUp)
{
    ui->setupUi(this);
    showOrHideLoginRedirectionWidgets(false);
    ui->incorrectDataLabel->setVisible(false);
    ui->passwordsNotMatchLabel->setVisible(false);
}

SingUp::~SingUp()
{
    delete ui;
}

void SingUp::showOrHideLoginRedirectionWidgets(bool is_show)
{
        ui->loginRedirectionPushButton->setVisible(is_show);
        ui->registerWasSuccessfulLabel->setVisible(is_show);
}

void SingUp::on_userNameLineEdit_textEdited(const QString &arg1)
{
    this->username = arg1;
}

void SingUp::on_emailLineEdit_textEdited(const QString &arg1)
{
    this->email = arg1;
}

void SingUp::on_passwordLineEdit_textEdited(const QString &arg1)
{
    this->password = arg1;
}

void SingUp::on_confirmPasswordLineEdit_textEdited(const QString &arg1)
{
    this->confirmPassword = arg1;
}

void SingUp::on_registerPushButton_clicked()
{
    std::string username_str, email_str, password_str;

    if (!username.isEmpty() && !email.isEmpty() && !password.compare(confirmPassword))
    {
        username_str = username.toStdString();
        email_str = email.toStdString();
        password_str = password.toStdString();

        json data =
            {
                {"username", username_str},
                {"email", email_str},
                {"password", password_str}
            };


        cpr::Response response = cpr::Post(cpr::Url{"http://127.0.0.1:8000/users"},
                                           cpr::Body{data.dump()});
        if (response.status_code == 200)
        {
            showOrHideLoginRedirectionWidgets(true);
        }
        else
        {
            ui->incorrectDataLabel->setVisible(true);
        }
    }
    else if (!username.isEmpty() && !email.isEmpty() && password.compare(confirmPassword))
    {
        ui->passwordsNotMatchLabel->setVisible(true);
    }
    else
    {
        ui->incorrectDataLabel->setVisible(true);
    }
}


void SingUp::on_loginRedirectionPushButton_clicked()
{
    Gui* loginWindow = new Gui();
    loginWindow->show();
    this->close();

}

void SingUp::on_returnFromSignUpButton_clicked()
{
    Gui* loginWindow = new Gui();
    loginWindow -> show();
    this->close();
}

