#include "../Mediator/object_model.h"

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

const std::vector<double>& ObjectModel::GetVertexes() { return model.vertexes; }

const std::vector<std::vector<unsigned>>& ObjectModel::GetFacets() {
  return model.facets;
}
