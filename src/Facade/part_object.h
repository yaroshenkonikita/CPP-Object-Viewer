#ifndef CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
#define CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H

#include <vector>

struct PartObject {
  std::vector<std::vector<unsigned>> facets{};
  std::vector<double> vertexes{};
};

#endif  // CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
