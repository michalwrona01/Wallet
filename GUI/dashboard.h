#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <string>
#include "QDate"
#include "transaction.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private:
    Ui::Dashboard *ui;

public:
    int userId;
    float budget;

    QString username;
    QString email;

    QString valueBudget;
    QString dateBudget;
    QString topicBudget;

    QDate dateAddReceipt;
    QString shopNameReceipt;
    QString companyNameReceipt;
    QString numberReceipt;
    QString numberNIPReceipt;
    QString priceReceipt;

    QString oldPassword;
    QString newPassword;
    QString newPasswordConfirm;

    QString passwordUsername;
    QString newUsername;



public:
    void setVariablesFromGui(int userId, std::string username, std::string email, float budget);

    QString idReceipt;

private slots:
    void on_actionAdd_Expense_triggered();
    void on_addTransactionButton_clicked();
    void on_valueBudgetEdit_textEdited(const QString &arg1);
    void on_topicBudgetEdit_textEdited(const QString &arg1);
    void on_calendarWidget_clicked(const QDate &date);
    void on_actionView_Dashboard_triggered();
    void on_chooseFilePushButton_clicked();
    void on_addReceiptPushButton_clicked();
    void on_shopNameLineEdit_textEdited(const QString &arg1);
    void on_companyNameLineEdit_textEdited(const QString &arg1);
    void on_NIP_LineEdit_textEdited(const QString &arg1);
    void on_priceReceiptLineEdit_textEdited(const QString &arg1);
    void on_addReceiptCalendarWidget_clicked(const QDate &date);
    void on_numberReceiptLineEdit_textEdited(const QString &arg1);
    void on_actionView_Statistics_triggered();
    void setReceiptsInView();
    void on_actionView_All_Receipts_triggered();
    void on_actionAdd_Receipt_triggered();
    void on_listWidget_currentTextChanged(const QString &currentText);
    void on_pushButtonDeleteCheckedId_clicked();

    void on_pushButtonChangePassword_clicked();

    void on_oldPassowordLineEdit_textEdited(const QString &arg1);

    void on_newPassword_textEdited(const QString &arg1);

    void on_newPasswordConfirm_textEdited(const QString &arg1);

    void on_passwordChangeUsername_textEdited(const QString &arg1);

    void on_newUsernameLineEdit_textEdited(const QString &arg1);

    void on_pushButtonChangeUsername_clicked();

    void on_pushButtonDeleteAccount_clicked();

    void on_actionLogout_triggered();

    void on_actionView_Delete_Receipt_triggered();

    void on_actionChange_Password_triggered();

    void on_actionChange_Username_triggered();

    void on_actionDelete_Account_triggered();

private:
    void updateUserNameButtonAndBudgetLabel();
    void setTransactionHistoryInListWidget();
    void setBudgetLabelValue(float amount);
    void uiUpdate();
    void sortHistoryBudgetByDate();
};

#endif // DASHBOARD_H
