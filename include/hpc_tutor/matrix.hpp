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
  constexpr Matrix() : dim_one_(0), dim_two_(0), container_() {}

  /**
   * Fill constructor.
   *
   * Constructs a matrix of size n x m.
   * Each element is default initialized.
   */
  constexpr Matrix(size_type n, size_type m)
      : dim_one_(n), dim_two_(m), container_(n * m) {}

  /**
   * Fill constructor.
   *
   * Constructs a matrix of size n x m.
   * Each element is a copy of val.
   */
  constexpr Matrix(size_type n, size_type m, const value_type& val)
      : dim_one_(n), dim_two_(m), container_(n * m, val) {}

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
  constexpr Matrix(Matrix&& m) noexcept {
    dim_one_ = m.dim_one_;
    dim_two_ = m.dim_two_;
    container_ = std::move(m.container_);
    m.dim_one_ = m.dim_two_ = 0;
  }

  /**
   * Initializer list constructor.
   *
   * Constructs a matrix with a copy of the elements of ill.
   * If not all lists contains the same amount of elements,
   * the missing positions are default initialized.
   */
  constexpr Matrix(
      std::initializer_list<std::initializer_list<value_type>> ill);

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
    dim_one_ = m.dim_one_;
    dim_two_ = m.dim_two_;
    container_ = std::move(m.container_);
    m.dim_one_ = m.dim_two_ = 0;
  }

  /**
   * Initializer list assignment operator.
   *
   * Replaces the contents with those identified by initializer list.
   * If not all lists contains the same amount of elements,
   * the missing positions are default initialized.
   */
  constexpr Matrix& operator=(
      std::initializer_list<std::initializer_list<value_type>> ill);

  /**
   * Resizes the matrix and initializes its elements with a copy of val.
   */
  constexpr void assign(size_type n, size_type m, const value_type& val) {
    dim_one_ = n;
    dim_two_ = m;
    container_.assign(n * m, val);
  }

  /**
   * Returns a reference to the ith row.
   */
  [[nodiscard]] constexpr row_reference operator[](size_type i) noexcept {
    return &container_[i * dim_two_];
  }

  /**
   * Returns a const reference to the ith row.
   */
  [[nodiscard]] constexpr const_row_reference operator[](
      size_type i) const noexcept {
    return &container_[i * dim_two_];
  }

  /**
   * Returns a pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + dim_one()*dim_two())
   * is valid.
   */
  [[nodiscard]] constexpr value_type* data() noexcept {
    return container_.data();
  }

  /**
   * Returns a const pointer to the underlying array serving as element storage.
   *
   * The pointer is such that the data in the range
   * [data(), data() + size()) or [data(), data() + dim_one()*dim_two())
   * is valid.
   */
  [[nodiscard]] constexpr value_type* data() const noexcept {
    return container_.data();
  }

  /**
   * Checks if the Matrix has no elements.
   */
  [[nodiscard]] constexpr bool empty() const noexcept { return dim_one_ == 0; }

  /**
   * Returns the total number of elements of the matrix.
   */
  [[nodiscard]] constexpr size_type size() const noexcept {
    return dim_one_ * dim_two_;
  }

  /**
   * Returns the number of rows of the matrix.
   */
  [[nodiscard]] constexpr size_type dim_one() const noexcept {
    return dim_one_;
  }

  /**
   * Returns the number of columns of the matrix.
   */
  [[nodiscard]] constexpr size_type dim_two() const noexcept {
    return dim_two_;
  }

 private:
  size_type dim_one_;
  size_type dim_two_;
  std::vector<T> container_;
};

// TODO(edsa): Write comparison operator.

// template <typename T>
// constexpr auto operator<=>(const Matrix& lhs, const Matrix& rhs) noexcept;

}  // namespace tutor

#endif  // HPC_TUTOR_MATRIX_HPP_
