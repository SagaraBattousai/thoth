#ifndef __THOTH_CONCEPTS_H__
#define __THOTH_CONCEPTS_H__

#include <concepts>
#include <functional>
#include <type_traits>

namespace thoth {

// Cant use std::integral<T> according to clang14
template <typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <typename U, typename T>
concept Addable = requires(T a, U b) {
  { a + b } -> std::convertible_to<T>;
};

template <typename U, typename T>
concept Multiplyable = requires(T a, U b) {
  { a* b } -> std::convertible_to<T>;
};

template <typename U, typename T>
concept Comparable = requires(T a, U b) {
  { a <=> b } -> std::convertible_to<bool>;
};

template <typename F, typename R, typename T, typename U>
concept binary_operator =
    std::regular_invocable<F, T, U> && requires(F&& func, T&& arg1, U&& arg2) {
      {
        std::invoke(std::forward<F>(func), std::forward<T>(arg1),
                    std::forward<U>(arg2))
      } -> std::convertible_to<R>;
    };

// Is this right? doesn't input iterator already assert it returns a reference
// to a type? maybe convertible to iterator type? Im trying to say that
// dereferencing this input iterator returns type T template <typename Iter,
// typename T> concept input_iterator_returning =
//     std::input_iterator<Iter> && requires(const Iter it) {
//                                    { *it } -> std::convertible_to<T>;
//                                  };

template <typename T>
concept enum_flag =
    std::is_enum_v<T> && requires(std::underlying_type_t<T> enum_val) {
      { enum_val | enum_val } -> std::convertible_to<std::underlying_type_t<T>>;
      { enum_val& enum_val } -> std::convertible_to<std::underlying_type_t<T>>;
      static_cast<T>(enum_val);
    };

template <typename Dist, typename Generator>
// concept RandomIntegralDist = requires(Generator& g) {
concept RandomIntegralDist = requires(Dist& d, Generator& g) {
  // concept RandomIntegralDist = requires(Dist d, Generator g) {
  { d.operator()(g) } -> std::integral;
};

// TODO: Make this better (and maybe more like python generators)
// template <typename T>
// concept Generator

//Not the best name as this is a combination of generator and dist

//template <typename T, typename O>
//concept RandomNumberGenerator = requires(T& t) {
//  { t() } -> std::same_as<O>;
//};
//
//template <typename T>
//concept RandomIntegralGenerator = requires(T& t) {
//  { t() } -> std::integral;
//};     // RandomNumberGenerator<T,std::is_integral_v>

}  // namespace thoth

#endif
