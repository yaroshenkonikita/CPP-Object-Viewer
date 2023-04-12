#include "ObjectModel.h"

ObjectModel* ObjectModel::instance{};

ObjectModel::ObjectModel() {
    models.reserve(0);
}

void ObjectModel::AddNewObject() {
    models.reserve(models.size() + 1);
    models.push_back(ObjectModel::PartObject());
}

void ObjectModel::OpenObject(std::string line) {
    std::ifstream file_in(line);
    models.clear();
    while (std::getline(file_in, line)) {
        if (line.empty()) {
            continue;
        }
        if (line[0] == 'g') {
            AddNewObject();
        } else if (line.length() < 2) {
            continue;
        } else if (line[0] == 'v' && line[1] == ' ') {
            if (models.empty()) {
                AddNewObject();
            }
            int count_vertex{};
            for (unsigned i{}; i < line.length(); ++i) {
                if (std::isdigit(line[i]) || line[i] == '-') {
                    std::size_t index_stod{};
                    models.back().vertexes.push_back(std::stod(line.c_str() + i, &index_stod));
                    i += index_stod;
                    ++count_vertex;
                }
            }
            if (count_vertex != 3) {
                throw std::invalid_argument("Invalid file .obj");
            }
        } else if (line[0] == 'f') {
            if (models.empty() || models.back().vertexes.empty()) {
                throw std::invalid_argument("Invalid file .obj");
            }
            std::vector<unsigned> face{};

            for (unsigned i{}; i < line.length(); ++i) {
                if (std::isdigit(line[i]) || line[i] == '-') {
                    std::size_t index_stoi{};
                    face.push_back(std::abs(std::stoi(line.c_str() + i, &index_stoi)));
                    i += index_stoi;
                    while (i < line.length()) {
                        if (line[i] != ' ') {
                            ++i;
                            continue;
                        }
                        break;
                    }
                }
            }
            models.back().facets.push_back(face);
        }
    }
}

ObjectModel *ObjectModel::GetInstance() {
    if (!instance) {
        instance = new ObjectModel();
    }
    return instance;
}

ObjectModel::~ObjectModel() {
    delete instance;
}

std::pair<std::size_t, std::size_t> ObjectModel::size() {
    std::size_t size_f{}, size_v{};
    for (auto&model : ObjectModel::GetInstance()->models) {
        size_f += model.facets.size();
        size_v += model.vertexes.size();
    }
    return {size_v, size_f};
}

ObjectModel::PartObject &ObjectModel::operator[](const std::size_t &index) {
    if (index >= models.capacity()) {
        throw std::invalid_argument("Cannot access models greater then capacity");
    }
    return models[index];
}

void ObjectModel::Rotate(double angle, ObjectModel::Axis axis) {
    for (auto &model : models) {
        std::size_t index{};
        double tmp_first{}, tmp_second;
        if (axis == Axis::xAxis) {
            for (; index < model.vertexes.size(); index += 3) {
                tmp_first = model.vertexes[index + Axis::yAxis];
                tmp_second = model.vertexes[index + Axis::zAxis];
                model.vertexes[index + Axis::yAxis] = cos(angle) * tmp_first - sin(angle) * tmp_second;
                model.vertexes[index + Axis::zAxis] = sin(angle) * tmp_first + cos(angle) * tmp_second;
            }
        } else if (axis == Axis::yAxis) {
            for (; index < model.vertexes.size(); index += 3) {
                tmp_first = model.vertexes[index + Axis::xAxis];
                tmp_second = model.vertexes[index + Axis::zAxis];
                model.vertexes[index + Axis::xAxis] = cos(angle) * tmp_first + sin(angle) * tmp_second;
                model.vertexes[index + Axis::zAxis] = -sin(angle) * tmp_first + cos(angle) * tmp_second;
            }
        } else if (axis == Axis::zAxis) {
            for (; index < model.vertexes.size(); index += 3) {
                tmp_first = model.vertexes[index + Axis::xAxis];
                tmp_second = model.vertexes[index + Axis::yAxis];
                model.vertexes[index + Axis::xAxis] = cos(angle) * tmp_first - sin(angle) * tmp_second;
                model.vertexes[index + Axis::yAxis] = sin(angle) * tmp_first + cos(angle) * tmp_second;
            }
        }
    }
}

void ObjectModel::Move(double coordinate, ObjectModel::AxisPoints axis) {
    for (auto &model : models) {
        for (std::size_t index = axis; index < model.vertexes.size(); index += 3) {
            model.vertexes[index] += coordinate;
        }
    }
}

void ObjectModel::Scale(double coordinate) {
    coordinate = coordinate / 100.;
    for (auto &model : models) {
        for (double &vertex : model.vertexes) {
            vertex *= coordinate;
        }
    }
}


ObjectModel::PartObject::PartObject(ObjectModel::PartObject &other) {
    facets = std::move(other.facets);
    vertexes = std::move(other.vertexes);
}

ObjectModel::PartObject::PartObject(ObjectModel::PartObject &&other) noexcept {
    facets = std::move(other.facets);
    vertexes = std::move(other.vertexes);
}

ObjectModel::PartObject &ObjectModel::PartObject::operator=(ObjectModel::PartObject &other) {
    facets = std::move(other.facets);
    vertexes = std::move(other.vertexes);
    return *this;
}

ObjectModel::PartObject &ObjectModel::PartObject::operator=(ObjectModel::PartObject &&other) {
    facets = std::move(other.facets);
    vertexes = std::move(other.vertexes);
    return *this;
}

#include <iostream>

int main () {
    ObjectModel &a = *ObjectModel::GetInstance();
    a.OpenObject("objs/skull.obj");
    for (ObjectModel::PartObject part : a.models) {
        for (double vertex : part.vertexes) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
        for (auto line : part.facets) {
            for (unsigned item : line) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "models count: " << a.models.size() << std::endl;
    return 0;
}
