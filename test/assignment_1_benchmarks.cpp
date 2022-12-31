#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <numeric>
#include <random>
#include <string>

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/matrix.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;

TEST_CASE("Basic LinAlg Benchmarks", "[basic-linalg]") {
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  size_t n = GENERATE(500, 1000, 2000, 3000, 4000);
  Matrix<double> a(n, n), b(n, n), c(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a[i][j] = rfloating(rng);
      b[i][j] = rfloating(rng);
      c[i][j] = rfloating(rng);
    }
  }
  std::vector<double> u(n), v(n), w(n);
  for (size_t i = 0; i < n; ++i) {
    u[i] = rfloating(rng);
    v[i] = rfloating(rng);
    w[i] = rfloating(rng);
  }
  double scalar = rfloating(rng);
  BENCHMARK("VectorScalarMul-" + std::to_string(n)) {
    tutor::ScalarMul(v.data(), n, scalar);
    return u[0];
  };
  BENCHMARK("Inner-" + std::to_string(n)) {
    return tutor::Inner(u.data(), v.data(), n);
  };
  BENCHMARK("VectorSum-" + std::to_string(n)) {
    tutor::VectorSum(u.data(), v.data(), w.data(), n);
    return u[0];
  };
  BENCHMARK("VectorAccumulate-" + std::to_string(n)) {
    return tutor::Accumulate(u.data(), n);
  };
  BENCHMARK("MatrixVectorMul-" + std::to_string(n)) {
    tutor::MatrixEval(u.data(), b.view(), v.data());
    return u[0];
  };
  BENCHMARK("MatrixMatrixMul-" + std::to_string(n)) {
    tutor::Gemm(a.view(), b.view(), c.view());
    return a[0][0];
  };
  BENCHMARK("MatrixTranspose-" + std::to_string(n)) {
    tutor::Transpose(a.view());
    return a[0][0];
  };
}

TEST_CASE("Gemm Benchmark", "[gemm]") {
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  size_t n = GENERATE(500, 1000, 2000, 3000, 4000);
  Matrix<double> a(n, n), b(n, n), c(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a[i][j] = rfloating(rng);
      b[i][j] = rfloating(rng);
      c[i][j] = rfloating(rng);
    }
  }
  BENCHMARK("Gemm-" + std::to_string(n)) {
    tutor::Gemm(a.view(), b.view(), c.view());
    return a[0][0];
  };
  BENCHMARK("Gemm_b-" + std::to_string(n)) {
    // TODO(exercise): Select proper block sizes.
    tutor::Gemm_b(a.view(), b.view(), c.view(), 1, 1, 1);
    return a[0][0];
  };
}

TEST_CASE("LuFact Benchmark", "[lu]") {
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  size_t n = GENERATE(500, 1000, 2000, 3000, 4000);
  Matrix<double> a(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a[i][j] = rfloating(rng);
    }
  }
  Matrix<double> acpy = a;
  BENCHMARK("LuFact-" + std::to_string(n)) {
    tutor::LuFact(a.view());
    return a[0][0];
  };
  BENCHMARK("LuFact_b-" + std::to_string(n)) {
    // TODO(exercise): Select a proper block size.
    tutor::LuFact_b(acpy.view(), 1);
    return a[0][0];
  };
}
