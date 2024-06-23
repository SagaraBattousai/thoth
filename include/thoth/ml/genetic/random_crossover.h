#ifndef __THOTH_ML_GENETIC_RANDOM_CROSSOVER_H_
#define __THOTH_ML_GENETIC_RANDOM_CROSSOVER_H_

// #include <_thoth_config.h>

#ifdef __cplusplus
// #include <cstddef>

#include <thoth/concepts.h>
// #include <thoth/ml/genetic/gene_base.h>
#include <thoth/ml/genetic/crossover.h>

#include <random>
#include <utility>

namespace thoth {
// template <typename> typename Gene,

//
// template <
//    typename T, typename Generator = std::default_random_engine,
//    RandomIntegralDist<Generator> Dist = std::uniform_int_distribution<int>>

// Do the generator and dist get automatically infered by default values in
// constructor?

template <typename Gene, typename Generator, RandomIntegralDist<Generator> Dist,
          template <typename, typename> typename Crossover>
class RandomCrossover : public Crossover<RandomCrossover, Gene> {
 public:
  RandomCrossover();
  RandomCrossover(std::random_device::result_type seed);
  RandomCrossover(Generator generator, Dist dist);

  int GetCrossoverPoint(int start, int end) {

    //Note that mod isn't great (as it's not uniform due to issues if max isn't
    // 

  }

 private:
  Generator generator_;
  Dist dist_;
};

template <typename T, typename Generator, RandomIntegralDist<Generator> Dist>
void RandomSingleCrossover(Generator& gen,
                           Dist& dist,  // make UniversalTemplate?
                           const T& parent1, const T& parent2, T* const child1,
                           T* const child2) {}
template <typename T>
inline void RandomSingleCrossover(const T& parent1, const T& parent2,
                                  T* const child1, T* const child2) {
  std::default_random_engine gen{};
  std::uniform_int_distribution<int> dist{};
  RandomSingleCrossover(gen, dist, parent1, parent2, child1, child2);
}

// template <typename T>
// class Crossover {
//
//   //Wish I could be cleverer with the concepts for the template arguments but
//   alas.
//
//
//   //TODO: check signature
//   T Crossover(const T& otherParent) const {
//     const T& thisParent = static_cast<T&>(*this);
//
//   }
//
// };

template <typename Gene, typename Generator, RandomIntegralDist<Generator> Dist,
          template <typename, typename> typename Crossover>
RandomCrossover<Gene, Generator, Dist, Crossover>::RandomCrossover()
    : RandomCrossover(std::random_device{}()) {}

template <typename Gene, typename Generator, RandomIntegralDist<Generator> Dist,
          template <typename, typename> typename Crossover>
RandomCrossover<Gene, Generator, Dist, Crossover>::RandomCrossover(
    std::random_device::result_type seed)
    : RandomCrossover(std::default_random_engine{seed},
                      std::uniform_int_distribution<int>{}) {}

template <typename Gene, typename Generator, RandomIntegralDist<Generator> Dist,
          template <typename, typename> typename Crossover>
RandomCrossover<Gene, Generator, Dist, Crossover>::RandomCrossover(
    Generator generator, Dist dist)
    : generator_(generator), dist_(dist) {}

}  // namespace thoth
#endif  // __cplusplus
#endif
