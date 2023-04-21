#ifndef OPTIONS_H
#define OPTIONS_H

#include <QColorDialog>
#include <QDialog>

#include "../Facade/Mediator/object_model.h"
#include "options_t.h"

namespace Ui {
class options;
}

namespace s21 {
/**
 * @brief Определение собственного класса Qt для изменения настроек класса
 * Options_t
 */
class options : public QDialog {
  Q_OBJECT

 public:
  explicit options(QWidget *parent = nullptr);  ///< Дефолтный конструктор

  ~options();  ///< Дефолтный деструктор

 private slots:
  void on_radioButton_central_clicked();

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
  Ui::options *ui;          ///< Указатель на окно ui
  Options_t settings_data;  ///< Экземпляр класса для отслеживания настроек
};

}  // namespace s21

#endif  // OPTIONS_H
