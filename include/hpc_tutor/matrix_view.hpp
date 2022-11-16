#ifndef HPC_TUTOR_MATRIXVIEW_HPP
#define HPC_TUTOR_MATRIXVIEW_HPP

#include <cstddef>

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
  using size_type = size_t;
  using row_reference = T*;
  using const_row_reference = const T*;

  /**
   * Data Range Constructor.
   *
   * Constructs a MatrixView from a pointer and a valid range.
   */
  constexpr MatrixView(value_type* data, size_type rows, size_type cols,
                       size_type rowStride) noexcept
      : data_(data), rows_(rows), cols_(cols), rowStride_(rowStride) {}

  /**
   * Copy constructor.
   *
   * Constructs a MatrixView with the same properties as mv.
   */
  constexpr MatrixView(const MatrixView& mv) noexcept = default;

  /**
   * Move constructor.
   *
   * The ownership from the elements of mv is moved to the constructed object.
   * The element mv is left in an unspecified but valid state.
   */
  constexpr MatrixView(MatrixView&& mv) noexcept = default;

  /**
   * Destructor.
   *
   * Destructs the view over the Matrix, but does not delete the Matrix.
   */
  ~MatrixView() = default;

  /**
   * Copy assignment operator.
   */
  constexpr MatrixView& operator=(const MatrixView& mv) noexcept = default;

  /**
   * Move assignment operator.
   *
   * Replaces the contents of the matrix with those of m using move semantics.
   * The element m is left in an unspecified but valid state.
   */
  constexpr MatrixView& operator=(MatrixView&& mv) noexcept = default;

  /**
   * Returns a subview of the view.
   */
  constexpr MatrixView<value_type> view(size_type row, size_type col,
                                        size_type rows, size_type cols) const {
    // TODO(edsa): throw if out-of-range.
    return MatrixView<value_type>(data_ + (row * rowStride_ + col), rows, cols,
                                  rowStride_);
  }

  /**
   * Returns a subview of the view.
   */
  constexpr MatrixView<value_type> view(size_type row, size_type col) const {
    return view(row, col, rows_ - row, cols_ - col);
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
   * Returns a pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + rows()*cols())
   * is valid.
   */
  [[nodiscard]] constexpr value_type* data() noexcept { return data_; }

  /**
   * Returns a const pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + rows()*cols())
   * is valid.
   */
  [[nodiscard]] constexpr value_type* data() const noexcept { return data_; }

  /**
   * Checks if the Matrix has no elements.
   */
  [[nodiscard]] constexpr bool empty() const noexcept {
    return rows_ == 0 || cols_ == 0;
  }

  /**
   * Returns the total number of elements of the matrix.
   */
  [[nodiscard]] constexpr size_type size() const noexcept {
    return rows_ * cols_;
  }

  /**
   * Returns the number of rows in the matrix.
   */
  [[nodiscard]] constexpr size_type rows() const noexcept { return rows_; }

  /**
   * Returns the number of columns in the matrix.
   */
  [[nodiscard]] constexpr size_type cols() const noexcept { return cols_; }

 private:
  value_type* data_;
  size_type rows_;
  size_type cols_;
  size_type rowStride_;
};

}  // namespace tutor

#endif  // HPC_TUTOR_MATRIXVIEW_HPP
