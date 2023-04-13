#ifndef GL_CONTROLLER_H
#define GL_CONTROLLER_H

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QWheelEvent>
#include <QOpenGLWidget>
#include <cmath>
#include "object_model.h"


#define GL_SILENCE_DEPRECATION

class GLController : public QOpenGLWidget {
  Q_OBJECT
 public:
  QPoint mPos;
  ObjectModel &object = *ObjectModel::GetInstance();
  int scaleVal = 1;
  int prev_scale = 1;
  GLController(QWidget *parent = nullptr);

  void initializeGL() override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;
  Options_t settings;
};

#endif  // GL_CONTROLLER_H
