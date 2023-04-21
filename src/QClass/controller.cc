#include "controller.h"

#include "ui_view.h"

using namespace s21;

Controller::Controller(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Controller),
      timer_(new QTimer),
      gif_(nullptr) {
  ui->setupUi(this);

  connect(timer_, SIGNAL(timeout()), this, SLOT(takeFrame()));
}

Controller::~Controller() {
  delete ui;
  delete timer_;
  delete gif_;
}

void Controller::on_actionClose_triggered() { close(); }

void Controller::on_button_open_path_clicked() {
  QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
                                              tr("Objects Files (*.obj)"));

  if (path.isEmpty()) {
    return;
  }
  ui->label_path->setText(path);
  ObjectModel &model_data = *ObjectModel::GetInstance();
  model_data.clear();

  try {
    model_data.OpenObject(path.toStdString());
    model_data.NormalizationAndCentralize();
  } catch (std::exception &e) {
    QMessageBox::warning(this, "Error", e.what());
  }
  auto size_models = model_data.size();
  ui->label_edges->setText("Facets : " + QString::number(size_models.second));
  ui->label_vertexes->setText("Vertexes : " +
                              QString::number(size_models.first / 3));
  ui->widget->update();
}

void Controller::on_button_jpeg_clicked() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.jpeg",
                                              "JPEG (*.jpeg)");
  if (file.isEmpty()) {
    return;
  }
  ui->widget->grabFramebuffer().save(file, NULL, 100);
}

void Controller::on_button_bmp_clicked() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.bmp",
                                              "BMP (*.bmp)");
  if (file.isEmpty()) {
    return;
  }
  ui->widget->grabFramebuffer().save(file, NULL, 100);
}

void Controller::on_button_gif_clicked() {
  ui->button_gif->setText("Gif is recording");
  delete gif_;
  gif_ = nullptr;
  gif_ = new QGifImage;
  timer_->start(100);
}

void Controller::takeFrame() {
  if (gif_->frameCount() < 100) {
    QImage frame = ui->widget->grabFramebuffer();
    gif_->addFrame(frame.scaled(640, 480), 0);
  } else {
    timer_->stop();
    ui->button_gif->setText("Recording is Finish");
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.gif",
                                                "GIF (*.gif)");
    gif_->save(file);
    ui->button_gif->setText("Record gif");
  }
}

void Controller::on_button_setting_clicked() {
  options options_form;
  options_form.exec();
  ui->widget->settings.LoadSettings();
  ui->widget->update();
}

void Controller::on_button_moving_clicked() {
  ObjectModel::GetInstance()->Move(ui->moving_x->value(), ObjectModel::xAxis);
  ObjectModel::GetInstance()->Move(ui->moving_y->value(), ObjectModel::yAxis);
  ObjectModel::GetInstance()->Move(ui->moving_z->value(), ObjectModel::zAxis);
  ui->widget->update();
}

void Controller::on_button_rotate_clicked() {
  ObjectModel::GetInstance()->Rotate(ui->rotate_x->value(), ObjectModel::xAxis);
  ObjectModel::GetInstance()->Rotate(ui->rotate_y->value(), ObjectModel::yAxis);
  ObjectModel::GetInstance()->Rotate(ui->rotate_z->value(), ObjectModel::zAxis);
  ui->widget->update();
}

void Controller::on_button_scaling_clicked() {
  ObjectModel::GetInstance()->Scale(ui->scaling->value());
  ui->widget->update();
}

void Controller::on_button_reset_position_clicked() {
  try {
    ObjectModel::GetInstance()->CentralizeAfterMove();
  } catch (std::exception &e) {
    QMessageBox::warning(this, "Error", e.what());
  }
  ui->widget->update();
}
