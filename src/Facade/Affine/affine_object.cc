#include "../Mediator/object_model.h"

#include <functional>

using namespace s21;

void ObjectModel::Rotate(double angle, ObjectModel::Axis axis) {
  const std::size_t threads_max = std::clamp(std::thread::hardware_concurrency() - 1u, 1u, multithreadingMaxSize);
  std::vector<std::thread> threads;
  auto RotateAxis = [&](std::size_t start, std::size_t end, int first_enum, int second_enum, int first_axis, int second_axis){
    for (std::size_t index = start; index < end; index += 3) {
      double tmp_first = model.vertexes[index + first_enum];
      double tmp_second = model.vertexes[index + second_enum];
      model.vertexes[index + first_axis] = cos(angle) * tmp_first - sin(angle) * tmp_second;
      model.vertexes[index + second_axis] = cos(angle) * tmp_second + sin(angle) * tmp_first;
    }
  };
  std::size_t start = 0, delta = model.vertexes.size() / threads_max, end, first_enum, second_enum, first_axis, second_axis;
  delta -= delta % 3;
  end = delta;
  if (axis == xAxis) {
    first_enum = yAxis, second_enum = zAxis, first_axis = yAxis, second_axis = zAxis;
  } else if (axis == yAxis) {
    first_enum = zAxis, second_enum = xAxis, first_axis = zAxis, second_axis = xAxis;
  } else if (axis == zAxis) {
    first_enum = xAxis, second_enum = yAxis, first_axis = xAxis, second_axis = yAxis;
  }
  for (std::size_t thread_num = 0; thread_num < threads_max; ++thread_num) {
    threads.emplace_back(RotateAxis, start, end, first_enum, second_enum, first_axis, second_axis);
    start += delta;
    end += delta;
  }
  RotateAxis(start, model.vertexes.size(), first_enum, second_enum, first_axis, second_axis);

  for (auto& thread : threads) {
    thread.join();
  }
}

void ObjectModel::MoveReal(double coordinate, ObjectModel::AxisPoints axis) {
  const std::size_t threads_max = std::clamp(std::thread::hardware_concurrency() - 1u, 1u, multithreadingMaxSize);
  std::vector<std::thread> threads;
  std::size_t start = axis, delta = model.vertexes.size() / threads_max, end;
  delta -= delta % 3;
  end = delta;
  auto MoveAxis = [&](std::size_t start, std::size_t end){
    for (std::size_t index = start; index < end; index += 3) {
      model.vertexes[index] += coordinate;
    }
  };
  
  for (std::size_t thread_num = 0; thread_num < threads_max; ++thread_num) {
    threads.emplace_back(MoveAxis, start, end);
    start += delta;
    end += delta;
  }
  MoveAxis(start, model.vertexes.size());
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
