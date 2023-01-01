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
#include "test_utils.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;

TEST_CASE("Basic LinAlg Benchmarks", "[basic-linalg]") {
  size_t n = GENERATE(500, 1000, 2000, 3000, 4000);
  auto a = RandomMatrix<double>(n, n);
  auto b = RandomMatrix<double>(n, n);
  auto c = RandomMatrix<double>(n, n);
  auto u = RandomVector<double>(n);
  auto v = RandomVector<double>(n);
  auto w = RandomVector<double>(n);
  double scalar = RandomVector<double>(1)[0];
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
  size_t n = GENERATE(500, 1000, 2000, 3000, 4000);
  auto lhs = RandomMatrix<double>(n, n);
  auto rhs = RandomMatrix<double>(n, n);
  auto ret = Matrix<double>(n, n);
  BENCHMARK("Gemm-" + std::to_string(n)) {
    tutor::Gemm(ret.view(), lhs.view(), rhs.view());
    return ret[0][0];
  };
  BENCHMARK("Gemm_b-" + std::to_string(n)) {
    // TODO(exercise): Select proper block sizes.
    tutor::Gemm_b(ret.view(), lhs.view(), rhs.view(), 1, 1, 1);
    return ret[0][0];
  };
}

TEST_CASE("LuFact Benchmark", "[lu]") {
  size_t n = GENERATE(500, 1000, 2000, 3000, 4000);
  auto a = RandomMatrix<double>(n, n);
  auto b = a;
  BENCHMARK("LuFact-" + std::to_string(n)) {
    tutor::LuFact(a.view());
    return a[0][0];
  };
  BENCHMARK("LuFact_b-" + std::to_string(n)) {
    // TODO(exercise): Select proper block sizes.
    tutor::LuFact_b(b.view(), 1);
    return a[0][0];
  };
}
