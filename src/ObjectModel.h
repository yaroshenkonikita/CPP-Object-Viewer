#ifndef CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
#define CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <utility>
#include <cstring>
#include <float.h>

struct Options_t {
    int projection_type{},        // Тип проекции
    edge_type{},              // Тип ребра
    vertex_type{};            // Тип вершины
    float background_color[4]{},  // Цвет фона {red, green, blue}
    edge_color[4]{},          // Цвет ребра {red, green, blue}
    vertex_color[4]{},        // Цвет вершины {red, green, blue}
    edge_width{},             // Толщина ребра
    vertex_width{};           // толщина вершины
    bool state_fill{};        // Полигон или каркас
};

class ObjectModel {
public:
    struct PartObject {
        std::vector<std::vector<unsigned>> facets{};
        std::vector<double> vertexes{};
    };
    typedef enum Axis { xAxis, yAxis, zAxis} AxisPoints;
    static ObjectModel* GetInstance();

    void OpenObject(std::string);

    void Move(double, AxisPoints);
    void Rotate(double, AxisPoints);
    void Scale(double);
    void RelocateOnStartPosition();
    bool empty();
    void clear();
    std::pair<std::size_t, std::size_t> size();

    PartObject model{};

private:
    static ObjectModel *instance;

    ObjectModel() = default;
    ~ObjectModel();

};

#endif //CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
