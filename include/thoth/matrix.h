#ifndef __THOTH_MATRIX_H__
#define __THOTH_MATRIX_H__

#include <_thoth_config.h>
#include <thoth/concepts.h>
#include <thoth/utils.h>

#include <memory>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace thoth {
// template<typename T, int n, int... dims>
// class Matrix { };

// template<typename T, int a, int b>
// class Matrix<T, a, b> { };

enum class MatrixBroadcastType : char { kEqual, kBroadcast };

template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj);

// Was going to be in anon namespace but it's good!
// However, BroadcastType cant be in Matrix therefore called MAtrixBroadcastType
template <typename T, typename U>
MatrixBroadcastType Broadcastable(const Matrix<T>*& lhs, const Matrix<U>*& rhs);

template <typename T>
class Matrix  // Its a header, it doesn't need to be exported
{
 public:
  using size_type = int;

  constexpr Matrix(std::initializer_list<size_type> dimensions,
                   std::initializer_list<T> values);

  constexpr Matrix(std::initializer_list<size_type> dimensions, const T& value);

  constexpr explicit Matrix(std::initializer_list<size_type> dimensions);

  static constexpr Matrix Zeros(std::initializer_list<size_type> dimensions);

  template <class InputIt>
  constexpr Matrix(std::initializer_list<size_type> dimensions, InputIt first,
                   InputIt last);

  // Could =default as I dont know what im doing but I will try with both
  constexpr Matrix(Matrix&& other);  // is it trivial?

  // copy ctor must be manually written as shared_ptr copy is "non" trivial
  constexpr Matrix(const Matrix& other);

  template <typename V>
  static constexpr Matrix ZerosLike(const Matrix<V>& other);

  template <typename V>
  static constexpr Matrix Like(const Matrix<V>& other);

  constexpr const std::vector<size_type>& Shape() const noexcept {
    return this->dimensions_;
  }

  constexpr const size_type& Size() const noexcept {
    return this->flattened_dims_;
  }

  template <CONSTRAINT(Comparable<T>) U>
  Matrix<bool> operator<=>(const Matrix<U>& rhs);

  //[] operator for flat access
  T& operator[](size_type i) { return (*values_)[i]; }
  constexpr T& operator[](size_type i) const { return (*values_)[i]; }

  // Matrix<T>& operator[](std::initializer_list<size_type> indicies);
  // const Matrix<T>& operator[](std::initializer_list<size_type> indicies)
  // const;

  // Plus and mult operators
  template <CONSTRAINT(Addable<T>) U>
  Matrix& operator+=(const U& scalar);

  template <CONSTRAINT(Addable<T>) U>
  Matrix& operator+=(const Matrix<U>& rhs);

  template <typename V, CONSTRAINT(Addable<V>) U>
  friend Matrix<V> operator+(Matrix<V> matrix, const U& scalar) {
    matrix += scalar;
    return matrix;
  };

  template <CONSTRAINT(Addable<T>) U>
  friend Matrix operator+(Matrix lhs, const Matrix<U>& rhs) {
    lhs += rhs;
    return lhs;
  };

  template <CONSTRAINT(Multiplyable<T>) U>
  Matrix& operator*=(const U& scalar);

  template <CONSTRAINT(Multiplyable<T>) U>
  Matrix& operator*=(const Matrix<U>& rhs);

  template <typename V, CONSTRAINT(Multiplyable<V>) U>
  friend Matrix<V> operator*(Matrix<V> matrix, const U& scalar) {
    matrix *= scalar;
    return matrix;
  };

  template <typename V, CONSTRAINT(Multiplyable<V>) U>
  friend Matrix<V> operator*(Matrix<V> lhs, const Matrix<U>& rhs) {
    lhs *= rhs;
    return lhs;
  };

  // friend std::ostream& operator<< <T>(std::ostream& os, const Matrix& obj);

 private:
  // Just to save typeing hence private
  using dimensions_type = const std::vector<size_type>;

  constexpr explicit Matrix(const std::vector<size_type>& dimensions);

  constexpr Matrix(const std::vector<size_type>& dimensions, const T& value);

  // Be sure to re read move semantics
  constexpr explicit Matrix(std::vector<size_type>&& dimensions,
                            std::vector<T>&& values);

  // static constexpr

  // Datamember order matters! (for member init list)!
  dimensions_type dimensions_;  // const (its in the using which i dont like)

  // Cant be constexpr but all constructors are :(
  const size_type flattened_dims_;  // may be too small but want it to be solid
                                    // on 32 bit machines too

  std::shared_ptr<std::vector<T>> values_;
};

template <>
class Matrix<bool>;

/////////////////////////////////////////////////////////////////////////////
//////////////////////// Constructors ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template <typename T>
constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions,
                            std::initializer_list<T> values)
    : dimensions_(dimensions),
      flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(values)) {}

template <typename T>
constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions,
                            const T& value)
    : dimensions_(dimensions),
      flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(flattened_dims_, value)) {}

template <typename T>
constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions)
    : dimensions_(dimensions),
      flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(flattened_dims_)) {}

// Private:
template <typename T>
constexpr Matrix<T>::Matrix(const std::vector<size_type>& dimensions)
    : dimensions_(dimensions),
      flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(flattened_dims_)) {}

// Private
template <typename T>
constexpr Matrix<T>::Matrix(const std::vector<size_type>& dimensions,
                            const T& value)
    : dimensions_(dimensions),
      flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(flattened_dims_, value)) {}

// Private
template <typename T>
constexpr Matrix<T>::Matrix(std::vector<size_type>&& dimensions,
                            std::vector<T>&& values)
    : dimensions_(std::move(dimensions)),
      flattened_dims_(std::reduce(dimensions_.begin(), dimensions_.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(std::move(values)))

{}

template <typename T>
constexpr Matrix<T> Matrix<T>::Zeros(
    std::initializer_list<size_type> dimensions) {
  return Matrix(dimensions, (T)0);
}

template <typename T>
template <class InputIt>
constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions,
                            InputIt first, InputIt last)
    : dimensions_(dimensions),
      flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1,
                                  std::multiplies<size_type>())),
      values_(first, last) {}

template <typename T>
constexpr Matrix<T>::Matrix(Matrix&& other)
    : dimensions_(std::move(other.dimensions_)),
      flattened_dims_(std::move(other.flattened_dims_)),
      values_(std::move(other.values_)) {}

template <typename T>
constexpr Matrix<T>::Matrix(const Matrix& other)
    : dimensions_(other.dimensions_),
      flattened_dims_(other.flattened_dims_),
      values_(std::make_shared<std::vector<T>>(*other.values_)) {}

template <typename T>
template <typename V>
constexpr Matrix<T> Matrix<T>::ZerosLike(const Matrix<V>& other) {
  return Matrix(other.Shape(), (T)0);
}

template <typename T>
template <typename V>
constexpr Matrix<T> Matrix<T>::Like(const Matrix<V>& other) {
  return Matrix(other.Shape());
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//////////////////////// Operators //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*
template <typename T>
Matrix<T>& Matrix<T>::operator[](std::initializer_list<size_type> indicies) {
  return (*this)[*indicies.begin()];
}
*/

template <typename T>
template <CONSTRAINT(Comparable<T>) U>
Matrix<bool> Matrix<T>::operator<=>(const Matrix<U>& rhs) {
  // Order is arbitary as long as the dims are in the same order
  dimensions_type* smaller_matrix_dimensions = &(this->dimensions_);
  dimensions_type* larger_matrix_dimensions = &(rhs.dimensions_);

  Min(smaller_matrix_dimensions, larger_matrix_dimensions,
      this->dimensions_.size(), rhs.dimensions_.size());

  // Now smaller_matrix_dimensions is the smaller of the two;

  dimensions_type::size_type smaller_dims_size =
      smaller_matrix_dimensions->size();
  dimensions_type::size_type larger_dims_size =
      larger_matrix_dimensions->size();

  std::vector<bool> equality_vector(larger_dims_size, false);

  for (dimensions_type::size_type i = 0; i < smaller_dims_size; ++i) {
    equality_vector[i] = (this->values_[i] <=> rhs.values_[i]);
  }
}

template <typename T>
template <CONSTRAINT(Addable<T>) U>
Matrix<T>& Matrix<T>::operator+=(const U& scalar) {
  // std::for_each is equal in release but I do a lotta debug work so......
  for (typename std::vector<T>::size_type i = 0; i < this->values_->size();
       ++i) {
    (*this->values_)[i] += scalar;
  }
  return *this;
}

template <typename T>
template <CONSTRAINT(Addable<T>) U>
Matrix<T>& Matrix<T>::operator+=(const Matrix<U>& rhs) {
  for (size_type i = 0; i < this->values_->size(); ++i) {
    this->values_->[i] += rhs->values_->[i];
  }

  return this;
}

template <typename T>
template <CONSTRAINT(Multiplyable<T>) U>
Matrix<T>& Matrix<T>::operator*=(const U& scalar) {
  // std::for_each is equal in release but I do a lotta debug work so......
  for (size_type i = 0; i < this->values_->size(); ++i) {
    this->values_[i] *= scalar;
  }
  return *this;
}

template <typename T>
template <CONSTRAINT(Multiplyable<T>) U>
Matrix<T>& Matrix<T>::operator*=(const Matrix<U>& rhs) {
  const Matrix<T>* matrix_a = this;
  const Matrix<U>* matrix_b = &rhs;

  switch (Broadcastable(matrix_a, matrix_b)) {
    case MatrixBroadcastType::kEqual:
      for (dimensions_type::size_type i = 0; i < this->values_->size(); ++i) {
        (*this->values_)[i] *= (*rhs.values_)[i];
      }
      break;
    case MatrixBroadcastType::kBroadcast:
      return *this;
      break;
  }
  return *this;
}

template <typename T, typename U>
MatrixBroadcastType Broadcastable(const Matrix<T>*& lhs,
                                  const Matrix<U>*& rhs) {
  const auto lhs_dim_size = lhs->Shape().size();
  const auto rhs_dim_size = rhs->Shape().size();

  if (lhs_dim_size == rhs_dim_size) {
    if (lhs->Shape() != rhs->Shape()) {
      throw std::domain_error(
          "For Matricies with equal length dimensions the dimensions must be "
          "equal.");
    } else {
      return MatrixBroadcastType::kEqual;
    }
  } else {
    Min(&lhs, &rhs, lhs_dim_size, rhs_dim_size);

    // lhs is now has the smaller matrix dimensions

    const auto& smaller_matrix_dimensions = lhs->Shape();
    const auto& larger_matrix_dimensions = rhs->Shape();

    // by value so ...... dont need const?
    auto smaller_dims_size = smaller_matrix_dimensions.size();

    // larger > smaller is garunteed but does auto know this?
    auto dim_size_diff = larger_matrix_dimensions.size() - smaller_dims_size;

    // dangerous to iterate backwards as vector's sizetype is unsigned
    for (decltype(smaller_dims_size) i = 0; i < smaller_dims_size; ++i) {
      if (larger_matrix_dimensions[i + dim_size_diff] !=
          smaller_matrix_dimensions[i]) {
        throw std::domain_error(
            "For Matricies with different length dimensions the dimensions of "
            "the smaller matrix must match the final dimensions of the longer "
            "matrix.");
      }
    }
    return MatrixBroadcastType::kBroadcast;
  }
}

/////////////////////////////////////////////////////////////////////////////////

// Simpler than you thought (I hope) remember we print in 2d
// For now we'll ignore the brackets (in some cases) as I dont think I'm ready
// for that yet
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj) {
  const auto ndims = obj.Shape().size();

  if (ndims == 1) {
    os << "[ ";
    for (Matrix<T>::size_type i = 0; i < obj.Size(); ++i) {
      os << " " << obj[i];
      if (i < obj.Size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    return os;
  }
  // else

  Matrix<T>::size_type index = 0;
  const auto column_mod = obj.Shape()[ndims - 1];
  const auto row_mod = obj.Shape()[ndims - 2] * column_mod;
  const auto block_mod = row_mod * (ndims > 2 ? obj.Shape()[ndims - 3] : 1);


  while (index < obj.Size()) {
    os << obj[index];
   
    if (index % column_mod < column_mod - 1)
    {
      os << ", ";
    }

    ++index;  // Good to increment before checks if poss (avoids +1's in mod)

    if (ndims > 2 && index % block_mod == 0) {
      os << "\n\n\n";
    }
    else if (index % row_mod == 0) //will always be 0 if previous is
    {
      os << "\n\n";
    } 
    else if (index % column_mod == 0) //will always be 0 if previous is
    {
      os << "\n";
    }
  }

  return os;
}

/////////////////////////////////////////////////////////////////////////////

}  // namespace thoth

#endif
