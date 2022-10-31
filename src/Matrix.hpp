#ifndef HPC_TUTOR_MATRIX_HPP_
#define HPC_TUTOR_MATRIX_HPP_

#include <vector>

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
  constexpr Matrix() noexcept = default;

  /**
   * Fill constructor.
   *
   * Constructs a matrix of size n x m.
   * Each element is default initialized.
   */
  constexpr Matrix(size_type n, size_type m) { assign(n, m); }

  /**
   * Fill constructor.
   *
   * Constructs a matrix of size n x m.
   * Each element is a copy of val.
   */
  constexpr Matrix(size_type n, size_type m, const value_type& val) {
    assign(n, m, val);
  }

  /**
   * Copy constructor.
   *
   * Constructs a matrix with the same size as m
   * and a copy of its contents.
   */
  constexpr Matrix(const Matrix& m) { this = m; }

  /**
   * Move constructor.
   *
   * The ownership from the elements of m is moved to the constructed object.
   * The element m is left in an unspecified but valid state.
   */
  constexpr Matrix(Matrix&& m) noexcept { this = m; }

  /**
   * Initializer list constructor.
   *
   * Constructs a matrix with a copy of the elements of ill.
   * If not all lists contains the same amount of elements,
   * the missing positions are default initialized.
   */
  constexpr Matrix(
      std::initializer_list<std::initializer_list<value_type>> ill) {
    this = ill;
  }

  /**
   * Destructor.
   *
   * Destructs the vector.
   * The destructors of the elements are called
   * and the used storage is deallocated.
   */
  ~Matrix() = default;

  /**
   * Copy assignment operator.
   *
   * Resizes the matrix to match m and copies its contents.
   */
  constexpr Matrix& operator=(const Matrix& m) {
    _rows = m._rows;
    _columns = m._columns;
    // TODO: review this
    _data = m._data;
  }

  /**
   * Move assignment operator.
   *
   * Replaces the contents of the matrix with those of m using move semantics.
   * The element m is left in an unspecified but valid state.
   */
  constexpr Matrix& operator=(Matrix&& m) noexcept {
    _rows = m._rows;
    _columns = m._columns;
    // TODO: review this
    _data = std::move(m._data);
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
    _rows = ill.size();
    _columns = 0;
    for (auto& row : ill) {
      _columns = std::max(_columns, row.size());
    }
    _data.resize(_rows * _columns);
    size_type i = 0;
    for (auto& row : ill) {
      size_type j = 0;
      for (auto& col : row) {
        _data[i * _columns + j] = col;
        j++;
      }
      i++;
    }
  }

  /**
   * Resizes the matrix.
   */
  constexpr void assign(size_type n, size_type m) {
    // TODO: check, this only changes the val for new elements when increasing
    // size
    _data.resize(n * m);
  }

  /**
   * Resizes the matrix and initializes its elements with a copy of val.
   */
  constexpr void assign(size_type n, size_type m, const value_type& val) {
    _rows = n;
    _columns = m;
    // TODO: check, this only changes the val for new elements when increasing
    // size
    _data.resize(n * m, val);
  }

  /**
   * Returns a reference to the ith row.
   */
  constexpr row_reference operator[](size_type i) noexcept {
    return &_data[i * _columns];
  }

  /**
   * Returns a const reference to the ith row.
   */
  constexpr const_row_reference operator[](size_type i) const noexcept {
    return &_data[i * _columns];
  }

  /**
   * Returns a pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + rows()*columns())
   * is valid.
   */
  constexpr value_type* data() noexcept { return _data.data(); }

  /**
   * Returns a const pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + rows()*columns())
   * is valid.
   */
  constexpr value_type* data() const noexcept { return _data.data(); }

  /**
   * Checks if the Matrix has no elements.
   */
  [[nodiscard]] constexpr bool empty() const noexcept { return _rows == 0; }

  /**
   * Returns the total number of elements of the matrix.
   */
  constexpr size_type size() const noexcept { return _rows * _columns; }

  /**
   * Returns the number of rows of the matrix.
   */
  constexpr size_type rows() const noexcept { return _rows; }

  /**
   * Returns the number of columns of the matrix.
   */
  constexpr size_type columns() const noexcept { return _columns; }

 private:
  size_type _rows;
  size_type _columns;
  std::vector<T> _data;
};

// TODO(edsa): Write constructors, destructor, assignment operators
// and their tests using Catch2.

// template <typename T>
// constexpr auto operator<=>(const Matrix& lhs, const Matrix& rhs) noexcept;

}  // namespace tutor

#endif  // HPC_TUTOR_MATRIX_HPP_
