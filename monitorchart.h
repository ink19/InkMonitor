#ifndef MONITORCHART_H
#define MONITORCHART_H
#include <QWidget>
#include <QtCharts>
#include <QTimer>
#include <QSplineSeries>
class MonitorChart: public QChartView
{
  Q_OBJECT
public:
  MonitorChart(QWidget *parent = nullptr);
  void appendData(double data);

private:
  QChart *chart_;
  QTimer *timer_;
  QSplineSeries *spline_series_;
  int now_time = 0;
private slots:
  void temp_add_data();
};

#endif // MONITORCHART_H
