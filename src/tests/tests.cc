#include <gtest/gtest.h>

#include "../Facade/Mediator/object_model.h"

struct CubeObj {
  std::vector<double> vertexesData{0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                   0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                   0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0,
                                   2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<std::vector<unsigned>> facetsData{
      {0, 6, 4}, {0, 2, 6}, {0, 3, 2}, {0, 1, 3}, {2, 7, 6},
      {2, 3, 7}, {4, 6, 7}, {4, 7, 5}, {0, 4, 5}, {0, 5, 1}};
};

TEST(Model, normalParsing) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  CubeObj pattern;
  EXPECT_EQ(pattern.vertexesData.size(), 30);
  for (std::size_t index{}; index < pattern.vertexesData.size(); ++index) {
    EXPECT_NEAR(pattern.vertexesData[index], object.GetVertexes()[index], 1e-6);
  }
  for (std::size_t i{}; i < pattern.facetsData.size(); ++i) {
    for (std::size_t j{}; j < pattern.facetsData[i].size(); ++j) {
      EXPECT_EQ(pattern.facetsData[i][j], object.GetFacets()[i][j]);
    }
  }
  EXPECT_EQ(object.size().first, 30);
  EXPECT_EQ(object.size().second, 10);
  EXPECT_FALSE(object.empty());
  object.clear();
}

TEST(Model, clearParsing) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  EXPECT_FALSE(object.empty());
  object.clear();
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(Model, errorParsing) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  EXPECT_ANY_THROW(object.OpenObject("tests/invalid_test.txt"));
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(Model, errorParsing2) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  EXPECT_ANY_THROW(object.OpenObject("tests/invalid_size_vertex.txt"));
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(Model, errorParsing3) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  EXPECT_ANY_THROW(object.OpenObject("tests/invalid_facet.txt"));
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(Model, normalization) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  object.NormalizationAndCentralize();
  for (std::size_t index{}; index < object.GetVertexes().size(); ++index) {
    EXPECT_NEAR(std::fabs(object.GetVertexes()[index]), 0.5, 1e-6);
  }
  object.clear();
}

TEST(Model, normalizationError) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  EXPECT_ANY_THROW(object.NormalizationAndCentralize());
  object.clear();
}

TEST(Model, getVertexesForNotEqualSize) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  auto &dataVertexes = object.GetVertexes(2, 1);
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::xAxis] * 0.5,
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::yAxis],
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::zAxis],
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, getVertexesForNotEqualSize2) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  auto &dataVertexes = object.GetVertexes(1, 2);
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::xAxis],
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::yAxis] * 0.5,
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::zAxis],
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, RotateX) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = 2;
  object.Rotate(angle, s21::ObjectModel::xAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::ObjectModel::yAxis],
           tmp_second = pattern.vertexesData[index + s21::ObjectModel::zAxis];
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::xAxis],
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, RotateX2) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = -234;
  object.Rotate(angle, s21::ObjectModel::xAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::ObjectModel::yAxis],
           tmp_second = pattern.vertexesData[index + s21::ObjectModel::zAxis];
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::xAxis],
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, RotateY) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = 15;
  object.Rotate(angle, s21::ObjectModel::yAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::ObjectModel::xAxis],
           tmp_second = pattern.vertexesData[index + s21::ObjectModel::zAxis];
    EXPECT_NEAR(cos(angle) * tmp_first + sin(angle) * tmp_second,
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::yAxis],
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second - sin(angle) * tmp_first,
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, RotateY2) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = -57;
  object.Rotate(angle, s21::ObjectModel::yAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::ObjectModel::xAxis],
           tmp_second = pattern.vertexesData[index + s21::ObjectModel::zAxis];
    EXPECT_NEAR(cos(angle) * tmp_first + sin(angle) * tmp_second,
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::yAxis],
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second - sin(angle) * tmp_first,
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, RotateZ) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = 543;
  object.Rotate(angle, s21::ObjectModel::zAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::ObjectModel::xAxis],
           tmp_second = pattern.vertexesData[index + s21::ObjectModel::yAxis];
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::zAxis],
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, RotateZ2) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = -84;
  object.Rotate(angle, s21::ObjectModel::zAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::ObjectModel::xAxis],
           tmp_second = pattern.vertexesData[index + s21::ObjectModel::yAxis];
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::zAxis],
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}

TEST(Model, Move) {
  s21::ObjectModel &object = *s21::ObjectModel::GetInstance();
  object.OpenObject("tests/test.txt");
  double move_coords[3] = {42, -23, 1234};
  object.Move(move_coords[s21::ObjectModel::xAxis], s21::ObjectModel::xAxis);
  object.Move(move_coords[s21::ObjectModel::yAxis], s21::ObjectModel::yAxis);
  object.Move(move_coords[s21::ObjectModel::zAxis], s21::ObjectModel::zAxis);
  auto &dataVertexes = object.GetVertexes();
  CubeObj pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::xAxis] +
                    move_coords[s21::ObjectModel::xAxis],
                dataVertexes[index + s21::ObjectModel::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::yAxis] +
                    move_coords[s21::ObjectModel::yAxis],
                dataVertexes[index + s21::ObjectModel::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::ObjectModel::zAxis] +
                    move_coords[s21::ObjectModel::zAxis],
                dataVertexes[index + s21::ObjectModel::zAxis], 1e-6);
  }
  object.clear();
}
