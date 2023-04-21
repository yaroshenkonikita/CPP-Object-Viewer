#include "gl_override.h"

#define GL_SILENCE_DEPRECATION

QOpenGLWidgetOverride::QOpenGLWidgetOverride(QWidget* parent)
    : QOpenGLWidget{parent} {}

void QOpenGLWidgetOverride::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LINE_STIPPLE);
}

void QOpenGLWidgetOverride::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glOrtho(-2.0, 2.0, -2.0, 2.0, -5, 5);
  //Блок отвечает за проекцию
  if (settings.projection_type) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fov = 60.0 * M_PI / 180;  // 60 угол в градусах
    float heapHeight = 1 / (2 * tan(fov / 2));
    glFrustum(-1, 1, -1, 1, heapHeight, 4);
    glTranslated(0, 0, -heapHeight * 2);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0,
                  object.GetVertexes(this->width(), this->height()).data());
  glClearColor(settings.background_color[0], settings.background_color[1],
               settings.background_color[2],
               settings.background_color[3]);  // цвет заднего фона

  glColor3d(settings.edge_color[0], settings.edge_color[1],
            settings.edge_color[2]);
  auto gl_state_poligons = GL_LINE_LOOP;
  if (settings.state_fill) {
    gl_state_poligons = GL_POLYGON;
  }
  for (auto& facet : object.GetFacets()) {
    glDrawElements(gl_state_poligons, facet.size(), GL_UNSIGNED_INT,
                   facet.data());
  }
  glLineWidth(settings.edge_width);  // толщина ребра
  if (settings.edge_type) {          //тип ребра
    glLineStipple(4, 0x1111);
  } else {
    glLineStipple(4, 0xFFFF);
  }
  if (settings.vertex_type) {  // тип вершины
    auto size_models = object.size();
    if (settings.vertex_type == 1) {
      glEnable(GL_POINT_SMOOTH);
      glColor3d(settings.vertex_color[0], settings.vertex_color[1],
                settings.vertex_color[2]);
      glDrawArrays(GL_POINTS, 0, size_models.first / 3);
      glPointSize(settings.vertex_width);  // толщина вершины
      glDisable(GL_POINT_SMOOTH);
    } else {
      glColor3d(settings.vertex_color[0], settings.vertex_color[1],
                settings.vertex_color[2]);
      glDrawArrays(GL_POINTS, 0, size_models.first / 3);
      glPointSize(settings.vertex_width);  // толщина вершины
    }
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void QOpenGLWidgetOverride::mousePressEvent(QMouseEvent* mouse) {
  mPos = mouse->pos();
}

void QOpenGLWidgetOverride::mouseMoveEvent(QMouseEvent* mouse) {
  double val_x = 0.013 / M_PI * (mouse->pos().y() - mPos.y());
  object.Rotate(val_x, s21::ObjectModel::xAxis);
  double val_y = 0.013 / M_PI * (mouse->pos().x() - mPos.x());
  object.Rotate(val_y, s21::ObjectModel::yAxis);
  mPos = mouse->pos();
  update();
}

void QOpenGLWidgetOverride::wheelEvent(QWheelEvent* mouse) {
  if (mouse->angleDelta().y() > 0) {
    object.Scale(103);
  } else {
    object.Scale(97);
  }
  update();
}
