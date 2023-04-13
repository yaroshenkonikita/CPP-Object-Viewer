#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>
#include <cstring>

#include <QSettings>
#include "QtGifImage/gifimage/qgifimage.h"
#include "ObjectModel.h"
#include "options.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString __buffpath;
  Ui::MainWindow *ui;
  QSettings *settings;  // настройки

 private:
  QTimer *_timer;
  QGifImage *_gif;

 private slots:
  void on_actionClose_triggered();
  void on_button_open_path_clicked();
  void on_button_jpeg_clicked();
  void on_button_bmp_clicked();
  void on_button_gif_clicked();
  void takeFrame();
  // установка значений по нажанию на соответствующую кнопку

  void on_button_setting_clicked();
  void load_Settings();  // подгрузить настройки

  void on_button_moving_clicked();
  void on_button_rotate_clicked();
  void on_button_scaling_clicked();
};

#endif  // MAINWINDOW_H
