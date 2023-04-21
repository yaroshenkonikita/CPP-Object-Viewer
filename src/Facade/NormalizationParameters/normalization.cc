#include "../Mediator/object_model.h"

using namespace s21;

void ObjectModel::NormalizationAndCentralize() {
  if (model.vertexes.empty()) {
    throw std::logic_error("Can't relocate. Haven't exist model");
  }
  double positionAxis[6] = {DBL_MAX,  DBL_MAX,  DBL_MAX,
                            -DBL_MAX, -DBL_MAX, -DBL_MAX};
  for (std::size_t index = 0; index < model.vertexes.size(); index += 3) {
    positionAxis[xAxis] =
        std::min(positionAxis[xAxis], model.vertexes[index + xAxis]);
    positionAxis[yAxis] =
        std::min(positionAxis[yAxis], model.vertexes[index + yAxis]);
    positionAxis[zAxis] =
        std::min(positionAxis[zAxis], model.vertexes[index + zAxis]);
    positionAxis[xAxis + 3] =
        std::max(positionAxis[xAxis + 3], model.vertexes[index + xAxis]);
    positionAxis[yAxis + 3] =
        std::max(positionAxis[yAxis + 3], model.vertexes[index + yAxis]);
    positionAxis[zAxis + 3] =
        std::max(positionAxis[zAxis + 3], model.vertexes[index + zAxis]);
  }
  double deltaAxis[3] = {positionAxis[xAxis + 3] - positionAxis[xAxis],
                         positionAxis[yAxis + 3] - positionAxis[yAxis],
                         positionAxis[zAxis + 3] - positionAxis[zAxis]};
  MoveReal(-(positionAxis[xAxis] + deltaAxis[xAxis] / 2), xAxis);
  MoveReal(-(positionAxis[yAxis] + deltaAxis[yAxis] / 2), yAxis);
  MoveReal(-(positionAxis[zAxis] + deltaAxis[zAxis] / 2), zAxis);
  Scale(100 / std::max(std::max(deltaAxis[xAxis], deltaAxis[yAxis]),
                       deltaAxis[zAxis]));
  move_coordinate[xAxis] = move_coordinate[yAxis] = move_coordinate[zAxis] =
      0.f;
}

void ObjectModel::CentralizeAfterMove() {
  move_coordinate[xAxis] = move_coordinate[yAxis] = move_coordinate[zAxis] =
      0.f;
}