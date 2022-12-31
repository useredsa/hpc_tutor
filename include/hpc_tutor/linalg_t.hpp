#ifndef HPC_TUTOR_LINALG_T_HPP_
#define HPC_TUTOR_LINALG_T_HPP_

#include "linalg.hpp"
#include "matrix_view.hpp"

namespace tutor {

/**
 * Element Search in Vector (with thread-level parallelism).
 */
template <typename T>
size_t Find_t(T* v, size_t n, const T& val) {
  // TODO(exercise): Implement this for assignment 2.
  return Find(v, n, val);
}

/**
 * Vector (Merge)Sort (with thread-level parallelism).
 */
template <typename T>
void MergeSort_t(T* v, size_t n) {
  // TODO(exercise): Implement this for assignment 2.
  MergeSort(v, n);
}

/**
 * Matrix by Vector Multiplication (with thread-level parallelism).
 */
template <typename T>
void MatrixEval_t(T* ret, const MatrixView<T>& m, const T* v) {
  // TODO(exercise): Implement this for assignment 2.
  MatrixEval(ret, m, v);
}

/**
 * Matrix Multiplication.
 *
 * This functions multiplies the matrices `lhs` and `rhs`
 * and adds (not stores) the result to `ret`.
 */
template <typename T>
void Gemm_t(MatrixView<T> ret, const MatrixView<T>& lhs,
            const MatrixView<T>& rhs) {
  // TODO(exercise): Implement this for assignment 2.
  Gemm(ret, lhs, rhs);
}

}  // namespace tutor

#endif  // HPC_TUTOR_LINALG_T_HPP_
