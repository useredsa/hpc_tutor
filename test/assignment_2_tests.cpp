#include <algorithm>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>
#include <random>

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/linalg_t.hpp"
#include "hpc_tutor/matrix.hpp"
#include "test_utils.hpp"

TEST_CASE("Find_t", "[assignment-2]") {
  constexpr size_t n = 100;
  GIVEN("Vector is random") {
    auto v = RandomVector<int>(n, 0, n / 2);
    THEN("Find_t matches Find") {
      size_t truth = tutor::Find(v.data(), v.size(), 0);
      size_t result = tutor::Find_t(v.data(), v.size(), 0);
      REQUIRE(result == truth);
    }
  }
  GIVEN("A vector that does not contain the value") {
    std::vector<int> v(n);
    THEN("Find_t returns the size of the vector") {
      size_t result = tutor::Find_t(v.data(), v.size(), 1);
      REQUIRE(result == v.size());
    }
  }
}

TEST_CASE("MergeSort_t", "[assignment-2]") {
  GIVEN("A random permutation") {
    constexpr size_t n = 10;
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    std::mt19937 rng(Catch::getSeed());
    std::shuffle(v.begin(), v.end(), rng);
    THEN("MergeSort_t returns the identity permutation") {
      std::vector<int> truth(n);
      std::iota(truth.begin(), truth.end(), 0);
      tutor::MergeSort_t(v.data(), v.size());
      REQUIRE(v == truth);
    }
  }
  GIVEN("A random vector") {
    constexpr size_t n = 100;
    auto v = RandomVector<int>(n, 0, n);
    THEN("MergeSort_t does the same as MergeSort") {
      auto truth = v;
      tutor::MergeSort(truth.data(), truth.size());
      tutor::MergeSort_t(v.data(), v.size());
      RequireEqual(v, truth);
    }
  }
}

TEST_CASE("MatrixEval_t", "[assignment-2]") {
  constexpr size_t n = 10;
  constexpr size_t m = 13;
  auto mat = RandomMatrix<int>(n, m, 0, 10);
  auto v = RandomVector<int>(m, 0, 10);
  std::vector<int> truth(n), result(n);
  tutor::MatrixEval(truth.data(), mat.view(), v.data());
  tutor::MatrixEval_t(result.data(), mat.view(), v.data());
  RequireEqual(result, truth);
}

TEST_CASE("Gemm_t", "[assignment-2]") {
  constexpr size_t n = 10;
  constexpr size_t m = 15;
  constexpr size_t l = 200;
  auto lhs = RandomMatrix<int>(n, l, -3, 3);
  auto rhs = RandomMatrix<int>(l, m, -3, 3);
  Matrix<int> truth(n, m), result(n, m);
  tutor::Gemm(truth.view(), lhs.view(), rhs.view());
  tutor::Gemm_t(result.view(), lhs.view(), rhs.view());
  RequireEqual(result, truth);
}
