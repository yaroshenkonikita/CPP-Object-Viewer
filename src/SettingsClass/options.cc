#include "options.h"

#include "ui_options.h"

using namespace s21;

options::options(QWidget *parent) : QDialog(parent), ui(new Ui::options) {
  settings_data.LoadSettings();
  ui->setupUi(this);
  putTheValues();
}

options::~options() { delete ui; }

void options::putTheValues() {
  // Вписываем в окно подгруженные настройки
  if (settings_data.projection_type) {
    ui->radioButton_central->setChecked(true);
  } else {
    ui->radioButton_parallel->setChecked(true);
  }

  QString color_background(
      "background: rgb(" +
      QString::number(settings_data.background_color[0] * 255) + "," +
      QString::number(settings_data.background_color[1] * 255) + "," +
      QString::number(settings_data.background_color[2] * 255) + ")");
  ui->button_background->setStyleSheet(color_background);

  if (settings_data.edge_type) {
    ui->radioButton_dashed->setChecked(true);
  } else {
    ui->radioButton_solid->setChecked(true);
  }

  QString color_edges("background: rgb(" +
                      QString::number(settings_data.edge_color[0] * 255) + "," +
                      QString::number(settings_data.edge_color[1] * 255) + "," +
                      QString::number(settings_data.edge_color[2] * 255) + ")");
  ui->button_color_edges->setStyleSheet(color_edges);

  QString color_vertexes(
      "background: rgb(" +
      QString::number(settings_data.vertex_color[0] * 255) + "," +
      QString::number(settings_data.vertex_color[1] * 255) + "," +
      QString::number(settings_data.vertex_color[2] * 255) + ")");
  ui->button_color_vertexes->setStyleSheet(color_vertexes);

  switch (settings_data.vertex_type) {
    case 0:
      ui->radioButton_vertex_nope->setChecked(true);
      break;
    case 1:
      ui->radioButton_vertex_shere->setChecked(true);
      break;
    case 2:
      ui->radioButton_vertex_cube->setChecked(true);
      break;
  }

  ui->horizontalSlider_wigth_edges->setSliderPosition(settings_data.edge_width);
  ui->horizontalSlider_size_vertexes->setSliderPosition(
      settings_data.vertex_width);

  if (settings_data.state_fill) {
    ui->polygon_facets->setChecked(true);
  } else {
    ui->frame_facets->setChecked(true);
  }
}

void options::on_button_apply_clicked() {
  settings_data.SaveSettings();
  QWidget::close();
}

void options::on_button_cancel_clicked() { QWidget::close(); }

void options::on_button_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  if (!color.isValid()) {
    return;
  }
  settings_data.background_color[0] = color.redF();
  settings_data.background_color[1] = color.greenF();
  settings_data.background_color[2] = color.blueF();
  settings_data.background_color[3] = color.alphaF();
  QString color_background("background: rgb(" +
                           QString::number(color.redF() * 255) + "," +
                           QString::number(color.greenF() * 255) + "," +
                           QString::number(color.blueF() * 255) + ")");
  ui->button_background->setStyleSheet(color_background);
}

void options::on_button_color_vertexes_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  if (!color.isValid()) {
    return;
  }
  settings_data.vertex_color[0] = color.redF();
  settings_data.vertex_color[1] = color.greenF();
  settings_data.vertex_color[2] = color.blueF();
  settings_data.vertex_color[3] = color.alphaF();
  QString color_vertexes("background: rgb(" +
                         QString::number(color.redF() * 255) + "," +
                         QString::number(color.greenF() * 255) + "," +
                         QString::number(color.blueF() * 255) + ")");
  ui->button_color_vertexes->setStyleSheet(color_vertexes);
}

void options::on_button_color_edges_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  if (!color.isValid()) {
    return;
  }
  settings_data.edge_color[0] = color.redF();
  settings_data.edge_color[1] = color.greenF();
  settings_data.edge_color[2] = color.blueF();
  settings_data.edge_color[3] = color.alphaF();
  QString color_edges("background: rgb(" + QString::number(color.redF() * 255) +
                      "," + QString::number(color.greenF() * 255) + "," +
                      QString::number(color.blueF() * 255) + ")");
  ui->button_color_edges->setStyleSheet(color_edges);
}

void options::on_horizontalSlider_size_vertexes_sliderMoved(int position) {
  settings_data.vertex_width = position;
}

void options::on_horizontalSlider_wigth_edges_sliderMoved(int position) {
  settings_data.edge_width = position;
}

void options::on_radioButton_solid_clicked() { settings_data.edge_type = 0; }
void options::on_radioButton_dashed_clicked() { settings_data.edge_type = 1; }

void options::on_radioButton_vertex_shere_clicked() {
  settings_data.vertex_type = 1;
}
void options::on_radioButton_vertex_cube_clicked() {
  settings_data.vertex_type = 2;
}
void options::on_radioButton_vertex_nope_clicked() {
  settings_data.vertex_type = 0;
}

void options::on_radioButton_central_clicked() {
  settings_data.projection_type = 1;
}
void options::on_radioButton_parallel_clicked() {
  settings_data.projection_type = 0;
}

void options::on_frame_facets_clicked() { settings_data.state_fill = false; }

void options::on_polygon_facets_clicked() { settings_data.state_fill = true; }
