#ifndef __THOTH_CONCEPTS_H__
#define __THOTH_CONCEPTS_H__

#include <concepts>

namespace thoth {
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
    std::regular_invocable<F, T, U> &&
    requires(F&& func, T&& arg1, U&& arg2) {
      {
        std::invoke(std::forward<F>(func), std::forward<T>(arg1),
                    std::forward<U>(arg2))
        } -> std::convertible_to<R>;
    };

//Is this right? doesn't input iterator already assert it returns a reference to 
//a type? maybe convertible to iterator type?
//Im trying to say that dereferencing this input iterator returns type T
//template <typename Iter, typename T>
//concept input_iterator_returning =
//    std::input_iterator<Iter> && requires(const Iter it) {
//                                   { *it } -> std::convertible_to<T>;
//                                 };

}  // namespace thoth

#endif