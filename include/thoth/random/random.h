#ifndef __THOTH_RANDOM_H__
#define __THOTH_RANDOM_H__

#ifdef __cplusplus

#include <concepts>
#include <limits>
#include <random>
#include <utility>

namespace thoth {
namespace random {

//I think this is all way way over the top but for now its where Im at!

// CRTP Class
template <template <typename, typename> typename Dist, typename ResultType,
          std::uniform_random_bit_generator URBG =
              decltype(std::default_random_engine())>
class RandomNumberGenerator {
 public:
  using seed_t = std::random_device::result_type;

  ResultType operator()() {
    return static_cast<Dist<ResultType, URBG>*>(this)->Generate(generator_);
  }

 protected:
  RandomNumberGenerator(seed_t seed = std::random_device{}());

  // Rvalue ref to avoid copy
  RandomNumberGenerator(URBG&& generator);

 private:
  URBG generator_;
};

template <template<typename, typename> typename Dist, typename ResultType,
          std::uniform_random_bit_generator URBG>
RandomNumberGenerator<Dist, ResultType, URBG>::RandomNumberGenerator(
    seed_t seed)
    : RandomNumberGenerator(std::default_random_engine{seed}) {}

template <template <typename, typename> typename Dist, typename ResultType,
          std::uniform_random_bit_generator URBG>
RandomNumberGenerator<Dist, ResultType, URBG>::RandomNumberGenerator(
    URBG&& generator)
    : generator_(std::move(generator)) {}



template <std::integral ResultType = int,
          std::uniform_random_bit_generator URBG =
              decltype(std::default_random_engine())>
class UniformIntegralRNG
    : public RandomNumberGenerator<UniformIntegralRNG, ResultType, URBG> {
 public:
  // limits specified first as more likely to be changed by user
  UniformIntegralRNG(ResultType a = 0,
                     ResultType b = std::numeric_limits<ResultType>::max(),
                     UniformIntegralRNG::seed_t seed = std::random_device{}());

  // uniform_int_distribution specified fist to "match" other constructor but
  // neither are defaultd so ... purely academic and is it bad it's not more
  // like base constructor (i.e. flip the args) (and possibly provide default
  // for uniform_it_distribution
  //
  // ^^ this is no longer a true comment but explains why we have an extra
  // constructor.

  UniformIntegralRNG(URBG&& generator, ResultType a = 0,
                     ResultType b = std::numeric_limits<ResultType>::max());

  // Rvalue ref to avoid copy
  UniformIntegralRNG(URBG&& generator,
                     std::uniform_int_distribution<ResultType>&& dist);

  ResultType Generate(URBG& generator) { return dist_(generator); }

 private:
  std::uniform_int_distribution<ResultType> dist_;
};

template <std::integral ResultType, std::uniform_random_bit_generator URBG>
UniformIntegralRNG<ResultType, URBG>::UniformIntegralRNG(
    ResultType a, ResultType b, UniformIntegralRNG::seed_t seed)
    : UniformIntegralRNG(std::default_random_engine{seed},
                         std::uniform_int_distribution<ResultType>{a, b}) {}

template <std::integral ResultType, std::uniform_random_bit_generator URBG>
UniformIntegralRNG<ResultType, URBG>::UniformIntegralRNG(URBG&& generator,
                                                         ResultType a,
                                                         ResultType b)
    : UniformIntegralRNG(std::move(generator),
                         std::uniform_int_distribution<ResultType>{a, b}) {}

template <std::integral ResultType, std::uniform_random_bit_generator URBG>
UniformIntegralRNG<ResultType, URBG>::UniformIntegralRNG(
    URBG&& generator, std::uniform_int_distribution<ResultType>&& dist)
    : RandomNumberGenerator<UniformIntegralRNG, ResultType, URBG>(std::move(generator)), dist_(dist) {}

}  // namespace random
}  // namespace thoth

#endif

#endif