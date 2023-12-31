﻿#ifndef __THOTH_NDARRAY_H__
#define __THOTH_NDARRAY_H__

#include <_thoth_config.h>

#include <thoth/concepts.h>
#include <thoth/utility.h>

#include <memory>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace thoth {

enum class NdArrayBroadcastType : char { kEqual, kBroadcast };

template <typename T>
class NdArray;

template <typename T>
std::ostream& operator<<(std::ostream& os, const NdArray<T>& obj);

// However, BroadcastType cant be in NdArray therefore called MAtrixBroadcastType
template <typename T, typename U>
NdArrayBroadcastType Broadcastable(const NdArray<T>*& lhs, const NdArray<U>*& rhs);

// I hate how messy template classes are :(
template <typename T>
class NdArray  // Its a header, it doesn't need to be exported
{
 public:
  using size_type = int;
  using slice_type = std::pair<size_type, size_type>;

 private:
#pragma region FINAL_CONSTRUCTORS
  // Final constructor in delegation chain requiring validation
  // Be sure to re read move semantics
  // Does this still need to be explicit?
  constexpr explicit NdArray(std::vector<size_type>&& dimensions,
                            std::vector<T>&& values);

  // Final constructor in delegation chain requiring no validation and is
  // therefore noexcept
  constexpr NdArray(std::vector<size_type>&& dimensions,
                   const T& value) noexcept;

  // Final constructor for view []operator
  // can assume validation has already been completed on the constructor
  // from which this ndarray is a view of.
  constexpr NdArray(std::vector<size_type>&& dimensions,
                   const std::vector<size_type>& strides,
                   const std::shared_ptr<std::vector<T>>& values,
                   T* const data_start) noexcept;

#pragma endregion

 public:
// Public Constructors and constructor like static Members
#pragma region CONSTRUCTORS

  constexpr NdArray(std::initializer_list<size_type> dimensions,
                   const T& value) noexcept
      : NdArray(std::vector(dimensions), value){};

  constexpr NdArray(std::initializer_list<size_type> dimensions,
                   std::initializer_list<T> values)
      : NdArray(std::vector(dimensions), std::vector(values)){};

  // I think this is fine vs not providing T to vector
  constexpr explicit NdArray(
      std::initializer_list<size_type> dimensions) noexcept
      : NdArray(std::vector(dimensions), T()){};

  template <class InputIt>
  constexpr NdArray(std::initializer_list<size_type> dimensions, InputIt first,
                   InputIt last)
      : NdArray(std::vector(dimensions), std::vector(first, last)) {}

  // Works as long as this is compatable with the pointer (test this)
  constexpr NdArray(NdArray&& other) = default;

  // Also a final constructor
  //  copy ctor must be manually written as shared_ptr copy is "non" trivial
  constexpr NdArray(const NdArray& other) noexcept;

  static constexpr NdArray Zeros(std::initializer_list<size_type> dimensions) {
    return NdArray(dimensions, (T)0);
  };

  template <typename V>
  static constexpr NdArray ZerosLike(const NdArray<V>& other) {
    return NdArray(other.Shape(), (T)0);
  }

  template <typename V>
  static constexpr NdArray Like(const NdArray<V>& other) {
    return NdArray(other.Shape());
  }

#pragma endregion

// Properties
#pragma region PROPERTIES

  constexpr const std::vector<size_type>& Shape() const noexcept {
    return this->dimensions_;
  }

  constexpr const size_type& Size() const noexcept {
    return this->flattened_dims_;
  }

#pragma endregion

// Operators
#pragma region OPERATORS

  // Implement convertable types and as type laters
  constexpr NdArray& operator=(const NdArray& other) noexcept;

  constexpr NdArray& operator=(NdArray&& other) = default;

  template <CONSTRAINT(Comparable<T>) U>
  NdArray<bool> operator<=>(const NdArray<U>& rhs);

  //[] operator for flat access. May not be ideal to expose
  // but relativly safe and allows us to unfriend operator<<
  const T& operator[](size_type) const;

  //[] operator for element access
  T& operator[](std::initializer_list<size_type>);
  const T& operator[](std::initializer_list<size_type>) const;

  //[] operator for views / view access
  // const as function wont modify this;
  // however, the returned ndarray shares the same values
  // pairs that create the range [get<0>slice, get<1>slice)
  NdArray operator[](std::initializer_list<slice_type> indicies) const;

  // Plus and mult operators
  template <CONSTRAINT(Addable<T>) U>
  NdArray& operator+=(const U& scalar);

  template <CONSTRAINT(Addable<T>) U>
  NdArray& operator+=(const NdArray<U>& rhs);

  /*
  template <typename V, CONSTRAINT(Addable<V>) U>
  friend NdArray<V> operator+(NdArray<V> ndarray, const U& scalar) {
    ndarray += scalar;
    return ndarray;
  };
  */

  template <CONSTRAINT(Addable<T>) U>
  friend NdArray operator+(NdArray lhs, const NdArray<U>& rhs) {
    lhs += rhs;
    return lhs;
  }

  // GCC not happy with this: template <CONSTRAINT(Multiplyable<T>) U> for some
  // reason I cant work out so im gonna try a cheaky cheat for now.
  template <Numeric U>
  NdArray& operator*=(const U& scalar);

  template <CONSTRAINT(Multiplyable<T>) U>
  NdArray& operator*=(const NdArray<U>& rhs);

  // For the two below leave at least on ndarray type as T (i.e. the one this
  // class uses else redefinition errors (loop somewhere)
  template <CONSTRAINT(Multiplyable<T>) U>
  friend NdArray<T> operator*(NdArray<T> ndarray, const U& scalar) {
    ndarray *= scalar;
    return ndarray;
  }

  // friend in order to allow definition inside class?!?
  template <CONSTRAINT(Multiplyable<T>) U>
  friend NdArray<T> operator*(NdArray<T> lhs, const NdArray<U>& rhs) {
    lhs *= rhs;
    return lhs;
  }

#pragma endregion

 private:
  // Just to save typeing hence private
  using dimensions_type = std::vector<size_type>;

// Private constructors
#pragma region PRIVATE_CONSTRUCTORS
  constexpr NdArray(const std::vector<size_type>& dimensions,
                   const T& value) noexcept
      : NdArray(std::vector(dimensions), value){};

  constexpr explicit NdArray(const std::vector<size_type>& dimensions) noexcept
      : NdArray(std::vector(dimensions), T()){};

  // One more will need to be added

#pragma endregion

#pragma region PRIVATE_OPERATORS
#pragma endregion

#pragma region PRIVATE_UTILITY_FUNCTIONS

  // May be buggy but I can't predict.
  // Is it possible for two different dimensions to have the same strides
  // and a different number of "total" elements.
  constexpr bool IsContiguous() const {
    std::vector<size_type> contiguous_strides(strides_.size());
    std::exclusive_scan(dimensions_.rbegin(), dimensions_.rend(),
                        contiguous_strides.rbegin(), 1, std::multiplies<>{});

    return this->strides_ == contiguous_strides;
  };

  // vector instead of init_list or iter or pointer etc
  //  PRE: indicies.size() == strides_.size()
  constexpr size_type IndexOffset(
      std::vector<size_type> indicies) const noexcept {
    return ZipWithReduce<>(strides_.begin(), strides_.end(), indicies.begin(),
                           0, std::multiplies<>(), std::plus<>());
  }

  constexpr size_type FlatIndexForView(size_type flat_index) const noexcept {
    std::vector<size_type> view_strides(strides_.size());
    std::exclusive_scan(dimensions_.rbegin(), dimensions_.rend(),
                        view_strides.rbegin(), 1, std::multiplies<>{});

    std::vector<size_type> indicies(this->dimensions_.size());

    for (dimensions_type::size_type i = 0; i < this->dimensions_.size(); ++i) {
      indicies[i] = (size_type)(flat_index / view_strides[i]);
      flat_index = flat_index % view_strides[i];
    }

    return IndexOffset(indicies);
  }

#pragma endregion

// Members
#pragma region MEMBERS

  // Datamember order matters! (for member init list)!
  const std::vector<size_type> dimensions_;

  const std::vector<size_type> strides_;

  // How to use const with move operator
  //  Cant be constexpr but all constructors are :(
  const size_type flattened_dims_;  // may be too small but want it to be solid
                                    // on 32 bit machines too

  const std::shared_ptr<std::vector<T>> values_;

  T* const data_start_;

#pragma endregion
};

template <>
class NdArray<bool> {
 public:
  using size_type = int;

  constexpr NdArray<bool>(std::initializer_list<size_type> dimensions,
                         const bool& value) noexcept
      : dimensions_(dimensions),
        flattened_dims_(std::reduce(dimensions_.begin(), dimensions_.end(), 1,
                                    std::multiplies<size_type>())),
        values_(flattened_dims_, value){}

 private:
  const std::vector<size_type> dimensions_;

  //const std::vector<size_type> strides_;

  // How to use const with move operator
  //  Cant be constexpr but all constructors are :(
  const size_type flattened_dims_;  // may be too small but want it to be solid
                                    // on 32 bit machines too

  //const std::shared_ptr<std::vector<bool>> values_;
  const std::vector<bool> values_;
};



/////////////////////////////////////////////////////////////////////////////
//////////////////////// Constructors ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Private: Final constructor in delegation chain requiring validation
template <typename T>
constexpr NdArray<T>::NdArray(std::vector<size_type>&& dimensions,
                            std::vector<T>&& values)
    : dimensions_(std::move(dimensions)),
      strides_(dimensions_.size()),
      flattened_dims_(std::reduce(dimensions_.begin(), dimensions_.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(std::move(values))),
      data_start_(values_->data()) {
  std::exclusive_scan(dimensions_.rbegin(), dimensions_.rend(),
                      const_cast<std::vector<size_type>&>(strides_).rbegin(), 1,
                      std::multiplies<>{});
}

// Private:  Final constructor in delegation chain requiring no validation
//  and is therefore noexcept
template <typename T>
constexpr NdArray<T>::NdArray(std::vector<size_type>&& dimensions,
                            const T& value) noexcept
    : dimensions_(std::move(dimensions)),
      strides_(dimensions_.size()),
      flattened_dims_(std::reduce(dimensions_.begin(), dimensions_.end(), 1,
                                  std::multiplies<size_type>())),
      values_(std::make_shared<std::vector<T>>(flattened_dims_, value)),
      data_start_(values_->data()) {
  std::exclusive_scan(dimensions_.rbegin(), dimensions_.rend(),
                      const_cast<std::vector<size_type>&>(strides_).rbegin(), 1,
                      std::multiplies<>{});
}

// Final constructor for view []operator
// can assume validation has already been completed on the constructor
// from which this ndarray is a view of.
template <typename T>
constexpr NdArray<T>::NdArray(std::vector<size_type>&& dimensions,
                            const std::vector<size_type>& strides,
                            const std::shared_ptr<std::vector<T>>& values,
                            T* const data_start) noexcept
    : dimensions_(std::move(dimensions)),
      strides_(strides),
      flattened_dims_(std::reduce(dimensions_.begin(), dimensions_.end(), 1,
                                  std::multiplies<size_type>())),
      values_(values),
      data_start_(data_start) {}

// No except as other should be already validated. Check this.
template <typename T>
constexpr NdArray<T>::NdArray(const NdArray& other) noexcept
    : dimensions_(other.dimensions_),
      strides_(other.strides_),
      flattened_dims_(other.flattened_dims_),
      values_(std::make_shared<std::vector<T>>(*other.values_)),
      data_start_(values_->data()) {}

// No except as other should be already validated. Check this.
template <typename T>
constexpr NdArray<T>& NdArray<T>::operator=(const NdArray& other) noexcept {
  if (this != &other)  // i.e. not self assignment
  {
    const_cast<std::vector<size_type>&>(this->dimensions_) = other.dimensions_;
    const_cast<std::vector<size_type>&>(this->strides_) = other.strides_;
    const_cast<size_type&>(this->flattened_dims_) = other.flattened_dims_;
    const_cast<std::shared_ptr<std::vector<T>>&>(this->values_) =
        std::make_shared<std::vector<T>>(*other.values_);
    const_cast<T*&>(this->data_start_) = this->values_->data();
  }
  return *this;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//////////////////////// Operators //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//[] operator for element access
template <typename T>
T& NdArray<T>::operator[](std::initializer_list<size_type> indicies) {
  if (indicies.size() != this->dimensions_.size()) {
    throw std::invalid_argument(
        "The number of indicies must match the number of dimensions of this "
        "ndarray.");
  }
  return *(this->data_start_ + this->IndexOffset(indicies));
}

template <typename T>
const T& NdArray<T>::operator[](
    std::initializer_list<size_type> indicies) const {
  if (indicies.size() != this->dimensions_.size()) {
    throw std::invalid_argument(
        "The number of indicies must match the number of dimensions of this "
        "ndarray.");
  }
  return *(this->data_start_ + this->IndexOffset(indicies));
}

//[] operator for views / view access
template <typename T>
NdArray<T> NdArray<T>::operator[](
    std::initializer_list<slice_type> indicies) const {
  std::vector<size_type> new_dimensions{this->dimensions_};
  auto index_ptr = indicies.begin();
  for (dimensions_type::size_type i = 0; i < indicies.size(); ++i) {
    auto index = index_ptr + i;
    if (index->second > this->dimensions_[i] || index->first < 0) {
      throw std::invalid_argument(
          "A Slice range contains and invalid start or end value.");
    }

    if (index->second <= index->first) {
      // learn how to interpolate error message without sprintf etc
      throw std::invalid_argument(
          "A Slice contains a zero width or negative range.");
    }

    new_dimensions[i] = index->second - index->first;
  }

  size_type offset = ZipWithReduce<>(
      indicies.begin(), indicies.end(), strides_.begin(), 0,
      [](const NdArray<T>::slice_type& a, const size_type& b) {
        return (size_type)(a.first * b);
      },
      std::plus<>());

  // should last arg be from pointer into new values_ even thought they both
  // point to the same address?
  return NdArray(std::move(new_dimensions), this->strides_, this->values_,
                this->data_start_ + offset);
}

// Flat access [] operator
template <typename T>
const T& NdArray<T>::operator[](size_type index) const {
  // maybe constepr if ???
  if (IsContiguous()) {
    return (*(this->values_))[index];
  }

  return *(this->data_start_ + this->FlatIndexForView(index));
}

template <typename T>
template <CONSTRAINT(Comparable<T>) U>
NdArray<bool> NdArray<T>::operator<=>(const NdArray<U>& rhs) {
  // Order is arbitary as long as the dims are in the same order
  const dimensions_type* smaller_ndarray_dimensions = &(this->dimensions_);
  const dimensions_type* larger_ndarray_dimensions = &(rhs.dimensions_);

  Min(smaller_ndarray_dimensions, larger_ndarray_dimensions,
      this->dimensions_.size(), rhs.dimensions_.size());

  // Now smaller_ndarray_dimensions is the smaller of the two;

  dimensions_type::size_type smaller_dims_size =
      smaller_ndarray_dimensions->size();
  dimensions_type::size_type larger_dims_size =
      larger_ndarray_dimensions->size();

  std::vector<bool> equality_vector(larger_dims_size, false);

  for (dimensions_type::size_type i = 0; i < smaller_dims_size; ++i) {
    equality_vector[i] = (this->values_[i] <=> rhs.values_[i]);
  }
  // TODO: IMPLEMENT
  return NdArray<bool>({1}, false);
}

// Overload resolution should handle this when U is a ndarray
template <typename T>
template <CONSTRAINT(Addable<T>) U>
NdArray<T>& NdArray<T>::operator+=(const U& scalar) {
  // std::for_each is equal in release but I do a lotta debug work so......
  for (typename std::vector<T>::size_type i = 0; i < this->values_->size();
       ++i) {
    (*this->values_)[i] += scalar;
  }
  return *this;
}

template <typename T>
template <CONSTRAINT(Addable<T>) U>
NdArray<T>& NdArray<T>::operator+=(const NdArray<U>& rhs) {
  for (size_type i = 0; i < this->values_->size(); ++i) {
    (*this->values_)[i] += (*rhs.values_)[i];
  }

  return *this;
}

// GCC not happy with this: template <CONSTRAINT(Multiplyable<T>) U> for some
// reason I cant work out so im gonna try a cheaky cheat for now.
template <typename T>
template <Numeric U>
NdArray<T>& NdArray<T>::operator*=(const U& scalar) {
  // std::for_each is equal in release but I do a lotta debug work so......
  for (size_type i = 0; i < this->values_->size(); ++i) {
    (*this->values_)[i] *= scalar;
  }
  return *this;
}

template <typename T>
template <CONSTRAINT(Multiplyable<T>) U>
NdArray<T>& NdArray<T>::operator*=(const NdArray<U>& rhs) {
  const NdArray<T>* ndarray_a = this;
  const NdArray<U>* ndarray_b = &rhs;

  switch (Broadcastable(ndarray_a, ndarray_b)) {
    case NdArrayBroadcastType::kEqual:
      for (dimensions_type::size_type i = 0; i < this->values_->size(); ++i) {
        (*this->values_)[i] *= (*rhs.values_)[i];
      }
      break;
    case NdArrayBroadcastType::kBroadcast:
      return *this;
      break;
  }
  return *this;
}

template <typename T, typename U>
NdArrayBroadcastType Broadcastable(const NdArray<T>*& lhs,
                                  const NdArray<U>*& rhs) {
  const auto lhs_dim_size = lhs->Shape().size();
  const auto rhs_dim_size = rhs->Shape().size();

  if (lhs_dim_size == rhs_dim_size) {
    if (lhs->Shape() != rhs->Shape()) {
      throw std::domain_error(
          "For NdArrays with equal length dimensions the dimensions must be "
          "equal.");
    } else {
      return NdArrayBroadcastType::kEqual;
    }
  } else {
    Min(&lhs, &rhs, lhs_dim_size, rhs_dim_size);

    // lhs is now has the smaller ndarray dimensions

    const auto& smaller_ndarray_dimensions = lhs->Shape();
    const auto& larger_ndarray_dimensions = rhs->Shape();

    // by value so ...... dont need const?
    auto smaller_dims_size = smaller_ndarray_dimensions.size();

    // larger > smaller is garunteed but does auto know this?
    auto dim_size_diff = larger_ndarray_dimensions.size() - smaller_dims_size;

    // dangerous to iterate backwards as vector's sizetype is unsigned
    for (decltype(smaller_dims_size) i = 0; i < smaller_dims_size; ++i) {
      if (larger_ndarray_dimensions[i + dim_size_diff] !=
          smaller_ndarray_dimensions[i]) {
        throw std::domain_error(
            "For NdArrays with different length dimensions the dimensions of "
            "the smaller ndarray must match the final dimensions of the longer "
            "ndarray.");
      }
    }
    return NdArrayBroadcastType::kBroadcast;
  }
}

/////////////////////////////////////////////////////////////////////////////////

// Simpler than you thought (I hope) remember we print in 2d
// For now we'll ignore the brackets (in some cases) as I dont think I'm ready
// for that yet
template <typename T>
std::ostream& operator<<(std::ostream& os, const NdArray<T>& obj) {
  const auto ndims = obj.Shape().size();

  if (ndims == 1) {
    os << "[ ";
    for (typename NdArray<T>::size_type i = 0; i < obj.Size(); ++i) {
      os << " " << obj[i];
      if (i < obj.Size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    return os;
  }
  // else

  typename NdArray<T>::size_type index = 0;
  const auto column_mod = obj.Shape()[ndims - 1];
  const auto row_mod = obj.Shape()[ndims - 2] * column_mod;
  const auto block_mod = row_mod * (ndims > 2 ? obj.Shape()[ndims - 3] : 1);

  while (index < obj.Size()) {
    os << obj[index];

    if (index % column_mod < column_mod - 1) {
      os << ", ";
    }

    ++index;  // Good to increment before checks if poss (avoids +1's in mod)

    if (ndims > 2 && index % block_mod == 0) {
      os << "\n\n\n";
    } else if (index % row_mod == 0)  // will always be 0 if previous is
    {
      os << "\n\n";
    } else if (index % column_mod == 0)  // will always be 0 if previous is
    {
      os << "\n";
    }
  }

  return os;
}

/////////////////////////////////////////////////////////////////////////////

}  // namespace thoth

#endif
