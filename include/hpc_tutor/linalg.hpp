#ifndef HPC_TUTOR_LINALG_HPP_
#define HPC_TUTOR_LINALG_HPP_

#include <algorithm>

#include "matrix_view.hpp"

namespace tutor {

// TODO(edsa): consider size checks in the functions and throwing.

/**
 * Vector-Scalar Multiplication.
 */
template <typename T>
void ScalarMul(T* data, size_t n, T val) {
  for (size_t i = 0; i < n; ++i) {
    data[i] *= val;
  }
}

/**
 * Accumulation.
 */
template <typename T>
T Accumulate(const T* data, size_t n) {
  T sum = 0;
  for (size_t i = 0; i < n; ++i) {
    sum += data[i];
  }
  return sum;
}

/**
 * Vector Inner Product.
 */
template <typename T>
T Inner(const T* lhs, const T* rhs, size_t n) {
  T sum = 0;
  for (size_t i = 0; i < n; ++i) {
    sum += lhs[i] * rhs[i];
  }
  return sum;
}

/**
 * Vector Addition.
 */
template <typename T>
void VectorSum(T* ret, const T* lhs, const T* rhs, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    ret[i] = lhs[i] + rhs[i];
  }
}

/**
 * Matrix by Vector Multiplication.
 */
template <typename T>
void MatrixEval(T* ret, const MatrixView<T>& m, const T* v) {
  for (size_t i = 0; i < m.rows(); ++i) {
    ret[i] = 0;
    for (size_t j = 0; j < m.cols(); ++j) {
      ret[i] += m[i][j] * v[j];
    }
  }
}

/**
 * (Trivial) General Matrix Multiplication Routine.
 *
 * This functions multiplies the matrices `lhs` and `rhs`
 * and adds (not stores) the result to `ret`.
 * The sizes of `ret`, `lhs` and `rhs` must be (n, m), (n, l) and (l, m)
 * for some numbers n, m and l.
 */
template <typename T>
void Gemm(MatrixView<T> ret, const MatrixView<T>& lhs,
          const MatrixView<T>& rhs) {
  // Gustavson's ordering.
  for (size_t i = 0; i < ret.rows(); ++i) {
    for (size_t k = 0; k < lhs.cols(); ++k) {
      for (size_t j = 0; j < ret.cols(); ++j) {
        ret[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }
}

/**
 * General Matrix Multiplication Routine.
 *
 * This functions must produce the same result
 * and requires the same conditions as `Gemm`.
 * However, this function performs the decomposition in a cache friendly way.
 */
template <typename T>
void Gemm_Block(MatrixView<T> ret, const MatrixView<T>& lhs,
                const MatrixView<T>& rhs, size_t nbs, size_t mbs, size_t lbs) {
  // TODO(exercise): Implement this for the first assignment.
  Gemm(ret, lhs, rhs);
}

/**
 * Transposes a matrix in place.
 */
template <typename T>
void Transpose(MatrixView<T> m) {
  for (size_t i = 0; i < m.rows(); ++i) {
    for (size_t j = i + 1; j < m.cols(); ++j) {
      std::swap(m[i][j], m[j][i]);
    }
  }
}

/**
 * LU Factorization Routine.
 *
 * This function receives a square matrix
 * for which the LU facotirzation exists
 * and computes it in place.
 * After the call,
 * the diagonal and upper half of `m` store the upper triangular matrix
 * and the lower half stores the lower triangular matrix.
 * The diagonal of the lower triangular matrix is composed on ones
 * and it is not stored explicitely.
 */
template <typename T>
void LuFact(MatrixView<T> m) {
  // TODO(exercise): Implement this for the first assignment.
}

/**
 * Solves a matricial equation Lx = b
 * given by a lower triangular matrix L which has ones in the diagonal.
 * The elements in the diagonal or above are not accessed.
 */
template <typename T>
void SolveLowerIdentity(T* x, const MatrixView<T>& l, const T* b) {
  // TODO(exercise): Implement this for the first assignment.
}

/**
 * Solves a matricial equation Ux = b given by an upper triangular matrix U.
 *
 * The elements below the diagonal are not accessed.
 */
template <typename T>
void SolveUpper(T* x, const MatrixView<T>& u, const T* b) {
  // TODO(exercise): Implement this for the first assignment.
}

/**
 * LU Factorization Routine.
 *
 * This functions must produce the same result
 * and requires the same conditions as `LuFact`.
 * However, this function performs the decomposition in a cache friendly way.
 */
template <typename T>
void LuFact_Block(MatrixView<T> m, size_t bs) {
  // TODO(exercise): Implement this for the first assignment.
}

/**
 * Performs GEMM using an LU decomposition.
 */
template <typename T>
void Multiply_Lu(T* ret, const MatrixView<T>& l, const MatrixView<T>& u) {
  // TODO(exercise): Implement this for the first assignment.
}

}  // namespace tutor

#endif  // HPC_TUTOR_LINALG_HPP_
