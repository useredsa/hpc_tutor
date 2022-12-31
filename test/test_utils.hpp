#ifndef HPC_TUTOR_TEST_UTILS_HPP_
#define HPC_TUTOR_TEST_UTILS_HPP_

#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <random>
#include <type_traits>
#include <vector>

#include "hpc_tutor/matrix.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
Matrix<T> RandomMatrix(size_t rows, size_t cols, T low = 0, T high = 100) {
  static std::mt19937 rng;
  if (rng == std::mt19937{}) rng.seed(Catch::getSeed());
  auto dist = std::uniform_int_distribution<T>(low, high);
  Matrix<T> m(rows, cols);
  std::generate_n(m.data(), m.size(), std::bind(dist, rng));
  return m;
}

template <typename T,
          std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
Matrix<T> RandomMatrix(size_t rows, size_t cols, T low = 0, T high = 1) {
  static std::mt19937 rng;
  if (rng == std::mt19937{}) rng.seed(Catch::getSeed());
  auto dist = std::uniform_real_distribution<T>(low, high);
  Matrix<T> m(rows, cols);
  std::generate_n(m.data(), m.size(), std::bind(dist, rng));
  return m;
}

template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
std::vector<T> RandomVector(size_t n, T low = 0, T high = 100) {
  static std::mt19937 rng;
  if (rng == std::mt19937{}) rng.seed(Catch::getSeed());
  auto dist = std::uniform_int_distribution<T>(low, high);
  std::vector<T> v(n);
  std::generate(v.begin(), v.end(), std::bind(dist, rng));
  return v;
}

template <typename T,
          std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
std::vector<T> RandomVector(size_t n, T low = 0, T high = 1) {
  static std::mt19937 rng;
  if (rng == std::mt19937{}) rng.seed(Catch::getSeed());
  auto dist = std::uniform_real_distribution<T>(low, high);
  std::vector<T> v(n);
  std::generate(v.begin(), v.end(), std::bind(dist, rng));
  return v;
}

template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void RequireEqual(const Matrix<T>& result, const Matrix<T>& truth) {
  INFO("Matrix result differs from matrix truth");
  INFO("result:\n" << result << "\ntruth:\n" << truth);
  REQUIRE(result.rows() == truth.rows());
  REQUIRE(result.cols() == truth.cols());
  for (size_t i = 0; i < truth.rows(); ++i) {
    for (size_t j = 0; j < truth.cols(); ++j) {
      INFO("Matrices differ at position " << i << ", " << j);
      REQUIRE(result[i][j] == truth[i][j]);
    }
  }
}

template <typename T,
          std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
void RequireEqual(const Matrix<T>& result, const Matrix<T>& truth) {
  INFO("Matrix result differs from matrix truth");
  INFO("result:\n" << result << "\ntruth:\n" << truth);
  REQUIRE(result.rows() == truth.rows());
  REQUIRE(result.cols() == truth.cols());
  for (size_t i = 0; i < truth.rows(); ++i) {
    for (size_t j = 0; j < truth.cols(); ++j) {
      INFO("Matrices differ at position " << i << ", " << j);
      REQUIRE_THAT(result[i][j], WithinRel(truth[i][j], 1e-6) ||
                                     WithinAbs(truth[i][j], 1e-6));
    }
  }
}

template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void RequireEqual(const std::vector<T>& result, const std::vector<T>& truth) {
  INFO("Vector result differs from vector truth");
  REQUIRE(result.size() == truth.size());
  for (size_t i = 0; i < truth.size(); ++i) {
    INFO("Vectors differ at position " << i);
    REQUIRE(result[i] == truth[i]);
  }
}

template <typename T,
          std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
void RequireEqual(const std::vector<T>& result, const std::vector<T>& truth) {
  INFO("Vector result differs from vector truth");
  REQUIRE(result.size() == truth.size());
  for (size_t i = 0; i < truth.size(); ++i) {
    INFO("Vectors differ at position " << i);
    REQUIRE_THAT(result[i],
                 WithinRel(truth[i], 1e-6) || WithinAbs(truth[i], 1e-6));
  }
}

#endif  // HPC_TUTOR_TEST_UTILS_HPP_
