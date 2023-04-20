#ifndef CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
#define CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

#include <float.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>

#include "../part_object.h"

namespace s21 {

class ObjectModel {
 public:
  typedef enum Axis { xAxis, yAxis, zAxis } AxisPoints;

  static ObjectModel* GetInstance();

  void OpenObject(std::string);

  void Move(double, AxisPoints);
  void Rotate(double, AxisPoints);
  void Scale(double);
  void RelocateOnStartPosition();

  bool empty();
  void clear();
  std::pair<std::size_t, std::size_t> size();

  std::vector<double>& GetVertexes(double, double);
  const std::vector<std::vector<unsigned>>& GetFacets();

 protected:
  static ObjectModel* instance;

  ObjectModel() = default;
  ~ObjectModel();

  PartObject model{};
  std::vector<double> prepare_data{};
  double move_coordinate[3]{};

  void ParsingFacet(std::vector<PartObject>&, std::string&, std::size_t&);
  void ParsingVertex(std::vector<PartObject>&, std::string&);
  void MoveReal(double, AxisPoints);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
