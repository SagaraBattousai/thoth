#ifndef __THOTH_ENUM_FLAG_H__
#define __THOTH_ENUM_FLAG_H__

#include <type_traits>
//#include <thoth/concepts.h>
#include "concepts.h"

namespace thoth {

  template <enum_flag Flag>
  constexpr Flag operator|(Flag lhs, Flag rhs) noexcept {
    using U = std::underlying_type_t<Flag>;
    return static_cast<Flag>(static_cast<U>(lhs) | static_cast<U>(rhs));
  }

  template <enum_flag Flag>
  constexpr Flag operator&(Flag lhs, Flag rhs) noexcept {
    using U = std::underlying_type_t<Flag>;
    return static_cast<Flag>(static_cast<U>(lhs) & static_cast<U>(rhs));
  }

  template <enum_flag Flag>
  constexpr Flag operator^(Flag lhs, Flag rhs) noexcept {
    using U = std::underlying_type_t<Flag>;
    return static_cast<Flag>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
  }

  template <enum_flag Flag>
  constexpr Flag& operator|=(Flag& lhs, Flag rhs) noexcept {
    lhs = lhs | rhs;
    return lhs;
  }

  template <enum_flag Flag>
  constexpr Flag& operator&=(Flag& lhs, Flag rhs) noexcept {
    lhs = lhs & rhs;
    return lhs;
  }

  template <enum_flag Flag>
  constexpr Flag& operator^=(Flag& lhs, Flag rhs) noexcept {
    lhs = lhs ^ rhs;
    return lhs;
  }

  // Since integral underlying I should pass vals?
  template <enum_flag Flag>
  constexpr bool IsSet(Flag lhs, Flag rhs) noexcept {
    using U = std::underlying_type_t<Flag>;
    return (static_cast<U>(lhs) & static_cast<U>(rhs)) != static_cast<U>(0);
  }

  // Since integral underlying I should pass vals?
  template <enum_flag Flag>
  constexpr bool IsUnset(Flag lhs, Flag rhs) noexcept {
    using U = std::underlying_type_t<Flag>;
    return (static_cast<U>(lhs) & static_cast<U>(rhs)) == static_cast<U>(0);
  }

  template <enum_flag Flag>
  constexpr void Set(Flag& lhs, Flag rhs) noexcept {
    lhs &= rhs;
  }

  template <enum_flag Flag>
  constexpr void Unset(Flag& lhs, Flag rhs) noexcept {
    lhs ^= rhs;
  }



}

#endif

/*
template<typename T>
requires std::is_enum_v<T> and
         requires (std::underlying_type_t<T> x) {
             { x | x } -> std::same_as<std::underlying_type_t<T>>;
             T(x);
         }
T operator|(T left, T right)
{
    using U = std::underlying_type_t<T>;
    return T( U(left) | U(right) );
}

template<typename T>
requires std::is_enum_v<T> and
         requires (std::underlying_type_t<T> x) {
             { x | x } -> std::same_as<std::underlying_type_t<T>>;
             T(x);
         }
T operator&(T left, T right)
{
    using U = std::underlying_type_t<T>;
    return T( U(left) & U(right) );
}

template<typename T>
requires std::is_enum_v<T> and requires (T x) { { x | x } -> std::same_as<T>; }
T & operator|=(T &left, T right)
{
    return left = left | right;
}

template<typename T>
requires std::is_enum_v<T> and requires (T x) { { x & x } -> std::same_as<T>; }
T & operator&=(T &left, T right)
{
    return left = left & right;
}
*/