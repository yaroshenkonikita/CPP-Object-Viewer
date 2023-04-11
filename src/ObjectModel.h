#ifndef CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
#define CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

#include <stdexcept>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>

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
    static ObjectModel* GetInstance();

    PartObject &operator[](const std::size_t &);
    void OpenObject(std::string);
    void AddNewObject();

    std::vector<PartObject> models{};

private:
    static ObjectModel *instance;

    ObjectModel();
    ~ObjectModel();

};

#endif //CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
