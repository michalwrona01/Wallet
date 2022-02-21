#include "transaction.h"
#include <iostream>
#include <QtCharts>


std::string Transaction::getInformation()
{
    std::string allItemsInHistoryListWidgets = value + " | " + topic + " | " + date;

    return allItemsInHistoryListWidgets;
}

void Transaction::setTransaction(std::string value, std::string topic, std::string date)
{
    this->value = value;
    this->topic = topic;
    this->date = date;
}

QChartView* Transaction::drawPlot()
{
        QtCharts::QLineSeries *series_donations = new QtCharts::QLineSeries();
        QtCharts::QLineSeries *series_expenses = new QtCharts::QLineSeries();

        for(int i=0; i < transactionsPtr->length; i++)
        {
            QDate date = QDate::fromString(QString::fromStdString(transactionsPtr[i].date), "yyyy.MM.dd");
            float value = std::stof(transactionsPtr[i].value);
            QDateTime dateTime(date);

            if (value >= 0)
            {
                series_donations->append(dateTime.toMSecsSinceEpoch(), value);
                *series_donations << QPointF(dateTime.toMSecsSinceEpoch(), value);
            }
            else
            {
                series_donations->append(dateTime.toMSecsSinceEpoch(), value);
                *series_donations << QPointF(dateTime.toMSecsSinceEpoch(), value);
            }

        }

        QtCharts::QChart *chart = new QtCharts::QChart();

        QColor red("#ff0000");
        series_donations->setColor(red);

        chart->addSeries(series_donations);
        chart->addSeries(series_expenses);
        chart->legend()->hide();
        chart->setTitle("Plot of transactions");


        QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setTickCount(5);
        axisX->setFormat("MM.dd");
        axisX->setTitleText("Date");
        chart->addAxis(axisX, Qt::AlignBottom);
        series_donations->attachAxis(axisX);
        series_expenses->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Value");
        chart->addAxis(axisY, Qt::AlignLeft);
        series_donations->attachAxis(axisY);
        series_expenses->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        return chartView;
}
