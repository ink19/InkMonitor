#ifndef MONITORCONFIG_H
#define MONITORCONFIG_H

#include "monitorchart.h"
#include <QVector>
#define MONITOR_TEMP_DIR "/tmp/monitor/"

class MonitorConfig
{
public:
  MonitorConfig();
  QVector<MonitorChartConfig> charts_config_;
};

#endif // MONITORCONFIG_H
