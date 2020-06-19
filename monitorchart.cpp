#include "monitorchart.h"

#include <QtCharts>
#include <QSplineSeries>
#include <QPalette>
#include <QTimer>
#include <algorithm>
#include <QProcess>

MonitorChart::MonitorChart(QWidget *parent):
  QChartView(parent)
{
  spline_series_ = new QSplineSeries;
  chart_ = new QtCharts::QChart;
  chart_->addSeries(spline_series_);
  chart_->legend()->hide();
  chart_->createDefaultAxes();
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(0, 0, 0, 0x20));
  this->setPalette(pal);
  
  chart_->setBackgroundVisible(false);
  chart_->axes(Qt::Horizontal).at(0)->setRange(-100, 0);
  chart_->axes(Qt::Horizontal).at(0)->hide();
  this->setChart(chart_);
  this->setFixedHeight(200);
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(temp_add_data()));
  
  timer_->start(400);
}

void MonitorChart::appendData(double data)
{
  spline_series_->append(now_time, data);
  qreal dwidth= chart_->plotArea().width()/(100);
  now_time += 1;
  chart_->scroll(dwidth, 0);
}

void MonitorChart::temp_add_data()
{
  QProcess p;
  p.start("sh", QStringList() << "/home/ink19/memratio.sh");
  p.waitForStarted();
  p.waitForFinished();
  double mem_ratio = QString::fromLocal8Bit(p.readAllStandardOutput()).toDouble();
  appendData(mem_ratio);
}
