#ifndef __THOTH_RANDOM_H__
#define __THOTH_RANDOM_H__

#ifdef __cplusplus

#include <concepts>
#include <random>

namespace thoth {

template <typename T, typename Dist,
          typename RNG = decltype(std::default_random_engine())>
class RandomNumberGenerator;

//Not the neatest solution but im 8 months behind and exhausted so... Fix later
template <std::integral T,
          typename RNG = decltype(std::default_random_engine())>
using UniformIntegralGenerator =
    RandomNumberGenerator<T, std::uniform_int_distribution<T>, RNG>;




template <typename T, typename Dist, typename RNG>
class RandomNumberGenerator {
 public:
  RandomNumberGenerator(
    Dist dist, std::random_device::result_type seed = std::random_device{}());
  RandomNumberGenerator(Dist dist, RNG generator);

  T operator()() { return dist_(generator_); }

 private:
  RNG generator_;
  Dist dist_;
};

// template <typename T, typename Dist, typename RNG>
// RandomNumberGenerator<T, Dist, RNG>::RandomNumberGenerator(Dist dist)
//     : RandomNumberGenerator(
//           dist,
//           std::default_random_engine{
//               std::
//                   random_device{}()})
//                   //(std::random_device::result_type)std::random_device{}())
//       {}

template <typename T, typename Dist, typename RNG>
RandomNumberGenerator<T, Dist, RNG>::RandomNumberGenerator(
    Dist dist, std::random_device::result_type seed)
    : RandomNumberGenerator(dist, std::default_random_engine{seed}) {}

template <typename T, typename Dist, typename RNG>
RandomNumberGenerator<T, Dist, RNG>::RandomNumberGenerator(Dist dist,
                                                           RNG generator)
    : generator_(generator), dist_(dist) {}

// template <typename T, typename >
// class DefaultUniformIntegralDistribution {
//  public:
//
// };

}  // namespace thoth

#endif

#endif