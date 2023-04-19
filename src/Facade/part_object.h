#ifndef CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
#define CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H

#include <vector>
namespace s21 {

struct PartObject {
  std::vector<std::vector<unsigned>> facets{};
  std::vector<double> vertexes{};
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
