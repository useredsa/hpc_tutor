#ifndef HPC_TUTOR_MATRIXVIEW_HPP
#define HPC_TUTOR_MATRIXVIEW_HPP

#include "matrix.hpp"

namespace tutor {

/**
 * HPC Tutor MatrixView Class.
 *
 * MatrixView is a viewer class which provides a new level of abstraction
 * when accessing to Matrix class.
 *
 * The MatrixView class abstracts the user how the storage of the Matrix
 * is organized, providing a new interface to access to the elements
 * of the Matrix. It also brings support for sub-matrices.
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
  constexpr MatrixView() noexcept
      : data_(nullptr), rows_(0), columns_(0), rowStride_(0) {}

  /**
   * Fill constructor.
   *
   * Constructs a MatrixView with same properties as original Matrix.
   */
  constexpr MatrixView(Matrix<value_type>& m) noexcept
      : data_(m.data()),
        rows_(m.rows()),
        columns_(m.columns()),
        rowStride_(m.columns()) {}

  /**
   * Fill constructor.
   *
   * Constructs a MatrixView specifying the dimensions of the sub-matrix.
   */
  constexpr MatrixView(Matrix<value_type>& m, size_type rows, size_type cols,
                       size_type startRow = 0, size_type startCol = 0) noexcept
      : data_(m.data() + (m.columns() * startRow + startCol)),
        rows_(rows),
        columns_(cols),
        rowStride_(m.columns()) {}

  /**
   * Copy constructor.
   *
   * Constructs a MatrixView with the same properties as mv.
   */
  constexpr MatrixView(const MatrixView& mv) = default;

  /**
   * Move constructor.
   *
   * The ownership from the elements of mv is moved to the constructed object.
   * The element mv is left in an unspecified but valid state.
   */
  constexpr MatrixView(MatrixView&& mv) noexcept { *this = mv; }

  /**
   * Destructor.
   *
   * Destructs the view over the Matrix, but does not delete the Matrix.
   */
  ~MatrixView() = default;

  /**
   * Fill operator.
   *
   * Creates a view of the original Matrix m.
   */
  constexpr MatrixView& operator=(const Matrix<value_type>& m) {
    data_ = m.data();
    rows_ = m.rows();
    columns_ = m.columns();
    rowStride_ = m.columns();
    return *this;
  }

  /**
   * Copy assignment operator.
   *
   * Creates a copy of the MatrixView mv.
   */
  constexpr MatrixView& operator=(const MatrixView& mv) = default;

  /**
   * Move assignment operator.
   *
   * Replaces the contents of the matrix with those of m using move semantics.
   * The element m is left in an unspecified but valid state.
   */
  constexpr MatrixView& operator=(MatrixView&& mv) noexcept {
    data_ = mv.data_;
    rows_ = mv.rows_;
    columns_ = mv.columns_;
    rowStride_ = mv.rowStride_;

    mv.data_ = nullptr;
    mv.rows_ = 0;
    mv.columns_ = 0;
    mv.rowStride_ = 0;
    return *this;
  }

  /**
   * Assigns a new matrix to the view.
   * A sub-matrix can be specified by providing the starting row and column.
   */
  constexpr void assign(Matrix<value_type>& m, size_type startRow = 0,
                        size_type startCol = 0) noexcept {
    data_ = m.data() + (m.columns() * startRow + startCol);
    rows_ = m.rows();
    columns_ = m.columns();
    rowStride_ = m.columns();
  }

  /**
   * Returns value of the matrix at position (i, j)
   */
  [[nodiscard]] constexpr value_type& operator()(size_type i, size_type j) {
    return data_[rowStride_ * i + j];
  }

  /**
   * Returns a reference to the ith row.
   */
  [[nodiscard]] constexpr row_reference operator[](size_type i) noexcept {
    return &data_[rowStride_ * i];
  }

  /**
   * Returns a const reference to the ith row.
   */
  [[nodiscard]] constexpr const_row_reference operator[](
      size_type i) const noexcept {
    return &data_[rowStride_ * i];
  }

  /**
   * Checks if the Matrix has no elements.
   */
  [[nodiscard]] constexpr bool empty() const noexcept { return rows_ == 0; }

  /**
   * Returns the total number of elements of the matrix.
   */
  [[nodiscard]] constexpr size_type size() const noexcept {
    return rows_ * columns_;
  }

  /**
   * Returns the number of rows in the matrix.
   */
  [[nodiscard]] constexpr size_type rows() const noexcept { return rows_; }

  /**
   * Returns the number of columns in the matrix.
   */
  [[nodiscard]] constexpr size_type columns() const noexcept {
    return columns_;
  }

 private:
  value_type* data_;
  size_type rows_;
  size_type columns_;
  size_type rowStride_;
};

}  // namespace tutor

#endif  // HPC_TUTOR_MATRIXVIEW_HPP
