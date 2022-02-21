#include "statistic.h"

#include <QtCharts>


Statistic::Statistic()
{

}

//QChartView* Statistic::drawPlot()
//{
//    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

//    for (int i=0; i < 5; i++)
//    {
//        series->append(i, i+5);
//    }

//    *series << QPointF(1, 5) << QPointF(2, 4) << QPointF(3, 3) << QPointF(2, 3) << QPointF(5, 3);

//    QtCharts::QChart *chart = new QtCharts::QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    chart->setTitle("Line Chart Example");

//    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);


//    return chartView;
//}
