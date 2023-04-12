#include "options.h"

#include "mainwindow.h"
#include "ui_options.h"

options::options(QWidget *parent) : QDialog(parent), ui(new Ui::options) {
  settings = new QSettings("3Danger_Masters", "3DViewer_v1", this);
  loadSettings();
  ui->setupUi(this);
}

options::~options() { delete ui; }

void options::saveSettings() {
  // задаем значения(имя настройки, значение)
  settings->setValue("projection_type", settings_data.projection_type);
  settings->setValue("edge_type", settings_data.edge_type);
  settings->setValue("vertex_type", settings_data.vertex_type);
  settings->setValue("edge_color_red", settings_data.edge_color[0]);
  settings->setValue("edge_color_green", settings_data.edge_color[1]);
  settings->setValue("edge_color_blue", settings_data.edge_color[2]);
  settings->setValue("edge_color_alpha", settings_data.edge_color[3]);
  settings->setValue("vertex_color_red", settings_data.vertex_color[0]);
  settings->setValue("vertex_color_green", settings_data.vertex_color[1]);
  settings->setValue("vertex_color_blue", settings_data.vertex_color[2]);
  settings->setValue("vertex_color_alpha", settings_data.vertex_color[3]);
  settings->setValue("background_color_red", settings_data.background_color[0]);
  settings->setValue("background_color_green", settings_data.background_color[1]);
  settings->setValue("background_color_blue", settings_data.background_color[2]);
  settings->setValue("background_color_alpha", settings_data.background_color[3]);
  settings->setValue("edge_width", settings_data.edge_width);
  settings->setValue("vertex_width", settings_data.vertex_width);
}

void options::loadSettings() {
  // выгружаем значения(имя настройки, значение по умолчанию(если не задано))
  settings_data.projection_type = settings->value("projection_type", 0).toInt();
  settings_data.edge_type = settings->value("edge_type", 0).toInt();
  settings_data.vertex_type = settings->value("vertex_type", 0).toInt();
  settings_data.background_color[0] = settings->value("background_color_red", 0.0).toFloat();
  settings_data.background_color[1] =
      settings->value("background_color_green", 0.0).toFloat();
  settings_data.background_color[2] = settings->value("background_color_blue", 0.0).toFloat();
  settings_data.background_color[3] =
      settings->value("background_color_alpha", 1.0).toFloat();
  settings_data.edge_color[0] = settings->value("edge_color_red", 255.0).toFloat();
  settings_data.edge_color[1] = settings->value("edge_color_green", 255.0).toFloat();
  settings_data.edge_color[2] = settings->value("edge_color_blue", 255.0).toFloat();
  settings_data.edge_color[3] = settings->value("edge_color_alpha", 1.0).toFloat();
  settings_data.vertex_color[0] = settings->value("vertex_color_red", 0.0).toFloat();
  settings_data.vertex_color[1] = settings->value("vertex_color_green", 255.0).toFloat();
  settings_data.vertex_color[2] = settings->value("vertex_color_blue", 0.0).toFloat();
  settings_data.vertex_color[3] = settings->value("vertex_color_alpha", 1.0).toFloat();
  settings_data.edge_width = settings->value("edge_width", 1.0).toFloat();
  settings_data.vertex_width = settings->value("vertex_width", 1.0).toFloat();
}

void options::on_button_apply_clicked() {
  saveSettings();
  QWidget::close();
}

void options::on_button_cancel_clicked() { QWidget::close(); }

void options::on_button_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  settings_data.background_color[0] = color.redF();
  settings_data.background_color[1] = color.greenF();
  settings_data.background_color[2] = color.blueF();
  settings_data.background_color[3] = color.alphaF();
  QString s("background: rgb(" + QString::number(color.redF() * 255) + "," +
            QString::number(color.greenF() * 255) + "," +
            QString::number(color.blueF() * 255) + ")");
  ui->button_background->setStyleSheet(s);
}

void options::on_button_color_vertexes_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  settings_data.vertex_color[0] = color.redF();
  settings_data.vertex_color[1] = color.greenF();
  settings_data.vertex_color[2] = color.blueF();
  settings_data.vertex_color[3] = color.alphaF();
  QString s("background: rgb(" + QString::number(color.redF() * 255) + "," +
            QString::number(color.greenF() * 255) + "," +
            QString::number(color.blueF() * 255) + ")");
  ui->button_color_vertexes->setStyleSheet(s);
}

void options::on_button_color_edges_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  settings_data.edge_color[0] = color.redF();
  settings_data.edge_color[1] = color.greenF();
  settings_data.edge_color[2] = color.blueF();
  settings_data.edge_color[3] = color.alphaF();
  QString s("background: rgb(" + QString::number(color.redF() * 255) + "," +
            QString::number(color.greenF() * 255) + "," +
            QString::number(color.blueF() * 255) + ")");
  ui->button_color_edges->setStyleSheet(s);
}

void options::on_horizontalSlider_size_vertexes_sliderMoved(int position) {
  settings_data.vertex_width = position;
}
void options::on_horizontalSlider_wigth_edges_sliderMoved(int position) {
  settings_data.edge_width = position;
}

void options::on_radioButton_solid_clicked() { settings_data.edge_type = 0; }
void options::on_radioButton_dashed_clicked() { settings_data.edge_type = 1; }

void options::on_radioButton_vertex_shere_clicked() { settings_data.vertex_type = 1; }
void options::on_radioButton_vertex_cube_clicked() { settings_data.vertex_type = 2; }
void options::on_radioButton_vertex_nope_clicked() { settings_data.vertex_type = 0; }

void options::on_radioButton_central_clicked() { settings_data.projection_type = 1; }
void options::on_radioButton_parallel_clicked() { settings_data.projection_type = 0; }
