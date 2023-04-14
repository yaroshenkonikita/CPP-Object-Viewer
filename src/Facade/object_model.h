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

    const std::vector<double>& GetVertexes();
    const std::vector<std::vector<unsigned>>& GetFacets();


protected:
    static ObjectModel *instance;

    ObjectModel() = default;
    ~ObjectModel();

    PartObject model{};

    void ParsingFacet(std::vector<PartObject>&, std::string&, std::size_t&);
    void ParsingVertex(std::vector<PartObject>&, std::string&, std::size_t&);

};

#endif //CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
