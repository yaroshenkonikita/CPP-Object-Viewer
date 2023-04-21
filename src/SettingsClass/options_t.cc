#include "options_t.h"

using namespace s21;

Options_t::Options_t() { LoadSettings(); }

void Options_t::LoadSettings() {
  projection_type = settings.value("projection_type", 0).toInt();
  edge_type = settings.value("edge_type", 0).toInt();
  vertex_type = settings.value("vertex_type", 0).toInt();
  background_color[0] = settings.value("background_color_red", 0.0).toFloat();
  background_color[1] = settings.value("background_color_green", 0.0).toFloat();
  background_color[2] = settings.value("background_color_blue", 0.0).toFloat();
  background_color[3] = settings.value("background_color_alpha", 1.0).toFloat();
  edge_color[0] = settings.value("edge_color_red", 170.0).toFloat();
  edge_color[1] = settings.value("edge_color_green", 0.0).toFloat();
  edge_color[2] = settings.value("edge_color_blue", 0.0).toFloat();
  edge_color[3] = settings.value("edge_color_alpha", 1.0).toFloat();
  vertex_color[0] = settings.value("vertex_color_red", 0.0).toFloat();
  vertex_color[1] = settings.value("vertex_color_green", 255.0).toFloat();
  vertex_color[2] = settings.value("vertex_color_blue", 0.0).toFloat();
  vertex_color[3] = settings.value("vertex_color_alpha", 1.0).toFloat();
  edge_width = settings.value("edge_width", 10).toInt();
  vertex_width = settings.value("vertex_width", 10).toInt();
  state_fill = settings.value("facet_type", false).toBool();
}

void Options_t::SaveSettings() {
  settings.setValue("projection_type", projection_type);
  settings.setValue("edge_type", edge_type);
  settings.setValue("vertex_type", vertex_type);
  settings.setValue("edge_color_red", edge_color[0]);
  settings.setValue("edge_color_green", edge_color[1]);
  settings.setValue("edge_color_blue", edge_color[2]);
  settings.setValue("edge_color_alpha", edge_color[3]);
  settings.setValue("vertex_color_red", vertex_color[0]);
  settings.setValue("vertex_color_green", vertex_color[1]);
  settings.setValue("vertex_color_blue", vertex_color[2]);
  settings.setValue("vertex_color_alpha", vertex_color[3]);
  settings.setValue("background_color_red", background_color[0]);
  settings.setValue("background_color_green", background_color[1]);
  settings.setValue("background_color_blue", background_color[2]);
  settings.setValue("background_color_alpha", background_color[3]);
  settings.setValue("edge_width", edge_width);
  settings.setValue("vertex_width", vertex_width);
  settings.setValue("facet_type", state_fill);
}
