#ifndef CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
#define CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

#include <float.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>

#include "../part_object.h"

constexpr unsigned multithreadingMaxSize =
    4u;  ///< максимальное количество потоков которое может использовать
         ///< программа

namespace s21 {
/**
 * @brief Класс предоставляющий работу объекта с программой
 */
class ObjectModel {
 public:
  /**
   * @brief Enum для обозначения осей
   */
  typedef enum Axis {
    xAxis,  ///< Ось X
    yAxis,  ///< Ось Y
    zAxis   ///< Ось Z
  } AxisPoints;

  /**
   * @brief Функция получения единственного объекта(SingleTon)
   * @return shared указатель на объект
   */
  static std::shared_ptr<ObjectModel> GetInstance();

  /**
   * @brief Функция открытия и обработки параметров объекта из заданного файла
   * @param line Путь до файла
   */
  void OpenObject(std::string line);

  /**
   * @brief Функция фиктивного перемещения
   * @details Объект перемещается только после GetVertexes()
   * @param coordinate
   * @param axis
   */
  void Move(double coordinate, ObjectModel::AxisPoints axis);
  /**
   * @brief Поворот всех точек относительно заданной оси
   * @param angle число для поворота
   * @param axis заданная ось
   */
  void Rotate(double angle, ObjectModel::Axis axis);
  /**
   * @brief Умножить каждую ось каждой точки на заданное число
   * @param coordinate число для умножения
   */
  void Scale(double coordinate);
  /**
   * @brief Сброс переменной отвечающую за перемещение объекта в пространстве
   */
  void CentralizeAfterMove();
  /**
   * @brief Перевод вершин объекта в объем 1x1x1 установка в центр координат
   */
  void NormalizationAndCentralize();

  /**
   * @brief Функция проверяет объект на пустоту
   * @return true если пуст, false в обратном
   */
  bool empty();
  /**
   * @brief Очистка векторов вершин и faсets.
   */
  void clear();
  /**
   * @brief Функция возвращает количество вершин и fasets
   * @return пара <размер вершин, размер faсets>
   */
  std::pair<std::size_t, std::size_t> size();

  /**
   * @brief Функция подгатавливает данные фершин для OpenGL
   * @details Функция берет исходные данные вершин, изменяет все вершины под
   * Move так как он переносить только фиктивно и маштабирует под размер экрана.
   * Маштабирование сделано из-за виджета OpenGL который адаптируется под размер
   * экрана только один раз. Функция занимает сложность прохождения по всему
   * массиву вершин.
   * @param width ширина экрана
   * @param height высота экрана
   * @return вектор вершин правильной ориентации в пространстве
   */
  const std::vector<double> &GetVertexes(double width = 1, double height = 1);
  /**
   * @brief Функция возвращающая исходные faсets
   * @return const std::vector<std::vector<unsigned>>&
   */
  const std::vector<std::vector<unsigned>> &GetFacets();

  ObjectModel(const ObjectModel &) =
      delete;  ///< Удаление конструктора копирования
  ObjectModel(ObjectModel &&) = delete;  ///< Удаление конструктора переноса

  ObjectModel &operator=(const ObjectModel &) =
      delete;  ///< Удаление оператора копирования
  ObjectModel &operator=(ObjectModel &&) =
      delete;  ///< Удаление оператора переноса

 private:
  ObjectModel() = default;  ///< Дефолтный конструктор, приватный для SingleTon

  PartObject model{};  ///< Все исходные данные об объекте
  std::vector<double>
      prepare_data{};  ///< Переменная хранящая вершины после вызова GetVertexes
  double move_coordinate[3]{};  ///< Переменная для хранения перемешений
                                ///< задаваемых во время работы с объектом

  /**
   * @brief Функция для обработки линии facet
   * @param models объект для сохранения преобразованной строки
   * @param line строка для обработки
   * @param position_old_vertexes количество обработанных вершин для
   * синхронизации с относительными индексами в facet
   */
  void ParsingFacet(std::vector<PartObject> &models, std::string &line,
                    std::size_t &position_old_vertexes);
  /**
   * @brief Функция для обработки линии вершины
   * @param models объект для сохранения преобразованной строки
   * @param line строка для обработки
   */
  void ParsingVertex(std::vector<PartObject> &models, std::string &line);
  /**
   * @brief Функция поворота объекта
   * @details Функция перемешает объект в исходных данных
   * Используется для централизации
   * @param coordinate количество перемещения объекта
   * @param axis выбранная координата для перемещения
   */
  void MoveReal(double coordinate, ObjectModel::AxisPoints axis);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
