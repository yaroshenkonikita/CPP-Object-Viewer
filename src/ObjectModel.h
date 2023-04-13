#ifndef CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
#define CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <utility>
#include <cstring>

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
        PartObject() = default;
        PartObject(PartObject&);
        PartObject(PartObject&&) noexcept;
        ~PartObject() = default;
        std::vector<std::vector<unsigned>> facets{};
        std::vector<double> vertexes{};
        PartObject &operator=(PartObject &);
        PartObject &operator=(PartObject &&);
    };
    typedef enum Axis { xAxis, yAxis, zAxis} AxisPoints;
    static ObjectModel* GetInstance();

    PartObject &operator[](const std::size_t &);
    void OpenObject(std::string);
    void AddNewObject();

    void Move(double, AxisPoints);
    void Rotate(double, AxisPoints);
    void Scale(double);
    std::pair<std::size_t, std::size_t> size();

    std::vector<PartObject> models{};

private:
    static ObjectModel *instance;

    ObjectModel();
    ~ObjectModel();

};

#endif //CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
