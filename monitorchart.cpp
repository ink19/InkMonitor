#include "monitorchart.h"

#include <QtCharts>
#include <QSplineSeries>
#include <QPalette>

MonitorChart::MonitorChart(QWidget *parent):
  QChartView(parent)
{
  QSplineSeries *spline_series = new QSplineSeries;
  spline_series->append(0, 6);
  spline_series->append(1, 12);
  spline_series->append(2, 100);
  spline_series->append(3, 2);
  spline_series->append(4, 4);
  spline_series->append(5, 10);
  chart_ = new QtCharts::QChart;
  chart_->addSeries(spline_series);
  chart_->legend()->hide();
  chart_->createDefaultAxes();
  
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(0, 0, 0, 0x20));
  this->setPalette(pal);
  
  chart_->setBackgroundVisible(false);
  
  this->setChart(chart_);
  this->setFixedHeight(200);
}
