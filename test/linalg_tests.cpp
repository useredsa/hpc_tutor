#include <algorithm>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>
#include <random>

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/matrix.hpp"

template <typename T>
using Matrix = tutor::Matrix<T>;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("GEMM by Identity", "[builtin-linalg]") {
  constexpr size_t n = 10;
  constexpr size_t m = 50;
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  auto id = Matrix<double>::eye(n);
  Matrix<double> a(n, m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      a[i][j] = rfloating(rng);
    }
  }
  Matrix<double> b(n, m);
  tutor::Gemm(b.view(), id.view(), a.view());
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      INFO("Failed at element b[" << i << ", " << j << "]");
      REQUIRE_THAT(b[i][j],
                   WithinRel(a[i][j], 1e-6) || WithinAbs(a[i][j], 1e-6));
    }
  }
}

TEST_CASE("GEMM", "[builtin-linalg]") {
  Matrix<double> lhs = {{6, 1, -2}, {-3, 5, 7}};
  Matrix<double> rhs = {{6, 6}, {1, -1}, {6, 1}};
  Matrix<double> ret(2, 2);
  Matrix<double> ans = {{25, 33}, {29, -16}};
  Gemm(ret.view(), lhs.view(), rhs.view());
  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      INFO("Failed at element b[" << i << ", " << j << "]");
      REQUIRE_THAT(ret[i][j],
                   WithinRel(ans[i][j], 1e-6) || WithinAbs(ans[i][j], 1e-6));
    }
  }
}

TEST_CASE("Gemm_Block", "[assignment-1]") {
  constexpr size_t n = 10;
  constexpr size_t m = 50;
  constexpr size_t k = 20;
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  auto id = Matrix<double>::eye(n);
  Matrix<double> lhs(n, k);
  Matrix<double> rhs(k, m);
  Matrix<double> gemm(n, m);
  Matrix<double> blck(n, m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < k; ++j) {
      lhs[i][j] = rfloating(rng);
    }
  }
  for (size_t i = 0; i < k; ++i) {
    for (size_t j = 0; j < m; ++j) {
      rhs[i][j] = rfloating(rng);
    }
  }
  tutor::Gemm(gemm.view(), lhs.view(), rhs.view());
  size_t nbs = GENERATE(2, 3, 4, 5);
  size_t mbs = GENERATE(2, 3, 4, 5, 13);
  size_t lbs = GENERATE(2, 3, 4, 5, 13);
  tutor::Gemm_Block(blck.view(), lhs.view(), rhs.view(), nbs, mbs, lbs);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      INFO("Failed at element b[" << i << ", " << j << "]");
      REQUIRE_THAT(blck[i][j],
                   WithinRel(gemm[i][j], 1e-6) || WithinAbs(gemm[i][j], 1e-6));
    }
  }
}

TEST_CASE("LuFact", "[assignment-1]") {
  constexpr size_t n = 30;
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  Matrix<double> m(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      m[i][j] = rfloating(rng);
    }
  }
  Matrix<double> lu = m;
  tutor::LuFact(lu.view());
  Matrix<double> l(n, n), u(n, n), p(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < i; ++j) {
      l[i][j] = lu[i][j];
    }
    l[i][i] = 1;
    for (size_t j = i; j < n; ++j) {
      u[i][j] = lu[i][j];
    }
  }
  tutor::Gemm(p.view(), l.view(), u.view());
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      INFO("(l*u)[" << i << ", " << j << "] != m[" << i << ", " << j << "]");
      REQUIRE_THAT(p[i][j],
                   WithinRel(m[i][j], 1e-6) || WithinAbs(m[i][j], 1e-6));
    }
  }
}

TEST_CASE("LuFact_Block", "[assignment-1]") {
  constexpr size_t n = 31;
  std::mt19937 rng(Catch::getSeed());
  auto rfloating = std::uniform_real_distribution{};
  Matrix<double> m(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      m[i][j] = rfloating(rng);
    }
  }
  Matrix<double> lu = m;
  tutor::LuFact(m.view());
  size_t bs = GENERATE(1, 3, 4, 16, 17, 22);
  tutor::LuFact_Block(lu.view(), bs);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      INFO("Block LU fact (bs = " << bs << ") differs at " << i << ", " << j);
      REQUIRE_THAT(lu[i][j],
                   WithinRel(m[i][j], 1e-6) || WithinAbs(m[i][j], 1e-6));
    }
  }
}

TEST_CASE("SolveLower and SolveUpper", "[assignment-1]") {
  Matrix<double> m = {{6, 18, 3}, {2, 12, 1}, {4, 15, 3}};
  std::vector<double> b = {3, 19, 0};
  std::vector<double> ans = {-3, 3, -11};
  std::vector<double> x(3), y(3);
  tutor::LuFact(m.view());
  tutor::SolveLowerIdentity(y.data(), m.view(), b.data());
  tutor::SolveUpper(x.data(), m.view(), y.data());
  for (size_t i = 0; i < 3; ++i) {
    INFO("x[" << i << "] != " << ans[i]);
    REQUIRE_THAT(x[i], WithinRel(ans[i], 1e-6) || WithinAbs(ans[i], 1e-6));
  }
}
