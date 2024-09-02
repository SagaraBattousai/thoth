#ifndef __THOTH_ML_GENETIC_GENE_BASE_H__
#define __THOTH_ML_GENETIC_GENE_BASE_H__
/**@file */

#include <_thoth_config.h>

#ifdef __cplusplus
#include <concepts>
#include <functional>
#include <utility>
#endif
//#include <thoth/ml/genetic/gene.h>

#include <cstddef>

#ifdef __cplusplus
namespace thoth {
namespace ml {
namespace genetic {

/**
* \note
* Despite internal struggle I finally think CRTP is the correct choice since,
* although there are techniques to avoid this, we dont want to mix subtypes
* which is possible with dynamic polymorphism (even with advice from
* more effective c++).
*/


template <std::default_initializable T>
class GeneBase {
 public:
  // For now we'll use function class for strategy instead of a separate class
  // hierarchy: A) It's more flexible and B) We don't need a hierarchy that
  // mirrors gene (although we could)
  using CrossoverFunc = std::function<void(const void*, const void*, void*,
                                           std::size_t, std::size_t)>;
  using MutationFunc = std::function<void(void*, std::size_t, std::size_t)>;

  GeneBase() = default;

  T Mutate() const { 
    T mutated;
    static_cast<T&>(*this).DoMutate(&mutated);
    return mutated;
  }

  T Crossover(const T& other) const {
    T child;
    static_cast<T&>(*this).DoCrossover(&child);
    return child;
  }

 private:
  //// const void* const GetDNA() const { return data_; }

  //void* data_;  // Could be ref? since data_must exist elsewhere
  //std::size_t data_type_size_;
  //std::size_t data_length_;
  //CrossoverFunc crossover_func_;
  //MutationFunc mutation_func_;
};
}  // namespace genetic
}  // namespace ml
}  // namespace thoth

#endif
#endif