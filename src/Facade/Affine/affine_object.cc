#include "object_model.h"

void ObjectModel::Rotate(double angle, ObjectModel::Axis axis) {
    std::size_t index{};
    double tmp_first{}, tmp_second{};
    if (axis == xAxis) {
        for (; index < model.vertexes.size(); index += 3) {
            tmp_first = model.vertexes[index + yAxis];
            tmp_second = model.vertexes[index + zAxis];
            model.vertexes[index + yAxis] = cos(angle) * tmp_first - sin(angle) * tmp_second;
            model.vertexes[index + zAxis] = cos(angle) * tmp_second + sin(angle) * tmp_first;
        }
    } else if (axis == yAxis) {
        for (; index < model.vertexes.size(); index += 3) {
            tmp_first = model.vertexes[index + xAxis];
            tmp_second = model.vertexes[index + zAxis];
            model.vertexes[index + zAxis] = cos(angle) * tmp_second - sin(angle) * tmp_first;
            model.vertexes[index + xAxis] = cos(angle) * tmp_first + sin(angle) * tmp_second;
        }
    } else if (axis == zAxis) {
        for (; index < model.vertexes.size(); index += 3) {
            tmp_first = model.vertexes[index + xAxis];
            tmp_second = model.vertexes[index + yAxis];
            model.vertexes[index + xAxis] = cos(angle) * tmp_first - sin(angle) * tmp_second;
            model.vertexes[index + yAxis] = cos(angle) * tmp_second + sin(angle) * tmp_first;
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
