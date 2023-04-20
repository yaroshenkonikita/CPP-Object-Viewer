#include "../Facade/Mediator/object_model.h"

TEST(Model, empty_valid) {
  s21::ObjectModel object;
  object.OpenObject("test.txt");
}
