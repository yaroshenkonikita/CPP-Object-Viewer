#ifndef CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
#define CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H

#include <vector>

namespace s21 {
/**
 * @brief Класс для хранения данных об Объекте
 */
struct PartObject {
  std::vector<std::vector<unsigned>> facets{};  ///< Вектор фигур
  std::vector<double> vertexes{};               ///< Вектор вершин
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
