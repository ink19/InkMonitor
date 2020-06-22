#ifndef MONITORCHART_H
#define MONITORCHART_H
#include <QWidget>
#include <QtCharts>
#include <QTimer>
#include <QSplineSeries>
#include <QProcess>

class MonitorChartConfig {
public:
  double min_;
  double max_;
  QString script_;
  MonitorChartConfig(QString script, double min, double max);
};

class MonitorChart: public QChartView
{
  Q_OBJECT
public:
  MonitorChart(MonitorChartConfig &config, QWidget *parent = nullptr);
  void appendData(double data);
  ~MonitorChart();
private:
  double last_value = 0;
  QProcess process;
  QChart *chart_;
  QTimer *timer_;
  QSplineSeries *spline_series_;
  int now_time = 0;
private slots:
  void temp_add_data();
};

#endif // MONITORCHART_H
