#include <algorithm>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>
#include <random>

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/matrix.hpp"
#include "test_utils.hpp"

TEST_CASE("GEMM by Identity", "[builtin-linalg]") {
  constexpr size_t n = 10;
  constexpr size_t m = 50;
  auto id = Matrix<double>::eye(n);
  auto mat = RandomMatrix<double>(n, m);
  auto result = Matrix<double>(n, m);
  tutor::Gemm(result.view(), id.view(), mat.view());
  RequireEqual(result, mat);
}

TEST_CASE("GEMM", "[builtin-linalg]") {
  auto lhs = Matrix<double>{{6, 1, -2}, {-3, 5, 7}};
  auto rhs = Matrix<double>{{6, 6}, {1, -1}, {6, 1}};
  auto ans = Matrix<double>{{25, 33}, {29, -16}};
  auto ret = Matrix<double>(2, 2);
  Gemm(ret.view(), lhs.view(), rhs.view());
  RequireEqual(ret, ans);
}

TEST_CASE("Gemm_Block", "[assignment-1]") {
  constexpr size_t n = 10;
  constexpr size_t m = 50;
  constexpr size_t l = 20;
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  auto id = Matrix<double>::eye(n);
  auto lhs = RandomMatrix<double>(n, l);
  auto rhs = RandomMatrix<double>(l, m);
  auto truth = Matrix<double>(n, m);
  auto result = Matrix<double>(n, m);
  tutor::Gemm(truth.view(), lhs.view(), rhs.view());
  size_t nbs = GENERATE(2, 3, 4, 5);
  size_t mbs = GENERATE(2, 3, 4, 5, 13);
  size_t lbs = GENERATE(2, 3, 4, 5, 13);
  tutor::Gemm_Block(result.view(), lhs.view(), rhs.view(), nbs, mbs, lbs);
  INFO("Block sizes were " << nbs << " " << mbs << " " << lbs);
  RequireEqual(result, truth);
}

TEST_CASE("LuFact", "[assignment-1]") {
  constexpr size_t n = 30;
  auto m = RandomMatrix<double>(n, n);
  auto u = m;
  tutor::LuFact(u.view());
  auto l = Matrix<double>(n, n);
  auto mul = Matrix<double>(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < i; ++j) {
      l[i][j] = u[i][j];
      u[i][j] = 0;
    }
    l[i][i] = 1;
  }
  tutor::Gemm(mul.view(), l.view(), u.view());
  INFO("LU factorization:\nL:\n" << l << "\nU:\n" << u);
  RequireEqual(mul, m);
}

TEST_CASE("LuFact_Block", "[assignment-1]") {
  constexpr size_t n = 31;
  auto m = RandomMatrix<double>(n, n);
  auto lu = m;
  tutor::LuFact(m.view());
  size_t bs = GENERATE(1, 3, 4, 16, 17, 22);
  INFO("bs = " << bs);
  tutor::LuFact_Block(lu.view(), bs);
  RequireEqual(lu, m);
}

TEST_CASE("SolveLower and SolveUpper", "[assignment-1]") {
  auto m = Matrix<double>{{6, 18, 3}, {2, 12, 1}, {4, 15, 3}};
  auto v = std::vector<double>{3, 19, 0};
  auto truth = std::vector<double>{-3, 3, -11};
  auto aux = std::vector<double>(3);
  auto result = std::vector<double>(3);
  tutor::LuFact(m.view());
  tutor::SolveLowerIdentity(aux.data(), m.view(), v.data());
  tutor::SolveUpper(result.data(), m.view(), aux.data());
  RequireEqual(result, truth);
}
