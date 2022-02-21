#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <QDate>
#include <QtCharts>


class Transaction
{
public:
    std::string value;
    std::string topic;
    std::string date;
    int length;
public:
    Transaction *transactionsPtr=nullptr;

public:
    std::string getInformation();
    void setTransaction(std::string value, std::string topic, std::string date);
    QChartView *drawPlot();
//

};

#endif // TRANSACTION_H
