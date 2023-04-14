#include "../Mediator/object_model.h"

void ObjectModel::ParsingVertex(std::vector<PartObject> &models,
                                std::string &line,
                                std::size_t &position_old_vertexes) {
  if (models.back().facets.size()) {
    position_old_vertexes += models.back().vertexes.size() / 3;
    models.emplace_back();
  }
  int count_vertex{};
  for (unsigned i{}; i < line.length(); ++i) {
    if (std::isdigit(line[i]) || line[i] == '-') {
      std::size_t index_stod{};
      models.back().vertexes.push_back(
          std::stod(line.c_str() + i, &index_stod));
      i += index_stod;
      ++count_vertex;
    }
  }
  if (count_vertex != 3) {
    throw std::invalid_argument("Invalid file .obj");
  }
}

void ObjectModel::ParsingFacet(std::vector<PartObject> &models,
                               std::string &line,
                               std::size_t &position_old_vertexes) {
  if (models.empty() || models.back().vertexes.empty()) {
    throw std::invalid_argument("Invalid file .obj");
  }
  char *token = std::strtok(line.data() + 1, " ");
  std::vector<unsigned> face{};
  while (token) {
    long tmp = std::stol(token);
    if (tmp < 0) {
      face.push_back(std::abs(tmp) - 1 + position_old_vertexes);
    } else {
      face.push_back(tmp - 1);
    }
    token = strtok(nullptr, " ");
  }
  models.back().facets.push_back(face);
}

void ObjectModel::OpenObject(std::string line) {
  std::ifstream file_in(line);
  std::vector<PartObject> models = {PartObject()};
  std::size_t position_old_vertexes{};
  while (std::getline(file_in, line)) {
    if (line.length() < 2) {
      continue;
    }
    if (line[0] == 'v' && line[1] == ' ') {
      ParsingVertex(models, line, position_old_vertexes);
    } else if (line[0] == 'f') {
      ParsingFacet(models, line, position_old_vertexes);
    }
  }
  for (auto &model_parse : models) {
    model.vertexes.insert(model.vertexes.end(), model_parse.vertexes.begin(),
                          model_parse.vertexes.end());
    model.facets.insert(model.facets.end(), model_parse.facets.begin(),
                        model_parse.facets.end());
  }
  RelocateOnStartPosition();
}
