#include "../Mediator/object_model.h"

using namespace s21;

std::pair<std::size_t, std::size_t> ObjectModel::size() {
  return {model.vertexes.size(), model.facets.size()};
}

bool ObjectModel::empty() {
  return model.vertexes.empty() || model.facets.empty();
}

void ObjectModel::clear() {
  model.facets.clear();
  model.vertexes.clear();
}

std::vector<double>& ObjectModel::GetVertexes(double width, double height) {
  char state_scaling{};
  double scale{};
  if (width > height) {
    state_scaling = 1;
    scale = height / width;
  } else if (height > width) {
    state_scaling = 2;
    scale = width / height;
  }

  prepare_data.clear();
  std::copy(model.vertexes.begin(), model.vertexes.end(),
            std::back_inserter(prepare_data));

  const std::size_t threads_max = 4;
  std::vector<std::thread> threads(threads_max);
  auto pd = prepare_data.data();
  std::size_t count_of_vertex = prepare_data.size();

  for (std::size_t thread_num = 0; thread_num < threads_max; ++thread_num) {
    threads[thread_num] = std::thread([this, pd, count_of_vertex, state_scaling,
                                       scale, thread_num, threads_max]() {
      for (std::size_t index = thread_num * 3; index < count_of_vertex;
           index += 3 * threads_max) {
        pd[index + xAxis] += move_coordinate[xAxis];
        pd[index + yAxis] += move_coordinate[yAxis];
        pd[index + zAxis] += move_coordinate[zAxis];
        if (state_scaling == 1) {
          pd[index + xAxis] *= scale;
        } else if (state_scaling == 2) {
          pd[index + yAxis] *= scale;
        }
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  return prepare_data;
}

const std::vector<std::vector<unsigned>>& ObjectModel::GetFacets() {
  return model.facets;
}
