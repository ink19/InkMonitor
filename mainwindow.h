#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPoint> 
#include "monitorchart.h"
#include <QVector>

class MainWidget : public QWidget {
public:
  MainWidget(QWidget *parent = nullptr);
  int appendChart(MonitorChart *chart);
private:
  QVector<MonitorChart *> charts_;
  void paintEvent(QPaintEvent *) override;
};

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
private:
  MainWidget *widget_;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  
  QPoint m_startPoint;
  bool is_left_pressed = false;
  bool is_titlebar_show = true;
  bool is_on_top = false;
private slots:
  void switchTitleVisible();
  void switchOnTop();
};
#endif // MAINWINDOW_H
