#include <catch2/catch_test_macros.hpp>

#include "hpc_tutor/matrix.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;

TEST_CASE("Empty Constructor", "[constructors]") {
  Matrix<double> a{};
  CHECK(a.empty());
  CHECK(a.size() == 0);
  CHECK(a.dim_one() == 0);
  CHECK(a.dim_two() == 0);
}

TEST_CASE("Default fill Constructor", "[constructors]") {
  size_t n = 15, m = 10;
  Matrix<double> a(n, m);
  CHECK_FALSE(a.empty());
  CHECK(a.size() == n * m);
  CHECK(a.dim_one() == n);
  CHECK(a.dim_two() == m);
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
  CHECK(a.dim_one() == n);
  CHECK(a.dim_two() == m);
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
  CHECK(a.dim_one() == n);
  CHECK(a.dim_two() == m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      INFO("Failed at element a[" << i << ", " << j << "]");
      REQUIRE(a[i][j] == val);
    }
  }
}
