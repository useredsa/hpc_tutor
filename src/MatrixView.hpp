#ifndef HPC_TUTOR_MATRIXVIEW_HPP
#define HPC_TUTOR_MATRIXVIEW_HPP

#include "Matrix.hpp"

namespace tutor {

/**
 * HPC Tutor MatrixView Class.
 *
 * MatrixView is a viewer class which provides a new level of abstraction
 * when accessing to Matrix class.
 *
 * The MatrixView class abstracts the user how the storage of the Matrix
 * is organized, providing a new interface to access to the elements
 * of the Matrix. It also brings support for sub-matrices and modifiable
 * views of the original matrix.
 */
template <typename T>
class MatrixView {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using row_reference = T*;
  using const_row_reference = const T*;

  /**
   * Empty matrix constructor (default constructor).
   *
   * Constructs an empty MatrixView without referencing any Matrix.
   */
  constexpr MatrixView() noexcept = default;

  /**
   * Fill constructor.
   *
   * Constructs a MatrixView with same properties as original Matrix.
   */
  constexpr MatrixView(Matrix<value_type>& m, bool modifiable = true) noexcept {
    startRow_ = 0;
    startCol_ = 0;
    rows_ = m.rows();
    columns_ = m.cols();
    modifiable_ = modifiable;
    // TODO: review this
    if (modifiable)
      matrix_ = &m;
    else
      matrix_ = Matrix<value_type>(m);
  }

  /**
   * Fill constructor.
   *
   * Constructs a MatrixView specifying the dimensions of the sub-matrix.
   */
  constexpr MatrixView(Matrix<value_type>& m, size_type startRow,
                       size_type startCol, size_type rows, size_type cols,
                       bool modifiable = true) noexcept {
    startRow_ = startRow;
    startCol_ = startCol;
    rows_ = rows;
    columns_ = cols;
    modifiable_ = modifiable;
    // TODO: review this
    if (modifiable)
      matrix_ = &m;
    else
      matrix_ = Matrix<value_type>(m);
  }

  /**
   * Copy constructor.
   *
   * Constructs a MatrixView with the same properties as mv.
   */
  constexpr MatrixView(const MatrixView& mv) { this = mv; }

  /**
   * Move constructor.
   *
   * The ownership from the elements of mv is moved to the constructed object.
   * The element mv is left in an unspecified but valid state.
   */
  constexpr MatrixView(MatrixView&& mv) noexcept { this = mv; }

  /**
   * Destructor.
   *
   * Destructs the view over the Matrix, but does not delete the Matrix.
   */
  ~MatrixView() = default;

  /**
   * Copy assignment operator.
   *
   * Resizes the matrix to match m and copies its contents.
   */
  constexpr MatrixView& operator=(const MatrixView& mv) {
    startRow_ = mv.startRow_;
    startCol_ = mv.startCol_;
    rows_ = mv.rows_;
    columns_ = mv.columns_;
    modifiable_ = mv.modifiable_;
    // TODO: review this
    matrix_ = mv.matrix_;

    return *this;
  }

  /**
   * Move assignment operator.
   *
   * Replaces the contents of the matrix with those of m using move semantics.
   * The element m is left in an unspecified but valid state.
   */
  constexpr MatrixView& operator=(MatrixView&& mv) noexcept {
    startRow_ = mv.startRow_;
    startCol_ = mv.startCol_;
    rows_ = mv.rows_;
    columns_ = mv.columns_;
    modifiable_ = mv.modifiable_;
    // TODO: review this
    matrix_ = std::move(mv.matrix_);

    return *this;
  }

  /**
   * Returns value of the matrix at position (i, j)
   */
  constexpr value_type& operator()(size_type i, size_type j) const {
    return matrix_[startRow_ + i][startCol_ + j];
  }

  /**
   * Checks if the Matrix has no elements.
   */
  [[nodiscard]] constexpr bool empty() const noexcept { return rows_ == 0; }

  /**
   * Returns the total number of elements of the matrix.
   */
  constexpr size_type size() const noexcept { return rows_ * columns_; }

  /**
   * Returns the number of rows in the matrix.
   */
  constexpr size_type rows() const noexcept { return rows_; }

  /**
   * Returns the number of columns in the matrix.
   */
  constexpr size_type columns() const noexcept { return columns_; }

 private:
  Matrix<value_type>& matrix_;
  size_type startRow_;
  size_type startCol_;
  size_type rows_;
  size_type columns_;
  bool modifiable_;
};

}  // namespace tutor

#endif  // HPC_TUTOR_MATRIXVIEW_HPP
