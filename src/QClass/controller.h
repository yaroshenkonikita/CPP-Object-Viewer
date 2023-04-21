#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <cstring>

#include "../GIFCreation/gifImage/qgifimage.h"
#include "../SettingsClass/options.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controller;
}
QT_END_NAMESPACE

namespace s21 {
/**
 * @brief Класс по работе между ObjectModel и UI
 */
class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(QWidget *parent = nullptr);  ///< Дефолтный конструктор

  ~Controller();  ///< Дефолтный деструктор

  Ui::Controller *ui;  ///< Указатель на окно ui

 private:
  QTimer *timer_;  ///< Указатель на таймер для Gif
  QGifImage *gif_;  /// Указатель на класс QGifImage для создания Gif

 private slots:
  void on_actionClose_triggered();

  void on_button_open_path_clicked();

  void on_button_jpeg_clicked();

  void on_button_bmp_clicked();

  void on_button_gif_clicked();

  void takeFrame();

  void on_button_setting_clicked();

  void on_button_moving_clicked();

  void on_button_rotate_clicked();

  void on_button_scaling_clicked();

  void on_button_reset_position_clicked();
};

}  // namespace s21

#endif  // CONTROLLER_H
