#include "../object_model.h"

ObjectModel* ObjectModel::instance = nullptr;

ObjectModel *ObjectModel::GetInstance() {
    if (!instance) {
        instance = new ObjectModel();
    }
    return instance;
}

ObjectModel::~ObjectModel() {
    delete instance;
    instance = nullptr;
}
