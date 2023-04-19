#include "../Mediator/object_model.h"

using namespace s21;

ObjectModel* ObjectModel::instance = nullptr;

ObjectModel* ObjectModel::GetInstance() {
  if (!instance) {
    instance = new ObjectModel();
  }
  return instance;
}

ObjectModel::~ObjectModel() {
  delete instance;
  instance = nullptr;
}
