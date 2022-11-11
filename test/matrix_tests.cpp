#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <numeric>

#include "hpc_tutor/matrix.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;

TEST_CASE("Empty Constructor", "[constructors]") {
  Matrix<double> a{};
  CHECK(a.empty());
  CHECK(a.size() == 0);
  CHECK(a.rows() == 0);
  CHECK(a.cols() == 0);
}

TEST_CASE("Default fill Constructor", "[constructors]") {
  size_t n = 15, m = 10;
  Matrix<double> a(n, m);
  CHECK_FALSE(a.empty());
  CHECK(a.size() == n * m);
  CHECK(a.rows() == n);
  CHECK(a.cols() == m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      INFO("Failed at element a[" << i << ", " << j << "] = " << a[i][j]);
      REQUIRE(a[i][j] == 0);
    }
  }
}

TEST_CASE("Fill Constructor", "[constructors]") {
  size_t n = 5, m = 100;
  double val = 17.0;
  Matrix<double> a(n, m, val);
  CHECK_FALSE(a.empty());
  CHECK(a.size() == n * m);
  CHECK(a.rows() == n);
  CHECK(a.cols() == m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      INFO("Failed at element a[" << i << ", " << j << "] = " << a[i][j]);
      REQUIRE(a[i][j] == val);
    }
  }
}

TEST_CASE("Assign method", "[constructors]") {
  size_t n = 5, m = 100;
  double val = 17.0;
  Matrix<double> a;
  CHECK(a.empty());
  a.assign(n, m, val);
  CHECK_FALSE(a.empty());
  CHECK(a.size() == n * m);
  CHECK(a.rows() == n);
  CHECK(a.cols() == m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      INFO("Failed at element a[" << i << ", " << j << "]");
      REQUIRE(a[i][j] == val);
    }
  }
}

TEST_CASE("Initializer List Constructor", "[constructors]") {
  Matrix<int> a = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
  REQUIRE(a.rows() == 3);
  REQUIRE(a.cols() == 4);
  for (size_t i = 0; i < a.rows(); ++i) {
    for (size_t j = 0; j < a.cols(); ++j) {
      INFO("Failed at element a[" << i << ", " << j << "]");
      REQUIRE(a[i][j] == i * a.cols() + j);
    }
  }
  Matrix<int> b{{1}, {0, 1}, {0, 0, 1}};
  REQUIRE(b.rows() == 3);
  REQUIRE(b.cols() == 3);
  auto identity = Matrix<int>::eye(3);
  for (size_t i = 0; i < b.rows(); ++i) {
    for (size_t j = 0; j < b.cols(); ++j) {
      INFO("Failed at element a[" << i << ", " << j << "]");
      REQUIRE(b[i][j] == identity[i][j]);
    }
  }
}
