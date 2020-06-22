#include "monitorconfig.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>

MonitorConfig::MonitorConfig()
{
  QDir dir;
  QString config_dir = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.config/ink_monitor/";
  if (!dir.exists(config_dir)) {
    dir.mkdir(config_dir);
  }
  
  if (!QFile::exists(config_dir + "config.json")) {
    QFile::copy(":/config/config.json", config_dir + "config.json");
  }
  
  QFile json_file(config_dir + "config.json");
  json_file.open(QIODevice::ReadOnly);
  QJsonDocument json_doc = QJsonDocument::fromJson(json_file.readAll());
  json_file.close();
  
  QJsonArray monitor_json_arr = json_doc.object().value("monitor").toArray();
  
  for (auto monitor_json : monitor_json_arr) {
    auto monitor_obj = monitor_json.toObject();
    charts_config_.push_back(MonitorChartConfig(monitor_obj.value("script").toString(), monitor_obj.value("min").toDouble(), monitor_obj.value("max").toDouble()));
  }
}
