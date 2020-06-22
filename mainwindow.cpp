#include "mainwindow.h"
#include "monitorconfig.h"
#include <QPaintEvent>
#include <QPainter>
#include "monitorchart.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenu>
#include <QAction>
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  initScript();
  //setWindowFlag(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
  this->resize(800, 600);
  QScrollArea *scroll_area = new QScrollArea(this);
  this->setCentralWidget(scroll_area);
  widget_ = new MainWidget (scroll_area); 
  scroll_area->setWidget(widget_);
  scroll_area->setAttribute(Qt::WA_TranslucentBackground);
  scroll_area->setWidgetResizable(true);
  widget_->setAttribute(Qt::WA_TranslucentBackground);
  
  
  for (auto chart_config : this->config_.charts_config_) {
    widget_->appendChart(new MonitorChart(chart_config, widget_));
  }
}

int MainWindow::initScript()
{
  QDir Monitor;
  if (!Monitor.exists(MONITOR_TEMP_DIR)) {
    Monitor.mkdir(MONITOR_TEMP_DIR);
  }
  
  if (!QFile::exists(QString(MONITOR_TEMP_DIR) + "inkmonitor_loop.sh")) {
    QFile::copy(":/script/inkmonitor_loop.sh", QString(MONITOR_TEMP_DIR) + "inkmonitor_loop.sh");
  }
  
  if (!QFile::exists(QString(MONITOR_TEMP_DIR) + "memratio.sh")) {
    QFile::copy(":/script/memratio.sh", QString(MONITOR_TEMP_DIR) + "memratio.sh");
  }
  
  if (!QFile::exists(QString(MONITOR_TEMP_DIR) + "cpuratio.sh")) {
    QFile::copy(":/script/cpuratio.sh", QString(MONITOR_TEMP_DIR) + "cpuratio.sh");
  }
  
  if (!QFile::exists(QString(MONITOR_TEMP_DIR) + "random.sh")) {
    QFile::copy(":/script/random.sh", QString(MONITOR_TEMP_DIR) + "random.sh");
  }
  return 0;
}

MainWindow::~MainWindow()
{
  
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
      qDebug() << "Clicked";
      is_left_pressed = true;
      m_startPoint = frameGeometry().topLeft() - event->globalPos();
    } else if (event->button() == Qt::RightButton) {
      QMenu right_menu;
      QAction *p_title_button = new QAction(tr("标题栏"), &right_menu);
      QAction *p_on_top = new QAction(tr("置顶"), &right_menu);
      p_on_top->setCheckable(true);
      p_title_button->setCheckable(true);
      
      if (this->is_on_top) {
        p_on_top->setChecked(true);
      }
      
      if (this->is_titlebar_show) {
        p_title_button->setChecked(true);
      }
      connect(p_title_button, SIGNAL(triggered()), this, SLOT(switchTitleVisible()));
      connect(p_on_top, SIGNAL(triggered()), this, SLOT(switchOnTop()));
      
      if (is_on_top) {
        p_title_button->setEnabled(false);
      }
      
      right_menu.addAction(p_title_button);
      right_menu.addAction(p_on_top);
      
      right_menu.exec(cursor().pos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    qDebug() << "Released";
    is_left_pressed = false;
  }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (is_left_pressed) {
      
      this->move(event->globalPos() + m_startPoint);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  this->widget_->resize(event->size().width(), this->widget_->height());
}

void MainWindow::switchTitleVisible()
{
  if (is_titlebar_show) {
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->show();
    is_titlebar_show = false;
  } else {
    setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
    this->show();
    is_titlebar_show = true;
  }
}

void MainWindow::switchOnTop()
{
  if (!is_on_top) {
    setWindowFlags(windowFlags()|Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint);
    this->show();
    is_on_top = true;
  } else {
    setWindowFlags(windowFlags() & ~(Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint));
    this->show();
    is_on_top = false;
  }
}

MainWidget::MainWidget(QWidget *parent) :
  QWidget(parent)
{
  QVBoxLayout *layout_ = new QVBoxLayout();
  this->setLayout(layout_);
}

int MainWidget::appendChart(MonitorChart *chart)
{
  charts_.push_back(chart);
  this->layout()->addWidget(chart);
  return 0;
}

void MainWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
 //   painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(this->rect(), QColor(0, 0, 0, 0x20));
}
