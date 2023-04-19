#include "../Mediator/object_model.h"

using namespace s21;

std::pair<std::size_t, std::size_t> ObjectModel::size() {
  return {model.vertexes.size(), model.facets.size()};
}

bool ObjectModel::empty() {
  return model.vertexes.empty() || model.facets.empty();
}

void ObjectModel::clear() {
  model.facets.clear();
  model.vertexes.clear();
}

std::vector<double> &ObjectModel::GetVertexes() {
    prepare_data.clear();
    std::copy(model.vertexes.begin(), model.vertexes.end(), std::back_inserter(prepare_data));
    for (std::size_t index = 0; index < prepare_data.size(); index += 3) {
        prepare_data[index + xAxis] += move_coordinate[xAxis];
        prepare_data[index + yAxis] += move_coordinate[yAxis];
        prepare_data[index + zAxis] += move_coordinate[zAxis];
    }
    return prepare_data;
}

const std::vector<std::vector<unsigned>>& ObjectModel::GetFacets() {
  return model.facets;
}
