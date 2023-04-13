#include "object_model.h"

ObjectModel* ObjectModel::instance = nullptr;

void ObjectModel::OpenObject(std::string line) {
    std::ifstream file_in(line);
    std::vector<PartObject> models = {PartObject()};
    std::size_t position_old_vertexes{};
    while (std::getline(file_in, line)) {
        if (line.length() < 2) {
            continue;
        }
        if (line[0] == 'v' && line[1] == ' ') {
            if (models.back().facets.size()) {
                position_old_vertexes += models.back().vertexes.size() / 3;
                models.emplace_back();
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
            char* token = std::strtok(line.data() + 1, " ");
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
    }
    for(auto &model_parse : models) {
        model.vertexes.insert(model.vertexes.end(), model_parse.vertexes.begin(), model_parse.vertexes.end());
        model.facets.insert(model.facets.end(), model_parse.facets.begin(), model_parse.facets.end());
    }
    RelocateOnStartPosition();
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
    return {model.vertexes.size(), model.facets.size()};
}

void ObjectModel::Rotate(double angle, ObjectModel::Axis axis) {
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

void ObjectModel::Move(double coordinate, ObjectModel::AxisPoints axis) {
    for (std::size_t index = axis; index < model.vertexes.size(); index += 3) {
        model.vertexes[index] += coordinate;
    }
}

void ObjectModel::Scale(double coordinate) {
    coordinate = coordinate / 100.;
    for (double &vertex : model.vertexes) {
        vertex *= coordinate;
    }
}

bool ObjectModel::empty() {
    return model.vertexes.empty() || model.facets.empty();
}

void ObjectModel::RelocateOnStartPosition() {
    if (empty()) {
        throw std::logic_error("Can't relocate. Haven't exist model");
    }
    double positionAxis[6] = {DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX};
    for (std::size_t index = 0; index < model.vertexes.size(); index += 3) {
        positionAxis[xAxis] = std::min(positionAxis[xAxis], model.vertexes[index + xAxis]);
        positionAxis[yAxis] = std::min(positionAxis[yAxis], model.vertexes[index + yAxis]);
        positionAxis[zAxis] = std::min(positionAxis[zAxis], model.vertexes[index + zAxis]);
        positionAxis[xAxis + 3] = std::max(positionAxis[xAxis + 3], model.vertexes[index + xAxis]);
        positionAxis[yAxis + 3] = std::max(positionAxis[yAxis + 3], model.vertexes[index + yAxis]);
        positionAxis[zAxis + 3] = std::max(positionAxis[zAxis + 3], model.vertexes[index + zAxis]);
    }
    double deltaAxis[3] = {positionAxis[xAxis + 3] - positionAxis[xAxis],
                           positionAxis[yAxis + 3] - positionAxis[yAxis],
                           positionAxis[zAxis + 3] - positionAxis[zAxis]};
    Move(-(positionAxis[xAxis] + deltaAxis[xAxis] / 2), xAxis);
    Move(-(positionAxis[yAxis] + deltaAxis[yAxis] / 2), yAxis);
    Move(-(positionAxis[zAxis] + deltaAxis[zAxis] / 2), zAxis);
    Scale(100/std::max(std::max(deltaAxis[xAxis], deltaAxis[yAxis]), deltaAxis[zAxis]));
}

void ObjectModel::clear() {
    model.facets.clear();
    model.vertexes.clear();
}

//#include <iostream>
//
//int main () {
//    ObjectModel &a = *ObjectModel::GetInstance();
//    a.OpenObject("objs/skull.obj");
//    for (double vertex : a.model.vertexes) {
//        std::cout << vertex << " ";
//    }
//    std::cout << std::endl;
//    for (auto line : a.model.facets) {
//        for (unsigned item : line) {
//            std::cout << item << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << a.model.vertexes.size() << std::endl;
//    std::cout << a.model.facets.size() << std::endl;
//    return 0;
//}
