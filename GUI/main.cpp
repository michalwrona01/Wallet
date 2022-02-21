#include "gui.h"

#include <QApplication>
#include <QtCharts>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui w;
    w.show();
    return a.exec();


}
