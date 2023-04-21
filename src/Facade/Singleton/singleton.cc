#include "../Mediator/object_model.h"

using namespace s21;

std::shared_ptr<ObjectModel> ObjectModel::GetInstance() {
  static std::shared_ptr<ObjectModel> instance(new ObjectModel());
  return instance;
}
