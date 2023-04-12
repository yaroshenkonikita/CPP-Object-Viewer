#include "glview.h"

#define GL_SILENCE_DEPRECATION

glview ::glview(QWidget* parent) : QOpenGLWidget{parent} {}

void glview ::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LINE_STIPPLE);
}

void glview ::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //Блок отвечает за проекцию
  if (projection_type) {
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
  for (auto&model : ObjectModel::GetInstance()->models) {
      glVertexPointer(3, GL_DOUBLE, 0, model.vertexes.data());
      glClearColor(background_color[0], background_color[1], background_color[2],
                   background_color[3]);  // цвет заднего фона

      glColor3d(edge_color[0], edge_color[1], edge_color[2]);
      for (auto &facet : model.facets) {
          glDrawElements(GL_LINE_LOOP, (unsigned)facet.size(), GL_UNSIGNED_INT, facet.data());
      }
  }
  glLineWidth(edge_width);  // толщина ребра
  if (edge_type) {          //тип ребра
    glLineStipple(4, 0x1111);
  } else {
    glLineStipple(4, 0xFFFF);
  }
  if (vertex_type) {  // тип вершины
      auto size_models = ObjectModel::GetInstance()->size();
    if (vertex_type == 1) {
      glEnable(GL_POINT_SMOOTH);
      glColor3d(vertex_color[0], vertex_color[1], vertex_color[2]);
      glDrawArrays(GL_POINTS, 0, size_models.first);
      glPointSize(vertex_width);  // толщина вершины
      glDisable(GL_POINT_SMOOTH);
    } else {
      glColor3d(vertex_color[0], vertex_color[1], vertex_color[2]);
      glDrawArrays(GL_POINTS, 0, size_models.first);
      glPointSize(vertex_width);  // толщина вершины
    }
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glview::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void glview::mouseMoveEvent(QMouseEvent* mo) {
  double val_x = 0.001 / M_PI * (mo->pos().y() - mPos.y());
  ObjectModel::GetInstance()->Rotate(val_x, ObjectModel::xAxis);
  double val_y = 0.001 / M_PI * (mo->pos().x() - mPos.x());
  ObjectModel::GetInstance()->Rotate(val_y, ObjectModel::yAxis);
  update();
}

void glview::wheelEvent(QWheelEvent* event) {
  if (event->angleDelta().y() > 0) {
    ObjectModel::GetInstance()->Scale(0.9);
  } else {
    ObjectModel::GetInstance()->Scale(1.1);
  }
  update();
}
