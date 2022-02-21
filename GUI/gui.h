#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <nlohmann/json.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

using json = nlohmann::json;

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui();

private slots:
    void on_emailLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_loginPushButton_clicked();

    void on_herePushButton_clicked();

private:
    Ui::Gui *ui;

public:
    QString email;
    QString password;
    json userData;
};
#endif // GUI_H
