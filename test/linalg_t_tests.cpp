#include <algorithm>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <functional>
#include <numeric>
#include <random>

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/linalg_t.hpp"
#include "hpc_tutor/matrix.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("Find_t", "[assignment-2]") {
  constexpr size_t n = 100;
  GIVEN("Vector is random") {
    std::vector<int> v(n);
    std::mt19937 rng(Catch::getSeed());
    auto dist = std::uniform_int_distribution(0, int{n} / 2);
    std::generate(v.begin(), v.end(), std::bind(dist, rng));
    size_t truth = tutor::Find(v.data(), v.size(), 0);
    size_t result = tutor::Find_t(v.data(), v.size(), 0);
    REQUIRE(result == truth);
  }
  GIVEN("A vector that does not contain the value") {
    std::vector<int> v(n);
    int val = 1;
    THEN("Find_t returns the size of the vector") {
      size_t result = tutor::Find_t(v.data(), v.size(), val);
      REQUIRE(result == v.size());
    }
  }
}

TEST_CASE("MergeSort_t", "[assignment-2]") {
  GIVEN("A permutation") {
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
    std::vector<int> v(n);
    std::mt19937 rng(Catch::getSeed());
    auto dist = std::uniform_int_distribution(0, int{n});
    std::generate(v.begin(), v.end(), std::bind(dist, rng));
    THEN("MergeSort_t does the same as MergeSort") {
      auto truth = v;
      tutor::MergeSort(truth.data(), truth.size());
      tutor::MergeSort_t(v.data(), v.size());
      REQUIRE(v == truth);
    }
  }
}

TEST_CASE("MatrixEval_t", "[assignment-2]") {
  constexpr size_t n = 10;
  constexpr size_t m = 13;
  Matrix<int> mat(n, m);
  std::vector<int> truth(n), result(n), v(m);
  std::mt19937 rng(Catch::getSeed());
  auto dist = std::uniform_int_distribution(0, 10);
  std::generate(v.begin(), v.end(), std::bind(dist, rng));
  std::generate_n(mat.data(), mat.size(), std::bind(dist, rng));
  tutor::MatrixEval(truth.data(), mat.view(), v.data());
  tutor::MatrixEval_t(result.data(), mat.view(), v.data());
  REQUIRE(result == truth);
}

TEST_CASE("Gemm_t", "[assignment-2]") {
  constexpr size_t n = 10;
  constexpr size_t m = 15;
  constexpr size_t l = 200;
  Matrix<int> lhs(n, l), rhs(l, m), truth(n, m), result(n, m);
  std::mt19937 rng(Catch::getSeed());
  auto dist = std::uniform_int_distribution(-3, 3);
  std::generate_n(lhs.data(), lhs.size(), std::bind(dist, rng));
  std::generate_n(rhs.data(), rhs.size(), std::bind(dist, rng));
  tutor::Gemm(truth.view(), lhs.view(), rhs.view());
  tutor::Gemm_t(result.view(), lhs.view(), rhs.view());
  REQUIRE(result == truth);
}
