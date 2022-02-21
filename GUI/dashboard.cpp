#include "dashboard.h"
#include "ui_dashboard.h"
#include <iostream>
#include "gui.h"
#include <cpr/cpr.h>
#include <cmath>
#include "transaction.h"
#include "QFileDialog"
#include "QDate"
#include <nlohmann/json.hpp>
#include <QtCharts>


void swap(Transaction *objOne, Transaction *objTwo) {
    std::string tempDate = objOne->date;
    std::string tempTopic = objOne->topic;
    std::string tempValue = objOne->value;

    objOne->date = objTwo->date;
    objOne->topic = objTwo->topic;
    objOne->value = objTwo->value;

    objTwo->date = tempDate;
    objTwo->topic = tempTopic;
    objTwo->value = tempValue;

}

void sortTransactionsByDate(Transaction *transactionsTab, int tabSize)
{
    for(int i=0; i < tabSize; i++)
        {
            for (int j=0; j < tabSize-i-1 ; j++)
            {
                QString dateFirstQStr = QString::fromStdString(transactionsTab[j].date);
                QDate dateFirst = QDate::fromString(dateFirstQStr, "yyyy.MM.dd");

                QString dateSecondQStr = QString::fromStdString(transactionsTab[j+1].date);
                QDate dateSecond = QDate::fromString(dateSecondQStr, "yyyy.MM.dd");

                if (dateFirst > dateSecond)
                {
                    swap(&transactionsTab[j], &transactionsTab[j+1]);
                }
            }
        }

}

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    ui->labelWasDelete->setVisible(false);
    ui->serverErrorOrIncorrectDataMessage->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->passwordHasBeenChanged->setVisible(false);
    ui->usernameHasBeenChanged->setVisible(false);
    ui->tabWidget->setCurrentWidget(ui->dashboardTab);
    uiUpdate();
}
Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::updateUserNameButtonAndBudgetLabel()
{
    ui->userNameButton->setText(this->username);
    ui->budgetLabel->setText(QString::fromStdString(std::to_string(budget)));
}

void Dashboard::setBudgetLabelValue(float amount)
{
   ui->budgetLabel->setText(QString::fromStdString(std::to_string(amount)));
}

void Dashboard::setVariablesFromGui(int userId, std::string username, std::string email, float budget)
{
    this->userId = userId;
    this->username = QString::fromStdString(username);
    this->email = QString::fromStdString(email);
    this->budget = budget;

    updateUserNameButtonAndBudgetLabel();

    setTransactionHistoryInListWidget();

}

void Dashboard::setTransactionHistoryInListWidget()
{
    ui->transactioHistoryListWidget->addScrollBarWidget(ui->verticalScrollBar, Qt::AlignmentFlag::AlignLeft);

    std::string url = "http://localhost:8000/budgets/user/";
    std::string urlParams = "/offset/0/limit/1000";
    std::string userIdStr = std::to_string(this->userId);

    cpr::Response response = cpr::Get(cpr::Url{url + userIdStr + urlParams});

    float sumOfBudget = 0;
    json historyBudgets = json::parse(response.text);
    int amountTransactions = historyBudgets["items"].size();


    Transaction transactions[amountTransactions];
    transactions->length = amountTransactions;

    for(int i=0; i < amountTransactions; i++)
    {
        float amount = historyBudgets["items"][i]["amount"];
        std::string topic = historyBudgets["items"][i]["topic"];
        std::string date = historyBudgets["items"][i]["dateCreated"];

        transactions[i].setTransaction(std::to_string(amount), topic, date);
        sumOfBudget+= amount;
    }

    setBudgetLabelValue(sumOfBudget);
    sortTransactionsByDate(transactions, amountTransactions);

    for(int i=0; i < amountTransactions; i++)
    {
        QString expense = QString::fromStdString(transactions[i].getInformation());
        ui->transactioHistoryListWidget->addItem(expense);
    }

    transactions->transactionsPtr = transactions;
    QChartView *chartView = transactions->drawPlot();
    ui->gridLayoutPlot->addWidget(chartView, 1, 1);
}

void Dashboard::setReceiptsInView()
{
    std::string url = "http://localhost:8000/receipts/user/";
    std::string urlParams = "/offset/0/limit/1000";
    std::string userIdStr = std::to_string(this->userId);

    cpr::Response response = cpr::Get(cpr::Url{url + userIdStr + urlParams});

    json receiptsData = json::parse(response.text);
    int amountReceipts = receiptsData["items"].size();

    for (int i=0; i < amountReceipts; i++)
    {
        int receiptId = receiptsData["items"][i]["id"];
        int numberReceipt = receiptsData["items"][i]["numberReceipt"];
        int NIP = receiptsData["items"][i]["nipNumber"];
        float price = receiptsData["items"][i]["price"];
        std::string dateReceiptCreated = receiptsData["items"][i]["dateCreated"];

        ui->listWidget->addItem(QString::fromStdString(std::to_string(receiptId)));
        ui->listWidgetShop->addItem(QString::fromStdString(receiptsData["items"][i]["shopName"]));
        ui->listWidgetCompany->addItem(QString::fromStdString(receiptsData["items"][i]["companyName"]));
        ui->listWidgetReceipt->addItem(QString::fromStdString(std::to_string(numberReceipt)));
        ui->listWidgetNIP->addItem(QString::fromStdString(std::to_string(NIP)));
        ui->listWidgetPrice->addItem(QString::fromStdString(std::to_string(price)));
        ui->listWidgetDateCreated->addItem(QString::fromStdString(dateReceiptCreated));
    }

}

void Dashboard::on_addTransactionButton_clicked()
{
    std::string dateStr, topicStr;
    float valueFloat;

    if (!valueBudget.isEmpty())
    {
        valueFloat = this->valueBudget.toFloat();
        dateStr = this->dateBudget.toStdString();
        topicStr = this->topicBudget.toStdString();

        json data = {
          {"amount", valueFloat},
          {"dateCreated", dateStr},
          {"topic", topicStr},
          {"userId", userId}
        };

        cpr::Response response = cpr::Post(cpr::Url{"http://127.0.0.1:8000/budgets"},
                                           cpr::Body{data.dump()});
    }

    uiUpdate();
}

void Dashboard::on_valueBudgetEdit_textEdited(const QString &arg1)
{
    this->valueBudget = arg1;
}

void Dashboard::on_topicBudgetEdit_textEdited(const QString &arg1)
{
    this->topicBudget = arg1;
}

void Dashboard::on_calendarWidget_clicked(const QDate &date)
{
    this->dateBudget = date.toString("yyyy.MM.dd");
}

void Dashboard::uiUpdate()
{
    updateUserNameButtonAndBudgetLabel();
    ui->transactioHistoryListWidget->clear();
    setTransactionHistoryInListWidget();

    ui->listWidget->clear();
    ui->listWidget->clear();
    ui->listWidgetShop->clear();
    ui->listWidgetCompany->clear();
    ui->listWidgetReceipt->clear();
    ui->listWidgetNIP->clear();
    ui->listWidgetPrice->clear();
    ui->listWidgetDateCreated->clear();
    setReceiptsInView();
}

void Dashboard::on_actionAdd_Expense_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->budgetsTab);
    ui->tabWidget->update();
    ui->groupBox->setVisible(false);
    ui->gridWidget->setVisible(true);
}

void Dashboard::on_actionView_Dashboard_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->dashboardTab);
    ui->tabWidget->update();

    uiUpdate();
}

void Dashboard::on_chooseFilePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(fileName, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(fileName);

        if (valid)
        {
            ui->imageLabel->setPixmap(QPixmap::fromImage(image));
        }
        else  {}
    }

}

void Dashboard::on_addReceiptPushButton_clicked()
{
    if (!(shopNameReceipt.isEmpty() || companyNameReceipt.isEmpty() ||
            numberReceipt.isEmpty() || numberNIPReceipt.isEmpty() || priceReceipt.isEmpty()))
    {
        std::string shopNameStr = shopNameReceipt.toStdString();
        std::string companyNameStr = companyNameReceipt.toStdString();
        int numberReceiptInt = numberReceipt.toInt();
        int numberNIPReceiptInt = numberNIPReceipt.toInt();
        float priceReceiptFloat = -(priceReceipt.toFloat());
        std::string dateCreatedStr = dateAddReceipt.toString("yyyy.MM.dd").toStdString();

        int receiptId;

        json dataReceipt = {
            {"shopName", shopNameStr},
            {"companyName", companyNameStr},
            {"numberReceipt", numberReceiptInt},
            {"nipNumber", numberNIPReceiptInt},
            {"price", priceReceiptFloat},
            {"dateCreated", dateCreatedStr},
            {"userId", userId}
        };

        cpr::Response responseReceipt = cpr::Post(cpr::Url{"http://127.0.0.1:8000/receipts"},
                                           cpr::Body{dataReceipt.dump()});

        if (responseReceipt.status_code == 200)
        {
            json responseReceiptData = json::parse(responseReceipt.text);
            receiptId = responseReceiptData["id"];

            json dataTransaction {
               {"amount", priceReceiptFloat},
               {"receiptId", receiptId},
               {"dateCreated", dateCreatedStr},
               {"topic", shopNameStr},
               {"userId", userId}
            };

            cpr::Response responseTransaction = cpr::Post(cpr::Url{"http://127.0.0.1:8000/budgets"},
                                                          cpr::Body{dataTransaction.dump()});
        }
        else
        {
            ui->serverErrorOrIncorrectDataMessage->setVisible(true);
        }
    }
    else
    {
        ui->serverErrorOrIncorrectDataMessage->setVisible(true);
    }

    uiUpdate();


}


void Dashboard::on_shopNameLineEdit_textEdited(const QString &arg1)
{
    this->shopNameReceipt = arg1;
}


void Dashboard::on_companyNameLineEdit_textEdited(const QString &arg1)
{
    this->companyNameReceipt = arg1;
}


void Dashboard::on_NIP_LineEdit_textEdited(const QString &arg1)
{
    this->numberNIPReceipt = arg1;
}


void Dashboard::on_priceReceiptLineEdit_textEdited(const QString &arg1)
{
    this->priceReceipt = arg1;
}


void Dashboard::on_addReceiptCalendarWidget_clicked(const QDate &date)
{
    this->dateAddReceipt = date;
}


void Dashboard::on_numberReceiptLineEdit_textEdited(const QString &arg1)
{
    this->numberReceipt = arg1;
}


void Dashboard::on_actionView_Statistics_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->budgetsTab);
    ui->tabWidget->update();

    uiUpdate();
    ui->groupBox->setVisible(true);
}

void Dashboard::on_actionView_All_Receipts_triggered()
{
    uiUpdate();
    ui->labelWasDelete->setVisible(false);
    ui->tabWidget->setCurrentWidget(ui->allReceiptsTab);
    ui->tabWidget->update();
}


void Dashboard::on_actionAdd_Receipt_triggered()
{
    uiUpdate();
    ui->tabWidget->setCurrentWidget(ui->receiptsTab);
    ui->tabWidget->update();
}


void Dashboard::on_listWidget_currentTextChanged(const QString &currentText)
{
    this->idReceipt = currentText;
}


void Dashboard::on_pushButtonDeleteCheckedId_clicked()
{
    std::string id = idReceipt.toStdString();
    std::cout << id;
    cpr::Response response = cpr::Get(cpr::Url{"http://127.0.0.1:8000/receipts/" + id});
    std::cout << response.text;

    if (response.status_code == 200)
    {
        std::cout << "WITAM";
        cpr::Response responseBudgetDelete = cpr::Delete(cpr::Url{"http://127.0.0.1:8000/budgets/receipt/" + id});
        if (responseBudgetDelete.status_code == 200)
        {
            ui->labelWasDelete->setVisible(true);
            uiUpdate();
        }
    }
}


void Dashboard::on_oldPassowordLineEdit_textEdited(const QString &arg1)
{
    this->oldPassword = arg1;
}


void Dashboard::on_newPassword_textEdited(const QString &arg1)
{
    this->newPassword = arg1;
}


void Dashboard::on_newPasswordConfirm_textEdited(const QString &arg1)
{
    this->newPasswordConfirm = arg1;
}


void Dashboard::on_passwordChangeUsername_textEdited(const QString &arg1)
{
    this->passwordUsername = arg1;
}


void Dashboard::on_newUsernameLineEdit_textEdited(const QString &arg1)
{
    this->newUsername = arg1;
}


void Dashboard::on_pushButtonChangePassword_clicked()
{
    cpr::Response responseUser = cpr::Get(cpr::Url{"http://127.0.0.1:8000/users/" + std::to_string(this->userId)});
    json dataUser = json::parse(responseUser.text);

    if (oldPassword.toStdString() == dataUser["password"] && newPassword == newPasswordConfirm)
    {
        json newDataUser = {
            {"id", this->userId},
            {"username", dataUser["username"]},
            {"email", dataUser["email"]},
            {"password", newPassword.toStdString()},
            {"budget", dataUser["budget"]}
        };

        cpr::Response response = cpr::Put(cpr::Url{"http://127.0.0.1:8000/users/" + std::to_string(this->userId)},
                                          cpr::Body{newDataUser.dump()});

        if (response.status_code == 200)
        {
            ui->passwordHasBeenChanged->setVisible(true);
        }
        uiUpdate();
    }
}


void Dashboard::on_pushButtonChangeUsername_clicked()
{
    cpr::Response responseUser = cpr::Get(cpr::Url{"http://127.0.0.1:8000/users/" + std::to_string(this->userId)});
    json dataUser = json::parse(responseUser.text);

    if (passwordUsername.toStdString() == dataUser["password"])
    {
        json newDataUser = {
            {"id", this->userId},
            {"username", newUsername.toStdString()},
            {"email", dataUser["email"]},
            {"password", dataUser["password"]},
            {"budget", dataUser["budget"]}
        };

        cpr::Response response = cpr::Put(cpr::Url{"http://127.0.0.1:8000/users/" + std::to_string(this->userId)},
                                          cpr::Body{newDataUser.dump()});

        if (response.status_code == 200)
        {
            ui->usernameHasBeenChanged->setVisible(true);
            this->username = newUsername;
        }
        uiUpdate();
    }
}

void Dashboard::on_actionLogout_triggered()
{
    Gui* guiWindow = new Gui();
    guiWindow->show();
    this->close();
}

void Dashboard::on_pushButtonDeleteAccount_clicked()
{
    cpr::Response response = cpr::Delete(cpr::Url{"http://127.0.0.1:8000/users/" + std::to_string(this->userId)});
    cpr::Response responseDeleteBudgets = cpr::Delete(cpr::Url{"http://127.0.0.1:8000/budgets/user/" + std::to_string(this->userId)});
    cpr::Response responseDeleteReceipts = cpr::Delete(cpr::Url{"http://127.0.0.1:8000/receipts/user/" + std::to_string(this->userId)});


    Gui* guiWindow = new Gui();
    guiWindow->show();
    this->close();

}

void Dashboard::on_actionView_Delete_Receipt_triggered()
{
    uiUpdate();
    ui->labelWasDelete->setVisible(false);
    ui->tabWidget->setCurrentWidget(ui->allReceiptsTab);
    ui->tabWidget->update();
}


void Dashboard::on_actionChange_Password_triggered()
{
    uiUpdate();
    ui->usernameHasBeenChanged->setVisible(false);
    ui->passwordHasBeenChanged->setVisible(false);
    ui->tabWidget->setCurrentWidget(ui->settingsTab);
    ui->tabWidget->update();
}


void Dashboard::on_actionChange_Username_triggered()
{
    uiUpdate();
    ui->usernameHasBeenChanged->setVisible(false);
    ui->passwordHasBeenChanged->setVisible(false);
    ui->tabWidget->setCurrentWidget(ui->settingsTab);
    ui->tabWidget->update();
}


void Dashboard::on_actionDelete_Account_triggered()
{
    uiUpdate();
    ui->usernameHasBeenChanged->setVisible(false);
    ui->passwordHasBeenChanged->setVisible(false);
    ui->tabWidget->setCurrentWidget(ui->settingsTab);
    ui->tabWidget->update();
}

