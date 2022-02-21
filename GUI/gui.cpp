#include "gui.h"
#include "ui_gui.h"
#include <string.h>
#include <iostream>
#include "singup.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "dashboard.h"

Gui::Gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gui)
{
    ui->setupUi(this);
    ui->wrongEmailPasswordLabel->setVisible(false);
}

Gui::~Gui()
{
    delete ui;
}
void Gui::on_emailLineEdit_textEdited(const QString &arg1)
{
    email = arg1;
}

void Gui::on_passwordLineEdit_textEdited(const QString &arg1)
{
    password = arg1;
}

void Gui::on_loginPushButton_clicked()
{
    std::string url = "http://127.0.0.1:8000/users/email/";

    cpr::Response response = cpr::Get(cpr::Url{url += email.toStdString()});


    userData = json::parse(response.text);

    if (response.status_code == 200 && userData["password"] == password.toStdString())
    {
        Dashboard* dashboardWindow = new Dashboard();
        dashboardWindow->show();
        dashboardWindow->setVariablesFromGui(userData["id"], userData["username"], userData["email"], 0);
        this->close();
    }
    else
    {
        ui->wrongEmailPasswordLabel->setVisible(true);
    }



}

void Gui::on_herePushButton_clicked()
{
    SingUp* singUpWindow = new SingUp();
    singUpWindow->show();
    this->close();

}













