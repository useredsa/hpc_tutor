#ifndef HPC_TUTOR_ASSIGNMENT_2_PROBLEM_1_HPP_
#define HPC_TUTOR_ASSIGNMENT_2_PROBLEM_1_HPP_

#include "hpc_tutor/linalg.hpp"
#include "hpc_tutor/matrix.hpp"
#include <omp.h>
#include <vector>

using Matrix = tutor::MatrixView<double>;

/**
 * This functions are for solving MPI exercises
 */

/**
 * Compute matrix-vector multiplicatin in secuential mode
 */
void mv_sec(const Matrix& a, double* b, double* c);

/**
 * Compute matrix-vector multiplication in parallel mode
 */
void mv_par(const Matrix& a, double* b, double* c);

/**
 * Search first ocurrence in secuential mode
 */
int search_sec(double* a, int size, int e);

/**
 * Search first ocurrence in parallel mode
 */
int search_par(double* a, int size, int e);

/**
 * Merge-sort in secuential mode
 */
void merge_sec(double* a, int size);

/**
 * Merge-sort in parallel mode
 */
void merge_par(double* a, int size);

/**
 * Matrix-matrix multiplication in secuential mode
 */
void mm_sec(const Matrix& a,const Matrix& b,Matrix& c);

/**
 * Matrix-matrix multiplication in parallel mode
 */
void mm_par(const Matrix& a,const Matrix& b,Matrix& c);
#endif  // HPC_TUTOR_ASSIGNMENT_2_PROBLEM_1_HPP_
