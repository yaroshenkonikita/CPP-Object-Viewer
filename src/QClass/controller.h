#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <cstring>

#include "../SettingsClass/options.h"
#include "QtGifImage/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controller;
}
QT_END_NAMESPACE

namespace s21 {

class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(QWidget *parent = nullptr);

  ~Controller();

  Ui::Controller *ui;

 private:
  QTimer *timer_;
  QGifImage *gif_;

 private slots:
  void on_actionClose_triggered();

  void on_button_open_path_clicked();

  void on_button_jpeg_clicked();

  void on_button_bmp_clicked();

  void on_button_gif_clicked();

  void takeFrame();
  // установка значений по нажанию на соответствующую кнопку

  void on_button_setting_clicked();

  void on_button_moving_clicked();

  void on_button_rotate_clicked();

  void on_button_scaling_clicked();

  void on_button_reset_position_clicked();
};

}  // namespace s21

#endif  // CONTROLLER_H
