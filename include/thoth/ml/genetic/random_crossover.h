#ifndef __THOTH_ML_GENETIC_RANDOM_CROSSOVER_H_
#define __THOTH_ML_GENETIC_RANDOM_CROSSOVER_H_

// #include <_thoth_config.h>

#ifdef __cplusplus
// #include <cstddef>
#include <thoth/ml/genetic/crossover.h>

#include <random>

namespace thoth {
namespace ml {
namespace genetic {

// Okay! Please note I went way way too over the top with my random code and
//  It's too complex and flexible (which we dont need, we can just write a
//  subclass per random distribution, well not quite but for now lets just get
//  this done as is

template <typename Gene, template <typename, typename> typename Crossover>
class RandomUniformCrossover : public Crossover<RandomUniformCrossover, Gene> {
 public:
  RandomUniformCrossover(
      std::random_device::result_type seed = std::random_device{}());

  int GetCrossoverPoint(int start, int end) {
    dist_.param(std::uniform_int_distribution<int>::param_type{start, end});
    return dist_(urbg_);
  }

 private:
  decltype(std::default_random_engine()) urbg_;
  std::uniform_int_distribution<int> dist_;
};

template <typename Gene, template <typename, typename> typename Crossover>
RandomUniformCrossover<Gene, Crossover>::RandomUniformCrossover(
    std::random_device::result_type seed)
    :urbg_(std::default_random_engine(seed)),
      dist_(std::uniform_int_distribution()) {}

//template <typename Gene, template <typename, typename> typename Crossover>
//int RandomUniformCrossover<Gene, Crossover>::GetCrossoverPoint(int start,
//                                                               int end) {
//  dist_.param(std::uniform_int_distribution<int>::param_type{start, end});
//  return dist_(urbg_);
//}

}  // namespace genetic
}  // namespace ml
}  // namespace thoth
#endif  // __cplusplus
#endif
