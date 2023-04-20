#include "../Mediator/object_model.h"

using namespace s21;

void ObjectModel::Rotate(double angle, ObjectModel::Axis axis) {
  const std::size_t threads_max =
      std::min(multithreadingMaxSize, std::thread::hardware_concurrency());
  std::vector<std::thread> threads(threads_max);
  if (axis == xAxis) {
    for (std::size_t thread_num = 0; thread_num < threads_max; ++thread_num) {
      threads[thread_num] =
          std::thread([this, angle, thread_num, threads_max]() {
            double tmp_first{}, tmp_second{};
            for (std::size_t index = thread_num * 3;
                 index < model.vertexes.size(); index += 3 * threads_max) {
              tmp_first = model.vertexes[index + yAxis];
              tmp_second = model.vertexes[index + zAxis];
              model.vertexes[index + yAxis] =
                  cos(angle) * tmp_first - sin(angle) * tmp_second;
              model.vertexes[index + zAxis] =
                  cos(angle) * tmp_second + sin(angle) * tmp_first;
            }
          });
    }
  } else if (axis == yAxis) {
    for (std::size_t thread_num = 0; thread_num < threads_max; ++thread_num) {
      threads[thread_num] =
          std::thread([this, angle, thread_num, threads_max]() {
            double tmp_first{}, tmp_second{};
            for (std::size_t index = thread_num * 3;
                 index < model.vertexes.size(); index += 3 * threads_max) {
              tmp_first = model.vertexes[index + xAxis];
              tmp_second = model.vertexes[index + zAxis];
              model.vertexes[index + zAxis] =
                  cos(angle) * tmp_second - sin(angle) * tmp_first;
              model.vertexes[index + xAxis] =
                  cos(angle) * tmp_first + sin(angle) * tmp_second;
            }
          });
    }
  } else if (axis == zAxis) {
    for (std::size_t thread_num = 0; thread_num < threads_max; ++thread_num) {
      threads[thread_num] =
          std::thread([this, angle, thread_num, threads_max]() {
            double tmp_first{}, tmp_second{};
            for (std::size_t index = thread_num * 3;
                 index < model.vertexes.size(); index += 3 * threads_max) {
              tmp_first = model.vertexes[index + xAxis];
              tmp_second = model.vertexes[index + yAxis];
              model.vertexes[index + xAxis] =
                  cos(angle) * tmp_first - sin(angle) * tmp_second;
              model.vertexes[index + yAxis] =
                  cos(angle) * tmp_second + sin(angle) * tmp_first;
            }
          });
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

void ObjectModel::MoveReal(double coordinate, ObjectModel::AxisPoints axis) {
  const std::size_t threads_max =
      std::min(multithreadingMaxSize, std::thread::hardware_concurrency());
  std::vector<std::thread> threads(threads_max);
  for (std::size_t thread_num{}; thread_num < threads_max; ++thread_num) {
    threads[thread_num] =
        std::thread([this, coordinate, axis, thread_num, threads_max]() {
          for (std::size_t index = axis + thread_num * 3;
               index < model.vertexes.size(); index += 3 * threads_max) {
            model.vertexes[index] += coordinate;
          }
        });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

void ObjectModel::Move(double coordinate, ObjectModel::AxisPoints axis) {
  move_coordinate[axis] += coordinate;
}

void ObjectModel::Scale(double coordinate) {
  coordinate = coordinate / 100.;
  const std::size_t threads_max =
      std::min(multithreadingMaxSize, std::thread::hardware_concurrency());
  std::vector<std::thread> threads(threads_max);
  for (std::size_t thread_num{}; thread_num < threads_max; ++thread_num) {
    threads[thread_num] =
        std::thread([this, coordinate, thread_num, threads_max]() {
          for (std::size_t index = thread_num; index < model.vertexes.size();
               index += threads_max) {
            model.vertexes[index] *= coordinate;
          }
        });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}
