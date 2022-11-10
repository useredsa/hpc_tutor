#ifndef HPC_TUTOR_MATRIX_HPP_
#define HPC_TUTOR_MATRIX_HPP_

#include <vector>

#include "matrix_view.hpp"

namespace tutor {

/**
 * HPC Tutor Matrix Class.
 *
 * Matrix is a container class representing a rectangular matrix
 * that can change in size.
 *
 * The Matrix class is greatly based in the class std::vector.
 * It uses contiguous storage locations for its elements,
 * which means that their elements can also be accessed
 * using offsets on regular pointers to its elements.
 * Both of its dimensions can change dynamically,
 * with their storage being handled automatically by the container.
 */
template <typename T>
class Matrix {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using row_reference = T*;
  using const_row_reference = const T*;

  // TODO(edsa): Write constructors, destructor, assignment operators
  // and their tests using Catch2.

  /**
   * Empty matrix constructor (default constructor).
   *
   * Constructs an empty Matrix with no elements.
   */
  constexpr Matrix() noexcept : rows_(0), columns_(0) {}

  /**
   * Fill constructor.
   *
   * Constructs a matrix of size n x m.
   * Each element is default initialized.
   */
  constexpr Matrix(size_type n, size_type m)
      : rows_(n), columns_(m), data_(n * m) {}

  /**
   * Fill constructor.
   *
   * Constructs a matrix of size n x m.
   * Each element is a copy of val.
   */
  constexpr Matrix(size_type n, size_type m, const value_type& val)
      : rows_(n), columns_(m), data_(n * m, val) {}

  /**
   * Copy constructor.
   *
   * Constructs a matrix with the same size as m
   * and a copy of its contents.
   */
  constexpr Matrix(const Matrix& m) = default;

  /**
   * Move constructor.
   *
   * The ownership from the elements of m is moved to the constructed object.
   * The element m is left in an unspecified but valid state.
   */
  constexpr Matrix(Matrix&& m) noexcept { *this = m; }

  /**
   * Initializer list constructor.
   *
   * Constructs a matrix with a copy of the elements of ill.
   * If not all lists contains the same amount of elements,
   * the missing positions are default initialized.
   */
  constexpr Matrix(
      std::initializer_list<std::initializer_list<value_type>> ill) {
    *this = ill;
  }

  /**
   * Destructor.
   *
   * Destructs the vector.
   * The destructors of the elements are called
   * and the used storage is deallocated.
   */
  constexpr ~Matrix() = default;

  /**
   * Copy assignment operator.
   *
   * Resizes the matrix to match m and copies its contents.
   */
  constexpr Matrix& operator=(const Matrix& m) = default;

  /**
   * Move assignment operator.
   *
   * Replaces the contents of the matrix with those of m using move semantics.
   * The element m is left in an unspecified but valid state.
   */
  constexpr Matrix& operator=(Matrix&& m) noexcept {
    rows_ = m.rows_;
    columns_ = m.columns_;
    data_ = std::move(m.data_);
    m.rows_ = m.columns_ = 0;

    return *this;
  }

  /**
   * Initializer list assignment operator.
   *
   * Replaces the contents with those identified by initializer list.
   * If not all lists contains the same amount of elements,
   * the missing positions are default initialized.
   */
  constexpr Matrix& operator=(
      std::initializer_list<std::initializer_list<value_type>> ill) {
    // TODO: review this function (initialization and vector iterator)
    rows_ = ill.size();
    columns_ = 0;
    for (auto& row : ill) {
      columns_ = std::max(columns_, row.size());
    }

    data_.resize(rows_ * columns_);
    auto it = data_.begin();
    for (auto& row : ill) {
      for (auto& col : row) {
        *(it++) = col;
      }
    }

    return *this;
  }

  /**
   * Returns a view of the matrix.
   * It can be used to specify a sub-matrix by using startRow and startCol
   */
  constexpr MatrixView<value_type> view(size_type rows, size_type cols,
                                        size_type startRow = 0,
                                        size_type startCol = 0) const {
    return MatrixView<value_type>(*this, rows, cols, startRow, startCol);
  }

  /**
   * Resizes the matrix and initializes its elements with a copy of val.
   */
  constexpr void assign(size_type n, size_type m, const value_type& val) {
    rows_ = n;
    columns_ = m;
    data_.assign(n * m, val);
  }

  /**
   * Returns value of the matrix at position (i, j)
   */
  [[nodiscard]] constexpr value_type& operator()(size_type i,
                                                 size_type j) const {
    return data_[i][j];
  }

  /**
   * Returns a reference to the ith row.
   */
  [[nodiscard]] constexpr row_reference operator[](size_type i) noexcept {
    return &data_[i * columns_];
  }

  /**
   * Returns a const reference to the ith row.
   */
  [[nodiscard]] constexpr const_row_reference operator[](
      size_type i) const noexcept {
    return &data_[i * columns_];
  }

  /**
   * Returns a pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + rows()*columns())
   * is valid.
   */
  [[nodiscard]] constexpr value_type* data() noexcept { return data_.data(); }

  /**
   * Returns a const pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + rows()*columns())
   * is valid.
   */
  [[nodiscard]] constexpr value_type* data() const noexcept {
    return data_.data();
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
   * Returns the number of rows of the matrix.
   */
  [[nodiscard]] constexpr size_type rows() const noexcept { return rows_; }

  /**
   * Returns the number of columns of the matrix.
   */
  [[nodiscard]] constexpr size_type columns() const noexcept {
    return columns_;
  }

 private:
  size_type rows_;
  size_type columns_;
  std::vector<T> data_;
};

// TODO(edsa): Write comparison operator.

// template <typename T>
// constexpr auto operator<=>(const Matrix& lhs, const Matrix& rhs) noexcept;

}  // namespace tutor

#endif  // HPC_TUTOR_MATRIX_HPP_
