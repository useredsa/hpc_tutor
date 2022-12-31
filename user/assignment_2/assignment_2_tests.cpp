#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>
#include <vector>

#include "problem_1.hpp"

static tutor::Matrix<double> a = {
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


static tutor::Matrix<double> b = {
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
    

static double* v = {11, 10, 20, 10, 10, 10, 10, 10, 27, 10, 29};

double compareM(const Matrix& a, const Matrix& b)
{
	double diff = 0.0;
	
	for(int i = 0; i < a.rows(); i++) 
    for (int j = 0; j < a.cols(); j++)
    {
		  diff += fabs(a[i][j] - b[i][j]);
	  }
	return diff;
}

double compareV(double* a, double* b, int size)
{
	double diff = 0.0;
	
	for(int i = 0; i < a.size; i++)
		  diff += fabs(a[i] - b[i]);
	return diff;
}

TEST_CASE("MM", "problem_1") {
    Matrix c1, c2;
    mm_sec(a,b,c1);
    mm_par(a,b,c2);
    //Check
    double diff = compareM(c1,c2);
    REQUIRE(diff < 0.1);
  }

TEST_CASE("MV", "problem_1") {
    double* v1 = (double*)malloc(sizeof(double)*11);
    double* v2 = (double*)malloc(sizeof(double)*11);
    mv_sec(a,v,v1);
    mv_par(a,v,v2);
    //Check
    double diff = compareV(v1,v2);
    REQUIRE(diff < 0.1);
  }

TEST_CASE("Search", "problem_1") {
    int r1 = search_sec(v,11,27);
    int r2 = search_par(v,11,27);
    REQUIRE(r1 == r2);        
}

TEST_CASE("Merge", "problem_1") {
    static double* v2 = {11, 10, 20, 10, 10, 10, 10, 10, 27, 10, 29};
    static double* v1 = {11, 10, 20, 10, 10, 10, 10, 10, 27, 10, 29};
    merge_sec(v1,11);
    merge_par(v2,11);
    //Check
    double diff = compareV(v1,v2);
    REQUIRE(diff < 0.1);
  }

TEST_CASE("MV", "problem_1") {
    double* v1 = (double*)malloc(sizeof(double)*11);
    double* v2 = (double*)malloc(sizeof(double)*11);
    mv_sec(a,v,v1);
    mv_par(a,v,v2);
    //Check
    double diff = compareV(v1,v2);
    REQUIRE(diff < 0.1);
  }



