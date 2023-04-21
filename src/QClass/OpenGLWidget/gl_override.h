#ifndef GL_CONTROLLER_H
#define GL_CONTROLLER_H

#define GL_SILENCE_DEPRECATION
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <cmath>

#include "../../Facade/Mediator/object_model.h"
#include "../../SettingsClass/options_t.h"

/**
 * @brief Класс наследуемый от QOpenGLWidget для переопределения функций по
 * работе с объектом
 */
class QOpenGLWidgetOverride : public QOpenGLWidget {
  Q_OBJECT
 public:
  QPoint mPos{};  ///< Последняя позиция мышки
  s21::ObjectModel &object =
      *s21::ObjectModel::GetInstance();  ///< Получение ссылки на SingleTon
                                         ///< объект

  QOpenGLWidgetOverride(QWidget *parent = nullptr);  ///< Дефолтный конструктор

  /**
   * @brief Перегрузка метода initializeGL для инициализации OpenGL в виджете
   */
  void initializeGL() override;
  /**
   * @brief Перегрузка метода paintGL для правильной отрисовки объекта на
   * виджете
   */
  void paintGL() override;

  /**
   * @brief Функция для сохранения позиции мышки на нажатие в виджет
   * @param event указатель на данные мышки
   */
  void mousePressEvent(QMouseEvent *mouse) override;
  /**
   * @brief Функция для вражения объекта по данным изменения позиций мышки
   * @param event указатель на данные мышки
   */
  void mouseMoveEvent(QMouseEvent *mouse) override;
  /**
   * @brief Функция для увеличения и уменьшения объекта по кручению колесика
   * мышки
   * @param event указатель на данные мышки
   */
  void wheelEvent(QWheelEvent *mouse) override;
  s21::Options_t settings;  ///< Экземпляр класса настроек где хранятся данные
                            ///< по настройкам объекта
};

#endif  // GL_CONTROLLER_H
