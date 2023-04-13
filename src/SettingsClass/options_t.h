#ifndef CPP4_3DVIEWER_V2_0_1_OPTIONS_T_H_
#define CPP4_3DVIEWER_V2_0_1_OPTIONS_T_H_

struct Options_t {
    int projection_type{},          // Тип проекции
    edge_type{},                    // Тип ребра
    vertex_type{},                  // Тип вершины
    edge_width{},                   // Толщина ребра
    vertex_width{};                 // толщина вершины
    float background_color[4]{},    // Цвет фона {red, green, blue}
    edge_color[4]{},                // Цвет ребра {red, green, blue}
    vertex_color[4]{};              // Цвет вершины {red, green, blue}
    bool state_fill{};              // Полигон или каркас
};

#endif //CPP4_3DVIEWER_V2_0_1_OPTIONS_T_H_
