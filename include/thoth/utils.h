#ifndef __THOTH_UTILS_H__
#define __THOTH_UTILS_H__

#include <thoth/concepts.h>

#include <concepts>
#include <functional>
#include <iterator>

namespace thoth {

/*******************************************************************************
 * This function will compare two pointers by their respective metrics and
 *set ptr_a to be the smaller of the two and ptr_b to be the larger (or
 *equal)
 *
 * @param ptr_a A pointer to one of the two elements to be compared.
 *								this
 *will point to the smaller of the two elements when the function returns.
 *
 * @param ptr_b A pointer to the other element to be compared
 *								this
 *will point to the larger of the two elements when the function returns.
 *
 ******************************************************************************/
// inline void Min(const T *&ptr_a, const T*& ptr_b, const U& metric_a,
// const U& metric_b)
template <typename T, typename U>
inline void Min(const T** ptr_a, const T** ptr_b, const U& metric_a,
                const U& metric_b) {
  if (metric_b < metric_a) {
    const T* tmp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = tmp;
  }
}

// Pre: All itererators have the same capacity (or larger) than InputIt1
template <typename R, std::input_iterator InputIt1,
          std::input_iterator InputIt2, std::output_iterator<R> OutIt,
          binary_operator<R, std::iter_reference_t<InputIt1>,
                          std::iter_reference_t<InputIt2>>
              BinOp>
constexpr inline OutIt ZipWith(InputIt1 first1, InputIt1 last, InputIt2 first2,
                               OutIt d_first,
                               BinOp func = std::multiplies<>()) {
  while (first1 != last) {
    *d_first = (R)func(*first1, *first2);
    ++d_first;
    ++first1;
    ++first2;
  }
  return d_first;
}

// Pre: All itererators have the same capacity (or larger) than InputIt1
template <typename R, std::input_iterator InputIt1,
          std::input_iterator InputIt2,
          binary_operator<R, std::iter_reference_t<InputIt1>,
                          std::iter_reference_t<InputIt2>>
              BinOp1,
          binary_operator<R, R, R> BinOp2>
constexpr inline R ZipWithReduce(InputIt1 first1, InputIt1 last,
                                 InputIt2 first2, R init = R{},
                                 BinOp1 zwFunc = std::multiplies<>(),
                                 BinOp2 reduceFunc = std::plus<>()) {
  R ret_val = init;
  while (first1 != last) {
    ret_val = reduceFunc(ret_val, (R)zwFunc(*first1, *first2));
    ++first1;
    ++first2;
  }
  return ret_val;
}

}  // namespace thoth

#endif