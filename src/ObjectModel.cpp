#include "ObjectModel.h"

ObjectModel* ObjectModel::instance{};

ObjectModel::ObjectModel() {
    models.reserve(0);
}

void ObjectModel::reserve(std::size_t size) {
    models.reserve(size);
}

void ObjectModel::AddNewObject() {
    models.reserve(models.size() + 1);
    models.push_back(ObjectModel::PartObject());
}

std::size_t ObjectModel::size() {
    return models.size();
}

bool ObjectModel::empty() {
    return size() == 0;
}

void ObjectModel::clear() {
    models.clear();
}

ObjectModel::PartObject &ObjectModel::back() {
    if (empty()) {
        throw std::invalid_argument("Models is empty");
    }
    return models.back();
}

void ObjectModel::OpenObject(std::string line) {
    std::ifstream file_in(line);
    clear();
    while (std::getline(file_in, line)) {
        if (line.empty()) {
            continue;
        }
        if (line[0] == 'g') {
            AddNewObject();
        } else if (line.length() < 2) {
            continue;
        } else if (line[0] == 'v' && line[1] == ' ') {
            if (empty()) {
                AddNewObject();
            }
            int count_vertex{};
            for (unsigned i{}; i < line.length(); ++i) {
                if (std::isdigit(line[i]) || line[i] == '-') {
                    std::size_t index_stod{};
                    back().vertexes.push_back(std::stod(line.c_str() + i, &index_stod));
                    i += index_stod;
                    ++count_vertex;
                }
            }
            if (count_vertex != 3) {
                throw std::invalid_argument("Invalid file .obj");
            }
        } else if (line[0] == 'f') {
            if (empty() || back().vertexes.empty()) {
                throw std::invalid_argument("Invalid file .obj");
            }
            std::vector<unsigned> face{};

            for (unsigned i{}; i < line.length(); ++i) {
                if (std::isdigit(line[i]) || line[i] == '-') {
                    std::size_t index_stoi{};
                    face.push_back(std::abs(std::stoi(line.c_str() + i, &index_stoi)));
                    i += index_stoi;
                }
            }
            back().facets.push_back(face);
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

ObjectModel::PartObject &ObjectModel::operator[](const std::size_t &index) {
    if (index >= models.capacity()) {
        throw std::invalid_argument("Cannot access models greater then capacity");
    }
    return models[index];
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

int main () {
    ObjectModel &a = *ObjectModel::GetInstance();
    a.OpenObject("/mnt/c/Users/12355/Documents/C8_3DViewer_v1.0-0/src/objs/cube.obj");
    a.OpenObject("/mnt/c/Users/12355/Documents/C8_3DViewer_v1.0-0/src/objs/cube.obj");
    a.OpenObject("/mnt/c/Users/12355/Documents/C8_3DViewer_v1.0-0/src/objs/cube.obj");
    for (double vertex : a.back().vertexes) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    for (auto line : a.back().facets) {
        for (unsigned item : line) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "models count: " << a.size() << std::endl;
    return 0;
}