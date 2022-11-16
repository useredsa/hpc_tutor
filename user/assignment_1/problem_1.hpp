#ifndef HPC_TUTOR_ASSIGNMENT_1_PROBLEM_1_HPP_
#define HPC_TUTOR_ASSIGNMENT_1_PROBLEM_1_HPP_

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/matrix.hpp"

using Matrix = tutor::MatrixView<double>;

/**
 * This functions work for a (n, 12) matrix representing
 * the average temperature of each month.
 */

/**
 * Returns the month with the highest average temperature in a year.
 * Assumes n = 1.
 */
size_t HottestMonth(const Matrix& m);

/**
 * Returns the year with the highest average temperature.
 *
 * If there is more than one such year, returns the first.
 */
size_t HottestYear(const Matrix& m);

/**
 * Computes the average increase from June to October.
 */
double AverageIncreaseJuneToOctober(const Matrix& m);

#endif  // HPC_TUTOR_ASSIGNMENT_1_PROBLEM_1_HPP_
