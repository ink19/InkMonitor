#include "monitorchart.h"

#include <QtCharts>
#include <QSplineSeries>
#include <QPalette>
#include <QTimer>
#include <algorithm>
#include <QProcess>
#include "monitorconfig.h"

MonitorChart::MonitorChart(MonitorChartConfig &config, QWidget *parent):
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
  
  chart_->axes(Qt::Vertical).at(0)->setRange(config.min_, config.max_);

  
  this->setChart(chart_);
  this->setFixedHeight(200);
  process.start("sh", QStringList() << QString(MONITOR_TEMP_DIR) + "inkmonitor_loop.sh" << config.script_);
  process.waitForStarted();
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

MonitorChart::~MonitorChart()
{
  process.kill();
  process.waitForFinished();
}

void MonitorChart::temp_add_data()
{
  QString mem_ratio_s = QString::fromLocal8Bit(process.readAllStandardOutput());
  int begin = 0, end = -1;
  for (int loop_s = 0; loop_s < mem_ratio_s.length(); ++loop_s) {
    if (mem_ratio_s.at(loop_s) == '\n') {
      begin = end + 1;
      end = loop_s;
    }
  }
  double mem_ratio = mem_ratio_s.mid(begin, end - begin).toDouble();
  if (end == -1) {
    mem_ratio = last_value;
  } else {
    last_value = mem_ratio;
  }
  appendData(mem_ratio);
}

MonitorChartConfig::MonitorChartConfig(QString script, double min, double max):
  min_(min),
  max_(max)
{
  script_ = script;
  if (script == ":memory") {
    script_ = QString(MONITOR_TEMP_DIR) + "memratio.sh";
  }
  
  if (script == ":cpu") {
    script_ = QString(MONITOR_TEMP_DIR) + "cpuratio.sh";
  }
  
  if (script == ":random") {
    script_ = QString(MONITOR_TEMP_DIR) + "random.sh";
  }
}
