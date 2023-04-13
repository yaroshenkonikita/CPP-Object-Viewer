#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QColorDialog>
#include <QSettings>
#include "ObjectModel.h"

namespace Ui {
class options;
}

class options : public QDialog {
  Q_OBJECT

 public:
  explicit options(QWidget *parent = nullptr);
  ~options();
  QSettings *settings;

  Options_t settings_data;
 private slots:
  void on_radioButton_central_clicked();
  void saveSettings();
  void loadSettings();
  void putTheValues();

  void on_button_apply_clicked();
  void on_button_cancel_clicked();
  void on_radioButton_parallel_clicked();

  void on_button_background_clicked();

  void on_button_color_vertexes_clicked();
  void on_button_color_edges_clicked();

  void on_horizontalSlider_size_vertexes_sliderMoved(int position);
  void on_horizontalSlider_wigth_edges_sliderMoved(int position);

  void on_radioButton_solid_clicked();
  void on_radioButton_dashed_clicked();

  void on_radioButton_vertex_shere_clicked();
  void on_radioButton_vertex_cube_clicked();
  void on_radioButton_vertex_nope_clicked();

  void on_frame_facets_clicked();

  void on_polygon_facets_clicked();

private:
  Ui::options *ui;
};

#endif  // OPTIONS_H
