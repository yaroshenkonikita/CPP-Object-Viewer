#include "controller.h"
#include "ui_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      timer_(new QTimer),
      gif_(nullptr) {
  ui->setupUi(this);

  connect(timer_, SIGNAL(timeout()), this, SLOT(takeFrame()));
  settings = new QSettings("3Danger_Masters", "3DViewer_v1", this);
  load_Settings();
}

MainWindow::~MainWindow() {
  delete ui;
  delete timer_;
}

void MainWindow::load_Settings() {
  // выгружаем значения(имя настройки, значение по умолчанию(если не задано))
  ui->widget->settings.projection_type = settings->value("projection_type", 0).toInt();
  ui->widget->settings.edge_type = settings->value("edge_type", 0).toInt();
  ui->widget->settings.vertex_type = settings->value("vertex_type", 0).toInt();
  ui->widget->settings.background_color[0] =
      settings->value("background_color_red", 0.0).toFloat();
  ui->widget->settings.background_color[1] =
      settings->value("background_color_green", 0.0).toFloat();
  ui->widget->settings.background_color[2] =
      settings->value("background_color_blue", 0.0).toFloat();
  ui->widget->settings.background_color[3] =
      settings->value("background_color_alpha", 1.0).toFloat();
  ui->widget->settings.edge_color[0] =
      settings->value("edge_color_red", 255.0).toFloat();
  ui->widget->settings.edge_color[1] =
      settings->value("edge_color_green", 255.0).toFloat();
  ui->widget->settings.edge_color[2] =
      settings->value("edge_color_blue", 255.0).toFloat();
  ui->widget->settings.edge_color[3] =
      settings->value("edge_color_alpha", 1.0).toFloat();
  ui->widget->settings.vertex_color[0] =
      settings->value("vertex_color_red", 0.0).toFloat();
  ui->widget->settings.vertex_color[1] =
      settings->value("vertex_color_green", 255.0).toFloat();
  ui->widget->settings.vertex_color[2] =
      settings->value("vertex_color_blue", 0.0).toFloat();
  ui->widget->settings.vertex_color[3] =
      settings->value("vertex_color_alpha", 1.0).toFloat();
  ui->widget->settings.edge_width = settings->value("edge_width", 1.0).toFloat();
  ui->widget->settings.vertex_width = settings->value("vertex_width", 1.0).toFloat();
  ui->widget->settings.state_fill = settings->value("facet_type", false).toBool();
}

void MainWindow::on_actionClose_triggered() { close(); }

void MainWindow::on_button_open_path_clicked() {
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
  } catch (std::exception &e) {
      QMessageBox::warning(this, "Error",
                                 e.what());
  }
  auto size_models = model_data.size();
  ui->label_edges->setText("Facets : " + QString::number(size_models.second));
  ui->label_vertexes->setText("Vertexes : " + QString::number(size_models.first / 3));
  ui->widget->update();
}

void MainWindow::on_button_jpeg_clicked() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.jpeg",
                                              "JPEG (*.jpeg)");
  ui->widget->grabFramebuffer().save(file, NULL, 100);
}

void MainWindow::on_button_bmp_clicked() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.bmp",
                                              "BMP (*.bmp)");
  ui->widget->grabFramebuffer().save(file, NULL, 100);
}

void MainWindow::on_button_gif_clicked() {
  ui->button_gif->setText("Gif is recording");
  gif_ = new QGifImage;
  timer_->start(100);
}

void MainWindow::takeFrame() {
  if (gif_->frameCount() < 50) {
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

void MainWindow::on_button_setting_clicked() {
  options options_form;
  options_form.setWindowTitle("Settings");
  options_form.exec();
  load_Settings();
  ui->widget->update();
}

void MainWindow::on_button_moving_clicked() {
    ObjectModel::GetInstance()->Move(ui->moving_x->value(), ObjectModel::xAxis);
    ObjectModel::GetInstance()->Move(ui->moving_y->value(), ObjectModel::yAxis);
    ObjectModel::GetInstance()->Move(ui->moving_z->value(), ObjectModel::zAxis);
    ui->widget->update();
}


void MainWindow::on_button_rotate_clicked() {
    ObjectModel::GetInstance()->Rotate(ui->rotate_x->value(), ObjectModel::xAxis);
    ObjectModel::GetInstance()->Rotate(ui->rotate_y->value(), ObjectModel::yAxis);
    ObjectModel::GetInstance()->Rotate(ui->rotate_z->value(), ObjectModel::zAxis);
    ui->widget->update();
}


void MainWindow::on_button_scaling_clicked() {
    ObjectModel::GetInstance()->Scale(ui->scaling->value());
    ui->widget->update();
}


void MainWindow::on_button_reset_position_clicked() {
    ObjectModel::GetInstance()->RelocateOnStartPosition();
    ui->widget->update();
}

