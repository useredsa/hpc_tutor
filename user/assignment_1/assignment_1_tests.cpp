#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>
#include <vector>

#include "problem_1.hpp"

static tutor::Matrix<double> Temp = {
    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 5},
    {11, 10, 11, 10, 10, 10, 10, 10, 19, 10, 21, 5},
    {10, 11, 10, 10, 10, 11, 12, 10, 20, 10, 22, 5},
    {50, 10, 50, 10, 10, 15, 16, 10, 21, 10, 23, 5},
    {10, 50, 10, 50, 10, 10, 10, 10, 22, 10, 24, 5},
    {11, 10, 20, 10, 10, 10, 12, 13, 23, 10, 25, 5},
    {10, 11, 30, 30, 30, 30, 30, 30, 30, 10, 26, 5},
    {11, 10, 40, 10, 10, 10, 10, 10, 29, 10, 27, 5},
    {10, 11, 30, 10, 10, 20, 20, 10, 28, 10, 28, 5},
    {11, 10, 20, 10, 10, 10, 10, 10, 27, 10, 29, 5},
    {10, 11, 10, 10, 10, 10, 10, 10, 26, 10, 30, 5}};

TEST_CASE("HottestMonth", "problem_1") {
  for (size_t year = 0; year < Temp.rows(); ++year) {
    size_t hottestMonth =
        std::max_element(Temp[year], Temp[year] + Temp.cols()) - Temp[year];
    size_t studentAns = HottestMonth(Temp.view(year, 0, 1, Temp.cols()));
    INFO("Failed maximum temperature of year " << year);
    REQUIRE(studentAns == hottestMonth);
  }
}

TEST_CASE("HottestYear", "problem_1") {
  std::vector<double> average(Temp.rows(), 1);
  for (size_t year = 0; year < Temp.rows(); ++year) {
    average[year] = std::accumulate(Temp[year], Temp[year] + Temp.cols(), 0.0);
    average[year] /= Temp.cols();
  }
  size_t hottestYear =
      std::max_element(average.begin(), average.end()) - average.begin();
  size_t studentAns = HottestYear(Temp.view());
  REQUIRE(studentAns == hottestYear);
}

TEST_CASE("AverageIncreaseJuneToOctober", "problem_1") {
  constexpr size_t YEAR_BEGIN = 4;
  constexpr size_t YEAR_END = 9;
  double avgIncrease = -6;
  double studentAns = AverageIncreaseJuneToOctober(
      Temp.view(YEAR_BEGIN, 0, YEAR_END - YEAR_BEGIN, 12));
  REQUIRE_THAT(studentAns, Catch::Matchers::WithinRel(avgIncrease, 1e-6) ||
                               Catch::Matchers::WithinAbs(avgIncrease, 1e-6));
}
