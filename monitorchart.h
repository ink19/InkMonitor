#ifndef MONITORCHART_H
#define MONITORCHART_H
#include <QWidget>
#include <QtCharts>

class MonitorChart: public QtCharts::QChartView
{
  Q_OBJECT
public:
  MonitorChart(QWidget *parent = nullptr);

protected:
  QtCharts::QChart *chart_;
  
};

#endif // MONITORCHART_H
